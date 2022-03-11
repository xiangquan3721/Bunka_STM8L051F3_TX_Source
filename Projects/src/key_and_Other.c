/***********************************************************************/
/*  FILE        :key_and_Other.c                                       */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

//#include "stm8s.h"
#include  <iostm8s003f3.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义

void key_check(void)
{
  if(FG_1ms){
    FG_1ms=0;
    
    if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN==0))TIME_KEY_OPEN++;
    if(PIN_KEY_OPEN==1){TIME_KEY_OPEN=0;FG_KEY_OPEN=0;}
    if((TIME_KEY_OPEN>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_OPEN==0)&&(TB_5s>=20)){
      FG_KEY_OPEN=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x08;
      SendTxData();
    }

    
    if((PIN_KEY_STOP==0)&&(FG_KEY_STOP==0))TIME_KEY_STOP++;
    if(PIN_KEY_STOP==1){TIME_KEY_STOP=0;FG_KEY_STOP=0;}
    if((TIME_KEY_STOP>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_STOP==0)&&(TB_5s>=20)){
      FG_KEY_STOP=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x04;
      SendTxData();
    }

    if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE==0))TIME_KEY_CLOSE++;
    if(PIN_KEY_CLOSE==1){TIME_KEY_CLOSE=0;FG_KEY_CLOSE=0;}
    if((TIME_KEY_CLOSE>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_CLOSE==0)&&(TB_5s>=20)){
      FG_KEY_CLOSE=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x02;
      SendTxData();
    } 

    if((PIN_KEY_LOGIN==0)&&(FG_KEY_LOGIN==0))TIME_KEY_LOGIN++;
    if(PIN_KEY_LOGIN==1){TIME_KEY_LOGIN=0;FG_KEY_LOGIN=0;}
    if((TIME_KEY_LOGIN>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_LOGIN==0)&&(TB_5s>=20)){
      FG_KEY_LOGIN=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x08;
      SendTxData();
    } 
    
    
  }
}


void time_control(void)
{
  if(FG_100ms){
    FG_100ms=0;
    if(FG_PWRON==1){
    if (TB_5s)	--TB_5s;
    }
  }
  
}