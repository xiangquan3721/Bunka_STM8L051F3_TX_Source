#ifndef __TIMER_H__
#define __TIMER_H__

#include "gpio_defs.h"

#define _NOP() asm(" nop ")
#define _EI() asm(" rim ")
#define _DI() asm(" sim ")





extern volatile u32 g_nSysTickCount;
extern u16 time_rx_led;
void led_init(void);
void TIM4_Init(void);
void TIM4_UPD_OVF(void);
void system_delay_ms(u32 nms);

#endif