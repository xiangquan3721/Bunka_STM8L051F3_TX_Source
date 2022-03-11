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
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断

void key_check(void)
{
//    if (TB_100ms)--TB_100ms;
//    else{                            
//	  TB_100ms = BASE_100ms;
//	  FG_100ms = 1;	      // 100mS FLAG
//	}
  
  
   if(FG_1ms){
    FG_1ms=0; 
    if(TIME_BEEP_on){
      --TIME_BEEP_on;
      if(FG_beep_on==0){FG_beep_on=1;FG_beep_off=0;BEEP_CSR_BEEPEN=1;}
    }
    else if(TIME_BEEP_off){
      --TIME_BEEP_off;
      if(FG_beep_off==0){FG_beep_off=1;FG_beep_on=0;BEEP_CSR_BEEPEN=0;}
    }
    else if(TIME_BEEP_freq){
      --TIME_BEEP_freq;
      TIME_BEEP_on=BASE_TIME_BEEP_on;
      TIME_BEEP_off=BASE_TIME_BEEP_off;
      if(FG_beep_on==0){FG_beep_on=1;FG_beep_off=0;BEEP_CSR_BEEPEN=1;}      
    }    
    
    
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
      BASE_TIME_BEEP_on=103;
      BASE_TIME_BEEP_off=103;
      TIME_BEEP_on=BASE_TIME_BEEP_on;
      TIME_BEEP_off=BASE_TIME_BEEP_off;
      TIME_BEEP_freq=0;
      SendTxData();
    }

    
    if((PIN_KEY_STOP==0)&&(FG_KEY_STOP==0))TIME_KEY_STOP++;
    if(PIN_KEY_STOP==1){TIME_KEY_STOP=0;FG_KEY_STOP=0;}
    if((TIME_KEY_STOP>=10)&&(TIME_KEY_LOGIN==0)&&(FLAG_APP_TX==0)&&(FG_KEY_STOP==0)&&(TB_5s>=20)){
      FG_KEY_STOP=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x04;
      BASE_TIME_BEEP_on=103;
      BASE_TIME_BEEP_off=103;
      TIME_BEEP_on=BASE_TIME_BEEP_on;
      TIME_BEEP_off=BASE_TIME_BEEP_off;
      TIME_BEEP_freq=1;
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
      BASE_TIME_BEEP_on=103;
      BASE_TIME_BEEP_off=103;
      TIME_BEEP_on=BASE_TIME_BEEP_on;
      TIME_BEEP_off=BASE_TIME_BEEP_off;
      TIME_BEEP_freq=2;
      SendTxData();
    } 

    if((PIN_KEY_LOGIN==0)&&(FG_KEY_LOGIN==0))TIME_KEY_LOGIN++;
    if(PIN_KEY_LOGIN==1){TIME_KEY_LOGIN=0;FG_KEY_LOGIN=0;}
    if((TIME_KEY_LOGIN>=4000)&&(FG_KEY_LOGIN==0)&&(FLAG_APP_TX==0)&&
       (TIME_KEY_STOP>=4000)&&(FG_KEY_STOP==0)&&(TB_5s>=20)){
      FG_KEY_LOGIN=1;
      if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=50;
      }
      dd_set_ADF7021_Power_on();
      dd_set_TX_mode();
      Control_code=0x14;
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


void test_mode_control(void)
{
  if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN==0)){
    FG_KEY_OPEN=1;
    dd_set_ADF7021_Power_on();
    dd_set_TX_mode();
    FG_test_mode=0;
    ADF7021_DATA_tx=0;
  }
  if(PIN_KEY_OPEN==1)FG_KEY_OPEN=0;
  
   if((PIN_KEY_STOP==0)&&(FG_KEY_STOP==0)){
    FG_KEY_STOP=1;
    ADF7021_CE = 0;
    FG_test_mode=0;
    ADF7021_DATA_tx=0;
  }
  if(PIN_KEY_STOP==1)FG_KEY_STOP=0; 
  
  if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE==0)){
    FG_KEY_CLOSE=1;
    dd_set_ADF7021_Power_on();
    dd_set_TX_mode();
    FG_test_mode=1;
  }
  if(PIN_KEY_CLOSE==1)FG_KEY_CLOSE=0;  
  
	
  if((ADF7021_DATA_CLK==1)&&(FG_test_mode==1)&&(FG_test1==0)){
     ADF7021_DATA_tx=!ADF7021_DATA_tx;
     FG_test1=1;
  }
  if(ADF7021_DATA_CLK==0)FG_test1=0;	  
}