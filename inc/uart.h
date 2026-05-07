#ifndef UART_H_
#define UART_H_


#include "main.h"

#define PD8 8
#define PD9 9


void USART3_init(uint16_t baud);
void USART3_sendByte(char tx_data); // отправка байта
void USART3_sendStr(char *str); // отправка строки - принимаем строковый массив
void USART3_IRQHandler(); // обработчик прерывания
void USART3_echo();
int USART_cmdHandler();

extern volatile uint8_t usart_data_buffer[32]; //буффер uart
extern volatile uint8_t usart_index_buffer;
extern volatile uint8_t USART3_flag;

#endif /* UART_H_ */
