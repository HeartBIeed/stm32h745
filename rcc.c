#include "rcc.h"

void SystemClock_HSI_8MHz(){

	RCC->CR |=RCC_CR_HSION; // enable HSI
	while(!(RCC->CR & RCC_CR_HSIRDY)); // wait stable HSI

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |=RCC_CFGR_SW_HSI; // HSI source SYSCLK
	//SW 0b00 HSI, 0b01-HSE, 0b10-PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); //SWS status CFGR ->HSI EN
}


void SystemClock_HSE_8MHz(){

	RCC->CR |=RCC_CR_HSEON; // enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY)); // wait stable HSE

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |=RCC_CFGR_SW_HSE; // HSE source SYSCLK
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); //SWS status CFGR ->HSE EN
}


void PLL_72MHz_enable(){
	//Flash access control register (FLASH_ACR)
    FLASH->ACR &= ~FLASH_ACR_LATENCY;     // Сбрасываем биты
    FLASH->ACR |= (7<<0);    //  7 wait states
    
	RCC->CR |=RCC_CR_HSEON; // enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY)); // wait stable HSE

	RCC->CR &= ~RCC_CR_PLLON;// PLL disable  
	while(RCC->CR & RCC_CR_PLLRDY); // wait PLL is unlocked

	RCC->CFGR &= ~(0xFF<<18); 
	RCC->CFGR |= (7<<18); // *9

	RCC->CFGR &= ~(3<<15); 
	RCC->CFGR |= (2<<15); // HSE

	RCC->CFGR &= ~(7<<8); 
	RCC->CFGR |= (0b100<<8); // APB1 /2 = 36

	RCC->CR |= RCC_CR_PLLON;// PLL enable  
	while(!(RCC->CR & RCC_CR_PLLRDY)); // wait PLL is set
	
	RCC->CFGR &= ~RCC_CFGR_SW; //PLL as system clock
	RCC->CFGR |= RCC_CFGR_SW_PLL1; //PLL as system clock
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1) //wait switched SC to PLL

	SystemCoreClockUpdate();

}
