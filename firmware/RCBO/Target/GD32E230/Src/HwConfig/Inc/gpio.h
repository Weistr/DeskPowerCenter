#ifndef _GPIO_H
#define _GPIO_H
#include "main.h"
#include "gd32e23x_gpio.h"
#define RLY_COIL_GPIO GPIOA
#define RLY_COIL_PIN GPIO_PIN_2

#define LED1_GPIO GPIOA
#define LED1_PIN GPIO_PIN_3

#define ACOUT_PG_GPIO GPIOA
#define ACOUT_PG_PIN GPIO_PIN_4

#define I_LEAK_ADC_GPIO GPIOA
#define I_LEAK_ADC_PIN GPIO_PIN_5

#define ACIN_I_ADC_GPIO GPIOA
#define ACIN_I_ADC_PIN GPIO_PIN_6

#define TIMER2_CH1_GPIO GPIOA
#define TIMER2_CH1_PIN GPIO_PIN_7

#define ACIN_ADC_GPIO GPIOB
#define ACIN_ADC_PIN GPIO_PIN_1

#define TX0_GPIO GPIOA
#define TX0_PIN GPIO_PIN_9

#define RX0_GPIO GPIOA
#define RX0_PIN GPIO_PIN_10

void gpioConfig(void);

#define led_gpio_set_l() gpio_bit_reset(LED1_GPIO, LED1_PIN)
#define led_gpio_set_h() gpio_bit_set(LED1_GPIO, LED1_PIN)
#endif // !_GPIO_H