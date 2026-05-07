#include "st7735.h"

void ST7735_setPins(){

	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; 

	GPIOA->MODER &= ~((3 << (RST*2))|(3 << (AO*2))|(3 << (CS*2))); 
	GPIOA->MODER |= ((1 << (RST*2))|(1 << (AO*2))|(1 << (CS*2))); // output

	GPIOA->OSPEEDR &= ~((3 << (RST*2))|(3 << (AO*2))|(3 << (CS*2))); 
	GPIOA->OSPEEDR |= ((3 << (RST*2))|(3 << (AO*2))|(3 << (CS*2))); //high

	GPIOA->BSRR |= (1 << RST); 

}

void DATA_mode(){
	GPIOA->BSRR |= (1 << AO); 
}

void CMD_mode(){
	GPIOA->BSRR |= (1 << (AO+16)); 
}

void CS_high(){
	GPIOA->BSRR |= (1 << CS); 
}

void CS_low(){
	GPIOA->BSRR |= (1 << (CS+16)); 
}

void ST7735_reset(){

	GPIOA->BSRR |= (1 << RST); 
		_delay_ms(10);	
	GPIOA->BSRR |= (1 << (RST+16)); 
		_delay_ms(10);	
	GPIOA->BSRR |= (1 << RST); 

}

void ST7735_cmd(uint8_t cmd){

	CMD_mode();
	SPI1_sendByte(cmd);
}

void ST7735_data(uint8_t data){

	DATA_mode();
	SPI1_sendByte(data);
}

void ST7735_init(){

	ST7735_setPins();

	ST7735_reset();
		_delay_ms(10);
	CS_low();
		_delay_ms(10);

	ST7735_cmd(0x11);
		_delay_ms(120);

	ST7735_cmd(0x3A);
	ST7735_data(0x05);

	ST7735_cmd(0x36);
	ST7735_data(0x14);

	ST7735_cmd(0x29);
		_delay_ms(100);

}


void ST7735_SetRegion(uint16_t x, uint16_t y, uint16_t w, uint16_t h){

	ST7735_cmd(0x2A);
	ST7735_data(0);
	ST7735_data(x);
	ST7735_data(0);
	ST7735_data(x + w - 1);

	ST7735_cmd(0x2B);
	ST7735_data(0);
	ST7735_data(y);
	ST7735_data(0);
	ST7735_data(y + h - 1);

	ST7735_cmd(0x2C);

}



