//***********************************************
//	user_tim2_example1.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_tim2.h"
#include "user_tim2_example1.h"

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_tim2_example1_setup(void)
{
	user_tim2_Init();
}

// Generates a 1Khz square wave at pin 29 (PD4)
void user_tim2_example1_a_main(void)
{
	user_tim2_Enable(ENABLE);
}