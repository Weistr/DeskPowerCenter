#ifndef _UART_H
#define _UART_H

#include "gd32e23x_usart.h"
#include "stdbool.h"

#define usart0TxBufferSize 8
#define usart0RxBufferSize 8
#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define USART0_TDATA_ADDRESS      ((uint32_t)0x40013828)  
#define USART0_RDATA_ADDRESS      ((uint32_t)0x40013824)  
typedef struct 
{
    bool USART_INT_FLAG_EB;                // end of block interrupt and flag
    bool USART_INT_FLAG_RT;                // receiver timeout interrupt and flag
    bool USART_INT_FLAG_AM;                // address match interrupt and flag
    bool USART_INT_FLAG_PERR;              // 奇偶校验错误
    bool USART_INT_FLAG_TBE;               // transmitter buffer empty interrupt and flag
    bool USART_INT_FLAG_TC;                // 发送完一帧数据发生中断/或者发送完一组
    bool USART_INT_FLAG_RBNE;              // 当接收到一个数据帧，USART_STAT寄存器中的RBNE置位
    bool USART_INT_FLAG_RBNE_ORERR;        // read data buffer not empty interrupt and overrun error flag
    bool USART_INT_FLAG_IDLE;              // IDLE line detected interrupt and flag
    bool USART_INT_FLAG_LBD;               // LIN break detected interrupt and flag
    bool USART_INT_FLAG_WU;                // wakeup from deep-sleep mode interrupt and flag
    bool USART_INT_FLAG_CTS;               // CTS interrupt and flag
    bool USART_INT_FLAG_ERR_NERR;          // 噪声错误,电平采样不对
    bool USART_INT_FLAG_ERR_ORERR;         // error interrupt and overrun error
    bool USART_INT_FLAG_ERR_FERR;          // 如果在停止位传输过程中RX引脚为0，将产生帧错误
    bool USART_INT_FLAG_RFF;               // receive FIFO full interrupt and flag
} usart_interrupt_flagSta_Typedef;

typedef struct 
{
    bool USART_FLAG_PERR;          // parity error flag
    bool USART_FLAG_FERR;          // frame error flag
    bool USART_FLAG_NERR;          // noise error flag
    bool USART_FLAG_ORERR;         // overrun error
    bool USART_FLAG_IDLE;          // idle line detected flag
    bool USART_FLAG_RBNE;          // read data buffer not empty
    bool USART_FLAG_TC;            // transmission completed
    bool USART_FLAG_TBE;           // transmit data register empty
    bool USART_FLAG_LBD;           // LIN break detected flag
    bool USART_FLAG_CTSF;          // CTS change flag
    bool USART_FLAG_CTS;           // CTS level
    bool USART_FLAG_RT;            // receiver timeout flag
    bool USART_FLAG_EB;            // end of block flag
    bool USART_FLAG_BSY;           // busy flag
    bool USART_FLAG_AM;            // address match flag
    bool USART_FLAG_SB;            // send break flag
    bool USART_FLAG_RWU;           // receiver wakeup from mute mode
    bool USART_FLAG_WU;            // wakeup from deep-sleep mode flag
    bool USART_FLAG_TEA;           // transmit enable acknowledge flag
    bool USART_FLAG_REA;           // receive enable acknowledge flag
    bool USART_FLAG_EPERR;         // early parity error flag
    bool USART_FLAG_RFE;           // receive FIFO empty flag
    bool USART_FLAG_RFF;           // receive FIFO full flag
    bool USART_FLAG_RFFINT;        // receive FIFO full interrupt flag
} usart_flagSta_Typedef;

void uartConfig(void);
void usartTransmit_1BYTE(uint8_t byte);
uint8_t usartRecive_1BYTE(void);
void usartx_readAll_interrupt_flagSta(uint32_t usart_periph, usart_interrupt_flagSta_Typedef *flag_sta);
void usartx_readAll_flagSta(uint32_t usart_periph, usart_flagSta_Typedef *flag_sta);
void usart_dma_tx_send(uint32_t usartx,uint8_t* txbuffer,uint16_t txlen);


extern uint8_t usart0TxBuffer[usart0TxBufferSize];
extern uint8_t usart0RxBuffer[usart0RxBufferSize];
extern usart_interrupt_flagSta_Typedef usart0_interrupt_flagSta;
extern usart_flagSta_Typedef usart0_flagSta;
#endif /* MAIN_H */
