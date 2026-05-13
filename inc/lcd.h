#ifndef LCD_H_
#define LCD_H_

#include "main.h"


// PIN SETTING FOR LCD
// PD

#define RS 0
#define E 1
#define DATA_4 4
#define DATA_5 5
#define DATA_6 6
#define DATA_7 7

void LCD1602_init(void);
void LCD_send_string(char *str, uint8_t x, uint8_t y);
void LCD_create_symb(const uint8_t *data, uint8_t index_symb, uint8_t x, uint8_t y);

#endif /* LCD_H_ */
