/***********************************************************************/
/*  FILE        :eeprom.c                                              */
/*  DATE        :June, 2011                                            */
/*  DESCRIPTION :routine for VHF60-2011                                */
/*  CPU TYPE    :STM8S207C8                                            */
/*  Programmer	:Gong Dong Sheng                                       */
/*  Mark        :STM8S207C8的CODE空间为64K                             */
/*              :STM8S207C8的EEPROM的大小为1536字节,即:3页,512节/页    */
/***********************************************************************/
#include  <iostm8l151c6.h>				// CPU型号 
//#include "stm8l15x.h"

#include "initial.h"		// 初始化  预定义
#include "Pin_define.h"		// 管脚定义
#include "ram.h"		// RAM定义
#include "ram_cyw.h"		// RAM定义
#include "eeprom.h"		// eeprom
#include "eeprom_cyw.h"		// eeprom
#include "lcd_cyw.h"
#include "pcf8563_cyw.h"
#include "key_and_Other_cyw.h"

#if(ProductID==Hanging_display)//
void eeprom_kai_save(void){
	unsigned char	i;  
	 ClearWDT(); // Service the WDT
	UnlockFlash( UNLOCK_EEPROM_TYPE );
	for (i=0;i<2;i++)
		WriteByteToFLASH( addr_eeprom_sys+i+16+0x80, open_timer_Store[i]);
        
       //for (i=0;i<2;i++)
	//	WriteByteToFLASH( addr_eeprom_sys+i+16+0x84, last_open_timer[i]);
	LockFlash( UNLOCK_EEPROM_TYPE );
         Delayus(5);
} 
void eeprom_guan_save(void){
	unsigned char	i;  
	 ClearWDT(); // Service the WDT
	UnlockFlash( UNLOCK_EEPROM_TYPE );
	for (i=0;i<2;i++)
		WriteByteToFLASH( addr_eeprom_sys+i+16+0x82, close_timer_Store[i]);
       // for (i=0;i<2;i++)
	//	WriteByteToFLASH( addr_eeprom_sys+i+16+0x86, last_close_timer[i]);
	LockFlash( UNLOCK_EEPROM_TYPE );
         Delayus(5);
} 
//
void eeprom_kaiguan_load(void)
{
       unsigned char	i;  
       for (i=0;i<2;i++)
          open_timer_Store[i] =  ReadByteEEPROM( addr_eeprom_sys+i+16+0x80 );
       for (i=0;i<2;i++)
           close_timer_Store[i] =  ReadByteEEPROM( addr_eeprom_sys+i+16+0x82 );
       
       if((decimal(open_hour) >= 24)&&(open_hour!=0xff))
       {
           open_hour = 0x00;
           
           eeprom_kai_save();
       }
       if((decimal(open_min) >= 60)&&(open_min!=0xff))
       {
           open_min = 0x00;
           eeprom_kai_save();
       }
        if((decimal(close_hour) >= 24)&&(close_hour!=0xff))
       {
           close_hour = 0x00;
           eeprom_guan_save();
       }
       if((decimal(close_min) >= 60)&&(close_min!=0xff))
       {
           close_min = 0x00;
           eeprom_guan_save();
       }
     //  for (i=0;i<2;i++)
     //     last_open_timer[i] =  ReadByteEEPROM( addr_eeprom_sys+i+16+0x84 );
     //  for (i=0;i<2;i++)
     //      last_close_timer[i] =  ReadByteEEPROM( addr_eeprom_sys+i+16+0x86 );
}

void eeprom_diqu_save(void)
{
     ClearWDT(); // Service the WDT
  UnlockFlash( UNLOCK_EEPROM_TYPE );
     WriteByteToFLASH( addr_eeprom_sys+16+0x84, DISP_DIQU);
     LockFlash( UNLOCK_EEPROM_TYPE );
      Delayus(5);
}

void eeprom_diqu_load(void)
{
    DISP_DIQU =  ReadByteEEPROM( addr_eeprom_sys+16+0x84 );
    if(DISP_DIQU>7)//8个地区
    {
      DISP_DIQU = 0;
      eeprom_diqu_save();
    }
}

void eeprom_kaimode_save(void)
{ 
     ClearWDT(); // Service the WDT
  UnlockFlash( UNLOCK_EEPROM_TYPE );
  if(TIMER_MODE_OPEN < 3)
  {
    WriteByteToFLASH( addr_eeprom_sys+16+0x86, TIMER_MODE_OPEN);
  }
    LockFlash( UNLOCK_EEPROM_TYPE );
     Delayus(5);
}

