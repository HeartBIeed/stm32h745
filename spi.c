#include "spi.h"

void SPI1_init(){

	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 

	GPIOA->MODER &= ~((3 << (SPI_SCK*2))|
					(3 << (MISO*2))|
					(3 << (MOSI*2))); 

	GPIOA->MODER |= ((2 << (SPI_SCK*2))|
					(2 << (MISO*2))|
					(2 << (MOSI*2)));

	GPIOA->OSPEEDR |= ((3 << (SPI_SCK*2))|
					(3 << (MISO*2))|
					(3 << (MOSI*2)));

	GPIOA->AFR[0] &= ~((0xF << (SPI_SCK*4))|
					(0xF << (MISO*4))|
					(0xF << (MOSI*4)));  

	GPIOA->AFR[0] |= ((5 << (SPI_SCK*4))| //AF5
					(5 << (MISO*4))|
					(5 << (MOSI*4)));

	SPI1->CR1 = 0;
	SPI1->CFG1 = 0;
	SPI1->CFG2 = 0;

	SPI1->CFG1 |= (1<<28); // baud rate f/
	SPI1->CFG1 |= (7<<0); // DSIZE /Data size 8 bit 0x111

	SPI1->CR1 |= SPI_CR1_SSI; // SSI7

	SPI1->CFG2 |= SPI_CFG2_SSM; // SSM Software slave management
	SPI1->CFG2 |= (1<<22); // Master
	SPI1->CFG2 |= SPI_CFG2_AFCNTR; // Bit 31 AFCNTR: alternate function GPIOs control

//	SPI1->CR2 |= 1; // TSIZE 1 byte

}

uint8_t SPI1_sendByte(uint8_t tx_data){

	SPI1->CR1 |= SPI_CR1_SPE; // SPI EN
	SPI1->CR1 |= SPI_CR1_CSTART; 

	while (!(SPI1->SR & SPI_SR_TXP)); // Tx-packet space available
	*((__IO uint8_t*)&SPI1->TXDR) = tx_data;

	while (!(SPI1->SR & SPI_SR_TXC));

//	while(!(SPI1->SR & SPI_SR_RXP)); // Rx-packet available
//	return *(volatile uint8_t*)&SPI1->RXDR;

	SPI1->CR1 &= ~SPI_CR1_SPE; // SPI DIS

	return 0;
}

/*

MBR[2:0]: master baud rate

0 000: SPI master clock/2
1 001: SPI master clock/4
2 010: SPI master clock/8
3 011: SPI master clock/16
4 100: SPI master clock/32
5 101: SPI master clock/64
6 110: SPI master clock/128
7 111: SPI master clock/256

*/