//***********************************************
//	user_tim1_example1.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_tim1_example1.h"
#include "user_tim1.h"
#include "user_clk.h"

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

//Period = 16000 * 0.0625 us  = 1000 us
#define MATCH_VALUE		16000

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_tim1_example1_setup(void)
{
	user_clk_Init();
	user_tim1_Init();
}

// Delay for 1000 us
void user_tim1_example1_a_main(void)
{
	USER_TIM1_RESET_COUNTER();
	USER_TIM1_ENABLE();

	// Delay for 1000 us
	while(TIM1_GetCounter() < MATCH_VALUE);	// wait until period 1000us

	USER_TIM1_DISABLE();
}