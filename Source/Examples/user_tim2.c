//***********************************************
// 	USER_TIM2.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_tim2.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s_tim2.h"

/* *************************************************************************
 * Timer 2 Configuration
 * *************************************************************************
 */
#define PRESCALER								TIM2_PRESCALER_8			// Clock = 16 MHz / (8) =  2 MHz
#define PERIOD									1999						// Counter period = 2MHz/ (1999 + 1) = 1KHz
#define CH1_PULSE_WIDTH							1000						// PWM Duty Cycle = 1000 / (1999 + 1) * 100 = 50%
#define OUTPUT_COMPARE_MODE  					TIM2_OCMODE_PWM1
#define OUTPUT_STATE							TIM2_OUTPUTSTATE_ENABLE
#define OUTPUT_COMPARE_POLARITY 				TIM2_OCPOLARITY_LOW

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using platforms setting
// Param1:		Void
// Return:		Void
// Note:		1. SPK (PD4) send square wave (PWM) to buzzer
void user_tim2_Init(void)
{
  // TIM2 Peripheral Configuration
  TIM2_DeInit();

  // Set TIM2 Frequency to 2KHz
  TIM2_TimeBaseInit(PRESCALER, PERIOD);
  // Enables TIM2 peripheral Preload register on ARR ( Top value)
  TIM2_ARRPreloadConfig(ENABLE);

  // Channel 1 PWM configuration
  TIM2_OC1Init(OUTPUT_COMPARE_MODE, OUTPUT_STATE, CH1_PULSE_WIDTH, OUTPUT_COMPARE_POLARITY);
  TIM2_OC1PreloadConfig(ENABLE);		// CCR = Compare value

  // Enable TIM2
  TIM2_Cmd(DISABLE);
}

// Brief:		Enable/Disable peripheral
// Param1:		Enable/Disable
// Return:		Void
void user_tim2_Enable(FunctionalState NewState)
{
  TIM2_Cmd(NewState);
}

