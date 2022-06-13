#include "adc.h"


void Init_Adc(void)
{
    PORT_SetP1AInputOnly(BIT0|BIT1|BIT2|BIT3|BIT5);  		//����P10�����룬��ADC����ͨ��
    
	ADC_Enable();						// ʹ��ADC
	ADC_SetClock_SYSCLKDiv2();			// ADCת��ʱ��Ϊ SYSCLK       ת����= ADC_CLK/30
    //ADC_SetClock_SYSCLKDiv4();
	ADC_SetMode_SetADCS();				// ADC����ģʽ, ��ADCS
	ADC_SetRightJustified();			// ADCת�������Ҷ���

	//ADC_SetVREF_IVR24();				// ����VREF+ Ϊ�ڲ�2.4V
    ADC_SetVREF_VDDA();

	ADC_SetChannel_AIN0();				// ѡ��ͨ��ΪAIN0(P10)

    INT_EnADC();                        // �����ж�
}

void Adc_Channel_Scan(u8 ch)
{
    switch(ch)
    {
        case 0:
            ADC_SetChannel_AIN0();				// ѡ��ͨ��ΪAIN0(P10)
            break;
        
        case 1:
            ADC_SetChannel_AIN1();				// ѡ��ͨ��ΪAIN1(P11)
            break;
        
        case 2:
            ADC_SetChannel_AIN2();				// ѡ��ͨ��ΪAIN2(P12)
            break;
        case 3:
            ADC_SetChannel_AIN3();				// ѡ��ͨ��ΪAIN2(P13)
            break; 
        case 5:
            ADC_SetChannel_AIN5();				// ѡ��ͨ��ΪAIN2(P15)
            break;                    
        default:
            break;
    }
}

void INT_ADC(void) interrupt INT_VECTOR_ADC
{
    xdata WordTypeDef wAdcValue;
    wAdcValue.B.BHigh = ADCDH;
    wAdcValue.B.BLow = ADCDL;
    RAM_BAT_SUM += (wAdcValue.W & 0x0FFF);
    RAM_BAT_CNT++;
    ADCON0 = ADCON0 & (~ADCI);		           		// ���־λ
    ADC_SoftStart();
    if(RAM_BAT_CNT >= 5)
    {
        Flag_adc_over = 1;
        INT_DisADC();                               //�ر�ADC�ж�
        ADC_Disable();                              //�ر�ADC
		RAM_BAT_CNT = 0;
        RAM_BAT_AVG = RAM_BAT_SUM / 5;
        if(channel == 0)
        {
            BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //�ɼ���ѹ0.9V.//0.9 * 1024 = 921.6
            RAM_BAT_SUM = 0;
            channel = 1;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 1)
        {
            RAM_BAT_AVG = RAM_BAT_SUM / 5;
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)   Flag_KEY_STOP = 0;
            else                   Flag_KEY_STOP = 1;
            RAM_BAT_SUM = 0;
            channel = 2;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 2)
        {
            RAM_BAT_AVG = RAM_BAT_SUM / 5;
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)    Flag_KEY_OPEN = 0;
            else                    Flag_KEY_OPEN = 1;
            RAM_BAT_SUM = 0;
            channel = 3;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 3)
        {
            RAM_BAT_AVG = RAM_BAT_SUM / 5;
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)    Flag_KEY_CLOSE = 0;
            else                    Flag_KEY_CLOSE = 1;
            RAM_BAT_SUM = 0;
            channel = 5;
            Adc_Channel_Scan(channel);
        } 
        else if(channel == 5)
        {
            RAM_BAT_AVG = RAM_BAT_SUM / 5;
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)    Flag_KEY_LOGIN = 0;
            else                    Flag_KEY_LOGIN = 1;
            RAM_BAT_SUM = 0;
            channel = 1;
            Adc_Channel_Scan(channel);
        }               
    }
}
void Adc_Open(void)
{
    ADC_Enable();
    INT_EnADC();
    Adc_Start(); 
}

void Adc_Start(void)
{
    ADC_SoftStart();
}

void AD_control(void)
{
    if(TIME_power_on_AD)
    {
      if(BAT_Voltage_value>2400)BAT_out=0;
      else if((BAT_Voltage_value<=2400)&&(BAT_Voltage_value>2200))BAT_out=1;
      else BAT_out=2; 
    }
}
/*
u16 Get_Adc_Value(void)
{
	xdata WordTypeDef wAdcValue;
	ADCON0 = ADCON0|ADCS;							// ��λADCS,����ADC
    while((ADCON0&ADCI)==0);           				// �ȴ�ADCת�����
    wAdcValue.B.BHigh=ADCDH;
    wAdcValue.B.BLow=ADCDL;
 	ADCON0 = ADCON0&(~ADCI);		           		// ���־λ
 	return wAdcValue.W&0x0FFF;
}*/