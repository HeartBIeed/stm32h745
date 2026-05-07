#ifndef ST7735_H_
#define ST7735_H_

#include "main.h"
#include "fonts.h"
#include "st7735_gfx.h"

#define RST 9
#define AO 2
#define CS 8

void ST7735_init();
void ST7735_SetRegion(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

void DATA_mode();
void CMD_mode();

void ST7735_cmd(uint8_t cmd);
void ST7735_data(uint8_t data);

void CS_high();
void CS_low();

#endif /* ST7735_H_ */
