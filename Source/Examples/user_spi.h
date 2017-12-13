//***********************************************
//	user_spi.h
//***********************************************

#ifndef _USER_SPI_H_
#define _USER_SPI_H_

#include "user_globalDef.h"

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */
void user_spi_Init(void);
U8 user_spi_Receive(void);
U8 user_spi_Send(U8 Data);

#endif /* _USER_SPI_H_ */
