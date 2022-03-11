/***********************************************************************/
/*  FILE        :initial.c                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include "stm8s.h"
#include  <iostm8s003f3.h>
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����


void RAM_clean(void)      // ���RAM 
{			
  asm("ldw X,#0");
  asm("clear_ram:");
  asm("clr (X)");
  asm("incw X");
  asm("cpw X,#0x3f0");	
  asm("jrule clear_ram");
}  

void SysClock_Init( void )
{ 				// ϵͳʱ�ӣ��ⲿʱ�ӣ�
//	CLK_ICKR_HSIEN = 1;						// ʹ���ڲ�RC OSC
//	CLK_ECKR_HSEEN = 1;						// ���ⲿ���� 
//	while(( CLK_ECKR & 0x02 ) == 0 );		// ����ⲿ���� 
//	CLK_SWR = 0xb4;							// ָ��HSEΪ��ʱ�� 
//	while(( CLK_SWCR & 0x08 ) == 0 );		// �ȴ��ⲿ���� 
//	CLK_SWCR_SWEN = 1;						// ִ���л�
//	CLK_CKDIVR = 0x00;						// ����ʱ�ӷ�Ƶ������Ƶ��
//	//---------------------------------------- ����
//	CLK_PCKENR1 = 0xF6;						// T1~4,UART1,SPI
//	CLK_PCKENR2 = 0x08;						// ADC

	
	CLK_ICKR_HSIEN = 1;				// ʹ���ڲ�RC OSC��16.00MHz��
	while(( CLK_ICKR & 0x02 ) == 0 );		// ����ڲ����� 
	CLK_SWR = 0xE1;					// ָ��HSIΪ��ʱ�� 
//	while(( CLK_SWCR & 0x08 ) == 0 );		// �ȴ�HSI�л� 
	CLK_SWCR_SWEN = 1;						// ִ���л�
	CLK_CKDIVR = 0x10;		// ����ʱ�ӷ�Ƶ  f HSI= f HSI RC���/4    f CPU= f MASTER
	//---------------------------------------- ����  
	//CLK_PCKENR1 = 0x84;						// T1,UART1
//	CLK_PCKENR1 = 0x14;						// T4,UART1
//	CLK_PCKENR2 = 0x08;						// ADC	
	
	CLK_ICKR_LSIEN = 1;				// ʹ���ڲ�LSI OSC��128KHz��
	while(CLK_ICKR_LSIRDY == 0 );		// ����ڲ�LSI OSC 
}

void beep_init( void )
{ 	
     //BEEP_CSR=0x4E; 
  BEEP_CSR=0;
  BEEP_CSR_BEEPDIV=14;
  BEEP_CSR_BEEPSEL=1; 
}
/****************�˿�����˵��***************************
CR1�Ĵ���  ��� Output��1=���졢0=OC��
           ���� Input��1=������0=������
***************end************************************/
void VHF_GPIO_INIT(void)   // CPU�˿�����
{
 /* ADF7012 register interface */  
  ADF7021_SCLK_direc = Output;   
  ADF7021_SCLK_CR1 = 1;	
  ADF7021_SCLK=0;
  
  ADF7021_SDATA_direc = Output;
  ADF7021_SDATA_CR1 = 1;
  ADF7021_SDATA=0;
  
  ADF7021_SLE_direc = Output;
  ADF7021_SLE_CR1 = 1;  
  ADF7021_SLE=0;
  
  ADF7021_POWER_direc = Output;
  ADF7021_POWER_CR1 = 1; 
  ADF7021_POWER=0;
//  ADF7021_CE_direc = Output;
//  ADF7021_CE_CR1 = 1; 
  
  
/* Other ADF7021 connections */
  ADF7021_DATA_tx_direc = Output; // Output   ����DATA��
  ADF7021_DATA_tx_CR1 = 1;
  ADF7021_DATA_tx=0;
  
  ADF7021_DATA_CLK_direc= Input;
  ADF7021_DATA_CLK_CR1= 1;

  PIN_KEY_OPEN_direc = Input; 	// ����  OPEN��
  PIN_KEY_OPEN_CR1 = 1;
  
  PIN_KEY_STOP_direc = Input;    // ����  STOP��
  PIN_KEY_STOP_CR1 = 1;
  
  PIN_KEY_CLOSE_direc = Input;   // ����  CLOSE��
  PIN_KEY_CLOSE_CR1 = 1;
  
  PIN_KEY_LOGIN_direc = Input;   // ����  LOGIN��
  PIN_KEY_LOGIN_CR1 = 1;

  PIN_LED_direc = Output;     // Output   LED��
  PIN_LED_CR1 = 1;

  PIN_BEEP_direc = Output;    // Output   ������
  PIN_BEEP_CR1 = 1;
  PIN_BEEP=0;
  
  PIN_POWER_CONTROL_direc = Output;    // Output   ��Դ����
  PIN_POWER_CONTROL_CR1 = 1;
  PIN_POWER_CONTROL=0;
  
  PIN_test_mode_direc=Input;    // ����     test��
  PIN_test_mode_CR1=1;
  
  PIN_POWER_AD_direc = Input;     // ����     ��Դ���AD�� 

}


//===================Delayus()��ʱ===============//
void Delayus(unsigned char timer)
{
unsigned char x;                   //��ʱT=(timer-1)*1.5+3 us
 for(x=0;x<timer;x++)
     __asm("nop");
}