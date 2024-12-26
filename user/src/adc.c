#include "adc.h"

xdata u8 ADC_AIN_ch=0;
void Init_Adc(void)
{
    PORT_SetP1AInputOnly(BIT0|BIT1|BIT2|BIT3|BIT4);  		//����P10�����룬��ADC����ͨ��
    
	ADC_Enable();						// ʹ��ADC
	ADC_SetClock_SYSCLKDiv2();			// ADCת��ʱ��Ϊ SYSCLK       ת����= ADC_CLK/30
    //ADC_SetClock_SYSCLKDiv4();
	ADC_SetMode_SetADCS();				// ADC����ģʽ, ��ADCS
	ADC_SetRightJustified();			// ADCת�������Ҷ���

	//ADC_SetVREF_IVR24();				// ����VREF+ Ϊ�ڲ�2.4V
    ADC_SetVREF_VDDA();

	ADC_SetChannel_AIN0();				// ѡ��ͨ��ΪAIN0(P10)

    //INT_EnADC();                        // �����ж�
}

void ADC_Inquire(void)
{
    xdata WordTypeDef wAdcValue;

    if((ADCON0&ADCI)==0);           				// �ȴ�ADCת�����
    else 
    {
        wAdcValue.B.BHigh = ADCDH;
        wAdcValue.B.BLow = ADCDL;
        ADCON0 = ADCON0&(~ADCI);		           		// ���־λ
        switch(ADC_AIN_ch)
        {
            case 0:
                RAM_BAT_SUM += (wAdcValue.W & 0x0FFF);
                RAM_BAT_CNT++;
                if(RAM_BAT_CNT >= 20)
                {
                    RAM_BAT_CNT = 0;
                    RAM_BAT_AVG = RAM_BAT_SUM / 20;
                    BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //??????0.9V.
                    RAM_BAT_SUM = 0;
                    Falg_ADC_Battery=1;
                }                
                break;
            
            case 1:
                if(wAdcValue.W < 0x200) PIN_KEY_STOP=0;
                else                    PIN_KEY_STOP=1;
                break;
            
            case 2:
                if(wAdcValue.W < 0x200) PIN_KEY_OPEN=0;
                else                    PIN_KEY_OPEN=1;                
                break;
            
            case 3:
                if(wAdcValue.W < 0x200) PIN_KEY_CLOSE=0;
                else                    PIN_KEY_CLOSE=1;                 
                break; 
            
            case 4:
                if(wAdcValue.W < 0x200) PIN_KEY_LOGIN=0;
                else                    PIN_KEY_LOGIN=1;                
                break;  
            
            default:
                break;
        }
        if(Falg_ADC_Battery==1) ADC_AIN_ch++;
        if(ADC_AIN_ch>4)        ADC_AIN_ch=1;
        switch(ADC_AIN_ch)
        {
            case 0:
                ADC_SetChannel_AIN0();				//AIN0(P10)               
                break;
            
            case 1:
                ADC_SetChannel_AIN1();				//AIN1(P11)
                break;
            
            case 2:
                ADC_SetChannel_AIN2();				//AIN2(P12)              
                break;
            
            case 3:
                ADC_SetChannel_AIN3();				//AIN2(P13)                
                break; 
            
            case 4:
                ADC_SetChannel_AIN4();				//AIN2(P14)               
                break; 
            
            default:
                break;
        }        
        ADC_SoftStart();        
    }
}

void INT_ADC(void) interrupt INT_VECTOR_ADC
{
    xdata WordTypeDef wAdcValue;
    wAdcValue.B.BHigh = ADCDH;
    wAdcValue.B.BLow = ADCDL;
    RAM_BAT_SUM += (wAdcValue.W & 0x0FFF);
    RAM_BAT_CNT++;
    ADCON0 = ADCON0 & (~ADCI);		           		// ????��
    ADC_SoftStart();
    if(RAM_BAT_CNT >= 20)
    {
        INT_DisADC();                               //???ADC?��?
        ADC_Disable();                              //???ADC
		RAM_BAT_CNT = 0;
		RAM_BAT_AVG = RAM_BAT_SUM / 20;
        BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //??????0.9V.
		RAM_BAT_SUM = 0;
    }
}
/*
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
        
        case 4:
            ADC_SetChannel_AIN4();				// ѡ��ͨ��ΪAIN2(P14)
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
        RAM_BAT_AVG = RAM_BAT_SUM / RAM_BAT_CNT;
        RAM_BAT_CNT = 0;
        if(channel == 0)
        {
            BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //�ɼ���ѹ0.9V.//0.9 * 1024 = 921.6
            RAM_BAT_SUM = 0;
            channel = 1;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 1)
        {
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)   Flag_KEY_STOP = 0;
            else                   Flag_KEY_STOP = 1;
            RAM_BAT_SUM = 0;
            channel = 2;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 2)
        {
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)    Flag_KEY_OPEN = 0;
            else                    Flag_KEY_OPEN = 1;
            RAM_BAT_SUM = 0;
            channel = 3;
            Adc_Channel_Scan(channel);
        }
        else if(channel == 3)
        {
            Adc_Value = (RAM_BAT_AVG * BAT_Voltage_value) / 1024;
            if(Adc_Value < 1200)    Flag_KEY_CLOSE = 0;
            else                    Flag_KEY_CLOSE = 1;
            RAM_BAT_SUM = 0;
            channel = 4;
            Adc_Channel_Scan(channel); 
        } 
        else if(channel == 4)
        {
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
void Adc_Close(void)
{
    INT_DisADC();                               //�ر�ADC�ж�
    ADC_Disable();
}*/

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