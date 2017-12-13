//***********************************************
// 	user_clk.h
//***********************************************

#ifndef _USER_CLK_H_
#define _USER_CLK_H_


/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"

/* *************************************************************************
 * TYPES
 * *************************************************************************
 */

// Brief:		Clock modules
typedef enum
{
	CLK_Module_ExternalHighSpeed,
	CLK_Module_InternalHighSpeed,
	CLK_Module_InternalLowSpeed,
	CLK_Module_ClockSwitcher
}CLK_Module;

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

void user_clk_Init(void);

#endif // _USER_CLK_H_
