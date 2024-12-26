#ifndef __ADC_H__
#define __ADC_H__

#include <Intrins.h>
#include <Absacc.h>

#include "REG_MA82G5Bxx.H"
#include "Type.h"
#include "API_Macro_MA82G5Bxx.H"
#include "API_Uart_BRGRL_MA82G5Bxx.H"
#include "ram.h"

void Init_Adc(void);
u16 Get_Adc_Value(void);
void AD_control(void);
void Adc_Start(void);
void Adc_Channel_Scan(u8 ch);
void Adc_Open(void);

#endif
