#include "adc.h"

xdata u8 ADC_AIN_ch=0;
void Init_Adc(void)
{
    PORT_SetP1AInputOnly(BIT0|BIT1|BIT2|BIT3|BIT4);  		//设置P10仅输入，做ADC输入通道
    
	ADC_Enable();						// 使能ADC
	ADC_SetClock_SYSCLKDiv2();			// ADC转换时钟为 SYSCLK       转换率= ADC_CLK/30
    //ADC_SetClock_SYSCLKDiv4();
	ADC_SetMode_SetADCS();				// ADC启动模式, 置ADCS
	ADC_SetRightJustified();			// ADC转换数据右对齐

	//ADC_SetVREF_IVR24();				// 设置VREF+ 为内部2.4V
    ADC_SetVREF_VDDA();

	ADC_SetChannel_AIN0();				// 选择通道为AIN0(P10)

    //INT_EnADC();                        // 开启中断
}

void ADC_Inquire(void)
{
    xdata WordTypeDef wAdcValue;

    if((ADCON0&ADCI)==0);           				// 等待ADC转换完成
    else 
    {
        wAdcValue.B.BHigh = ADCDH;
        wAdcValue.B.BLow = ADCDL;
        ADCON0 = ADCON0&(~ADCI);		           		// 清标志位
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
    ADCON0 = ADCON0 & (~ADCI);		           		// ????λ
    ADC_SoftStart();
    if(RAM_BAT_CNT >= 20)
    {
        INT_DisADC();                               //???ADC?ж?
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
            ADC_SetChannel_AIN0();				// 选择通道为AIN0(P10)
            break;
        
        case 1:
            ADC_SetChannel_AIN1();				// 选择通道为AIN1(P11)
            break;
        
        case 2:
            ADC_SetChannel_AIN2();				// 选择通道为AIN2(P12)
            break;
        
        case 3:
            ADC_SetChannel_AIN3();				// 选择通道为AIN2(P13)
            break;
        
        case 4:
            ADC_SetChannel_AIN4();				// 选择通道为AIN2(P14)
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
    ADCON0 = ADCON0 & (~ADCI);		           		// 清标志位
    ADC_SoftStart();
    if(RAM_BAT_CNT >= 5)
    {
        Flag_adc_over = 1;
        INT_DisADC();                               //关闭ADC中断
        ADC_Disable();                              //关闭ADC
        RAM_BAT_AVG = RAM_BAT_SUM / RAM_BAT_CNT;
        RAM_BAT_CNT = 0;
        if(channel == 0)
        {
            BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //采集电压0.9V.//0.9 * 1024 = 921.6
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
    INT_DisADC();                               //关闭ADC中断
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
	ADCON0 = ADCON0|ADCS;							// 置位ADCS,启动ADC
    while((ADCON0&ADCI)==0);           				// 等待ADC转换完成
    wAdcValue.B.BHigh=ADCDH;
    wAdcValue.B.BLow=ADCDL;
 	ADCON0 = ADCON0&(~ADCI);		           		// 清标志位
 	return wAdcValue.W&0x0FFF;
}*/