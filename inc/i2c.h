#ifndef I2C_H_
#define I2C_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void I2C_init( );
int I2C_checkAddress(int addr);
void I2C_readByte(int addr,uint8_t* data,int len);
void I2C_writeByte(int addr,uint8_t* data,int nbytes);
void I2C_scan();

// I2C1
// PB8 - SCL
// PB9 - SDA

#define TIMEOUT 1000000

#define SCL 8
#define SDA 9

#endif /* I2C_H_ */
