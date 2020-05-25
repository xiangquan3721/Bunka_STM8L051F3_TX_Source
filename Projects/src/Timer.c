/***********************************************************************/
/*  FILE        :Timer.c                                               */
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


void TIM3_init(void){			// 2015.3.11修正

}
void Tone_OFF(void){		// 关闭Tone   2015.3.11修正

        PIN_BEEP=0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Timer 4 start   1ms
void TIM4_Init(void){				
 TMR2=0X00;          //定时器赋初值
 PR2=0X64;
 TMR2IF=0;                  //定时器中断标志置0
 //INTCON=0XC0;//GIE=1; PEIE=1;      //开总中断,开外设中断
 TMR2IE=1;              //开定时器中断
 T2CON=0B01001101;            //TMR2ON=1; 设分频比1:16
}

void TIM4_UPD_OVF(void){
        FG_1ms = 1;
}

