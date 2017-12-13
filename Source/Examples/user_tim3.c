//***********************************************
// 	user_tim3.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_tim3.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s_tim3.h"

/* *************************************************************************
 * Timer 3 Configuration
 * *************************************************************************
 */

#define PRESCALER 									TIM3_PRESCALER_1			// Clock = 16 MHz / (1 + 0) =  16 MHz
#define PERIOD										16000						// Counter period =  16000 * 0.0625 us  = 1 ms
#define SWITCH_ON									ENABLE
/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using configuration setting
// Param1:		Void
// Return:		Void
void user_tim3_Init(void)
{
    TIM3_DeInit();
    TIM3_TimeBaseInit(PRESCALER, PERIOD);
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);
    TIM3_Cmd(SWITCH_ON);
}

// Brief:		Enable/Disable peripheral
// Param1:		Enable/Disable
// Return:		Void
void user_tim3_Enable(FunctionalState State)
{
	 TIM3_Cmd(State);
}

void user_tim3_InterruptHandler(void)
{
	 // Do Something at every 1 ms

	TIM3_ClearITPendingBit(TIM3_IT_UPDATE);
}

