//***********************************************
// 	user_tim1.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_tim1.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */
#include "stm8s.h"
#include "stm8s_tim1.h"

/* *************************************************************************
 * Timer 1 Configuration
 * *************************************************************************
 */

#define PRESCALER 		0							// Timer 1 Clock = 16 MHz / (1 + prescaler) = 16 MHz / (1 + 0) =  16 MHz
#define PERIOD			0xffff						// Counter period =  65535 * 0.0625 us  = 4095.93 us
#define MODE			TIM1_COUNTERMODE_UP			// Set counter to count up mode (0... 65535)

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using configuration setting
// Param1:		Void
// Return:		Void
void user_tim1_Init(void)
{
    TIM1_DeInit();
    TIM1_TimeBaseInit(PRESCALER, MODE, PERIOD, TIM1_RCR_RESET_VALUE);
    TIM1_ITConfig(TIM1_IT_UPDATE, DISABLE);
    TIM1_Cmd(DISABLE);
}
