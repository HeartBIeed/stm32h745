#ifndef RTC_H_
#define RTC_H_

#include "main.h"

void RTC_init();
void RTC_setTime(uint8_t h,uint8_t m);
void RTC_getTime(volatile uint8_t *hour,volatile uint8_t *min,volatile uint8_t *sec);
void RTC_alarmSec();
void RTC_printTime(uint8_t x, uint8_t y);

extern volatile uint8_t hour;
extern volatile uint8_t min;
extern volatile uint8_t sec;

#endif /* RTC_H_ */
