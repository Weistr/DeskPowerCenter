#include "uart.h"
#include <stddef.h>  // 添加 NULL 定义
#include "dma.h"
#include "main.h"
uint8_t USART0_FLAG_BSY = 0;
uint8_t USART0_INT_FLAG_IDLE = 0;


uint8_t usart0TxBuffer[usart0TxBufferSize] = {0,1,2,3};
uint8_t usart0RxBuffer[usart0RxBufferSize] = {0};


usart_interrupt_flagSta_Typedef usart0_interrupt_flagSta={0};
usart_flagSta_Typedef usart0_flagSta={0};

/**
 * @brief 读取指定 USART 的所有中断标志状态
 * @param usart_periph: USART 外设地址 (USART0, USART1)
 * @param flag_sta: 指向 usart_interrupt_flagSta_Typedef 结构体的指针，用于存储标志状态
 * @retval None
 */
void usartx_readAll_interrupt_flagSta(uint32_t usart_periph, usart_interrupt_flagSta_Typedef *flag_sta)
{
    if (flag_sta == NULL) {
        return;
    }
    
    // 使用 usart_interrupt_flag_get 读取每个中断标志
    flag_sta->USART_INT_FLAG_EB = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_EB) == SET);
    flag_sta->USART_INT_FLAG_RT = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_RT) == SET);
    flag_sta->USART_INT_FLAG_AM = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_AM) == SET);
    flag_sta->USART_INT_FLAG_PERR = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_PERR) == SET);
    flag_sta->USART_INT_FLAG_TBE = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_TBE) == SET);
    flag_sta->USART_INT_FLAG_TC = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_TC) == SET);
    flag_sta->USART_INT_FLAG_RBNE = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_RBNE) == SET);
    flag_sta->USART_INT_FLAG_RBNE_ORERR = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_RBNE_ORERR) == SET);
    flag_sta->USART_INT_FLAG_IDLE = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_IDLE) == SET);
    flag_sta->USART_INT_FLAG_LBD = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_LBD) == SET);
    flag_sta->USART_INT_FLAG_WU = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_WU) == SET);
    flag_sta->USART_INT_FLAG_CTS = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_CTS) == SET);
    flag_sta->USART_INT_FLAG_ERR_NERR = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_ERR_NERR) == SET);
    flag_sta->USART_INT_FLAG_ERR_ORERR = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_ERR_ORERR) == SET);
    flag_sta->USART_INT_FLAG_ERR_FERR = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_ERR_FERR) == SET);
    flag_sta->USART_INT_FLAG_RFF = (usart_interrupt_flag_get(usart_periph, USART_INT_FLAG_RFF) == SET);
}

/**
 * @brief 读取指定 USART 的所有标志状态
 * @param usart_periph: USART 外设地址 (USART0, USART1)
 * @param flag_sta: 指向 usart_flagSta_Typedef 结构体的指针，用于存储标志状态
 * @retval None
 */
