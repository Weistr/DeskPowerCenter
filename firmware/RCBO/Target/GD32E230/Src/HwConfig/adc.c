#include "adc.h"
#include "cmsis_delay.h"

uint16_t adcRes[3]={0} ;
void adcConfig()
{

    adc_deinit();
    rcu_periph_clock_enable(RCU_ADC);
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);


    //DMA请求使能
    adc_dma_mode_enable();
    //使能内部16(ADCIN16,temp),17(ADCIN17,Vrefint)通道，
    adc_tempsensor_vrefint_enable();
    //扫描模式，除此之外还有单次模式，连续模式，间断模式
    adc_special_function_config(ADC_SCAN_MODE,ENABLE);
    //数据对齐
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    //常规序列配置(E230只有常规序列)，扫描模式；设置一个序列总共几个通道转换
    adc_channel_length_config(ADC_REGULAR_CHANNEL,3);
    //设置转换顺序
    adc_regular_channel_config(0,I_LEAK_ADC_CHANNEL,ADC_SAMPLETIME_71POINT5);
    adc_regular_channel_config(1,ACIN_I_ADC_CHANNEL,ADC_SAMPLETIME_71POINT5);
    adc_regular_channel_config(2,ACIN_ADC_CHANNEL,ADC_SAMPLETIME_71POINT5);
    //使能/失能ADC外部触发
    adc_external_trigger_config(ADC_REGULAR_CHANNEL,DISABLE);
    //选择外部触发源
    //adc_external_trigger_source_config(ADC_EXTTRIG_REGULAR_T0_CH0);
    //软件触发常规序列转换开始, 调用该方法后会开启转换!
    //adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    adc_flag_clear(ADC_FLAG_STRC);////常规序列转换开始时硬件置位。软件写0清除。
    adc_flag_clear(ADC_FLAG_EOC);//软件写0或读ADC_RDATA寄存器清除。
    
    //该位从‘0’变成‘1’将在稳定时间结束后唤醒ADC。
    //当该位被置位以后，不改变寄存器的其他位仅仅对该位写‘1’， 将开启转换。    
    adc_enable();
    cmsis_delay_ms(5);
    //校准ADC
    adc_calibration_enable();
    //使能ADC中断
    adc_interrupt_enable(ADC_INT_EOC);
    nvic_irq_enable(ADC_CMP_IRQn,0x01U);
}

//软件操作ADC转换，调用后开始转换，不会阻塞，再次调用时会检查是否转换完成并返回结果
uint16_t adc_transform_softWare()
{
    uint16_t adcres = 0;
    if (adc_flag_get(ADC_FLAG_STRC) == RESET)//常规序列转换开始时硬件置位。软件写0清除。
    {
        adc_software_trigger_enable(ADC_REGULAR_CHANNEL);//启动ADC转换
        if(adc_flag_get(ADC_FLAG_EOC) == SET)
        {
            adcres = adc_regular_data_read();
            adc_flag_clear(ADC_FLAG_STRC);
            return adcres;
        }
        return 0;
    }
    else
    {
        return 0;//正在转换
    }
}
void ADC_CMP_IRQHandler(void)
{
    adc_interrupt_flag_clear(ADC_INT_FLAG_EOC);
    adc_flag_clear(ADC_FLAG_STRC);////常规序列转换开始时硬件置位。软件写0清除。
}