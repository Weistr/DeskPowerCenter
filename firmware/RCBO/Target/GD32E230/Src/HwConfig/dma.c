#include "dma.h"
#include "adc.h"
#include "uart.h"



void dmaConfig()
{
    rcu_periph_clock_enable(RCU_DMA);
    dma_parameter_struct dmaConfigParm;
    //ADC DMA设置
    dma_deinit(DMA_CH0);//ADC
    dma_struct_para_init(&dmaConfigParm);//初始化结构体
    dmaConfigParm.direction = DMA_PERIPHERAL_TO_MEMORY;
    dmaConfigParm.memory_addr = (uint32_t)adcRes;
    dmaConfigParm.memory_width = DMA_MEMORY_WIDTH_16BIT;
    dmaConfigParm.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dmaConfigParm.number = 3;
    dmaConfigParm.periph_addr = (uint32_t)&(ADC_RDATA);
    dmaConfigParm.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dmaConfigParm.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dmaConfigParm.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH0,&dmaConfigParm);
    /* configure DMA mode */
    dma_circulation_enable(DMA_CH0);
    dma_memory_to_memory_disable(DMA_CH0);
    dma_channel_enable(DMA_CH0);    

    dma_deinit(DMA_CH_USART0_TX);
    dmaConfigParm.direction = DMA_MEMORY_TO_PERIPHERAL;
    dmaConfigParm.memory_addr = (uint32_t)usart0TxBuffer;
    dmaConfigParm.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dmaConfigParm.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dmaConfigParm.number = usart0TxBufferSize;
    dmaConfigParm.periph_addr = USART0_TDATA_ADDRESS;
    dmaConfigParm.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dmaConfigParm.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dmaConfigParm.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH_USART0_TX,&dmaConfigParm);
    /* configure DMA mode */
    dma_circulation_disable(DMA_CH_USART0_TX);
    dma_memory_to_memory_disable(DMA_CH_USART0_TX);
    /* enable DMA channel1 */
    dma_channel_enable(DMA_CH_USART0_TX);

    /* deinitialize DMA channel2 */
    dma_deinit(DMA_CH_USART0_RX);
    dmaConfigParm.direction = DMA_PERIPHERAL_TO_MEMORY;
    dmaConfigParm.memory_addr = (uint32_t)usart0RxBuffer;
    dmaConfigParm.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dmaConfigParm.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dmaConfigParm.number = usart0RxBufferSize;
    dmaConfigParm.periph_addr = USART0_RDATA_ADDRESS;
    dmaConfigParm.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dmaConfigParm.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dmaConfigParm.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH_USART0_RX, &dmaConfigParm);
    
    dma_circulation_disable(DMA_CH_USART0_RX);
    dma_memory_to_memory_disable(DMA_CH_USART0_RX);

    dma_channel_enable(DMA_CH_USART0_RX);
}
