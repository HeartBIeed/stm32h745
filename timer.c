#include "timer.h"

volatile uint32_t ms_ticks = 0;

void SysTick_init(){

    SystemCoreClockUpdate();

    SysTick->LOAD =(SystemCoreClock/1000) - 1; // 1 ms
    SysTick->VAL = 0; //clear
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk| //source AHB
    SysTick_CTRL_TICKINT_Msk | //interrupt
    SysTick_CTRL_ENABLE_Msk; 
}

void SysTick_Handler(){

        ms_ticks++;
}

void _delay_ms(uint32_t ms){

    uint32_t start = ms_ticks;
    while (( ms_ticks - start) < ms);

}

void _delay_us(uint32_t us){

    us *= 1; 
    while(us--) __NOP();
}