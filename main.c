#include "main.h"

void PE1_blink();

void GPIO(){
	
	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOBEN);
	MODIFY_REG(GPIOB->MODER,
	           (3 << (1 * 2)),
	           (1 << (1 * 2)));
}


// ***************** main *****************
int main(void){

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

ST7735_FillRect(0,0, 128, 160, BLACK); 
USART3_sendStr("\033[1;32m START \n\r\033[0m");

uint32_t start[4] = {0};

while(1) {



	if (ms_ticks - start[1] >= 50){

	USART3_echo();
 	USART_cmdHandler();
	Buttons_Handler();

	start[1] = ms_ticks;
	}


	if (ms_ticks - start[0] >= 2000){

	AHT_output(3, 20);
	//BMP280_print(3,140);
	
	start[0] = ms_ticks;
	}


	PE1_blink();
	}
}


void PE1_blink(){

	static uint8_t init_state = 1;

	if (init_state){

	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOEEN);
	MODIFY_REG(GPIOE->MODER,
		    (3 << (1 * 2)),
		    (1 << (1 * 2)));

	init_state = 0;
	}

	static uint32_t	start = 0;
	if (ms_ticks - start >= 1000){

	GPIOE->ODR ^= (1 << 1);

	RTC_printTime(3,3); // to diplay

	start = ms_ticks;
	}
}

