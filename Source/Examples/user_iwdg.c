//***********************************************
//	USER_IWDG.c
//***********************************************

// Brief:		Indenpendent watchdog
// IMPORTTANT: 	To use independent watch dog you must
//				1. 	Set LSI_EN of "Option Bytes" to enabled (clock source for indenpendent watchdog)
// 				2. 	Enable internal low speed clock with CLK driver

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_iwdg.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */
#include "stm8s_iwdg.h"

/* *************************************************************************
 * Independent Watch Dog Configuration
 * *************************************************************************
 */

#define PRESCALER			IWDG_Prescaler_256			// 1 s
#define PERIOD				0xff

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Configure using platforms setting
// Param1:		Void
// Return:		Void
void user_iwdg_Init(void)
{
	IWDG_Enable();										// Start watchdog (otherwise you can t change prescaler and reload register values)
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		// Allow watchdog prescaler and reload register to be programmed
	IWDG_SetPrescaler(PRESCALER);						// Set watchdog prescaler
	IWDG_SetReload(PERIOD);								// Set watchdog reload value
	IWDG_ReloadCounter();								// Reset watchdog counter
}

// Brief:		Reload watch dog counter
// Param1:		Void
// Return:		Void
void user_iwdg_Reload(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_ReloadCounter();
}

