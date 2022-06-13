#include "timer.h"

/* PCA��ʱ��Ϊ16λ,������65536,*/
#if (MCU_SYSCLK == 3000000)
#define PCA_RELOAD		(1500)  //f = PCA_CLK/PCA_RELOAD,PWM���Ƶ��2.0K,PCAʱ��ΪSysClk 3MHz
#define Duty_Cycle      750       //50%
#endif

#if (MCU_SYSCLK == 4000000)
#define PCA_RELOAD		(2000)  //f = PCA_CLK/PCA_RELOAD,PWM���Ƶ��2.0K,PCAʱ��ΪSysClk 4MHz
#define Duty_Cycle      1000       //50%
#endif

#if (MCU_SYSCLK == 6000000)
#define PCA_RELOAD		(3000)  //f = PCA_CLK/PCA_RELOAD,PWM���Ƶ��2.0K,PCAʱ��ΪSysClk 6MHz
#define Duty_Cycle      1500       //50%
#endif

#if (MCU_SYSCLK == 16000000)
#define PCA_RELOAD		(5926)  //f = PCA_CLK/PCA_RELOAD,PWM���Ƶ��2.7K,PCAʱ��ΪSysClk 16MHz
#define Duty_Cycle      2963       //50%
#endif

#if (MCU_SYSCLK == 24000000)
#define PCA_RELOAD		(8888)  //f = PCA_CLK/PCA_RELOAD,PWM���Ƶ��2.7K,PCAʱ��ΪSysClk 24MHz
#define Duty_Cycle      4444       //50%
#endif

#define PCA_C           (65536)
#define PCA_CL(x)		(u8)((PCA_C-(x))%256) 
#define PCA_CH(x)     	(u8)((PCA_C-(x))/256)


xdata u16 Time_Tx_Out = 0;
volatile u16 g_nSysTickCount = 0;

/***********************************************************************************
��������:   void InitTimer0(void)
��������:Timer0��ʼ������
		 ����T0Ϊ16λ��ʱ��,ʱ��ΪSysclk/12 
�������:   
���ز���:     
*************************************************************************************/
void Init_Timer0(void)
{
	TM_SetT0Mode_1_16BIT_TIMER();			// ����T0ģʽΪ16λģʽ
    
    TM_SetT0Clock_SYSCLK();            // ����T0ʱ��ԴΪ SYSCLK.

	TM_SetT0Gate_Disable();	
		
    TM_SetT0LowByte(TIMER_1T_1ms_TL);		// ����T0��8λ
	TM_SetT0HighByte(TIMER_1T_1ms_TH);		// ����T0��8λ

	TM_EnableT0();							// ʹ��T0
    INT_EnTIMER0();			//	ʹ��T0�ж�
}


/***********************************************************************************
��������:   void INT_T0(void)
��������:T0 �жϷ������
		 ���1ms
�������:   
���ز���:     
*************************************************************************************/
void INT_T0(void) interrupt INT_VECTOR_T0
{
	TH0 = TIMER_1T_1ms_TH;
	TL0 = TIMER_1T_1ms_TL;
    
    FG_1ms = 1;
	  g_nSysTickCount++; 
    if (TB_100ms)	--TB_100ms;
    else{                            
        TB_100ms = BASE_100ms;
        FG_100ms = 1;	      // 100mS FLAG
	}
    if(Time_Tx_Out) --Time_Tx_Out;
    if(TIME_BEEP_on)
    {
        if(FG_beep_on==1)--TIME_BEEP_on;
    }
    else if(TIME_BEEP_off)
        --TIME_BEEP_off;	
    if(time_adc)    --time_adc;	
        else
        {
            if((Flag_adc_over == 1)&&(FLAG_APP_TX==0)&&(CMT2300A_POWER == FG_NOT_allow_out))
            {
                Flag_adc_over = 0;
                time_adc = 3;
                Adc_Open();
            }
        }    	
}


void Init_PCA_PWM(void)
{
    PCA_SetCLOCK_SYSCLK();          // PCAʱ��ΪSysClk
    PCA_CH6_SetMode_PWM();          // PWMģʽ
    PCA_CH6_SetPWM_16Bit();         //
    PCA_SetPWM_EdgeAligned();	    // ���ض���
    
    // ����PWMռ�ձȱȽ�ֵ
	PCA_CH6_SetValue(PCA_CH(Duty_Cycle),PCA_CL(Duty_Cycle));
    
    // ���ö�ʱ������ֵ PWMƵ��
	PCA_SetCounter(PCA_C-PCA_RELOAD);
	PCA_SetCounterReload(PCA_C-PCA_RELOAD);
}

void Init_Beep(void)
{
    Init_PCA_PWM();
}

void Beep_On(void)
{
    PCA_EnPCACounter();
}

void Beep_Off(void)
{
    PCA_DisPCACounter();
    P20 = 0;
}


/*************************************************
��������:     void DelayXus(u16 xUs)
��������:   	��ʱ���򣬵�λΪus
���ú���:        
�������:     u8 Us -> *1us  (1~255)
�������:     
*************************************************/
void DelayXus(u8 xUs)
{
	while(xUs!=0)
	{
		_nop_();
		_nop_();
		xUs--;
	}
}


/*************************************************
��������:     void DelayXms(u16 xMs)
��������:     ��ʱ���򣬵�λΪms
�������:     u16 xMs -> *1ms  (1~65535)
�������:     
*************************************************/

void delay_ms(u8 ms) //
{
    while(ms--)
    {
        DelayXus(100);
        DelayXus(100);
    }
}

void system_delay_100us(u8 n)
{
    xdata u32 nDelayUsCnt = n*100;

    while(nDelayUsCnt--) {
			_nop_();
//        _nop_(); _nop_(); _nop_(); _nop_();_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//        _nop_(); _nop_(); _nop_(); _nop_();_nop_();
//        _nop_(); _nop_(); _nop_(); _nop_();_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//        _nop_(); _nop_(); _nop_(); _nop_();_nop_();
    }
}

void system_delay_ms(u8 nms)
{
    xdata u32 nDelayUsCnt = nms*10;

    while(nDelayUsCnt--)
        system_delay_100us(1);
}