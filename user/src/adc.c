#include "adc.h"


void Init_Adc(void)
{
    PORT_SetP1AInputOnly(BIT0);  		//设置P10仅输入，做ADC输入通道
    
	ADC_Enable();						// 使能ADC
	ADC_SetClock_SYSCLKDiv2();			// ADC转换时钟为 SYSCLK       转换率= ADC_CLK/30
    //ADC_SetClock_SYSCLKDiv4();
	ADC_SetMode_SetADCS();				// ADC启动模式, 置ADCS
	ADC_SetRightJustified();			// ADC转换数据右对齐

	//ADC_SetVREF_IVR24();				// 设置VREF+ 为内部2.4V
    ADC_SetVREF_VDDA();

	ADC_SetChannel_AIN0();				// 选择通道为AIN0(P10)

    INT_EnADC();                        // 开启中断
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
    if(RAM_BAT_CNT >= 20)
    {
        INT_DisADC();                               //关闭ADC中断
        ADC_Disable();                              //关闭ADC
		RAM_BAT_CNT = 0;
		RAM_BAT_AVG = RAM_BAT_SUM / 20;
        BAT_Voltage_value = 921600 / RAM_BAT_AVG;   //采集电压0.9V.//0.9 * 1024 = 921.6
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
	ADCON0 = ADCON0|ADCS;							// 置位ADCS,启动ADC
    while((ADCON0&ADCI)==0);           				// 等待ADC转换完成
    wAdcValue.B.BHigh=ADCDH;
    wAdcValue.B.BLow=ADCDL;
 	ADCON0 = ADCON0&(~ADCI);		           		// 清标志位
 	return wAdcValue.W&0x0FFF;
}*/