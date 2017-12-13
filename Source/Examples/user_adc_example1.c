//***********************************************
//	user_adc_example1.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_adc.h"
#include "user_adc_example1.h"
#include "user_clk.h"

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */
void user_adc_example1_setup(void)
{
	user_clk_Init();
	user_adc_Init();
}

void user_adc_example1_a_main(void)
{
	static U16 analogResult;

	analogResult = user_adc_GetResult();
}