void usartx_readAll_flagSta(uint32_t usart_periph, usart_flagSta_Typedef *flag_sta)
{
    if (flag_sta == NULL) {
        return;
    }
    
    // 使用 usart_flag_get 读取每个标志
    flag_sta->USART_FLAG_PERR = (usart_flag_get(usart_periph, USART_FLAG_PERR) == SET);
    flag_sta->USART_FLAG_FERR = (usart_flag_get(usart_periph, USART_FLAG_FERR) == SET);
    flag_sta->USART_FLAG_NERR = (usart_flag_get(usart_periph, USART_FLAG_NERR) == SET);
    flag_sta->USART_FLAG_ORERR = (usart_flag_get(usart_periph, USART_FLAG_ORERR) == SET);
    flag_sta->USART_FLAG_IDLE = (usart_flag_get(usart_periph, USART_FLAG_IDLE) == SET);
    flag_sta->USART_FLAG_RBNE = (usart_flag_get(usart_periph, USART_FLAG_RBNE) == SET);
    flag_sta->USART_FLAG_TC = (usart_flag_get(usart_periph, USART_FLAG_TC) == SET);
    flag_sta->USART_FLAG_TBE = (usart_flag_get(usart_periph, USART_FLAG_TBE) == SET);
    flag_sta->USART_FLAG_LBD = (usart_flag_get(usart_periph, USART_FLAG_LBD) == SET);
    flag_sta->USART_FLAG_CTSF = (usart_flag_get(usart_periph, USART_FLAG_CTSF) == SET);
    flag_sta->USART_FLAG_CTS = (usart_flag_get(usart_periph, USART_FLAG_CTS) == SET);
    flag_sta->USART_FLAG_RT = (usart_flag_get(usart_periph, USART_FLAG_RT) == SET);
    flag_sta->USART_FLAG_EB = (usart_flag_get(usart_periph, USART_FLAG_EB) == SET);
    flag_sta->USART_FLAG_BSY = (usart_flag_get(usart_periph, USART_FLAG_BSY) == SET);
    flag_sta->USART_FLAG_AM = (usart_flag_get(usart_periph, USART_FLAG_AM) == SET);
    flag_sta->USART_FLAG_SB = (usart_flag_get(usart_periph, USART_FLAG_SB) == SET);
    flag_sta->USART_FLAG_RWU = (usart_flag_get(usart_periph, USART_FLAG_RWU) == SET);
    flag_sta->USART_FLAG_WU = (usart_flag_get(usart_periph, USART_FLAG_WU) == SET);
    flag_sta->USART_FLAG_TEA = (usart_flag_get(usart_periph, USART_FLAG_TEA) == SET);
    flag_sta->USART_FLAG_REA = (usart_flag_get(usart_periph, USART_FLAG_REA) == SET);
    flag_sta->USART_FLAG_EPERR = (usart_flag_get(usart_periph, USART_FLAG_EPERR) == SET);
    flag_sta->USART_FLAG_RFE = (usart_flag_get(usart_periph, USART_FLAG_RFE) == SET);
    flag_sta->USART_FLAG_RFF = (usart_flag_get(usart_periph, USART_FLAG_RFF) == SET);
    flag_sta->USART_FLAG_RFFINT = (usart_flag_get(usart_periph, USART_FLAG_RFFINT) == SET);
}

