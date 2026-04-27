#include "pll.h"

void PLL_init(){
	
	// Switch internal CSI (~4 MHz) clock on and wait when its ready
	RCC->CR |= RCC_CR_CSION;
	while(((RCC->CR)&RCC_CR_CSIRDY) != RCC_CR_CSIRDY){};
	
	MODIFY_REG(RCC->PLLCKSELR,
          RCC_PLLCKSELR_PLLSRC,
          RCC_PLLCKSELR_PLLSRC_CSI);

	MODIFY_REG(RCC->PLLCKSELR,
          RCC_PLLCKSELR_DIVM1,
          RCC_PLLCKSELR_DIVM1_0);

	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLL1VCOSEL);
// Medium VCO (150-420) MHz

	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLL1RGE);
// PLL1 input fqu between 4 and 8 MHz

	CLEAR_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLL1FRACEN);
// fractional latch = 0

	// PLL1 DIVP divider setup, first check PLL1 state, if on or ready -> shutdown
	if(((RCC->CR)&RCC_CR_PLL1ON) == RCC_CR_PLL1ON ||
	   ((RCC->CR)&RCC_CR_PLL1RDY) == RCC_CR_PLL1RDY){
	
	RCC->CR &= ~RCC_CR_PLL1ON;
	while(((RCC->CR)&RCC_CR_PLL1RDY) != RCC_CR_PLL1RDY){};
	}
	RCC->PLLCFGR &= ~RCC_PLLCFGR_DIVP1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN;
	
	//PLL1 DIVQ divider enable
	MODIFY_REG(RCC->PLLCFGR,
          RCC_PLLCFGR_DIVQ1EN,
          RCC_PLLCFGR_DIVQ1EN);

	//PLL1 DIVR divider enable
	MODIFY_REG(RCC->PLLCFGR,
          RCC_PLLCFGR_DIVR1EN,
          RCC_PLLCFGR_DIVR1EN);	

	MODIFY_REG(RCC->PLL1DIVR,
          RCC_PLL1DIVR_N1,
          RCC_PLL1DIVR_N1&0x32);

	SET_BIT(RCC->CR,RCC_CR_PLL1ON);

	
	while(((RCC->CR)&RCC_CR_PLL1RDY) != RCC_CR_PLL1RDY){};
	
	
}

