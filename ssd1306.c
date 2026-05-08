#include "ssd1306.h"


void SSD1306_cmd(uint8_t cmd){

    uint8_t arr[2];
    arr[0] = 0x00;
    arr[1] = cmd;
    I2C_writeByte(OLED_ADDR,arr,2);
}

void SSD1306_data(uint8_t data){
    
    uint8_t arr[2];
    arr[0] = 0x40;
    arr[1] = data;
    I2C_writeByte(OLED_ADDR,arr,2);
}

void SSD1306_init(){

uint8_t init_commands_list[27] ={
    0xAE, // display off
    0x20, // addressing mode
    0x00, // horizontal mode
    0xB0, // page start
    0xC8, // scan direction
    0x00, // low column
    0x10, // high column
    0x40, // start line
    0x81, // contrast
    0xFF,
    0xA1, // segment remap
    0xA6, // normal display
    0xA8, // multiplex
    0x3F, // 64 lines
    0xD3, // offset
    0x00,
    0xD5, // clock
    0x80,
    0xD9, // precharge
    0xF1,
    0xDA, // com pins
    0x12,
    0xDB, // vcom detect
    0x40,
    0x8D, // charge pump
    0x14,
    0xAF // display on
    };

    for (int i = 0; i < 27; ++i){

    SSD1306_cmd(init_commands_list[i]);
  //  _delay_us(10);
    }

}

void SSD1306_fill(uint8_t pixel){

    SSD1306_cmd(0x21);
    SSD1306_cmd(0x00);
    SSD1306_cmd(0x7F);

    SSD1306_cmd(0x22);
    SSD1306_cmd(0x00);
    SSD1306_cmd(0x07);

    for (uint16_t i = 0; i < (128*64/8); i++){

    SSD1306_data(pixel);
    }
}



