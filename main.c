#include "main.h"

void PE1_blink();

void GPIO()
{
	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOEEN);
	MODIFY_REG(GPIOE->MODER,
           (3 << (1 * 2)),
           (1 << (1 * 2)));

	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOBEN);
	MODIFY_REG(GPIOB->MODER,
           (3 << (1 * 2)),
           (1 << (1 * 2)));

}



// ***************** main *****************
int main(void){

//SystemClock_HSE_8MHz();
PLL_400MHz_enable();

SysTick_init();
DWT_init();

USART3_init(9600);
I2C_init();
RTC_init();
SPI1_init();
//SPI2_init();

//bmp280_init();
GPIO();
Buttons_init();
ST7735_init();

LCD1602_init();

ST7735_FillRect(0,0, 128, 160, BLACK); 
USART3_sendStr("\033[1;32m START \n\r\033[0m");

uint32_t start[4] = {0};

LCD_send_string("Hello world!",0,0);


const uint8_t degree[8] = {
    0b01100,
    0b10010,
    0b10010,
    0b01100,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

const uint8_t heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};



LCD_create_symb(degree,0,15,0);
LCD_create_symb(heart,1,0,1);

while(1) {



	if (ms_ticks - start[1] >= 50){

	USART3_echo();
 	USART_cmdHandler();
//	Buttons_Handler();

	start[1] = ms_ticks;
	}


	if (ms_ticks - start[0] >= 2000){

	AHT_output(3, 15);
	//BMP280_print(3,140);
	//I2C_scan();

	start[0] = ms_ticks;
	}


	PE1_blink();
	}
}


void PE1_blink(){

	static uint32_t	start = 0;
	if (ms_ticks - start >= 1000){

	GPIOE->ODR ^= (1 << 1);

	RTC_printTime(3,3); // to diplay

	start = ms_ticks;
	}
}

