//***********************************************
// 	USER_TIM3.h
//***********************************************

#ifndef _USER_TIM3_H_
#define _USER_TIM3_H_

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

void user_tim3_Init(void);
void user_tim3_Enable(FunctionalState State);
void user_tim3_ClearInterruptUpdateStatus(void);

#endif // _USER_TIM3_H_