void uartConfig()
{
    rcu_periph_clock_enable(RCU_USART0);
    usart_deinit(USART0);
    usart_baudrate_set(USART0,115200);
    //奇偶校验：无
    usart_parity_config(USART0,USART_PM_NONE);
    //数据宽度：8bit
    usart_word_length_set(USART0,USART_WL_8BIT);
    //停止位：1
    usart_stop_bit_set(USART0,USART_STB_1BIT);

    //先传低位/LSB
    usart_data_first_config(USART0,USART_MSBF_LSB);
    //不反相电平
    //usart_invert_config(USART0,USART_DINV_DISABLE);
    //16倍过采样
    usart_oversample_config(USART0,USART_OVSMOD_16);
    //采样3次
    usart_sample_bit_config(USART0,USART_OSB_3BIT);
    //使能接收超时
    usart_receiver_timeout_enable(USART0);
    //
    //标准模式下，如果在最后一个字节接收后，在RT规定的时长内(n个波特时钟的时长)，没有检测到新的起始位， RTF标志被置位。
    usart_receiver_timeout_threshold_config(USART0,96000);//9600下10个字节
    //配置USART节点地址
    //在多处理器通信并且静默模式或者深度睡眠模式期间，这些位用来唤醒进行地址匹配
    //的检测。接收到的最高位为1的数据帧将和这些位进行比较。当ADDM位被清零时，
    //仅仅ADDR[3:0]被用来比较。
    //在正常的接收期间，这些位也用来进行字符检测。所有接收到的字符（8位）与
    //ADDR[7:0]的值进行比较，如果匹配，AMF标志将被置位。
    //当接收器（REN=1）和USART（UEN=1） 被使能时，该位域不能被改写。
    usart_address_config(USART0,0xAA);
    //选择为4位地址或全地址匹配
    usart_address_detection_mode_config(USART0,USART_ADDM_FULLBIT);
    //使能静默模式
    //usart_mute_mode_enable(USART0);
    //配置静默模式唤醒方式
    //usart_mute_mode_wakeup_config(USART0,USART_WM_ADDR);
    //LIN模式
    //usart_lin_mode_enable();
    //Lin模式配置
    //usart_lin_break_detection_length_config(USART0,USART_LBLEN_11B);
    //半双工模式，适用单线通信
    //usart_halfduplex_enable(USART0);
    //使能USART时钟CK引脚
    //usart_clock_enable(USART0);
    //同步模式时钟配置
    //usart_synchronous_clock_config(USART0,USART_CLEN_EN,USART_CPH_2CK,USART_CPL_HIGH);
    //智能卡模式 (ISO7816-3)配置 
    //usart_guard_time_config(USART0,0xFF);
    //
    //usart_smartcard_mode_enable(USART0);
    //
    //usart_smartcard_mode_nack_enable(USART0);
    //
    //usart_smartcard_mode_early_nack_enable(USART0);
    //
    //usart_smartcard_autoretry_config();
    //
    //usart_block_length_config();

    //串行红外（IrDA SIR）编解码功能
    //usart_irda_mode_enable();
    //configure the peripheral clock prescaler in USART IrDA low-power or SmartCard mode
    //usart_prescaler_config()
    //
    //usart_irda_lowpower_config

    //使能串口硬件RTS功能
    //usart_hardware_flow_rts_config(USART0,USART_RTS_ENABLE);
    //使能串口硬件CTS功能
    //usart_hardware_flow_cts_config(USART0,USART_CTS_ENABLE);

    //硬件流控制兼容性模式
    //usart_hardware_flow_coherence_config(USART0,USART_HCM_EN);

    //驱动使能模式
    //用户使能该位以后，可以通过DE信号对外部收发器进行控制。DE信号是从RTS 管
    //脚输出的。
    //0：禁能DE功能
    //1：使能DE功能
    //usart_rs485_driver_enable(USART0);

    //驱动使能置位时间
    //这些数字用来定义DE （驱动使能）信号的置位与第一个字节的起始位之间的时间间
    //隔。它以采样时间为单位 （1/8或1/16位时间），可以通过OVSMOD位来配置。
    //usart_driver_assertime_config(USART0,0x0F);

    //驱动使能低时间
    //这些位用来定义一个发送信息最后一个字节的停止位与置低DE（驱动使能）信
    //号之间的时间间隔。它以采样时间为单位（1/8或1/16位时间），可以通过OVSMOD位来配置。
    //usart_driver_assertime_config(USART0,0x0F);
   
    //驱动使能的极性选择模式(DE信号)
    //usart_depolarity_config(USART0,USART_DEP_LOW);


    //在接收错误时禁止DMA,DDRE值1
    //1：在接收错误的情况下，DMA请求会被屏蔽，直到相应的标志位被清0。RBNE标
    //志和相应的错误标志位会被置位。软件在清除错误标志前，必须首先失能DMA接收
    //（DMAR = 0）或清RBNE。
    //0：在发生接收错误的情况下，不禁用DMA。所有的错误数据不会产生DMA请求，
    //以确保错误的数据不会被传输，但是下一个接收到的正确的数据会被传输。在发送
    //接收错误时，RBNE位保持0以阻止过载错误，但是相应错误标志位会被置位。this模式可用于智能卡模式。
    //usart_reception_error_dma_disable(USART0);


    //enable USART to wakeup the mcu from deep-sleep mode
    //usart_wakeup_enable(USART0);
    //串口以何种方式唤醒MCU
    //usart_wakeup_mode_config(USART0,USART_WUM_ADDR);

    //使能接收FIFO
    //可以避免当CPU无法迅速响应
    //RBNE中断时，发生过载错误。接收FIFO和接收缓存区可储存多至5帧的数据。若接收FIFO满，
    //RFFINT位将被置位。如果RFFIE被置位，将产生中断。
    //如果软件在响应RBNE中断时读数据接收缓冲区，在响应开始时，RBNEIE位应清0。当所有接
    //收的数据被读出后，RBNEIE位应置位。在读出接收的数据前，PERR，NERR，FERR，EBF
    //都应被清0。
    usart_receive_fifo_enable(USART0);

    //读取FIFO中数据数目
    //fifo.num = usart_receive_fifo_counter_number(USART0);
    //读取标志位
    USART0_FLAG_BSY = usart_flag_get(USART0,USART_FLAG_BSY);
    //清除标志位
    usart_flag_get(USART0,USART_FLAG_RT);

    // USART_INT_IDLE: idle interrupt
    //USART_INT_RBNE: 当接收到一个数据帧，USART_STAT寄存器中的RBNE置位,对USART_RDATA寄存器的一个读操作都可以清除RBNE位,包括DMA
    //USART_INT_TC:  发送完一帧数据发生中断/或者发送完一组
    //USART_INT_PERR: 奇偶校验错误
    //USART_INT_ERR: error interrupt enable
    usart_interrupt_enable(USART0, USART_INT_TC);
    usart_interrupt_enable(USART0, USART_INT_RT);
    //进入静默模式
    //usart_command_enable(USART_CMD_MMCMD);

    //清除标志位
    usart_interrupt_flag_clear(USART0,USART_INT_FLAG_TC);

    //使能串口
    usart_enable(USART0);

    //使能USART发送器 TEN置位
    usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);

    //使能USART接收器 REN置位
    usart_receive_config(USART0,USART_RECEIVE_ENABLE);    

    //使能DMA接收
    //DENR位
    usart_dma_receive_config(USART0,USART_DENR_ENABLE);

    //使能DMA发送
    usart_dma_transmit_config(USART0,USART_DENT_ENABLE);

    //清除标志位
    usart_interrupt_flag_clear(USART0,USART_INT_FLAG_TC);

    //使能串口中断
    nvic_irq_enable(USART0_IRQn, 2);
}


