//***********************************************
//	user_wwdg_example1.c
//***********************************************

#include "user_wwdg_example1.h"
#include "user_clk.h"
#include "user_wwdg.h"

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

// TODO: Uncomment to stop watch dog from reset
//#define WINDOW_WATCHDOG_RESET

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

void user_wwdg_example1_Init(void)
{
	user_clk_Init();
	user_wwdg_Init();

	/* Check if the system has resumed from IWDG reset */
	if (RST->SR & RST_SR_WWDGF != RESET)
	{

		/* Clear IWDGF Flag */
		RST->SR = RST->SR & ~(RST_SR_WWDGF);
	}

	enableInterrupts();

}

void user_wwdg_example1_a_main(void)
{
	#ifdef WINDOW_WATCHDOG_RESET
	user_wwdg_Reset();
	#endif
}


