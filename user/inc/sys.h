#ifndef __SYS_H__
#define __SYS_H__

#include "gpio_defs.h"
#include "iostm8l151g4.h"

typedef union{
    u8  flag_byte;
    struct{
        u8 flag_bit0 :1;
        u8 flag_bit1 :1;
        u8 flag_bit2 :1;
        u8 flag_bit3 :1;
        u8 flag_bit4 :1;
        u8 flag_bit5 :1;
        u8 flag_bit6 :1;
        u8 flag_bit7 :1;
    }bit;
}cmt_flag;









void SysClock_Init(void);
void WDT_init(void);
void ClearWDT(void);
void GPIO_Pin_Init(void);


#endif