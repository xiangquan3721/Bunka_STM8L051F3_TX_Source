/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

/******************以下是data寄存器************************************/
/* ADF7012 register interface */
#define ADF7021_SCLK            PC_ODR_ODR5     // Output   时钟线
#define ADF7021_SDATA           PC_ODR_ODR6     // Output   数据线
#define ADF7021_SLE             PA_ODR_ODR3     // Output   片选
#define ADF7021_POWER           PC_ODR_ODR4     // Output   ADF7012电源使能脚
#define ADF7021_CE              PC_ODR_ODR4     // Output   ADF7012使能脚


/* Other ADF7021 connections */
#define ADF7021_DATA_tx         PC_ODR_ODR7     // Output   调制DATA线
#define ADF7021_DATA_CLK        PA_IDR_IDR1     // 输入   调制同步时钟线

#define	PIN_KEY_OPEN		PA_IDR_IDR2   	// 输入  OPEN键
#define	PIN_KEY_STOP		PB_IDR_IDR4     // 输入  STOP键
#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // 输入  CLOSE键
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // 输入  LOGIN键
#define	PIN_KEY_LOGIN		PD_IDR_IDR6     // 输入  LOGIN键

//#define PIN_LED                 PD_ODR_ODR0     // Output   LED灯
#define PIN_LED                 PC_ODR_ODR3     // Output   LED灯
#define PIN_TX_LED              PC_ODR_ODR3     // Output   LED灯

#define PIN_BEEP                PB_ODR_ODR5     // Output   蜂鸣器
#define PIN_POWER_CONTROL       PD_ODR_ODR2     // Output   电源控制
#define PIN_POWER_AD            PD_IDR_IDR3     // 输入     电源监测AD脚


/************************以下是方向寄存器*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_direc      PC_DDR_DDR5     // Output   时钟线
#define ADF7021_SDATA_direc     PC_DDR_DDR6     // Output   数据线
#define ADF7021_SLE_direc       PA_DDR_DDR3     // Output   片选
#define ADF7021_POWER_direc     PC_DDR_DDR4     // Output   ADF7012电源使能脚
//#define ADF7021_CE_direc        PC_DDR_DDR4     // Output   ADF7012使能脚

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_direc   PC_DDR_DDR7     // Output   调制DATA线
#define ADF7021_DATA_CLK_direc  PA_DDR_DDR1     // 输入   调制同步时钟线

#define	PIN_KEY_OPEN_direc	PA_DDR_DDR2   	// 输入  OPEN键
#define	PIN_KEY_STOP_direc	PB_DDR_DDR4     // 输入  STOP键
#define	PIN_KEY_CLOSE_direc	PD_DDR_DDR4     // 输入  CLOSE键
//#define	PIN_KEY_LOGIN_direc	PB_DDR_DDR7     // 输入  LOGIN键
#define	PIN_KEY_LOGIN_direc		PD_DDR_DDR6     // 输入  LOGIN键

//#define PIN_LED_direc          PD_DDR_DDR0     // Output   LED灯
#define PIN_LED_direc                 PC_DDR_DDR3     // Output   LED灯

#define PIN_BEEP_direc          PB_DDR_DDR5     // Output   蜂鸣器
#define PIN_POWER_CONTROL_direc PD_DDR_DDR2     // Output   电源控制
#define PIN_POWER_AD_direc      PD_DDR_DDR3     // 输入     电源监测AD脚


/************************以下是控制寄存器*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_CR1        PC_CR1_C15     // Output   时钟线
#define ADF7021_SDATA_CR1       PC_CR1_C16     // Output   数据线
#define ADF7021_SLE_CR1         PA_CR1_C13     // Output   片选
#define ADF7021_POWER_CR1       PC_CR1_C14     // Output   ADF7012电源使能脚
//#define ADF7021_CE_CR1          PC_CR1_C14     // Output   ADF7012使能脚

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_CR1     PC_CR1_C17     // Output   调制DATA线
#define ADF7021_DATA_CLK_CR1    PA_CR1_C11     // 输入   调制同步时钟线

#define	PIN_KEY_OPEN_CR1	PA_CR1_C12   	// 输入  OPEN键
#define	PIN_KEY_STOP_CR1	PB_CR1_C14     // 输入  STOP键
#define	PIN_KEY_CLOSE_CR1	PD_CR1_C14     // 输入  CLOSE键
//#define	PIN_KEY_LOGIN_CR1	PB_CR1_C17     // 输入  LOGIN键
#define	PIN_KEY_LOGIN_CR1		PD_CR1_C16     // 输入  LOGIN键

//#define PIN_LED_CR1           PD_CR1_C10     // Output   LED灯
#define PIN_LED_CR1                 PC_CR1_C13     // Output   LED灯

#define PIN_BEEP_CR1           PB_CR1_C15     // Output   蜂鸣器
#define PIN_POWER_CONTROL_CR1  PD_CR1_C12     // Output   电源控制
#define PIN_POWER_AD_CR1       PD_CR1_C13     // 输入     电源监测AD脚




#define ADF7021_DATA_CLK_CR2    PA_CR2_C21     // 输入   调制同步时钟线