void usartTransmit_1BYTE(uint8_t byte)
{
    usart_data_transmit(USART0,byte);
}

uint8_t usartRecive_1BYTE(void)
{
    return usart_data_receive(USART0);
}

void usart_dma_tx_send(uint32_t usartx,uint8_t* txbuffer,uint16_t txlen)
{
    dma_channel_disable(DMA_CH_USART0_TX);
    dma_transfer_number_config(DMA_CH_USART0_TX,(uint32_t)txlen);
    dma_memory_address_config(DMA_CH_USART0_TX,(uint32_t)txbuffer);
    dma_channel_enable(DMA_CH_USART0_TX);
    usart_interrupt_flag_clear(usartx,USART_INT_FLAG_TC);
    usart_dma_transmit_config(usartx,USART_DENT_ENABLE);
}


void USART0_IRQHandler(void)
{
    usartx_readAll_interrupt_flagSta(USART0,&usart0_interrupt_flagSta);
    usartx_readAll_flagSta(USART0,&usart0_flagSta);

    if(usart0_interrupt_flagSta.USART_INT_FLAG_RT == 1)
    {
        usart_interrupt_flag_clear(USART0,USART_INT_FLAG_RT);
        debval[3] = dma_transfer_number_get(DMA_CH_USART0_RX);
    }
    else if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TC)){
        /* transmit data */
        usart_interrupt_flag_clear(USART0,USART_INT_FLAG_TC);
        
    }
}
