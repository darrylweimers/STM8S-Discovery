//***********************************************
// 	USER_GPIO.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_gpio.h"

/* *************************************************************************
 * General Purpose Input Output Configuration
 * *************************************************************************
 */
#define LED_1_INIT()      		GPIO_Init(LED_1_PORT, LED_1_PIN, GPIO_MODE_OUT_PP_LOW_FAST)

#define LED_2_INIT()   	 		GPIO_Init(LED_2_PORT, LED_2_PIN, GPIO_MODE_OUT_PP_LOW_FAST)

#define DIGITAL_INPUT_INIT()	GPIO_Init(DIGITAL_INPUT_PORT, DIGITAL_INPUT_PIN, GPIO_MODE_IN_FL_NO_IT)

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */
void user_gpio_Init(void)
{
	DIGITAL_INPUT_INIT();
	LED_1_INIT();
	LED_2_INIT();
	LED_1_OFF();
	LED_2_OFF();
}
