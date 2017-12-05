//***********************************************
// 	USER_CLK.h
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

void CLK_Init(void);
void CLK_Enable(CLK_Module Module, FunctionalState NewState);
void CLK_PeripheralEnable(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState);


#endif // _USER_CLK_H_