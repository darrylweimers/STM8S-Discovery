//***********************************************
//	user_tim4_example1.c
//***********************************************


/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_tim4.h"
#include "user_tim4_example1.h"
#include "user_clk.h"

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

//Period = 100 * 1 us  = 200 us
#define MATCH_VALUE		100

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_tim4_example1_setup(void)
{
	user_clk_Init();
	user_tim4_Init();
}

// Delay for 100 us
void user_tim4_example1_a_main(void)
{
	USER_TIM4_RESET_COUNTER();
	user_tim4_Enable(ENABLE);

	// Delay for 100 us
	while(TIM4->CNTR < MATCH_VALUE);	// wait until period 1000us

	user_tim4_Enable(DISABLE);
}