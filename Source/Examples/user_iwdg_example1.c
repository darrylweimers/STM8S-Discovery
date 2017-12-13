//***********************************************
//	user_iwdg_example1.c
//***********************************************

#include "user_iwdg_example1.h"
#include "user_iwdg.h"
#include "stm8s.h"
#include "user_clk.h"

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

// Prescaler set to 256
// reload value set to 0xFF
// watch dog window is ~1 second

// TODO: Uncomment to activate watch dog reset
#define WATCHDOG_RESET


/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_iwdg_example1_Init(void)
{
	user_clk_Init();

	// Check if the system has resumed from independent watchdog reset
	if (RST->SR & RST_SR_IWDGF != RESET)
	{
		// Set a pin to output high

		// Clear Independent Watchdog Flag
		RST->SR = RST->SR & ~(RST_SR_IWDGF);
	}
	else
	{
		// Set a pin to output low
	}

	user_iwdg_Init();
	enableInterrupts();
}

// Watch dog reset in main loop
void user_iwdg_example1_a_main(void)
{
	#ifdef WATCHDOG_RESET
	user_iwdg_Reload();		// Prevent watch dog reset
	#endif
}

// Time constraint watchdog reset
void user_iwdg_example1_b_main(void)
{
	user_iwdg_Reload();

	// Delay for 900 ms		// no reset

	#ifdef WATCHDOG_RESET
	// Delay for 100 ms		// Watch Dog Rest will kick in
	#endif
}
