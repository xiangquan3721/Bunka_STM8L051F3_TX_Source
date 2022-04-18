#include "sys.h"


void Init_Clock(void)
{
#if (MCU_SYSCLK == 16000000)
    CLK_SetCKCON0(IHRCO_12MHz|ENABLE_CKM|CKM_OSCIN_DIV_2|CPUCLK_SYSCLK_DIV_1|SYSCLK_MCKDO_DIV_1);
    CLK_SetCKCON2(ENABLE_IHRCO|MCK_CKMI_X533|OSCIn_IHRCO);  
    CLK_SetCKCON3(0x06);                                    //12MHz/2*5.33/2 = 16MHz 
#endif
 
#if (MCU_SYSCLK == 24000000)
	// SysClk=24MHz CpuClk=24MHz
	CLK_SetCKCON0(IHRCO_12MHz|ENABLE_CKM|CKM_OSCIN_DIV_2|CPUCLK_SYSCLK_DIV_1|SYSCLK_MCKDO_DIV_1);
	DelayXus(100);
	// IHRCO, MCK=CKMIx4, OSCin=IHRCO
	CLK_SetCKCON2(ENABLE_IHRCO|MCK_CKMI_X4|OSCIn_IHRCO);
#endif
    
#if (MCU_SYSCLK == 4000000)
    CLK_SetCKCON0(IHRCO_12MHz|ENABLE_CKM|CKM_OSCIN_DIV_2|CPUCLK_SYSCLK_DIV_1|SYSCLK_MCKDO_DIV_1);
    DelayXus(100);
    CLK_SetCKCON2(ENABLE_IHRCO|MCK_CKMI_X533|OSCIn_IHRCO);  
    DelayXus(100);
    CLK_SetCKCON3(0x0E);                                    //12MHz/2*5.33/8 = 4MHz 
#endif

#if (MCU_SYSCLK == 6000000)
    CLK_SetCKCON2(ENABLE_IHRCO);
    DelayXus(100);
    CLK_SetCKCON3(0x06);                                    //12MHz/2
    DelayXus(100);
#endif

#if (MCU_SYSCLK == 3000000)
    CLK_SetCKCON2(ENABLE_IHRCO);
    CLK_SetCKCON3(0x0A);                                    //12MHz/4
#endif
}


void Init_WDT(void)
{
    PCON1 |= WDTF;
    WDT_SetClock_32K_DIV_16_256ms();
    WDT_EnReset();
	WDT_Enable();		// ʹ�ܿ��Ź�
}

void ClearWDT(void)
{
    WDT_Clear();
}