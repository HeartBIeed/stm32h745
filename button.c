#include "button.h"


void Buttons_init(){

	SET_BIT(RCC->AHB4ENR,RCC_AHB4ENR_GPIOEEN);
	
	CLEAR_BIT(GPIOE->MODER,(3<<10*2));
	CLEAR_BIT(GPIOE->MODER,(3<<12*2));
	CLEAR_BIT(GPIOE->MODER,(3<<14*2));

	CLEAR_BIT(GPIOE->OTYPER,(1<<10));
	CLEAR_BIT(GPIOE->OTYPER,(1<<12));
	CLEAR_BIT(GPIOE->OTYPER,(1<<14));

	SET_BIT(GPIOE->PUPDR,(1<<10*2));
	SET_BIT(GPIOE->PUPDR,(1<<12*2));
	SET_BIT(GPIOE->PUPDR,(1<<14*2));
// PE 10/12/14 на вход
}


void Buttons_Handler(){

//    if (Debounce(10));
//    if (Debounce(12));
//    if (Debounce(14));

}




int Debounce(uint8_t pin){ // обработка нажатия кнопки (дребезг + состояние)

    static uint8_t current_state[16]; 

    switch (current_state[pin])
    	{

        case RELEASED:
            if (!(GPIOE->IDR & (1 << pin))) // если кнопка нажата (т.е. притянута к 0)
            {           
            _delay_ms(20);

                if (!(GPIOE->IDR & (1 << pin)))
                {
                current_state[pin] = PRESSED; // состояние "нажато"
                return 1;
                }
            }
        break;

        case PRESSED:
            if (GPIOE->IDR & (1 << pin)) // если кнопка отпущена (т.е. уровень  VCС)
            {            
            _delay_ms(20);

                if (GPIOE->IDR & (1 << pin)) 
                {
                current_state[pin] = RELEASED; // состояние "отпущено"
                return 0;
                }

            }
        break;

        default:
            current_state[pin] = RELEASED; // дефолт "отпущено"
        break;

        }
    return 0;
}




