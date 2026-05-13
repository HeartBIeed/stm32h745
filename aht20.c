#include "aht20.h"

void AHT_output(uint8_t x, uint8_t y){

	uint8_t init_aht20[3] = {0xBE,0x08,0x00};
	uint8_t trig[3] = {0xAC, 0x33, 0x00};
	uint8_t buffer[6];
	char string[41];

	if (I2C_checkAddress(0x38)){

		USART3_sendStr("AHT EN\n\r");
		ST7735_DrawString(110,3, "X",BLACK,Font_7x10);

	} else {
	
		USART3_sendStr("AHT NOT FOUND (0x38)\n\r");
		ST7735_DrawString(110,3, "X",RED,Font_7x10);
		return;
	}

	I2C_writeByte(0x38,init_aht20,3);
			_delay_ms(50);

	I2C_writeByte(0x38,trig,3);
			_delay_ms(100);

	I2C_readByte(0x38,buffer,6);

	uint32_t raw_H = (buffer[1] <<12) | (buffer[2] << 8) | (buffer[3]>>4);
	uint32_t raw_T = ((buffer[3] & 0x0F) <<16) | (buffer[4] << 8) | buffer[5];

	uint32_t Humi = raw_H * 100 / 1048576; //1048576 = 2^20
	uint32_t Temp = raw_T * 200 / 1048576 - 50;

//************ OUTPUT TO USART ************

	sprintf(string,"AHT20_H: %lu\n\r",Humi);
	USART3_sendStr(string);

	sprintf(string,"AHT20_T: %lu\n\r",Temp);
	USART3_sendStr(string);

//*********** OUTPUT TO DISPLAY ***********

	static uint32_t Humi_old;
	static uint32_t Temp_old;

	if (!(Humi_old == Humi)){

		sprintf(string,"H: %lu %%",Humi_old);
		ST7735_DrawString(x,y, string,BLACK,Font_7x10);

		sprintf(string,"H: %lu %%",Humi);
		ST7735_DrawString(x,y, string,GREEN,Font_7x10);
	}

	if (!(Temp_old == Temp)){

		sprintf(string,"T: %lu*C",Temp_old);
		ST7735_DrawString(x,y+12, string,BLACK,Font_7x10);

		sprintf(string,"T: %lu*C",Temp);
		ST7735_DrawString(x,y+12, string,GREEN,Font_7x10);
	}

	Humi_old = Humi;
	Temp_old = Temp;

	string[0] = '\0';
}




