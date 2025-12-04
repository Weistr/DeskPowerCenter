#ifndef _RCU_H
#define _RCU_H


//使用预定义方式配置时钟
/* select a system clock by uncommenting the following line */
//#define __SYSTEM_CLOCK_8M_HXTAL              (__HXTAL)
//#define __SYSTEM_CLOCK_8M_IRC8M              (__IRC8M)
#define __SYSTEM_CLOCK_72M_PLL_HXTAL         (uint32_t)(72000000)
//#define __SYSTEM_CLOCK_72M_PLL_IRC8M_DIV2    (uint32_t)(72000000)

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  (HXTAL_VALUE)
#define HXTAL_VALUE    ((uint32_t)12000000)
#endif /* high speed crystal oscillator value */

#define pll_preSet() (RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL6))
#endif // !_RCU_H
