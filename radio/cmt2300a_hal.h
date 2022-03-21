/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, CMOSTEK SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * Copyright (C) CMOSTEK SZ.
 */

/*!
 * @file    cmt2300a_hal.h
 * @brief   CMT2300A hardware abstraction layer
 *
 * @version 1.2
 * @date    Jul 17 2017
 * @author  CMOSTEK R@D
 */

#ifndef __CMT2300A_HAL_H
#define __CMT2300A_HAL_H

#include "cmt2300a_spi.h"



/*如果需要将 Demo 程序移植到其他 MCU 平台，需要修改 cmt2300a_hal.h 中的一些宏定义*/
/* ************************************************************************
*  The following need to be modified by user
*  ************************************************************************ */
#define CMT2300A_SetGpio1In()           {PORT_SetP3InputOnly(BIT3);}
#define CMT2300A_SetGpio2In()           {PORT_SetP3InputOnly(BIT2);}
#define CMT2300A_SetGpio3In()           {PORT_SetP3InputOnly(BIT4);}
#define CMT2300A_SetGpio1Out()          {PORT_SetP3PushPull(BIT3);}
#define CMT2300A_SetGpio2Out()          {PORT_SetP3PushPull(BIT2);}
#define CMT2300A_SetGpio3Out()          {PORT_SetP3PushPull(BIT4);}
#define CMT2300A_ReadGpio1()            P33
#define CMT2300A_ReadGpio2()            P32
#define CMT2300A_ReadGpio3()            P34
#define CMT2300A_Gpio1            		P33
#define CMT2300A_Gpio2            		P32
#define CMT2300A_Gpio3           			P34
#define CMT2300A_POWER       					P35
#define CMT2300A_DelayMs(ms)            system_delay_ms(ms)
#define CMT2300A_GetTickCount()         g_nSysTickCount
#define dd_set_CMT2300A_Power_on()       {if(CMT2300A_POWER == FG_NOT_allow_out){CMT2300A_POWER = FG_allow_out;delay_ms(2);}}
#define dd_set_CMT2300A_Power_on_Init()       {if(CMT2300A_POWER == FG_NOT_allow_out){CMT2300A_POWER = FG_allow_out;delay_ms(2);}}
/* ************************************************************************ */

void CMT2300A_InitGpio(void);

u8 CMT2300A_ReadReg(u8 addr);
void CMT2300A_WriteReg(u8 addr, u8 dat);

void CMT2300A_ReadFifo(u8 buf[], u16 len);
void CMT2300A_WriteFifo(const u8 buf[], u16 len);



#endif
