//***********************************************
//	user_wwdg.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_wwdg.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */
#include "stm8s_wwdg.h"

/* *************************************************************************
 * Window Watchdog Configuration
 * *************************************************************************
 */
// Total number of counts to bottom: 63
// Top value (absolute):   			 127
// Bottom value (absolute): 		 64
// Step: 							 12288 / Main Clock = 12288 / 16 MHz = 0.000768

// Watchdog window:					49.152 ms = (WWD_COUNTER_INIT - 63) * step
// not allow refresh window:        0 ms =      (WWD_COUNTER_INIT - WWD_WINDOW_VALUE) * step
// refresh possible from 0 ms to 49.152 ms

#define COUNTER_INIT 								127						// Starting count value which decrements
#define WINDOW_VALUE 								127						// Refresh not allow from "WWD_COUNTER_INIT" to "WWD_WINDOW_VALUE"

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Reset micro-controller
// Param1:		Void
// Return:		Void
void user_wwdg_CpuReset(void)
{
	WWDG_SWReset();
}

// Brief:		Initialiaze using platform setting
// Param1:		Void
// Return:		Void
// Note: 		1. Window watchdog timer will be enabled
void user_wwdg_Init(void)
{
	WWDG_Init(COUNTER_INIT, WINDOW_VALUE);
}

// Brief:		Refresh watchdog timer to prevent cpu reset
// Param1:		Void
// Return:		Void
void user_wwdg_Reset(void)
{
	// Reset only during allow reset window
	while((WWDG_GetCounter() & 0x7F) > WINDOW_VALUE);
	WWDG_SetCounter(COUNTER_INIT);
}
