//***********************************************
// 	user_tim1.h
//***********************************************

#ifndef _USER_TIM1_H_
#define _USER_TIM1_H_

/* *************************************************************************
 * General operations
 * *************************************************************************
 */

#define USER_TIM1_RESET_COUNTER()		TIM1->CNTRH = 0;TIM1->CNTRL = 0
#define USER_TIM1_ENABLE()				TIM1->CR1 |= TIM1_CR1_CEN
#define USER_TIM1_DISABLE()				TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN)
#define USER_TIM1_GET_COUNTER_VALUE()	(uint16_t)(((uint16_t)TIM1->CNTRH << 8) | (uint16_t)(TIM1->CNTRL))

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

void user_tim1_Init(void);

#endif // _USER_TIM1_H_
