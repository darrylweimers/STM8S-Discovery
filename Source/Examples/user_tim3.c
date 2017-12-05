//***********************************************
// 	USER_TIM3.c
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

#define MODULE_ID_DELAY_MILLISECONDS				0
#define MODULE_TIMEOUT_DELAY_MILLISECONDS			1
#define MODULE_TIMER_TYPE_DELAY_MILLISECONDS		SoftwareTimer_Type_Timeout

#define MODULE_ID_LED_PATTERN						1
#define MODULE_PERIOD_LED_PATTERN 	    			500
#define MODULE_TIMER_TYPE_LED_PATTERN				SoftwareTimer_Type_Periodic

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialiaze using platforms setting
// Param1:		Void
// Return:		Void
void user_tim3_Init(void)
{
    TIM3_DeInit();
    TIM3_TimeBaseInit(PRESCALER, PERIOD);
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);
    TIM3_Cmd(DISABLE);
}

// Brief:		Enable/Disable peripheral
// Param1:		Enable/Disable
// Return:		Void
void user_tim3_Enable(FunctionalState State)
{
	 TIM3_Cmd(State);
}

// Brief:		Clear interrupt update status
// Param1:		Void
// Return:		Void
void user_tim3_ClearInterruptUpdateStatus(void)
{
	TIM3_ClearITPendingBit(TIM3_IT_UPDATE);
}
