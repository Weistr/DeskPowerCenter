#include "main.h"
#include "task.h"
#include "gpio.h"
#include "systic.h"
#include "led.h"
#include "cmsis_delay.h"
#include "adc.h"
#include "dma.h"
#include "uart.h"
#include "timer.h"
uint32_t debval[8];
void basicTask()
{
    led_sta_update_20ms();
    //debval[0] = adc_transform_softWare();

    //usart_dma_tx_send(USART0,usart0TxBuffer,3);
    debval[1] = timer_counter_read(TIMER2);
    debval[2] = timer_flag_get(TIMER2, TIMER_FLAG_CH1);
    //timer_flag_clear(TIMER2, TIMER_FLAG_CH1);
    usartx_readAll_interrupt_flagSta(USART0,&usart0_interrupt_flagSta);
    usartx_readAll_flagSta(USART0,&usart0_flagSta);
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, debval[4]);
    
}

TASK_COMPONENTS Task_Comps[]=
{
//状态  计数  周期  函数
	{0, 20, 20, basicTask},				/* task 1 Period： 2ms*/
//	{0, 500, 500, task_B},					/* task 5 Period： 500ms */
//	{0, 500, 500, task_C},					/* task 6 Period： 500ms */
//	{0, 500, 500, task_D},					/* task 7 Period： 500ms */
//	{0, 500, 500, task_E},					/* task 8 Period： 500ms */

	/* Add new task here */
};
uint8_t Tasks_Max = sizeof(Task_Comps)/sizeof(Task_Comps[0]);


void main()
{
    systick_config();
    cmsis_delay_init();
    gpioConfig();
    adcConfig();
    dmaConfig();
    uartConfig();
    // //使能时钟
    // rcu_periph_clock_enable(RCU_GPIOA);
    // //使能定时器14时钟
    // rcu_periph_clock_enable(RCU_TIMER2);

    // //GPIO复用模式设置--PA2-TIMER14_CH0
    // gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    // //输出类型设置
    // gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);
    // //复用模式0
    // gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_7);
    // //定时器初始化参数结构体
    // timer_parameter_struct timer_initpara;
    // //复位定时器14
    // timer_deinit(TIMER2);

    // //初始化定时器结构体参数
    // timer_struct_para_init(&timer_initpara);
    // timer_initpara.prescaler         = 71;                                 //预分频器参数
    // timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;                  //边沿对齐
    // timer_initpara.counterdirection  = TIMER_COUNTER_UP;                    //向上计数
    // timer_initpara.period            = 999;                              	//周期
    // timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;                    //时钟分频
    // timer_initpara.repetitioncounter = 0;                                   //重装载值
    // timer_init(TIMER2, &timer_initpara);
    // //定时器输出参数结构体
    // timer_oc_parameter_struct timer_ocinitpara;
    // //初始化定时器通道输出参数结构体
    // timer_channel_output_struct_para_init(&timer_ocinitpara);

    // timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;			//输出状态，主输出通道开启
    // timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;			//互补输出状态关闭
    // timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;		//输出极性为高
    // timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;	//互补输出极性为高
    // timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;	//空闲状态通道输出低
    // timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;	//空闲状态互补通道输出低
    // //通道输出配置
    // timer_channel_output_config(TIMER2, TIMER_CH_1, &timer_ocinitpara);
    // //输出比较值
    // timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 500);
    // //定时器通道输出模式设置
    // timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    // //影子模式输出关闭
    // timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
    // //使能自动重装载
    // timer_auto_reload_shadow_enable(TIMER2);
    // //配置定时器为主要输出函数，所有通道使能
    // timer_primary_output_config(TIMER2, ENABLE);

    // //使能定时器
    // timer_enable(TIMER2);
    timerConfig();
    while (1)
    {

        Task_Pro_Handler_Callback();
    }
}






