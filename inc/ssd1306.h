#ifndef SSD1306_H_
#define SSD1306_H_

#include "main.h"

#define OLED_ADDR 0x3c

void SSD1306_init();
void SSD1306_fill(uint8_t pixel);

#endif /* SSD1306_H_ */
