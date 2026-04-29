#include "rcc.h"

void SystemClock_HSE_8MHz(){

	RCC->CR |=RCC_CR_HSEON; // enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY)); // wait stable HSE
	
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |=RCC_CFGR_SW_HSE; // HSE source SYSCLK
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); //SWS status CFGR ->HSE EN

}

void PLL_400MHz_enable(){ //400 MHz from HSE 8 MHz

	RCC->CR |=RCC_CR_HSEON; // enable HSE
	while(!(RCC->CR & RCC_CR_HSERDY)); // wait stable HSE
 	RCC->CR &= ~RCC_CR_PLLON; // PLL disable                  

	FLASH->ACR = 7; 

	RCC->PLLCKSELR = RCC_PLLCKSELR_PLLSRC_HSE|(4<<4); // M
	RCC->PLL1DIVR  = (0x18F<<0)|//N
                      (1<<9)|  //P
                      (1<<16)| //Q
                      (1<<24); //R

 	RCC->PLLCFGR |= RCC_PLLCFGR_PLL1RGE_3;
// Указание диапазона входной частоты PLL1

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL1VCOSEL;
// Указание диапазона выходной частоты PLL1

	RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVQ1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVR1EN;

	RCC->CR |= RCC_CR_PLLON; // PLL enable                  
	while(!(RCC->CR & RCC_CR_PLL1RDY)); // wait PLL is set  

	RCC -> D1CFGR = (0b1000<<0)|(0b100<<4); //HPRE /2 /AHB //D1PPRE /2 /APB3; 
	RCC -> D2CFGR |= (0b100<<4); //D2PPRE1 /2 /APB1
	RCC -> D2CFGR |= (0b101<<8); //D2PPRE2 /100-2 /APB2 //101-4
	RCC -> D3CFGR |= (0b100<<4); //D3PPRE2 /2 /APB4

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |=RCC_CFGR_SW_PLL1;//PLL1 SW[2:0]: System clock switch
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1); 

}



