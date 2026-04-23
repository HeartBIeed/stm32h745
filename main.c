#include "main.h"


void GPIO()
{
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN; 

	GPIOE->MODER =0; 

	GPIOE->MODER |= (1 << (1*2)); // out

	GPIOE->BSRR |= (1 << 1); 
}




// ***************** main *****************
int main(void){

GPIO();
USART3_init(9600);

USART3_sendStr("\033[1;32m USART EN\n\r\033[0m");

while(1)
{

	USART3_echo();
	for (int i = 0; i < 1000; ++i);


}
}


