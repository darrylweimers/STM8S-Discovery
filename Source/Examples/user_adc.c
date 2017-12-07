//***********************************************
//	user_adc.c
//***********************************************

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */
#include "user_adc.h"

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */

#include "stm8s.h"
#include "stm8s_adc1.h"

/* *************************************************************************
 * ADC Configuration
 * *************************************************************************
 */

#define ADC_12_PORT					GPIOF
#define ADC_12_PIN					GPIO_PIN_4
#define CHANNEL						ADC1_CHANNEL_12
#define MODE 						ADC1_CONVERSIONMODE_SINGLE

/* *************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 * *************************************************************************
 */

// Brief:		Initialize using configuration setting
// Param1:		Void
// Return:		Void
// Note:		Max conversion resolution: 0x3FF
void user_adc_Init(void)
{
	//  Initialize pin
	GPIO_Init(ADC_12_PORT, ADC_12_PIN, GPIO_MODE_IN_FL_NO_IT);

	// De-Init ADC peripheral
	ADC1_DeInit();

	// Init ADC1 peripheral
	ADC1_Init(MODE, CHANNEL, ADC1_PRESSEL_FCPU_D2, \
			ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL12,\
			DISABLE);

	ADC1_StartConversion();
}

U16 user_adc_GetResult(void)
{
  	ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_12, ADC1_ALIGN_RIGHT);

	ADC1_Cmd(ENABLE);

  	// trigger adc reading
  	ADC1_StartConversion();

	// wait until end of convertion
	while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == RESET);

	// Get converted value */
   	return ADC1_GetConversionValue();
}