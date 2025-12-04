#ifndef _ADC_H
#define _ADC_H


#include "gd32e23x_adc.h"

#define ACIN_ADC_CHANNEL ADC_CHANNEL_9
#define ACIN_I_ADC_CHANNEL ADC_CHANNEL_6
#define I_LEAK_ADC_CHANNEL ADC_CHANNEL_5
void adcConfig(void);
uint16_t adc_transform_softWare(void);

extern uint16_t adcRes[3];
#endif // !_ADC_H