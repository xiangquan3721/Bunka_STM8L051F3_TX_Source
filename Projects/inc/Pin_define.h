/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <stdio.h>
#include <pic.h>
/******************以下是data寄存器************************************/
/* ADF7012 register interface */
#define ADF7021_SCLK            RB6     // Output   时钟线
#define ADF7021_SDATA           RC7     // Output   数据线
#define ADF7021_SLE             RC6     // Output   片选
#define ADF7021_POWER           RC2     // Output   ADF7012电源使能脚
//#define ADF7021_CE              PB_ODR_ODR0     // Output   ADF7012使能脚
#define ADF7021_MUXOUT          RC1    // Input   ADF7012电池检测 <2.35


/* Other ADF7021 connections */
#define ADF7021_DATA_tx         RC0     // Output   调制DATA线
#define ADF7021_DATA_CLK        RA2     // 输入   调制同步时钟线

#define	PIN_KEY_OPEN		RB4   	// 输入  OPEN键
#define	PIN_KEY_STOP		RC4     // 输入  STOP键
#define	PIN_KEY_CLOSE		RA4     // 输入  CLOSE键    //2015.3.11修正
#define PIN_KEY_VENT            RA3     // 输入  换气键
//#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // 输入  CLOSE键
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // 输入  LOGIN键
#define	PIN_KEY_LOGIN		RC5     // 输入  LOGIN键
#define	PIN_UART_TX		RC4     // Output  uart TX

//#define PIN_LED                 PD_ODR_ODR0     // Output   LED灯
#define PIN_LED                 RB5     // Output   LED灯
#define PIN_TX_LED              RB5     // Output   LED灯

//#define PIN_BEEP                PB_ODR_ODR5     // Output   蜂鸣器
#define PIN_BEEP                RA5     // Output   蜂鸣器     //2015.3.11修正
//#define PIN_POWER_CONTROL       PC_ODR_ODR1     // Output   电源控制
#define PIN_POWER_CONTROL       RB7     // Output   电源控制
#define PIN_POWER_AD            RC1     // 输入     电源监测AD脚

#define PIN_test_mode           RC3     // 输入     test脚

