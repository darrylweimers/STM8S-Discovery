//***********************************************
//	user_tim3_example1.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_tim3.h"
#include "user_tim3_example1.h"
#include "user_clk.h"

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_tim3_example1_setup(void)
{
	user_clk_Init();
	user_tim3_Init();
	enableInterrupts();
}

void user_tim3_example1_a_main(void)
{
	// Left black intetionally
}
