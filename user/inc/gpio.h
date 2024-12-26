#ifndef __GPIO_H__
#define __GPIO_H__

#include "REG_MA82G5Bxx.H"
#include "Type.h"
#include "API_Macro_MA82G5Bxx.H"
#include "API_Uart_BRGRL_MA82G5Bxx.H"
#include "timer.h"
#include "ram.h"
#include "ML7345.h"


#define ML7345_RESETN       P34
#define PIN_test_mode       P25
#define PIN_LED             P27
#define PIN_TX_LED          P27
#define PIN_KEY_OPEN        P12
#define PIN_KEY_STOP        P11
#define PIN_KEY_CLOSE       P25
#define PIN_KEY_LOGIN       P21
#define PIN_POWER_CONTROL   P40
#define ML7345D_POWER       P35
#define PIN_KEY_VENT        1

extern void Init_Port(void);
extern void Init_Interrupt(void); 
extern u8 key_scan(void);
void gpio_dc_test(void);
void SpiGpio_Init(void);
void SpiGpio_UnInit(void);


#endif
