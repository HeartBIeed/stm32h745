#ifndef ST7735_H_
#define ST7735_H_

#include "main.h"
#include "fonts.h"

#define RST 9
#define AO 12
#define CS 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

#define EN 32
#define RU 0xC0

void ST7735_init();
int ST7735_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ST7735_Color color);
void ST7735_DrawChar(uint16_t x, uint16_t y, char c, ST7735_Color color, FontDef font);
void ST7735_DrawString(uint16_t x, uint16_t y, const char* str, ST7735_Color color, FontDef font);
void ST7735_DrawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1,ST7735_Color color);
void bresenhamCircle(int16_t x0, int16_t y0, int16_t radius, ST7735_Color color);
void bresenhamCircleFill(int16_t x0, int16_t y0, int16_t radius, ST7735_Color color);

#endif /* ST7735_H_ */
