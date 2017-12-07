//***********************************************
// user_tim4.h
//***********************************************

#ifndef _USER_TIM4_H_
#define _USER_TIM4_H_

/* *************************************************************************
 * STM8S Driver Includes
 * *************************************************************************
 */
#include "stm8s.h"

/* *************************************************************************
 * DEFINES
 * *************************************************************************
 */

// Brief:		General operations
#define USER_TIM4_CLEAR_STATUS_REGISTER_1()	TIM4->SR1 = 0
#define USER_TIM4_GET_COUNTER_VALUE() 		TIM4->CNTR
#define USER_TIM4_RESET_COUNTER() 			TIM4->CNTR = 0
#define USER_TIM4_ENABLE()					TIM4->CR1 |= TIM4_CR1_CEN
#define USER_TIM4_DISABLE()					TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);

/* *************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 * *************************************************************************
 */

void user_tim4_Init(void);
void user_tim4_Enable(FunctionalState State);
void user_tim4_ClearInterruptUpdateStatus(void);

#endif // _USER_TIM4_H_
