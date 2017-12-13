//***********************************************
//	user_spi.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_spi.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"
#include "stm8s_spi.h"

/* *************************************************************************
 * SPI Configuration
 * *************************************************************************
 */

// Speed of system clock divided by 128
#define BAUD_RATE_PRESCALER 		SPI_BAUDRATEPRESCALER_128
#define CLOCK_PHASE 				SPI_CLOCKPHASE_2EDGE
// set to master/ slave
#define MODE 						SPI_MODE_MASTER
// bit format most or less siginificant bit first
// depends on the device you are communicate with
#define FIRST_BIT					SPI_FIRSTBIT_MSB
#define CLOCK_POLARITY				SPI_CLOCKPOLARITY_HIGH
#define DATA_DIRECTION 				SPI_DATADIRECTION_2LINES_FULLDUPLEX
#define SLAVE_MANAGEMENT			SPI_NSS_SOFT
#define CRC_POLYNOMIAL				7


#define SPI_DUMMY_BYTE				0x00
/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */
void user_spi_Init(void)
{
	// set to default settings
	SPI_DeInit();

	// new settings
	SPI_Init(FIRST_BIT,
              BAUD_RATE_PRESCALER,
              MODE,
			  CLOCK_POLARITY,
              CLOCK_PHASE,
              DATA_DIRECTION,
              SLAVE_MANAGEMENT,
			  CRC_POLYNOMIAL);

	// start spi
	SPI_Cmd(ENABLE);
}

U8 user_spi_Send(U8 Data)
{
 	// Wait until end of transmit
  	while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
  	SPI_SendData(Data);

  	// Wait to receive a byte
   	while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
  	return (U8)SPI_ReceiveData();
}


U8 user_spi_Receive(void)
{
	return (user_spi_Send(SPI_DUMMY_BYTE)); 	// Send a dummy byte
}

