#ifndef _LED_H
#define _LED_H
#include "main.h"
#define LED0constOFF 0
#define LED0constON 1
#define LED0blinkONE 2
void led_sta_update_20ms(void);
void LED0_ON();
void LED0_OFF();
extern uint8_t LED_MODE;

#endif
