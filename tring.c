#include "tring.h"


uint32_t TRING_getRandom(){

	static uint8_t init_state = 0;

	if (init_state == 0){

	SET_BIT(RCC->CR, RCC_CR_HSI48ON);//Включаем HSI48 (48 МГц)
	while (!READ_BIT(RCC->CR, RCC_CR_HSI48RDY));

	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); 
	SET_BIT(RNG->CR, RNG_CR_RNGEN);
	//SET_BIT(RNG->CR, RNG_CR_IE);

	init_state = 1;
	}

	while (!READ_BIT(RNG->SR, RNG_SR_DRDY));
	return RNG->DR;
}

void TRING_Handler(){

    if (Debounce(14)) {

	ST7735_FillRect(50,50, 70, 15, BLACK);

	char string[32];
	sprintf(string,"%lu",TRING_getRandom());
	ST7735_DrawString(50,50, string,RED,Font_7x10);
    }
}