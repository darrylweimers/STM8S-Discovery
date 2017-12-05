//***********************************************
//	USER_ADC.h
//***********************************************

#ifndef _USER_ADC_H_
#define _USER_ADC_H_

/* *************************************************************************
 * User Includes
 * *************************************************************************
 */

#include "user_globalDef.h"

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

void user_adc_Init(void);
U16 user_adc_GetResult(void);

#endif /* _ADC_H_ */