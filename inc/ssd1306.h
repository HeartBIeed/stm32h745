#ifndef SSD1306_H_
#define SSD1306_H_

#include "main.h"

#define OLED_ADDR 0x3c

void SSD1306_init();
void SSD1306_inverse(uint8_t state);
void SSD1306_fill(uint8_t pixel);
void SSD1306_draw(uint8_t x, uint8_t page, uint8_t width, uint8_t height);
void SSD1306_drawChar(char c, uint8_t page, uint8_t x);
void SSD1306_drawString(const char* str, uint8_t page_start, uint8_t x_start);
void SSD1306_drawProgress(uint8_t input_dec, uint8_t page);

extern const uint8_t ssd1306_font5x7[][5];

#endif /* SSD1306_H_ */
