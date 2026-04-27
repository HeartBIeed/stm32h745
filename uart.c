#include "uart.h"

volatile uint8_t usart_data_buffer[32]; //буффер uart
volatile uint8_t usart_index_buffer =0;
volatile uint8_t USART3_flag =0;

void USART3_init(uint16_t baud){

	RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN; 
	RCC->APB1LENR |= RCC_APB1LENR_USART3EN; //APB bus
//moder 10 - alt 2 bit
	GPIOD->MODER &= ~(3 << (PD9*2)); 
	GPIOD->MODER |= (2 << (PD9*2)); //PD9 set tx

	GPIOD->MODER &= ~(3 << (PD8*2)); 
	GPIOD->MODER |= (2 << (PD8*2)); //PD8 set rx
//otyper 0- push-pull 1 bit
	GPIOD->OTYPER &= ~((1<<PD9)|(1<<PD8));
//speed 10 high 2 bit
	GPIOD->OSPEEDR |= ((2<<(PD9*2))|(2<<(PD8*2))); 

	GPIOD->AFR[1] |= ((7<<(0*4))|(7<<(1*4))); //AF7

	USART3->CR1 = 0;
	USART3->CR2 = 0;
	USART3->CR3 = 0;
			
	USART3->BRR = FCPU/baud; 

	USART3->CR1 |= USART_CR1_RXNEIE ; // interrupts
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; //tx rx usart enable
		
	NVIC_SetPriority(USART3_IRQn,2);
	NVIC_EnableIRQ(USART3_IRQn);
}


void USART3_sendByte(char tx_data){

	while (!(USART3->ISR & (1<<7))); // Bit 7 TXFNF: TXFIFO not full
	USART3->TDR = tx_data; 
}



void USART3_sendStr(char *str){
	
	while (*str) USART3_sendByte(*str++); // отправка до \0
}


void USART3_IRQHandler(){

	if (USART3->ISR & (1<<5)){ //RXFNE: RXFIFO not empty
	//проверяем флаг/RXNE сбросится
	
	char data_rx = USART3->RDR;
	USART3_flag =1; // поставим флаг

		if (data_rx == '\r' || usart_index_buffer >= sizeof(usart_data_buffer)-1){ 
		//если конец строки или переполнение
		
		usart_data_buffer[usart_index_buffer] = '\0'; //вставляем 0-терминатор
		usart_index_buffer = 0;

		} else {

		usart_data_buffer[usart_index_buffer] = data_rx;
		usart_index_buffer++;
		}
			
	}

}	



	

void USART3_echo(){

	if (USART3_flag)
	{
	USART3_sendStr("GET: ");
	USART3_sendStr((char*)usart_data_buffer);
	USART3_sendStr("\r\n");
	
	USART3_flag = 0;
	
	}	
}

	
int USART_commands(){

	if (strncmp((char*)usart_data_buffer,"st",2) == 0) 
	{

		char *command = strtok((char*)usart_data_buffer," ");
		char *h_char = strtok(NULL, ",");
		char *m_char = strtok(NULL, ",");

		int h = atoi(h_char);
		int m = atoi(m_char);

		RTC_setTime(h,m);


		char string[32];
		sprintf(string, "SET TIME -> %2d:%2d \r\n",h,m);///!!!!!!!!
		USART3_sendStr(string);
	 	usart_data_buffer[0] = '\0';

	 		return 1;

	} else {
			return 0;
	}
	
}