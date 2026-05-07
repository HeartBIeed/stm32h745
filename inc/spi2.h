#ifndef SPI2_H_
#define SPI2_H_

#include "main.h"

#define SPI2_SCK 13 // PB13
#define MISO_2 14 // PB14
#define MOSI_2 15 // PB15

void SPI2_init();
uint8_t SPI2_sendByte(uint8_t tx_data);

#endif /* SPI2_H_ */
