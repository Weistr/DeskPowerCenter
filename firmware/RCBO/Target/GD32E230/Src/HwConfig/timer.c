#include "timer.h"
#include "gd32e23x_rcu.h"
#include "main.h"

void timerConfig(void)
{
    /* 使能 TIMER0 时钟 */
    rcu_periph_clock_enable(RCU_TIMER2);
    
    /* 复位 TIMER0 */
    timer_deinit(TIMER2);
    
    /* 初始化 TIMER 参数结构体 */
    timer_parameter_struct timer_init_para;
    timer_struct_para_init(&timer_init_para);
    
    /* 配置 TIMER 基本参数 */
    timer_init_para.prescaler = 71;          /* 预分频值: 72MHz / (71+1) = 1MHz */
    //CTL0:00：无中央对齐计数模式(边沿对齐模式)。 DIR位指定了计数方向
    timer_init_para.alignedmode = TIMER_COUNTER_EDGE; 
    timer_init_para.counterdirection = TIMER_COUNTER_UP; /* 向上计数 */
    timer_init_para.period = 999;              /* 自动重装载值: 1000000Hz / (999+1) = 1000Hz */
    //CTL0: 时钟分频: 不分频 
    //通过软件配置CKDIV，规定定时器时钟(CK_TIMER) 与死区时间和数字滤波器采样
    //时钟(DTS)之间的分频系数。
    timer_init_para.clockdivision = TIMER_CKDIV_DIV1; 
    //TIMERx_CREP
    //这些位定义了更新事件的产生速率。重复计数器计数值减为0时产生更新事件。影
    //子寄存器的更新速率也会受这些位影响(前提是影子寄存器被使能)。
    timer_init_para.repetitioncounter = 0;     /* 重复计数器值 */
    
    /* 初始化 TIMER */
    timer_init(TIMER2, &timer_init_para);
    
    /* 使能自动重装载影子寄存器 */
    //更新事件发生时，相应的影子寄存器被装入预装载值
    timer_auto_reload_shadow_enable(TIMER2);
    
    /* 使能更新事件 */
    //0：更新事件使能. 更新事件发生时，相应的影子寄存器被装入预装载值，以下事件
    //均会产生更新事件：
    // UPG位被置1 
    // 计数器溢出/下溢
    // 复位模式产生的更新
    // 1：更新事件禁能.
    //timer_update_event_enable(TIMER2);
    
    /* 配置 TIMER 计数器对齐模式 */
    //timer_counter_alignment(TIMER0, TIMER_COUNTER_EDGE);
    
    /* 配置 TIMER 计数器方向 */
    //timer_counter_up_direction(TIMER0);
    //timer_counter_down_direction(TIMER0);
    
    /* 配置 TIMER 预分频器 */
    //timer_prescaler_config(TIMER0, 7199, TIMER_PSC_RELOAD_NOW);
    
    /* 配置 TIMER 重复寄存器值 */
    //timer_repetition_value_config(TIMER0, 0);
    
    /* 配置 TIMER 自动重装载寄存器值 */
    //timer_autoreload_value_config(TIMER0, 999);
    
    /* 配置 TIMER 计数器寄存器值 */
    //timer_counter_value_config(TIMER0, 0);
    
    /* 读取 TIMER 计数器值 */
    //uint32_t counter_val = timer_counter_read(TIMER0);
    
    /* 读取 TIMER 预分频器值 */
    //uint16_t prescaler_val = timer_prescaler_read(TIMER0);
    
    /* 配置 TIMER 单脉冲模式 */
    //timer_single_pulse_mode_config(TIMER0, TIMER_SP_MODE_REPETITIVE);
    
    /* 配置 TIMER 更新源 */
    // 0：更新事件使能. 更新事件发生时，相应的影子寄存器被装入预装载值，以下事件
    // 均会产生更新事件：
    // UPG位被置1 
    // 计数器溢出/下溢
    // 复位模式产生的更新
    // 1：更新事件禁能.
    //timer_update_source_config(TIMER2, TIMER_UPDATE_SRC_GLOBAL);
    
    /* 配置 TIMER OCPRE 清除源选择 */
    //timer_ocpre_clear_source_config(TIMER0, TIMER_OCPRE_CLEAR_SOURCE_CLR);
    
    /* 使能 TIMER 中断 */
    //timer_interrupt_enable(TIMER0, TIMER_INT_UP);
    //timer_interrupt_enable(TIMER0, TIMER_INT_CH0);
    //timer_interrupt_enable(TIMER2, TIMER_INT_CH1);
    //timer_interrupt_enable(TIMER0, TIMER_INT_CH2);
    //timer_interrupt_enable(TIMER0, TIMER_INT_CH3);
    //timer_interrupt_enable(TIMER0, TIMER_INT_CMT);
    //timer_interrupt_enable(TIMER0, TIMER_INT_TRG);
    //timer_interrupt_enable(TIMER0, TIMER_INT_BRK);
    
    /* 禁用 TIMER 中断 */
    //timer_interrupt_disable(TIMER0, TIMER_INT_UP);
    
    /* 获取 TIMER 中断标志 */
    //FlagStatus int_flag = timer_interrupt_flag_get(TIMER0, TIMER_INT_FLAG_UP);
    
    /* 清除 TIMER 中断标志 */
    //timer_interrupt_flag_clear(TIMER0, TIMER_INT_FLAG_UP);
    
    /* 获取 TIMER 标志 */
    //debval[2] = timer_flag_get(TIMER2, TIMER_FLAG_CH1);
    
    /* 清除 TIMER 标志 */
    //timer_flag_clear(TIMER0, TIMER_FLAG_UP);
    
    /* 使能 TIMER DMA */
    //timer_dma_enable(TIMER0, TIMER_DMA_UPD);
    //timer_dma_enable(TIMER0, TIMER_DMA_CH0D);
    //timer_dma_enable(TIMER0, TIMER_DMA_CH1D);
    //timer_dma_enable(TIMER0, TIMER_DMA_CH2D);
    //timer_dma_enable(TIMER0, TIMER_DMA_CH3D);
    //timer_dma_enable(TIMER0, TIMER_DMA_CMTD);
    //timer_dma_enable(TIMER0, TIMER_DMA_TRGD);
    
    /* 禁用 TIMER DMA */
    //timer_dma_disable(TIMER0, TIMER_DMA_UPD);
    
    /* 通道 DMA 请求源选择 */
    //timer_channel_dma_request_source_select(TIMER0, TIMER_DMAREQUEST_CHANNELEVENT);
    
    /* 配置 TIMER DMA 传输 */
    //timer_dma_transfer_config(TIMER0, TIMER_DMACFG_DMATA_CTL0, TIMER_DMACFG_DMATC_1TRANSFER);
    
    /* 软件生成事件 */
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_UPG);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CH0G);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CH1G);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CH2G);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CH3G);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_CMTG);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_TRGG);
    //timer_event_software_generate(TIMER0, TIMER_EVENT_SRC_BRKG);
    
    /* 初始化 TIMER 刹车参数结构体 */
    //timer_break_parameter_struct break_para;
    //timer_break_struct_para_init(&break_para);
    
    /* 配置 TIMER 刹车功能 */
    // break_para.runoffstate = TIMER_ROS_STATE_DISABLE;
    // break_para.ideloffstate = TIMER_IOS_STATE_DISABLE;
    // break_para.deadtime = 0;
    // break_para.breakpolarity = TIMER_BREAK_POLARITY_LOW;
    // break_para.outputautostate = TIMER_OUTAUTO_DISABLE;
    // break_para.protectmode = TIMER_CCHP_PROT_OFF;
    // break_para.breakstate = TIMER_BREAK_DISABLE;
    //timer_break_config(TIMER0, &break_para);
    
    /* 使能 TIMER 刹车功能 */
    //timer_break_enable(TIMER0);
    
    /* 禁用 TIMER 刹车功能 */
    //timer_break_disable(TIMER0);
    
    /* 使能 TIMER 输出自动功能 */
    //timer_automatic_output_enable(TIMER0);
    
    /* 禁用 TIMER 输出自动功能 */
    //timer_automatic_output_disable(TIMER0);
    
    /* 配置 TIMER 主输出功能 */
    //timer_primary_output_config(TIMER0, ENABLE);
    
    /* 使能或禁用通道捕获/比较控制影子寄存器 */
    //timer_channel_control_shadow_config(TIMER0, ENABLE);
    
    /* 配置 TIMER 通道控制影子寄存器更新控制 */
    //timer_channel_control_shadow_update_config(TIMER0, TIMER_UPDATECTL_CCU);
    
    /* ========== PWM 配置 ========== */
    /* 初始化 TIMER 通道输出参数结构体 */
    timer_oc_parameter_struct oc_para;
    timer_channel_output_struct_para_init(&oc_para);
    
    /* 配置通道 1 PWM 输出 */
    oc_para.outputstate = TIMER_CCX_ENABLE;        /* 使能通道输出 */
    oc_para.outputnstate = TIMER_CCXN_DISABLE;     /* 禁用互补输出 （timer2无效） */
    oc_para.ocpolarity = TIMER_OC_POLARITY_HIGH;   /* 输出极性: 高电平有效 */
    oc_para.ocnpolarity = TIMER_OCN_POLARITY_HIGH; /* 互补输出极性: 高电平有效 timer2无效*/
    oc_para.ocidlestate = TIMER_OC_IDLE_STATE_LOW; /* 空闲状态: 低电平 timer2无效*/
    oc_para.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW; /* 互补空闲状态: 低电平 timer2无效*/
    /* 配置通道 2 输出功能 */
    timer_channel_output_config(TIMER2, TIMER_CH_1, &oc_para);
    
    /* 配置通道 2 输出比较模式为 PWM 模式 0 */
    timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    
    /* 配置通道 2 PWM 脉冲值 (占空比: 50%) */
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 500);
    
    /* 配置通道 2 输出影子功能 */
    timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
    
    /* 配置通道 2 输出快速功能 */
    //timer_channel_output_fast_config(TIMER2, TIMER_CH_1, TIMER_OC_FAST_DISABLE);
    
    /* 配置通道 2 输出清除功能 */
    //timer_channel_output_clear_config(TIMER2, TIMER_CH_1, TIMER_OC_CLEAR_DISABLE);
    
    /* 配置通道 2 输出极性 */
    //timer_channel_output_polarity_config(TIMER2, TIMER_CH_1, TIMER_OC_POLARITY_HIGH);
    
    /* 配置通道 2 互补输出极性 */
    //timer_channel_complementary_output_polarity_config(TIMER2, TIMER_CH_1, TIMER_OCN_POLARITY_HIGH);
    
    /* 配置通道 2 使能状态 */
    //timer_channel_output_state_config(TIMER2, TIMER_CH_1, TIMER_CCX_ENABLE);
    
    /* 配置通道 2 互补输出使能状态 */
    //timer_channel_complementary_output_state_config(TIMER2, TIMER_CH_1, TIMER_CCXN_DISABLE);
    

    /* ========== 输入捕获配置 ========== */
    /* 初始化 TIMER 通道输入参数结构体 */
    // timer_ic_parameter_struct ic_para;
    // timer_channel_input_struct_para_init(&ic_para);
    
    // /* 配置输入捕获参数 */
    // ic_para.icpolarity = TIMER_IC_POLARITY_RISING;     /* 上升沿捕获 */
    // ic_para.icselection = TIMER_IC_SELECTION_DIRECTTI; /* 直接输入 */
    // ic_para.icprescaler = TIMER_IC_PSC_DIV1;           /* 不分频 */
    // ic_para.icfilter = 0;                              /* 无滤波 */
    
    /* 配置输入捕获 (注释掉，需要时启用) */
    //timer_input_capture_config(TIMER0, TIMER_CH_0, &ic_para);
    
    /* 配置通道输入捕获预分频器值 */
    //timer_channel_input_capture_prescaler_config(TIMER0, TIMER_CH_0, TIMER_IC_PSC_DIV1);
    
    /* 读取通道捕获比较寄存器值 */
    //uint32_t capture_val = timer_channel_capture_value_register_read(TIMER0, TIMER_CH_0);
    
    /* 配置 TIMER 输入 PWM 捕获功能 */
    //timer_input_pwm_capture_config(TIMER0, TIMER_CH_0, &ic_para);
    
    /* ========== 霍尔传感器模式配置 ========== */
    /* 配置 TIMER 霍尔传感器模式 */
    //timer_hall_mode_config(TIMER0, TIMER_HALLINTERFACE_ENABLE);
    
    /* ========== 触发源配置 ========== */
    /* 选择 TIMER 输入触发源 */
    //timer_input_trigger_source_select(TIMER0, TIMER_SMCFG_TRGSEL_ITI0);
    
    /* 选择 TIMER 主模式输出触发源 */
    //timer_master_output_trigger_source_select(TIMER0, TIMER_TRI_OUT_SRC_UPDATE);
    
    /* 选择 TIMER 从模式 */
    //timer_slave_mode_select(TIMER0, TIMER_SLAVE_MODE_DISABLE);
    
    /* 配置 TIMER 主从模式 */
    //timer_master_slave_mode_config(TIMER0, TIMER_MASTER_SLAVE_MODE_DISABLE);
    
    /* ========== 外部触发配置 ========== */
    /* 配置 TIMER 外部触发输入 */
    //timer_external_trigger_config(TIMER0, TIMER_EXT_TRI_PSC_OFF, TIMER_ETP_RISING, 0);
    
    /* 配置 TIMER 正交解码器模式 */
    //timer_quadrature_decoder_mode_config(TIMER0, TIMER_QUAD_DECODER_MODE0, 
    //                                     TIMER_IC_POLARITY_RISING, TIMER_IC_POLARITY_RISING);
    
    /* ========== 时钟模式配置 ========== */
    /* 配置 TIMER 内部时钟模式 */
    //timer_internal_clock_config(TIMER2);
    
    /* 配置 TIMER 内部触发作为外部时钟输入 */
    //timer_internal_trigger_as_external_clock_config(TIMER0, TIMER_SMCFG_TRGSEL_ITI0);
    
    /* 配置 TIMER 外部触发作为外部时钟输入 */
    //timer_external_trigger_as_external_clock_config(TIMER0, TIMER_SMCFG_TRGSEL_CI0F_ED, 
    //                                                TIMER_IC_POLARITY_RISING, 0);
    
    /* 配置 TIMER 外部时钟模式0 */
    //timer_external_clock_mode0_config(TIMER0, TIMER_EXT_TRI_PSC_OFF, TIMER_ETP_RISING, 0);
    
    /* 配置 TIMER 外部时钟模式1 */
    //timer_external_clock_mode1_config(TIMER0, TIMER_EXT_TRI_PSC_OFF, TIMER_ETP_RISING, 0);
    
    /* 禁用 TIMER 外部时钟模式1 */
    //timer_external_clock_mode1_disable(TIMER0);
    
    /* ========== 通道重映射配置 ========== */
    /* 配置 TIMER 通道重映射功能 (仅 TIMER13) */
    //timer_channel_remap_config(TIMER13, TIMER13_CI0_RMP_GPIO);
    
    /* ========== 其他配置 ========== */
    /* 配置 TIMER 写 CHxVAL 寄存器选择 */
    //timer_write_chxval_register_config(TIMER0, TIMER_CHVSEL_DISABLE);
    
    /* 配置 TIMER 输出值选择 */
    //timer_output_value_selection_config(TIMER0, TIMER_OUTSEL_DISABLE);
    
    /* 使能 TIMER */
    timer_enable(TIMER2);
}
