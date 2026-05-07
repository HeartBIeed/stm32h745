#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

enum button_state{
    RELEASED,
    PRESSED
    };


void Buttons_Handler();
void Buttons_init();
int Debounce(uint8_t pin);


#endif /* BUTTON_H_ */