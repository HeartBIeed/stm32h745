#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"

void SysTick_init();
void SysTick_Handler();
void _delay_ms(uint32_t ms);
void _delay_us(uint32_t us);

extern volatile uint32_t ms_ticks;



#endif /* TIMER_H_ */