void eeprom_guanmode_save(void)
{ 
     ClearWDT(); // Service the WDT
  UnlockFlash( UNLOCK_EEPROM_TYPE );
  if(TIMER_MODE_CLOSE < 3)
  {
    WriteByteToFLASH( addr_eeprom_sys+16+0x88, TIMER_MODE_CLOSE);
  }
   LockFlash( UNLOCK_EEPROM_TYPE );
     Delayus(5);
}

void eeprom_kaiguanmode_load(void)
{ 
     //在调用之前必须执行开关时间的LOAD
     TIMER_MODE_OPEN = ReadByteEEPROM( addr_eeprom_sys+16+0x86 );
     TIMER_MODE_CLOSE = ReadByteEEPROM( addr_eeprom_sys+16+0x88 );
     if(TIMER_MODE_OPEN >= 3)
     {
       TIMER_MODE_OPEN = Timer_Mode_SET;
       eeprom_kaimode_save();
     }
     
     if(TIMER_MODE_OPEN == Timer_Mode_OFF)
     {
        if((open_hour!=0xff)||(open_min!=0xff))
        {
          open_hour = 0xff;
          open_min = 0xff;
          //TIMER_MODE_OPEN = Timer_Mode_SET;
         // eeprom_kaimode_save();
          eeprom_kai_save();
        }
     }
     if(TIMER_MODE_OPEN == Timer_Mode_SET)
     {
        if((open_hour==0xff)||(open_min==0xff))
        {
          open_hour = 0;
          open_min = 0;
          //TIMER_MODE_OPEN = Timer_Mode_SET;
         // eeprom_kaimode_save();
          eeprom_kai_save();
        }
     }
      if(TIMER_MODE_CLOSE >= 3)
     {
       TIMER_MODE_CLOSE = Timer_Mode_SET;
       eeprom_guanmode_save();
     }
     
     if(TIMER_MODE_CLOSE == Timer_Mode_OFF)
     {
        if((close_hour!=0xff)||(close_min!=0xff))
        {
          close_hour = 0xff;
          close_min = 0xff;
          //TIMER_MODE_OPEN = Timer_Mode_SET;
         // eeprom_kaimode_save();
          eeprom_guan_save();
        }
     }
     if(TIMER_MODE_CLOSE == Timer_Mode_SET)
     {
        if((close_hour==0xff)||(close_min==0xff))
        {
          close_hour = 0;
          close_min = 0;
          //TIMER_MODE_OPEN = Timer_Mode_SET;
         // eeprom_kaimode_save();
          eeprom_guan_save();
        }
     }
     
}


void eeprom_kaiguanlast_save(void)
{
    unsigned char	i;  
     ClearWDT(); // Service the WDT
    UnlockFlash( UNLOCK_EEPROM_TYPE );
    for (i=0;i<2;i++)
    {
        if(last_open_timer[i]!=0xff)
        {
            WriteByteToFLASH( addr_eeprom_sys+16+0x8a+i, last_open_timer[i]);
        }
   } 
    ClearWDT(); // Service the WDT
  Delayus(5);
    for (i=0;i<2;i++)
    {
        if(last_close_timer[i]!=0xff)
        {
           WriteByteToFLASH( addr_eeprom_sys+16+0x8c+i, last_close_timer[i]);
        }
    }
    LockFlash( UNLOCK_EEPROM_TYPE );
     Delayus(5);
}


void eeprom_kaiguanlast_load(void)
{
   unsigned char i; 
   unsigned char flag_flag = 0;
    //  if(TIMER_MODE_OPEN==Timer_Mode_SET)
    //  {
           
     //      for (i=0;i<2;i++)
      //     last_open_timer[i] = open_timer_Store[i];
     // }
     //// else
    //  {
           for (i=0;i<2;i++)
           last_open_timer[i] = ReadByteEEPROM( addr_eeprom_sys+16+0x8a+i );
              Delayus(5);
    //  }
     // if(TIMER_MODE_CLOSE==Timer_Mode_SET)
     // {
     //     for (i=0;i<2;i++)
     //     last_close_timer[i] =close_timer_Store[i];
     // }
     // else
     // {
          for (i=0;i<2;i++)
          last_close_timer[i] = ReadByteEEPROM( addr_eeprom_sys+16+0x8c+i );
     // }
          
          if(decimal(last_open_hour)>=24)
          {
             last_open_hour = 0;
             flag_flag = 1;
            
          }
          if(decimal(last_open_min)>=60)
          {
             last_open_min = 0;
             flag_flag = 1;
             
          }
          if(decimal(last_close_hour)>=24)
          {
             last_close_hour = 0;
             flag_flag = 1;
            
          }
          if(decimal(last_close_min)>=60)
          {
             last_close_min = 0;
             flag_flag = 1;
             
          }
          if(flag_flag == 1)
          {
            eeprom_kaiguanlast_save();
          }
          
}
#endif