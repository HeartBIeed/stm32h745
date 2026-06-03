#include "tmp100.h"

void TMP100(){

	char string[41];
	uint8_t addr = 0x4e;
	
	uint8_t config[2] = {0};
	config[0] = 0x01; // Select configuration register(0x01)
	config[1] = 0x60; // Continuous conversion, comparator mode, 12-bit resolution(0x60)
	I2C_writeByte(addr,config, 2);
		_delay_ms(400);

	uint8_t reg[1] = {0x00}; // Read 2 bytes of data from register(0x00)
	I2C_writeByte(addr,reg, 1);
		_delay_ms(10);

	uint8_t data[2] = {0};// temp msb, temp lsb
	I2C_readByte(addr,data,2);

	// Convert the data to 12-bits
	int temp = (data[0] * 256 + (data[1] & 0xF0)) / 16;

	if(temp > 2047) temp -= 4096;

	uint8_t whole = temp / 16;
	uint8_t tens = (temp % 16)*100/16;

	sprintf(string,"TMP100: %d.%02d *C\n",whole,tens);
	USART3_sendStr(string);
}