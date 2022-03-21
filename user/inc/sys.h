#ifndef __SYS_H__
#define __SYS_H__


#include "REG_MA82G5Bxx.H"
#include "Type.h"
#include "API_Macro_MA82G5Bxx.H"
#include "API_Uart_BRGRL_MA82G5Bxx.H"
#include "gpio.h"
#include "timer.h"


/*************************************************
����ϵͳʱ��SysClk (MAX.25MHz)
��ѡ: 
	11059200,12000000,
	22118400,24000000,
*************************************************/
#define MCU_SYSCLK		3000000
/*************************************************/
/*************************************************
����CPUʱ�� CpuClk (MAX.25MHz)
	1) CpuCLK=SysCLK
	2) CpuClk=SysClk/2
*************************************************/
#define MCU_CPUCLK		(MCU_SYSCLK)
//#define MCU_CPUCLK		(MCU_SYSCLK/2)





void Init_Clock(void);
void Init_WDT(void);
void ClearWDT(void);

#endif
