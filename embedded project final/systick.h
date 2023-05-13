#ifndef __systick_H__
#define __systick_H__
#include "tm4c123gh6pm.h"
#include <stdint.h>

void SysTick_Init(void);
void SysTick_Wait(void);
void SysTick_Wait1ms(uint32_t delay);
void SysTick_Wait1us(uint32_t delay);
void SysTick_Waitu(void);

#endif 
