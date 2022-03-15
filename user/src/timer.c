#include "timer.h"

/* PCA��ʱ��Ϊ16λ,������65536,*/
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

      
//xdata u16 time_ms = 0;
idata u16 Time_Tx_Out = 0;

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
    
    TM_SetT0Clock_SYSCLKDiv12();            // ����T0ʱ��ԴΪ SYSCLK/12.

	TM_SetT0Gate_Disable();	
		
    TM_SetT0LowByte(TIMER_12T_1ms_TL);		// ����T0��8λ
	TM_SetT0HighByte(TIMER_12T_1ms_TH);		// ����T0��8λ

	TM_EnableT0();							// ʹ��T0
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
	TH0=TIMER_12T_1ms_TH;
	TL0=TIMER_12T_1ms_TL;
    
    if (TIMER1s)
        --TIMER1s;
	if(TIME_power_led)
		--TIME_power_led;
    if (TIMER300ms)
        --TIMER300ms;
    if (TIMER18ms)
        --TIMER18ms;
    if (TIMER250ms_STOP)
        --TIMER250ms_STOP;
    if (TIME_10ms)
        --TIME_10ms;
    else
    { // 10mS FLAG
        TIME_10ms = 10;
        FG_10ms = 1;
    }
    if (U1AckTimer)
        U1AckTimer--;
    if (Time_APP_RXstart)
      --Time_APP_RXstart;
    if(Time_APP_blank_TX)
       --Time_APP_blank_TX;
    if (X_ERRTimer)
        X_ERRTimer--;
	if (TIME_ID_SCX1801_Login)
		--TIME_ID_SCX1801_Login;

    if(Time_Tx_Out)  --Time_Tx_Out;
    if(Time_rf_init) --Time_rf_init;
}


//38K/14 = 2.7kHz;
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
		_nop_();
		_nop_();
		_nop_();
		_nop_();
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

void delay_ms(u8 ms) //1Լ1.2ms
{
    while(ms--)
    {
        DelayXus(200);
        DelayXus(200);
        DelayXus(200);
        DelayXus(200);
    }
}