/*********************************************************************
    ��Ŀ����:MA82G5Bxx-DEMO
			���԰�ʹ�� MA82G5B32	LQFP32_V10 EV Board (TH156A)
			CpuCLK=12MHz, SysCLK=12MHz
	����������

	ע�����

    ����ʱ��:
    �޸���־:
    
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
    INT_EnAll();  // ʹ��ȫ���ж�

    RF_Test_Mode();
	
    while(1) 
    {
        ClearWDT(); // Service the WDT
    }
}


