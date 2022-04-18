#include "gpio.h" 
#include "timer.h"
#include "uart.h"
#include "IAP_flash.h"
#include "spi.h"  
#include "ML7345.h"
#include "adc.h"
#include "key_and_Other.h"
#include <Stdio.h>  // for printf
//ID 00000001
//xdata u8 g_txBuffer1[12] = {0x95,0x55,0x55,0x55,0x55,0x55,0x56,0x55,0x95,0x55,0x56,0x55};//open
//xdata u8 g_txBuffer2[12] = {0x95,0x55,0x55,0x55,0x55,0x55,0x59,0x55,0x95,0x55,0x59,0x55};//stop   /* RF Tx buffer */
//xdata u8 g_txBuffer3[12] = {0x95,0x55,0x55,0x55,0x55,0x55,0x65,0x55,0x95,0x55,0x65,0x55}; //close
//xdata u8 sw = 0;

void main()
{
    Init_WDT();
    Init_Clock(); 
    Init_IAP_flash();
    Init_Timer0();
    eeprom_sys_load();
    Init_Port();
    Init_Spi();
    Init_Adc(); 
    _Init_RAM();
    Init_Beep(); 
    test_mode_control();
    Init_Interrupt();
    INT_EnAll();
    Adc_Start();
    TIME_power_on_AD = 30;
    
    while(1) 
    {
        ClearWDT(); 
        key_check();
        time_control();
        AD_control();
        
	//if((TB_5s==0)&&(m_KeyOptSetMode==0)&&(m_KeyDupli1stTimer==0)&&(FG_PWRON==1)){
        if((TB_5s==0)&&(m_KeyOptSetMode==0)&&(FG_PWRON==1)&&(key_Value!=2)&&(FLAG_APP_TX==0))//2015.4.13ÐÞÕý
        {  
            FG_PWRON=0;
            PIN_POWER_CONTROL=0;
            FG_10s=1;    // 2015.1.31ÐÞÕý3
          /*******************2015.1.31ÐÞÕý2************************/
            while(1){
               if(FG_Complex_Single_shot==1)ClearWDT(); // Service the WDT
                else if((FG_Complex_Single_shot==0)&&(m_KeyNo>=1)&&(m_KeyNo<=4)){
                    key_check();
                    ClearWDT(); // Service the WDT
                }
            }
        }
    }
}


