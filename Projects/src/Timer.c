/***********************************************************************/
/*  FILE        :Timer.c                                               */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l051f3.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义

////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Timer 1 start
//void TIM1_init(void){						// 0.8333ms定时器
//	TIM1_PSCRH = 0x00;				// 10M系统时钟经预分频f=fck/(PSCR+1)
//	TIM1_PSCRL =0x00; 		     // PSCR=0x1F3F，f=3.6864M/(0x1200)=800Hz，计数周期1.25ms
//	TIM1_ARRH = 0x20;					// 自动重载寄存器ARR=5
//	TIM1_ARRL = 0x8c;		//78.125*(3+1)=312.5us		// 每2.5ms产生一次中断
//	TIM1_IER = 0x01;						// 允许更新中断
//	TIM1_CR1 = 0x01;					// 计数器使能，开始计数
//}
//
//void TIM1_OVR_UIF(void){        
//	TIM1_SR1 = 0;						// 清除中断标记
//}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Timer 4 start   1ms
void TIM4_Init(void){				
	TIM4_PSCR = 0x04;	// Timer 4 prescaler  计数器时钟频率  f CK_CNT  =f CK_PSC  / 2的N次方
        //TIM4_PSCR = 0x08;	// Timer 4 prescaler  计数器时钟频率  f CK_CNT  = f CK_PSC/ 2(PSC[3:0])
	TIM4_ARR  = 0xF9;						// Timer 4 period
	TIM4_CR1 |= 0x01;						// Timer 4 Enable
	TIM4_IER |= 0x01;						// Timer 4 OVR interrupt
}

void TIM4_UPD_OVF(void){
        FG_1ms = 1;
	if (TB_100ms)	--TB_100ms;
        else{                            
	  TB_100ms = BASE_100ms;
	  FG_100ms = 1;	      // 100mS FLAG
	}
	TIM4_SR1_bit.UIF=0;						// 清除中断标记
}


////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Timer 4 start   0.244ms
//void TIM4_Init(void){				
//	TIM4_PSCR = 0x04;	// Timer 4 prescaler  计数器时钟频率  f CK_CNT  =f CK_PSC  / 2的N次方
//	TIM4_ARR  = 0x3C;						// Timer 4 period
//	TIM4_CR1 |= 0x01;						// Timer 4 Enable
//	TIM4_IER |= 0x01;						// Timer 4 OVR interrupt
//}
//
//void TIM4_UPD_OVF(void){
//        if (TB_976us)--TB_976us;
//        else{                            
//	  TB_976us = BASE_976us;
//	  FG_976us = 1;	      // 976us FLAG
//	}
//        if(FLAG_beep==1)PIN_BEEP=!PIN_BEEP;
//	
//	TIM4_SR_bit.UIF=0;						// 清除中断标记
//}