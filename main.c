#include "main.h"

void GPIO()
{
	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOEEN);
	
	MODIFY_REG(GPIOE->MODER,
           (3 << (1 * 2)),
           (1 << (1 * 2)));
}

void PE1_blink(){

//	static uint32_t	start = 0;
_delay_us(100000);
//	if (ms_ticks - start >= 1000){

	GPIOE->ODR ^= (1 << 1);
//	start = ms_ticks;
	//}
}

void usart_Time(){


	RTC_getTime(&hour,&min,&sec);
	char text[20]={"\0"};	
	sprintf(text, "%02d:%02d:%02d",hour,min,sec);


USART3_sendStr(text);
USART3_sendStr("\n\r");

}

// ***************** main *****************
int main(void){

//SystemClock_HSE_8MHz();
PLL_400MHz_enable();
SysTick_init();
DWT_init();

GPIO();
USART3_init(9600);
RTC_init();
//SPI1_init();
	USART3_sendStr("\033[1;32m SPI1_init \n\r\033[0m");

//ST7735_init();
//	USART3_sendStr("\033[1;32m ST7735_init \n\r\033[0m");

//ST7735_FillRect(0,0, 128, 160, BLACK); 

I2C_init();

USART3_sendStr("\033[1;32m START \n\r\033[0m");

uint32_t start[4] = {0};

while(1)
{


	if (ms_ticks - start[2] >= 1000)
	{

usart_Time();

	start[2] = ms_ticks;
	}


	if (ms_ticks - start[1] >= 100)
	{

	USART3_echo();
 USART_commands();

	start[1] = ms_ticks;
	}



	if (ms_ticks - start[0] >= 5000)
	{
	AHT_output(10, 10);
	start[0] = ms_ticks;
	}


	PE1_blink();

}
}


