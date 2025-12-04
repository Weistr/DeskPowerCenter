#ifndef _CMSIS_DELAY_H
#define _CMSIS_DELAY_H

#include "main.h"

void cmsis_delay_init(void);
void cmsis_delay_us(uint16_t nus);
void cmsis_delay_ms(uint16_t nms);
#endif //