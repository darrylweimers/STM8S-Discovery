//***********************************************
//	user_i2c.c
//***********************************************

// IMPORTANT: Set option byte (bit AFR6 to alternate function) to enable I2C pins

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_i2c.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s_i2c.h"

/* *************************************************************************
 * I2C Configuration
 * *************************************************************************
 */

#define I2C_OWN_ADDRESS									0x24
#define I2C_SPEED										100000
#define I2C_SLAVE_INTERRUPT_CONFIG						(I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT)
#define I2C_MASTER_INTERRUPT_CONFIG						I2C_IT_ERR
#define I2C_SLAVE_RX_BUFFER_SIZE						30

// Brief:		Receiver flag status
#define I2C_IN_RECEIVER_MODE() 				(I2C_GetFlagStatus(I2C_FLAG_TRANSMITTERRECEIVER) == RESET)
#define I2C_IN_COMMUNICATION() 				(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY) == SET)
#define I2C_RECEIVER_ADDRESS_DETECTED() 	(I2C_GetFlagStatus(I2C_FLAG_ADDRESSSENTMATCHED) == SET)
#define I2C_RECEIVER_STOP_DETECTED() 		(I2C_GetFlagStatus(I2C_FLAG_STOPDETECTION) == SET)
#define I2C_RECEIVER_ACKNOWLEDGE_FAILURE() 	(I2C_GetFlagStatus(I2C_FLAG_ACKNOWLEDGEFAILURE) == SET)
#define I2C_RECEIVER_BYTE_RECEIVED() 		(I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == SET)

// Brief:		Transmitter flag status
#define I2C_TRANSCEIVER_ADDRESS_SENT() 		(I2C_GetFlagStatus(I2C_FLAG_ADDRESSSENTMATCHED) == SET)
#define I2C_TRANSCEIVER_START_SENT()		(I2C_GetFlagStatus(I2C_FLAG_STARTDETECTION) == SET)
#define I2C_TRANSCEIVER_DATA_SENT()			(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET)
#define I2C_TRANSCEIVER_DATA_TRANSFERRED()	(I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == SET)

/* *************************************************************************
 * PRIVATE VARIABLES
 * *************************************************************************
 */

// Brief:		Receiver variables: data size, data bytes (array), status
static volatile U16 sizeOfSlaveBufferRx = 0;
static volatile U8 slaveBufferRx[I2C_SLAVE_RX_BUFFER_SIZE] = {0};
static volatile bool newFrameReceived = FALSE;

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */


// Brief:		Enable/Disable peripheral
// Param1: 		Enable/disable
// Return:		Void
void user_i2c_Enable(FunctionalState NewState)
{
	I2C_Cmd(NewState);
}

// Brief:		Initialize using platforms setting
// Param1:		Void
// Return:		Void
// Note:		1. Set option byte (bit AFR6 to alternate function) to enable I2C pins
void user_i2c_Init(void)
{
	// GPIO input mode, external interrupt disable, input with pull up
	GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);

	// I2C setup
	I2C_DeInit();
	I2C_Init(I2C_SPEED, I2C_OWN_ADDRESS << 1, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, (CLK_GetClockFreq() / 1000000));
}

// Brief:		Enable/Disable interrupt
// Param1: 		Error/event/buffer
// Param2: 		Enable/disable
void user_i2c_InterruptConfig(I2C_IT_TypeDef Config, FunctionalState NewState)
{
	I2C_ITConfig(Config, NewState);
}

