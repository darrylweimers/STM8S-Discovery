//***********************************************
// 	USER_TIM4.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_tim4.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */
#include "stm8s_tim4.h"

/* *************************************************************************
 * Timer 4 Configuration
 * *************************************************************************
 */

#define PRESCALER 									TIM4_PRESCALER_16			// Clock = 16 MHz / (16) =  1 MHz
#define PERIOD										255							// Counter period =  255 * 1 us  = 255 us

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using platforms setting
// Param1:		Void
// Return:		Void
void user_tim4_Init(void)
{
    TIM4_DeInit();
    TIM4_TimeBaseInit(PRESCALER, PERIOD);
    TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
	TIM4_Cmd(DISABLE);
}

// Brief:		Enable/Disable peripheral
// Param1:		Enable/Disable
// Return:		Void
void user_tim4_Enable(FunctionalState State)
{
	TIM4_Cmd(State);
}

// Brief:		Clear interrupt update status
// Param1:		Void
// Return:		Void
void user_tim4_ClearInterruptUpdateStatus(void)
{
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}

