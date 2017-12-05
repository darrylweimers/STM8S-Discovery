//***********************************************
//	USER_I2C.h
//***********************************************

#ifndef _USER_I2C_H_
#define _USER_I2C_H_

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_globalDef.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"
#include "stm8s_i2c.h"

/* *************************************************************************
 * TYPES
 * *************************************************************************
 */

// Brief:		I2C errors
typedef enum
{
	I2C_Tx_Error_NoError,
	I2C_Tx_Error_CommunicationLineIsBusy,
	I2C_Tx_Error_StartConditionNotSent,
	I2C_Tx_Error_AddressNotSent,
	I2C_Tx_Error_DataNotSent,
	I2C_Tx_Error_LastDataNotSent
}I2C_Tx_Error;

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

// Brief:		General operations
#define I2C_CLEAR_ACKNOWLEDGE_FAILURE()		I2C->SR2 &= ~I2C_SR2_AF
#define I2C_CLEAR_STATUS_REGISTER_2()		I2C->SR2 = 0
#define I2C_ACKNOWLEDGE_ENABLE()			I2C->CR2 |= I2C_CR2_ACK
#define I2C_Get_ERROR()						I2C->SR2
#define I2C_ENABLE_ALL_INTERRUPTS() 		I2C->ITR = 0x07

// Brief:		7-bit device address shift to left to indicate write operation (value 0 at bit position 0)
#define I2C_ADD_WRITE_BIT_TO(ADDRESS) 		(U8)(ADDRESS << 1)

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

U8 I2C_Read(void);
void I2C_Send(U8 Data);
FlagStatus I2C_GetStatus(I2C_Flag_TypeDef I2C_Flag);
void I2C_GenerateStart(FunctionalState NewState);
void I2C_GenerateStop(FunctionalState NewState);
void I2C_DefaultConfig(void);
void I2C_Enable(FunctionalState NewState);
void I2C_InitConfig(void);
void I2C_InterruptConfig(I2C_IT_TypeDef Config, FunctionalState NewState);
void I2C_SlaveReceiverInterruptHanlder(void);
bool I2C_ReadFrame(U8 Data[], U16* SizeOfData);
I2C_Tx_Error I2C_SendFrame(U8 Address, U8 Data[], U16 SizeOfData, Func_Ptr_GetBool Timeout);

#endif /* _USER_I2C_H_ */
