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
 * @file    radio.h
 * @brief   Generic radio handlers
 *
 * @version 1.2
 * @date    Jul 17 2017
 * @author  CMOSTEK R@D
 */

#ifndef __RADIO_H
#define __RADIO_H

#include "cmt2300a.h"
#include "timer.h"


#ifdef __cplusplus
extern "C" {
#endif

/* RF state machine */
typedef enum {
	RF_STATE_IDLE = 0,  //空闲
    RF_STATE_RX_START,  //接收启动状态，使能读 FIFO，进行接收
    RF_STATE_RX_WAIT,   //接收等待状态，不停检测接收完成中断
    RF_STATE_RX_DONE,   //接收完成状态，读 FIFO，检查并清除中断
    RF_STATE_RX_TIMEOUT,//接收超时状态，让芯片退出接收
    RF_STATE_TX_START,  //发射启动状态，填写 FIFO 数据，进入发射
    RF_STATE_TX_WAIT,   //发射等待状态，不停检测发射完成中断
    RF_STATE_TX_DONE,   //发射完成状态，检查并清除中断
    RF_STATE_TX_TIMEOUT,//发射超时状态，让芯片退出发射
    RF_STATE_ERROR,     //错误状态，芯片无法进入接收或发射，对芯片进行软复位，并重新配置
} EnumRFStatus;

/* RF process function results */
typedef enum {
    RF_IDLE = 0,    //芯片空闲，可让其进入接收或者发射
    RF_BUSY,        //芯片忙碌，当前正在发射或者接收数据
    RF_RX_DONE,     //芯片接收完成， 上层可处理接收数据
    RF_RX_TIMEOUT,  //芯片接收超时
    RF_TX_DONE,     //芯片发射完成
    RF_TX_TIMEOUT,  //芯片发射超时
    RF_ERROR,       //芯片接收或者发射错误
} EnumRFResult;

//#define ENABLE_ANTENNA_SWITCH

void RF_Init(void);
void RF_Config(void);

void RF_SetStatus(EnumRFStatus nStatus);
EnumRFStatus RF_GetStatus(void);
u8 RF_GetInterruptFlags(void);

void RF_StartRx(u8 buf[], u16 len, u32 timeout);
void RF_StartTx(u8 buf[], u16 len, u32 timeout);

EnumRFResult RF_Process(void);

void RF_Init_TestMode(void);

#ifdef __cplusplus
}
#endif

#endif
