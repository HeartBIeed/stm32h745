#include "spi2.h"

void SPI2_init(){

	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN; 
	RCC->APB1LENR |= RCC_APB1LENR_SPI2EN; 

	GPIOB->MODER &= ~((3 << (SPI2_SCK*2))|
					(3 << (MISO_2*2))|
					(3 << (MOSI_2*2))); 

	GPIOB->MODER |= ((2 << (SPI2_SCK*2))|
					(2 << (MISO_2*2))|
					(2 << (MOSI_2*2)));

	GPIOB->OSPEEDR |= ((3 << (SPI2_SCK*2))|
					(3 << (MISO_2*2))|
					(3 << (MOSI_2*2)));

	GPIOB->AFR[1] &= ~((0xF << ((SPI2_SCK-8)*4))|
					(0xF << ((MISO_2-8)*4))|
					(0xF << ((MOSI_2-8)*4)));  

	GPIOB->AFR[1] |= ((5 << ((SPI2_SCK-8)*4))| //AF5
					(5 << ((MISO_2-8)*4))|
					(5 << ((MOSI_2-8)*4)));

	SPI2->CR1 = 0;
	SPI2->CFG1 = 0;
	SPI2->CFG2 = 0;

	SPI2->CFG1 |= (5<<28); // baud rate f/
	SPI2->CFG1 |= (7<<0); // DSIZE /Data size 8 bit 0x111

	SPI2->CR1 |= SPI_CR1_SSI; // SSI7

	SPI2->CFG2 |= SPI_CFG2_SSM; // SSM Software slave management
	SPI2->CFG2 |= (1<<22); // Master
	SPI2->CFG2 |= SPI_CFG2_AFCNTR; // Bit 31 AFCNTR: alternate function GPIOs control

//	SPI2->CR2 |= 1; // TSIZE 1 byte

}

uint8_t SPI2_sendByte(uint8_t tx_data){

	SPI2->CR1 |= SPI_CR1_SPE; // SPI ENABLE
	SPI2->CR1 |= SPI_CR1_CSTART; 

	while (!(SPI2->SR & SPI_SR_TXP)); // Tx-packet space available
	*((__IO uint8_t*)&SPI2->TXDR) = tx_data;

	while (!(SPI2->SR & SPI_SR_TXC));

	while(!(SPI2->SR & SPI_SR_RXP)); // Rx-packet available

	SPI2->CR1 &= ~SPI_CR1_SPE; // SPI DISABLE

	return *(volatile uint8_t*)&SPI2->RXDR;

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

