#include "lcd.h"

void send_byte(uint8_t data,uint8_t mode);
void send_nibble(uint8_t byte);

void LCD_init_port(){

	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIODEN);
	
	MODIFY_REG(GPIOD->MODER, (3<< RS *2), (1<< RS *2));  
	MODIFY_REG(GPIOD->MODER, (3<< E *2), (1<< E *2)); 
	MODIFY_REG(GPIOD->MODER, (3<< DATA_4 *2), (1<< DATA_4 *2));  
	MODIFY_REG(GPIOD->MODER, (3<< DATA_5 *2), (1<< DATA_5 *2));  
	MODIFY_REG(GPIOD->MODER, (3<< DATA_6 *2), (1<< DATA_6 *2));  
	MODIFY_REG(GPIOD->MODER, (3<< DATA_7 *2), (1<< DATA_7 *2)); 

	MODIFY_REG(GPIOD->OSPEEDR, (3<< RS *2), (2<< RS *2));  
	MODIFY_REG(GPIOD->OSPEEDR, (3<< E *2), (2<< E *2)); 
	MODIFY_REG(GPIOD->OSPEEDR, (3<< DATA_4 *2), (2<< DATA_4 *2));  
	MODIFY_REG(GPIOD->OSPEEDR, (3<< DATA_5 *2), (2<< DATA_5 *2));  
	MODIFY_REG(GPIOD->OSPEEDR, (3<< DATA_6 *2), (2<< DATA_6 *2));  
	MODIFY_REG(GPIOD->OSPEEDR, (3<< DATA_7 *2), (2<< DATA_7 *2)); 

}

void E_up(){
	GPIOD->BSRR |= (1 << E); 
}

void E_down(){
	GPIOD->BSRR |= (1 << (E+16)); 
}

void RS_up(){
	GPIOD->BSRR |= (1 << RS); 
}

void RS_down(){
	GPIOD->BSRR |= (1 << (RS+16)); 
}


void LCD1602_init(void){

	LCD_init_port();

		_delay_ms(15);
	send_nibble(0x3);  // 4 битный режим
		_delay_ms(4);
	send_nibble(0x3);
		_delay_us(100);
	send_nibble(0x3);
		_delay_ms(1);
	send_nibble(0x2);
		_delay_ms(1);

	send_byte(0x28, 0); // отправка команд
		_delay_ms(1);

	send_byte(0xC, 0);
		_delay_ms(1);

	send_byte(0x6, 0);
		_delay_ms(1);
}

void send_nibble(uint8_t byte){ 

	byte <<= 4;
	byte &= 0xF0;

	E_up();

	GPIOD->ODR &= 0xFFFFFF0F; 
	GPIOD->ODR |= byte; 
			
		_delay_us(50);
	E_down();
			
}

void send_byte(uint8_t data,uint8_t mode){

	if (mode) RS_up(); 	 // данные 1  
	else 	  RS_down(); // команда 0
		
	uint8_t h_nibble = data >> 4;

	send_nibble(h_nibble);
	send_nibble(data);	
}

void send_char(char c){ 

	send_byte(c,1);
}

void set_position( uint8_t x, uint8_t y){ 

	uint8_t address;

    switch(y){
        case 0: address = 0x00; break; // 1-я строка
        case 1: address = 0x40; break; // 2-я 
        case 2: address = 0x14; break; // 3-я  
        case 3: address = 0x54; break; // 4-я  
    default: address = 0x00; break;
    }

	send_byte((address + x)|0x80, 0); 
	// 7й бит  команд установки позиции DDRAM
}



void LCD_send_string(char *str, uint8_t x, uint8_t y){

	set_position(x,y);
	while (*str) send_char(*str++);
}


void LCD_create_symb(const uint8_t *data, uint8_t index_symb, uint8_t x, uint8_t y){
		
	uint8_t address=0x40|(index_symb * 8); // address in to DDRAM
	send_byte(address, 0);

	for (uint8_t i = 0; i < 8; i++)	send_byte(data[i], 1); 
	
	set_position(x,y);
	send_byte(index_symb, 1);		  // send symbol from array
}


/*

1-я строка		0x00
2-я строка		0x40
3-я строка	—	0x14
4-я строка	—	0x54

*/
