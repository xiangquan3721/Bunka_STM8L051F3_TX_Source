#include "adc.h"


void Init_Adc(void)
{
    PORT_SetP1AInputOnly(BIT0);  		//����P10�����룬��ADC����ͨ��
    
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



void INT_ADC(void) interrupt INT_VECTOR_ADC
{
    xdata WordTypeDef wAdcValue;
    wAdcValue.B.BHigh = ADCDH;
    wAdcValue.B.BLow = ADCDL;
    RAM_BAT_SUM += (wAdcValue.W & 0x0FFF);
    RAM_BAT_CNT++;
    ADCON0 = ADCON0 & (~ADCI);		           		// ���־λ
    ADC_SoftStart();
    if(RAM_BAT_CNT >= 20)
    {
        INT_DisADC();                               //�ر�ADC�ж�
        ADC_Disable();                              //�ر�ADC
		RAM_BAT_CNT = 0;
		RAM_BAT_AVG = RAM_BAT_SUM / 20;
        BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //�ɼ���ѹ0.9V.//0.9 * 1024 = 921.6
		RAM_BAT_SUM = 0;
    }
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