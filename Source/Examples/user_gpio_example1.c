//***********************************************
// 	USER_GPIO_EXAMPLE_1.c
//***********************************************


/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_gpio.h"
#include "user_gpio_example1.h"

/* ******************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * ******************************************************************/

void user_gpio_example1_setup(void)
{
	user_gpio_Init();
}

// Whenever button is pressed, turn on led
void user_gpio_example1_a_main(void)
{
	  while (DIGITAL_INPUT_READ() == RESET)
	  {
		  LED_1_ON();
		  LED_2_ON();
	  }

 	  LED_1_OFF();
 	  LED_2_OFF();
}
