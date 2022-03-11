/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

/******************������data�Ĵ���************************************/
/* ADF7012 register interface */
#define ADF7021_SCLK            PC_ODR_ODR5     // Output   ʱ����
#define ADF7021_SDATA           PC_ODR_ODR6     // Output   ������
#define ADF7021_SLE             PA_ODR_ODR3     // Output   Ƭѡ
#define ADF7021_POWER           PC_ODR_ODR4     // Output   ADF7012��Դʹ�ܽ�
#define ADF7021_CE              PC_ODR_ODR4     // Output   ADF7012ʹ�ܽ�


/* Other ADF7021 connections */
#define ADF7021_DATA_tx         PC_ODR_ODR7     // Output   ����DATA��
#define ADF7021_DATA_CLK        PA_IDR_IDR1     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN		PA_IDR_IDR2   	// ����  OPEN��
#define	PIN_KEY_STOP		PB_IDR_IDR4     // ����  STOP��
#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // ����  LOGIN��
#define	PIN_KEY_LOGIN		PD_IDR_IDR6     // ����  LOGIN��

//#define PIN_LED                 PD_ODR_ODR0     // Output   LED��
#define PIN_LED                 PC_ODR_ODR3     // Output   LED��
#define PIN_TX_LED              PC_ODR_ODR3     // Output   LED��

#define PIN_BEEP                PB_ODR_ODR5     // Output   ������
#define PIN_POWER_CONTROL       PD_ODR_ODR2     // Output   ��Դ����
#define PIN_POWER_AD            PD_IDR_IDR3     // ����     ��Դ���AD��


/************************�����Ƿ���Ĵ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_direc      PC_DDR_DDR5     // Output   ʱ����
#define ADF7021_SDATA_direc     PC_DDR_DDR6     // Output   ������
#define ADF7021_SLE_direc       PA_DDR_DDR3     // Output   Ƭѡ
#define ADF7021_POWER_direc     PC_DDR_DDR4     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_direc        PC_DDR_DDR4     // Output   ADF7012ʹ�ܽ�

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_direc   PC_DDR_DDR7     // Output   ����DATA��
#define ADF7021_DATA_CLK_direc  PA_DDR_DDR1     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_direc	PA_DDR_DDR2   	// ����  OPEN��
#define	PIN_KEY_STOP_direc	PB_DDR_DDR4     // ����  STOP��
#define	PIN_KEY_CLOSE_direc	PD_DDR_DDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_direc	PB_DDR_DDR7     // ����  LOGIN��
#define	PIN_KEY_LOGIN_direc		PD_DDR_DDR6     // ����  LOGIN��

//#define PIN_LED_direc          PD_DDR_DDR0     // Output   LED��
#define PIN_LED_direc                 PC_DDR_DDR3     // Output   LED��

#define PIN_BEEP_direc          PB_DDR_DDR5     // Output   ������
#define PIN_POWER_CONTROL_direc PD_DDR_DDR2     // Output   ��Դ����
#define PIN_POWER_AD_direc      PD_DDR_DDR3     // ����     ��Դ���AD��


/************************�����ǿ��ƼĴ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_CR1        PC_CR1_C15     // Output   ʱ����
#define ADF7021_SDATA_CR1       PC_CR1_C16     // Output   ������
#define ADF7021_SLE_CR1         PA_CR1_C13     // Output   Ƭѡ
#define ADF7021_POWER_CR1       PC_CR1_C14     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_CR1          PC_CR1_C14     // Output   ADF7012ʹ�ܽ�

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_CR1     PC_CR1_C17     // Output   ����DATA��
#define ADF7021_DATA_CLK_CR1    PA_CR1_C11     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_CR1	PA_CR1_C12   	// ����  OPEN��
#define	PIN_KEY_STOP_CR1	PB_CR1_C14     // ����  STOP��
#define	PIN_KEY_CLOSE_CR1	PD_CR1_C14     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_CR1	PB_CR1_C17     // ����  LOGIN��
#define	PIN_KEY_LOGIN_CR1		PD_CR1_C16     // ����  LOGIN��

//#define PIN_LED_CR1           PD_CR1_C10     // Output   LED��
#define PIN_LED_CR1                 PC_CR1_C13     // Output   LED��

#define PIN_BEEP_CR1           PB_CR1_C15     // Output   ������
#define PIN_POWER_CONTROL_CR1  PD_CR1_C12     // Output   ��Դ����
#define PIN_POWER_AD_CR1       PD_CR1_C13     // ����     ��Դ���AD��




#define ADF7021_DATA_CLK_CR2    PA_CR2_C21     // ����   ����ͬ��ʱ����