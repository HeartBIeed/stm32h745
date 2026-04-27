#include "spi.h"

void pllInit(){
	
	/*
			PLL1 setup
	
	*/
	
	// Switch internal CSI (~4 MHz) clock on and wait when its ready
	RCC->CR |= RCC_CR_CSION;
	while(((RCC->CR)&RCC_CR_CSIRDY) != RCC_CR_CSIRDY){};
	
	
	
	// CSI selected to PLL1 clock
	RCC->PLLCKSELR &= ~RCC_PLLCKSELR_PLLSRC;
	RCC->PLLCKSELR |= RCC_PLLCKSELR_PLLSRC_CSI;
	
	// Prescaler reset & set /1
	RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM1;
	RCC->PLLCKSELR |= RCC_PLLCKSELR_DIVM1_0;
	
	// Medium VCO (150-420) MHz
	RCC->PLLCFGR |= RCC_PLLCFGR_PLL1VCOSEL;
	// PLL1 input fqu between 4 and 8 MHz
	RCC->PLLCFGR |= RCC_PLLCFGR_PLL1RGE;
	// fractional latch = 0
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL1FRACEN;
	
	// PLL1 DIVP divider setup, first check PLL1 state, if on or ready -> shutdown
	if(((RCC->CR)&RCC_CR_PLL1ON) == RCC_CR_PLL1ON || ((RCC->CR)&RCC_CR_PLL1RDY) == RCC_CR_PLL1RDY){
		RCC->CR &= ~RCC_CR_PLL1ON;
		while(((RCC->CR)&RCC_CR_PLL1RDY) != RCC_CR_PLL1RDY){};
	}
	RCC->PLLCFGR &= ~RCC_PLLCFGR_DIVP1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN;
	
	//PLL1 DIVQ divider enable
	RCC->PLLCFGR &= ~RCC_PLLCFGR_DIVQ1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVQ1EN;
	
	//PLL1 DIVR divider enable
	RCC->PLLCFGR &= ~RCC_PLLCFGR_DIVR1EN;
	RCC->PLLCFGR |= RCC_PLLCFGR_DIVR1EN;
	
	// VCO selected 150-420
	// input fqu selected 4-8
	// multiplication factor for VCO will be 50 (0x32)
	// so output fqu will be 200 - 400 MHz
	RCC->PLL1DIVR &= ~RCC_PLL1DIVR_N1;
	RCC->PLL1DIVR |= RCC_PLL1DIVR_N1&0x32;
	
	
	
	
	
	// PLL1 DIVP division factor = 0
	RCC->PLL1DIVR &= ~RCC_PLL1DIVR_P1;
	// PLL1 DIVQ division factor = 0
	RCC->PLL1DIVR &= ~RCC_PLL1DIVR_Q1;
	// PLL1 DIVR division factor = 0
	RCC->PLL1DIVR &= ~RCC_PLL1DIVR_R1;
	
	
	// PLL1 enable and wait ready flag to continue
	RCC->CR |= RCC_CR_PLL1ON;
	while(((RCC->CR)&RCC_CR_PLL1RDY) != RCC_CR_PLL1RDY){};

}


void SPI1_init(){

	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 

pllInit();
//RCC->D2CCIP1R &= ~(7U << 12);
//RCC->D2CCIP1R |=  (4U << 12); // PER_CK


	GPIOA->MODER &= ~((3 << (SPI_SCK*2))|
					(3 << (MISO*2))|
					(3 << (MOSI*2))); 

	GPIOA->MODER |= ((2 << (SPI_SCK*2))|
					(2 << (MISO*2))|
					(2 << (MOSI*2)));

	GPIOA->OSPEEDR |= ((2 << (SPI_SCK*2))|
					(2 << (MISO*2))|
					(2 << (MOSI*2)));

	GPIOA->AFR[0] &= ~((0xF << (SPI_SCK*4))|
					(0xF << (MISO*4))|
					(0xF << (MOSI*4)));  

	GPIOA->AFR[0] |= ((5 << (SPI_SCK*4))| //AF5
					(5 << (MISO*4))|
					(5 << (MOSI*4)));

	SPI1->CR1 = 0;
	SPI1->CR2 = 0;
	SPI1->CFG1 = 0;
	SPI1->CFG2 = 0;

	SPI1->CFG1 |= (2<<28); // baud rate f/8
	SPI1->CFG1 |= (7<<0); // DSIZE /Data size 8 bit 0x111

//	SPI1->CFG2 |= SPI_CFG2_AFCNTR; // Bit 31 AFCNTR: alternate function GPIOs control
	SPI1->CFG2 |= SPI_CFG2_MASTER; // Master
	SPI1->CFG2 |= SPI_CFG2_SSM; // SSM Software slave management

	SPI1->CR1 |= SPI_CR1_SSI; // SSI
	SPI1->CR1 |= SPI_CR1_SPE; // SPI EN

}

uint8_t SPI1_sendByte(uint8_t tx_data){
	
	SPI1->CR2 = 1; // TSIZE 1 byte
	SPI1->CR1 |= SPI_CR1_CSTART; // 1: master transfer is on-going

	while (!(SPI1->SR & SPI_SR_TXP)); // Tx-packet space available

	*(volatile uint8_t*)&SPI1->TXDR = tx_data; 

//while(!(SPI1->SR & SPI_SR_TXC));
//while(!(SPI1->SR & SPI_SR_EOT));// wait end of the transmission
	
	while(!(SPI1->SR & (1<<0))); //RXP: Rx-packet available
	return *(volatile uint8_t*)&SPI1->RXDR;


	return 0;

}


