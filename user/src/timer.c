#include "timer.h"

u16 time_rx_led = 0;
volatile u32 g_nSysTickCount = 0;

void TIM4_Init(void)
{
    CLK_PCKENR1 |= 0x04;    /* 开启定时器4时钟*/

    /* fCK_CNT = 16M/(2的n次方),fCK_CNT = fCK_PSC / 2(PSC[3:0]) */
    TIM4_PSCR = 0x06;   /* n = 0x06,64分频 */

    TIM4_ARR = 0xF9;    /* ARR值249,1ms */
    TIM4_IER |= 0x01;   /* 开启更新中断 */
    TIM4_CR1 |= 0x01;   /* 开启定时器 */
}

void TIM4_UPD_OVF(void)
{
    g_nSysTickCount++;

    if(time_rx_led) --time_rx_led;

    TIM4_SR1_bit.UIF = 0;   /* 清标志 */
}


void TIM3_init(void)
{
    CLK_PCKENR1 |= 0x02;
    TIM3_CCMR1 = TIM3_CCMR1 | 0x70;
    TIM3_CCER1 = TIM3_CCER1 | 0x03;  //TIME3_CH1
    TIM3_ARRH = 0x08;                //0x07D0 -->PWM=2K        0x0880 -->PWM=1.83K
    TIM3_ARRL = 0x84;
                                     //TIM2_IER = 0x01;						// ??????????
    TIM3_CCR1H = 0x04;               //50%
    TIM3_CCR1L = 0x42;
    TIM3_PSCR = 0x02;                // ?????=Fsystem/(2(PSC[2:0])????4MHz=16MHz/2/2
    TIM3_CR1 = TIM3_CR1 | 0x01;
    TIM3_BKR = 0x80;
}
void Tone_OFF(void)
{                     // ???Tone   2015.3.11????
    TIM3_CR1_CEN = 0; // Timer 3 Disable
    TIM3_CCMR1 =  0x00;
    TIM3_CCER1 =  0x00; //????PWM?????????????????I/O
    PIN_BEEP = 0;
}



void system_delay_100us(u32 n)
{
    u32 nDelayUsCnt = n*100;

    while(nDelayUsCnt--) {
        _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
        _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
        _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
        _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
    }
}

void system_delay_ms(u32 nms)
{
    u32 nDelayUsCnt = nms*10;

    while(nDelayUsCnt--)
        system_delay_100us(1);
}


