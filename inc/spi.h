#ifndef SPI_H_
#define SPI_H_

#include "main.h"

#define SPI_SCK 5 // PA5
#define MISO 6 // PA6
#define MOSI 7 // PA7

void SPI1_init();
uint8_t SPI1_sendByte(uint8_t tx_data);

#endif /* SPI_H_ */
