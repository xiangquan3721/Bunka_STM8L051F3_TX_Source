/***********************************************************************/
/*  FILE        :initial_cyw.c                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l151c6.h>				// CPU型号 
#include "initial.h"		// 初始化  预定义
#include "Pin_define.h"		// 管脚定义
#include "initial_cyw.h"		// 初始化  预定义
#include "ram_cyw.h"		// RAM定义


#if(ProductID==Hanging_display)//
/****************端口设置说明***************************
CR1寄存器  输出 Output（1=推挽、0=OC）
           输入 Input（1=上拉、0=浮动）
***************end************************************/
void VHF_GPIO_INIT_cyw(void)   // CPU端口设置
{
 /* ADF7012 register interface */  
  ADF7021_SCLK_direc = Output;   //PB2
  ADF7021_SCLK_CR1 = 1;	
  ADF7021_SCLK=0;
  
  ADF7021_SDATA_direc = Output;// PB2
  ADF7021_SDATA_CR1 = 1;
  ADF7021_SDATA=0;
  
  ADF7021_SLE_direc = Output; //PB1
  ADF7021_SLE_CR1 = 1;  
  ADF7021_SLE=0;
  
  ADF7021_POWER_direc = Output;//PB6
  ADF7021_POWER_CR1 = 1; 
  //ADF7021_POWER=1;
  ADF7012_POWEROFF;
  //ADF7021_CE_direc = Output;
  //ADF7021_CE_CR1 = 1; 
  //ADF7021_CE=0;
  
  ADF7021_MUXOUT_direc=Input;//PB7
  ADF7021_MUXOUT_CR1=0;    //ADF7012要求必须下拉
  
/* Other ADF7021 connections */
  ADF7021_DATA_tx_direc = Output; // Output   调制DATA线//PB5
  ADF7021_DATA_tx_CR1 = 1;
  ADF7021_DATA_tx=0;
  
  ADF7021_DATA_CLK_direc= Input;//PB4
  ADF7021_DATA_CLK_CR1= 1;

  PIN_KEY_OPEN_direc = Input; 	// 输入  OPEN键
  PIN_KEY_OPEN_CR1 = 1;
  
  PIN_KEY_STOP_direc = Input;    // 输入  STOP键
  PIN_KEY_STOP_CR1 = 1;
  
  PIN_KEY_CLOSE_direc = Input;   // 输入  CLOSE键
  PIN_KEY_CLOSE_CR1 = 1;
  
  PIN_KEY_VENT_direc = Input;   // 输入  换气键
  PIN_KEY_VENT_CR1 = 1;
  
 PIN_KEY_LOGIN_direc = Input;   // 输入  LOGIN键
  PIN_KEY_LOGIN_CR1 = 1;
  
  PIN_KEY_DECIDE_direc = Input;   // 输入  LOGIN键
  PIN_KEY_DECIDE_CR1 = 1;
  
  PIN_KEY_CLOSETIME_direc = Input;   // 输入  LOGIN键
  PIN_KEY_CLOSETIME_CR1 = 1;
  
  PIN_KEY_NOWTIME_direc = Input;   // 输入  LOGIN键
  PIN_KEY_NOWTIME_CR1 = 1;
  
  PIN_KEY_OPENTIME_direc = Input;   // 输入  LOGIN键
  PIN_KEY_OPENTIME_CR1 = 1;

  PIN_KEY_DEC_direc = Input;   // 输入  LOGIN键
  PIN_KEY_DEC_CR1 = 1;
  
  PIN_KEY_ADD_direc = Input;   // 输入  LOGIN键
  PIN_KEY_ADD_CR1 = 1;
  
  PIN_LED_direc = Output;     // Output   LED灯
  PIN_LED_CR1 = 1;
  LED_OFF;
  
  
  PIN_BEEP_direc = Output;    // Output   蜂鸣器
  PIN_BEEP_CR1 = 1;
  PIN_BEEP=0;
  
  PIN_POWER_CONTROL_direc = Output;    // Output   电源控制
  PIN_POWER_CONTROL_CR1 = 1;
  POWER_OFF;
  
  PIN_test_mode_direc=Input;    // 输入     test脚
  PIN_test_mode_CR1=1;
  
  PIN_POWER_AD_direc = Input;     // 输入     电源监测AD脚 
  PIN_POWER_AD_CR1 =1;//时钟报警
  
  PIN_LCD_SEL_direc = Output;
  PIN_LCD_SEL_CR1   = 1;// 上拉
  PIN_LCD_SEL       = 1;// 液晶LCD不选中
  
  
  PIN_LCD_LIGHT_direc = Output;
  PIN_LCD_LIGHT_CR1   = 1;
  
  PIN_LCD_RST_direc = Output;
  PIN_LCD_RST_CR1  = 1;
  
  
  
  PIN_LCD_LIGHT_direc = Output;
  PIN_LCD_LIGHT_CR1 = 1;
  
  
  PIN_FONT_SEL_direc = Output;
  PIN_FONT_SEL_CR1  = 1;
  PIN_FONT_SEL      = 1;//font 不选中
  
  PIN_LCD_RS_direc = Output;
  PIN_LCD_RS_CR1   = 1;
  
  
  PIN_FONT_DATAIN_direc = Input;
  PIN_FONT_DATAIN_CR1 = 1;//上拉
  
  
  PIN_PCF8563_SDA_direc = Output;
  PIN_PCF8563_SDA_CR1 = 0;
  PIN_PCF8563_SDAOUT = 1;//ZHIGAO
  
  PIN_PCF8563_SCL_direc = Output;
  PIN_PCF8563_SCL_CR1 = 0;
  PIN_PCF8563_SCL = 1;//ZHIGAO
  
}

void WDT_init_cyw(void)
{
  IWDG_KR=0x55;//使能IWDG_PR IWDG_RLR寄存器
  IWDG_PR=6;//分频
  IWDG_RLR=0xFF;//重新装载 重这个值开始DOWN
  IWDG_KR=0xCC;//使能看门狗
}

void Power_On_Init_cyw(void)
{
   TB_POWER = 20;
}

void Delaycyw(unsigned char timer)
{
unsigned char x;   

for(x=0;x<timer;x++)
{
  Delayus(255);
}

}

#endif