// Brief:		In master mode, transmit data bytes to a given address
// Param1:		Slave address (7 bits which should occupy bit position 7-1; bit 0 is a read/write bit indicator)
// Param2:		Address of data bytes
// Param3:		Size of data bytes
// Param4:		Null/timeout function
// Return:		Transmit error (no error, communication line is busy, start condition not send, address not send, data byte not send, or last data byte not send)
// Note:		1. Slave address bit 0 read/write bit indicator will be updated by this function
//				2. timeout to terminate infinite waiting for a state
I2C_Tx_Error user_i2c_SendFrame(U8 Address, U8 Data[], U16 SizeOfData, Func_Ptr_GetBool Timeout)
{
	U16 index = 0;

	// Wait until line free up
	while(I2C_IN_COMMUNICATION())
	{
		if (Timeout != 0 && (*Timeout)() == TRUE)
		{
			return I2C_Tx_Error_CommunicationLineIsBusy;
		}
	}

	// Start condition
	// Clear by writting data register with address
	I2C_GenerateSTART(ENABLE);
	while(!I2C_TRANSCEIVER_START_SENT())
	{
		if (Timeout != 0 && (*Timeout)() == TRUE)
		{
			return I2C_Tx_Error_StartConditionNotSent;
		}
	}

	// Send address byte
	I2C_Send7bitAddress(Address, I2C_DIRECTION_TX);
	while(!I2C_TRANSCEIVER_ADDRESS_SENT()  || !I2C_TRANSCEIVER_DATA_SENT())
	{
		if (Timeout != 0 && (*Timeout)() == TRUE)
		{
			return I2C_Tx_Error_AddressNotSent;
		}
	}

	// Read SR3 to clear address flag
	I2C_GetFlagStatus(I2C_FLAG_BUSBUSY);

	// Send data bytes
	for (index = 0; index < SizeOfData; index++)
	{
		// byte transfer
		I2C_SendData(Data[index]);

		while(!I2C_TRANSCEIVER_DATA_SENT())
		{
			if (Timeout != 0 && (*Timeout)() == TRUE)
			{
				return I2C_Tx_Error_DataNotSent;		// break here and program is never restored
			}
		}

		if(index == SizeOfData - 1)
		{
			while(!I2C_TRANSCEIVER_DATA_TRANSFERRED())
			{
				if (Timeout != 0 && (*Timeout)() == TRUE)
				{
					return I2C_Tx_Error_LastDataNotSent;
				}
			}
			I2C_GenerateSTOP(ENABLE);
		}

	}

	return I2C_Tx_Error_NoError;
}

// Brief:		Read frame
// Param1:		Data bytes array which will be updated if return value is true
// Param2:		Size of data which will be updated if return value is true
// Return:		True/False (True, if frame is available)
// Note:		Call slave receiver interrupt under I2C ISR
bool user_i2c_ReadFrame(U8 Data[], U16* SizeOfData)
{
	U16 index = 0;

	if (newFrameReceived == TRUE)
	{
		for (index = 0; index < sizeOfSlaveBufferRx; index++)
		{
			Data[index] = slaveBufferRx[index];
		}
		*SizeOfData = sizeOfSlaveBufferRx;
		newFrameReceived = FALSE;

		return TRUE;

	}

	return FALSE;
}

// Brief:		Slave interrupt handler
// Param1:		Void
// Return:		Void
void user_i2c_SlaveReceiverInterruptHanlder(void)
{
	// Receiver mode
	if (I2C_IN_RECEIVER_MODE())
	{
		if (I2C_IN_COMMUNICATION())
		{

			if (I2C_RECEIVER_ADDRESS_DETECTED())
			{
				sizeOfSlaveBufferRx = 0;
				newFrameReceived = FALSE;
			}

			if (I2C_RECEIVER_BYTE_RECEIVED())
			{
				slaveBufferRx[sizeOfSlaveBufferRx++] = I2C_ReceiveData();		// Clear byte received flag by reading data register
			}

		}

		if (I2C_RECEIVER_BYTE_RECEIVED())
		{
			slaveBufferRx[sizeOfSlaveBufferRx++] = I2C_ReceiveData();		// Clear byte received flag by reading data register
		}

		if (I2C_RECEIVER_STOP_DETECTED())
		{
			newFrameReceived = TRUE;
			I2C->CR2 |= I2C_CR2_ACK;			// Write CR2 to clear Stop detected flag
		}

	}
}

