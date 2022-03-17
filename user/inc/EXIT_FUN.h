/***********************************************************************/
/*  FILE        :EXIT_FUN.h                                            */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#ifndef __EXIT_FUN_H__
#define __EXIT_FUN_H__

#include "gpio.h"		// 管脚定义
#include "Type.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "EXIT_FUN.h"
#include "ML7345.h"

void SendTxData(void);
void SetTxData(u8 count_set ,uni_rom_id ID_data_set,u8 Control_code_set);
u16 SetFixedLengthCode(u8 Data);
void EXTI_PORTA1(void);

#endif