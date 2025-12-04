#include "gpio.h"
void gpioConfig()
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
  
    //LED
    gpio_mode_set(LED1_GPIO, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_PIN);
    gpio_output_options_set(LED1_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED1_PIN);
    //ADC
    gpio_mode_set(I_LEAK_ADC_GPIO, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, I_LEAK_ADC_PIN);
    gpio_mode_set(ACIN_I_ADC_GPIO, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ACIN_I_ADC_PIN);
    gpio_mode_set(ACIN_ADC_GPIO, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ACIN_ADC_PIN);
    //USART
    /* connect port to USARTx_Tx */
    gpio_af_set(TX0_GPIO, GPIO_AF_1, TX0_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(RX0_GPIO, GPIO_AF_1, RX0_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(TX0_GPIO, GPIO_MODE_AF, GPIO_PUPD_PULLUP, TX0_PIN);
    gpio_output_options_set(TX0_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, TX0_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(RX0_GPIO, GPIO_MODE_AF, GPIO_PUPD_PULLUP, RX0_PIN);
    gpio_output_options_set(RX0_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, RX0_PIN);

    //timer
    gpio_mode_set(TIMER2_CH1_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, TIMER2_CH1_PIN);
    gpio_output_options_set(TIMER2_CH1_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,TIMER2_CH1_PIN);
    gpio_af_set(TIMER2_CH1_GPIO, GPIO_AF_1, TIMER2_CH1_PIN);    
}

