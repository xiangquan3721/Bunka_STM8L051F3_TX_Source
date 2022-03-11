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
	RF_STATE_IDLE = 0,  //����
    RF_STATE_RX_START,  //��������״̬��ʹ�ܶ� FIFO�����н���
    RF_STATE_RX_WAIT,   //���յȴ�״̬����ͣ����������ж�
    RF_STATE_RX_DONE,   //�������״̬���� FIFO����鲢����ж�
    RF_STATE_RX_TIMEOUT,//���ճ�ʱ״̬����оƬ�˳�����
    RF_STATE_TX_START,  //��������״̬����д FIFO ���ݣ����뷢��
    RF_STATE_TX_WAIT,   //����ȴ�״̬����ͣ��ⷢ������ж�
    RF_STATE_TX_DONE,   //�������״̬����鲢����ж�
    RF_STATE_TX_TIMEOUT,//���䳬ʱ״̬����оƬ�˳�����
    RF_STATE_ERROR,     //����״̬��оƬ�޷�������ջ��䣬��оƬ��������λ������������
} EnumRFStatus;

/* RF process function results */
typedef enum {
    RF_IDLE = 0,    //оƬ���У������������ջ��߷���
    RF_BUSY,        //оƬæµ����ǰ���ڷ�����߽�������
    RF_RX_DONE,     //оƬ������ɣ� �ϲ�ɴ�����������
    RF_RX_TIMEOUT,  //оƬ���ճ�ʱ
    RF_TX_DONE,     //оƬ�������
    RF_TX_TIMEOUT,  //оƬ���䳬ʱ
    RF_ERROR,       //оƬ���ջ��߷������
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