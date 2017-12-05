//***********************************************
// 	USER_GPIO.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_gpio.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"
#include "stm8s_gpio.h"

/* *************************************************************************
 * General Purpose Input Output Configuration
 * *************************************************************************
 */

#define LED_1_PORT          	GPIOB
#define LED_1_PIN           	GPIO_PIN_0

#define LED_2_PORT      		GPIOB
#define LED_2_PIN       		GPIO_PIN_1

#define DIGITAL_INPUT_PORT		GPIOC
#define DIGITAL_INPUT_PIN		GPIO_PIN_5

#define LED_1_INIT()      		GPIO_Init(LED_1_PORT, LED_1_PIN, GPIO_MODE_OUT_PP_LOW_FAST)
#define LED_1_ON()	    		GPIO_WriteHigh(LED_1_PORT, LED_1_PIN)
#define LED_1_OFF()	    		GPIO_WriteLow(LED_1_PORT, LED_1_PIN)

#define LED_2_INIT()   	 		GPIO_Init(LED_2_PORT, LED_2_PIN, GPIO_MODE_OUT_PP_LOW_FAST)
#define LED_2_ON()	    		GPIO_WriteHigh(LED_2_PORT, LED_2_PIN)
#define LED_2_OFF()	    		GPIO_WriteLow(LED_2_PORT, LED_2_PIN)

#define DIGITAL_INPUT_READ()    GPIO_ReadInputPin(DIGITAL_INPUT_PORT, DIGITAL_INPUT_PIN)
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
