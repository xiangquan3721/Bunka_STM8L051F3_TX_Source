/*********************************************************************
    项目名称:MA82G5Bxx-DEMO
			测试板使用 MA82G5B32	LQFP32_V10 EV Board (TH156A)
			CpuCLK=12MHz, SysCLK=12MHz
	功能描述：

	注意事项：

    建立时间:
    修改日志:
    
*********************************************************************/
#include "timer.h"

void main()
{
    Init_WDT();    
    Init_Clock();
    ClearWDT();
    //Init_Port();
	Init_Timer0();       
    Init_Beep();
    ClearWDT();
    Init_Interrupt();
    INT_EnAll();  // 使能全局中断

    RF_Test_Mode();
	
    while(1) 
    {
        ClearWDT(); // Service the WDT
    }
}


