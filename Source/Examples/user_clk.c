//***********************************************
// 	USER_CLK.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_clk.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"
#include "stm8s_clk.h"

/* *************************************************************************
 * Clock Configuration
 * *************************************************************************
 */

// Prescaler
#define PRESCALER_INTERNAL_HIGH_SPEED				CLK_PRESCALER_HSIDIV1		// Internal High Speed clock divider number 1
#define PRESCALER_CPU								CLK_PRESCALER_CPUDIV1		// Internal High Speed clock divider number 2 e.g. source for clock cpu may be one of the selected options [internal low speed clock, internal high speed clock, external high speed clock]

// Module
#define MODULE_EXTERNAL_HIGH_SPEED_STATE			DISABLE						// External clock disable
#define MODULE_INTERNAL_HIGH_SPEED_STATE			ENABLE						// Clock source for CPU (16 MHz)
#define MODULE_INTERNAL_LOW_SPEED_STATE				ENABLE						// Clock source for independent watchdog //TODO: Disable
#define MODULE_SWITCHER_STATE						ENABLE						// No desire to switch between [internal low speed clock, internal high speed clock, external high speed clock]

// Perihperal
#define PERIPHERAL_SPI_STATE						DISABLE
#define PERIPHERAL_I2C_STATE						ENABLE
#define PERIPHERAL_ADC_STATE						ENABLE
#define PERIPHERAL_AWU_STATE						DISABLE
#define PERIPHERAL_UART1_STATE						DISABLE
#define PERIPHERAL_TIMER1_STATE						ENABLE
#define PERIPHERAL_TIMER2_STATE						ENABLE
#define PERIPHERAL_TIMER3_STATE						ENABLE
#define PERIPHERAL_TIMER4_STATE						ENABLE


/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using platforms setting
// Param1:		Void
// Return:		Void
// Note:		1. Clock Speed @ 16 MHz (for micro-controller)
// 				2. Internal low speed clock disabled (for watch dog)
// 				3. Internal high speed clock enabled (for micro-controller)
// 				4. Peripheral clock enabled: I2C, Timer1-4
void user_clk_Init(void)
{
    CLK_DeInit();

	// Module clock setting
	CLK_ClockSwitchCmd(MODULE_SWITCHER_STATE);
	CLK_HSECmd(MODULE_EXTERNAL_HIGH_SPEED_STATE);
	CLK_LSICmd(MODULE_INTERNAL_LOW_SPEED_STATE);
    CLK_HSICmd(MODULE_INTERNAL_HIGH_SPEED_STATE);

	// Precaler
	CLK_HSIPrescalerConfig(PRESCALER_INTERNAL_HIGH_SPEED);
	CLK_SYSCLKConfig(PRESCALER_CPU);

	// Perihpheral clock setting
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, PERIPHERAL_SPI_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, PERIPHERAL_I2C_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, PERIPHERAL_ADC_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, PERIPHERAL_AWU_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, PERIPHERAL_UART1_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, PERIPHERAL_TIMER1_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, PERIPHERAL_TIMER2_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, PERIPHERAL_TIMER3_STATE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, PERIPHERAL_TIMER4_STATE);
}
