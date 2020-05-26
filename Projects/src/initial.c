/***********************************************************************/
/*  FILE        :initial.c                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <stdio.h>
#include <pic.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "key_and_Other.h"		// 按键

void RAM_clean(void)      // 清除RAM 
{			

}  

void WDT_init(void)
{
 
}
void ClearWDT(void)
{

}


void SysClock_Init( void )
{ 				// 系统时钟（外部时钟）
  OSCCON=0x78;  //0x68
  while(!HFIOFR);            //等待内部振荡器稳定
}

void beep_init( void )
{ 	

}
/****************端口设置说明***************************
CR1寄存器  输出 Output（1=推挽、0=OC）
           输入 Input（1=上拉、0=浮动）
***************end************************************/
void VHF_GPIO_INIT(void)   // CPU端口设置
{
  ANSELA=0X00;
  ANSELB=0X00;
  ANSELC=0X00;   
  
  nWPUEN=0;
  TRISA=0B00010100;          //方向
  WPUA =0B00010100;
  TRISB=0B01010000;
  WPUB =0B11010000;
  TRISC=0B00111010;
  WPUC =0B00111100;  
  
  PIN_TX_LED=0;
 /* ADF7012 register interface */  
  ADF7021_SCLK=0;
  
  ADF7021_SDATA=0;
  
  ADF7021_SLE=0;
  
  ADF7021_POWER=FG_NOT_allow_out;
  
  //ADF7021_MUXOUT_CR1=1;    //ADF7012要求必须下拉
  
/* Other ADF7021 connections */
  ADF7021_DATA_tx=0;
  
  PIN_BEEP=0;
  
  PIN_POWER_CONTROL=0;

}
void _Init_RAM(void)
{
  TB_100ms = BASE_100ms;
  //TB_5s=TB_50s;//50;
  TB_51s=26;//69;
  TB_5s=TB_51s-1;
  
  	/*		Timer		*/
								// General 1s timer
	
	/*		Key		*/
	_SetKeyChatterCount() ;									// Chatter counter set
	m_KeyNew = m_KeyOld = d_KeyNoPush ;
	m_KindOfKey          = d_IdleKey ;
	//mb_Keycheck          = d_Clear ;
	mb_NoPush            = d_On ;
	mb_NoPushWait        = d_Clear ;
	_ClearSpecialMultiKeyState() ;
	m_TimerKey = d_Clear ;
	m_TimerKeyMonitor = d_Clear ;
}
//===================Delayus()延时===============//
void Delayus(unsigned char timer)
{
unsigned char x;                   //延时T=(timer-1)*1.5+3 us
 for(x=0;x<timer;x++)
     __asm("nop");
}