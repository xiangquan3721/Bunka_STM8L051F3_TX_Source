/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include  <iostm8l151c6.h>				// CPU型号 
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "Timer.h"		// 定时器
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断
#include "key_and_Other.h"		// 按键
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart
#include "ad.h"		        // AD
#include "initial_cyw.h"        // 初始化  预定义
#include "ram_cyw.h"		// RAM定义
#include "key_and_Other_cyw.h"		// 按键
#include "eeprom_cyw.h"		// eeprom
#include "lcd_cyw.h"		// eeprom
#include "pcf8563_cyw.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  _DI();		// 关全局中断
  RAM_clean(); 		// 清除RAM  
  
  
   #if(ProductID==Hanging_none)//不带屏的初始化
  VHF_GPIO_INIT();
  WDT_init();
   #endif
  
   #if(ProductID==Hanging_display)//带屏的初始化
  VHF_GPIO_INIT_cyw();
 // WDT_init_cyw();
  #endif
  
  
  SysClock_Init();
  EXIT_init();
  InitialFlashReg();
  eeprom_sys_load();
  
   #if(ProductID==Hanging_display)//带屏的初始化
  Power_On_Init_cyw();
  #endif
  
  
  _Init_RAM();
  TIM4_Init();
  
  START_AD_SAMPLER();
  

    
   // while(PIN_test_mode==0){
    while(PIN_test_mode==0){//这句是测试
   PIN_POWER_CONTROL=1;
    //PIN_TX_LED=1;
    LED_ON;
    UART1_INIT();
    _EI();    
    test_mode_control();
    }
  _EI();		// 允许中断	
  //beep_init();//2015.3.13修正

  
  FLAG_POWER = 1;
  
  
  /* Infinite loop */
  while (1)
  {     
    
       // PIN_LED=!PIN_LED;
        
        
        ClearWDT(); // Service the WDT
	key_check();
        ClearWDT(); // Service the WDT
	AD_control();
        ClearWDT(); // Service the WDT
        time_control();
        
        #if(ProductID==Hanging_display)//
     
       if(FLAG_PRESS) FLAG_PRESS--;//按键防抖
       ClearWDT(); // Service the WDT
	key_scan();//按键扫描
        ClearWDT(); // Service the WDT
        lcd_backlight();//lcd背光控制
        ClearWDT(); // Service the WDT
        power_control();//power控制 规格书第二版背光与电源同步了 普通模式等5S关  其它模式等10S进入普通模式 TB_POWER无效变量
        ClearWDT(); // Service the WDT
        openclose_output();//开关控制
        ClearWDT(); // Service the WDT
        //dianciqianya_lcd();//电池欠压表示
        Power_Low();
        ClearWDT(); // Service the WDT
        real_time();
       
      #endif
        
         
        if((TB_5s==0)&&(m_KeyOptSetMode==0)&&(FG_PWRON==1)&&(key_Value!=2)&&(FLAG_APP_TX==0)&&(FLAG_POWER == 1)){
	  FG_PWRON=0;
	  PIN_POWER_CONTROL=0;
         
          
          FG_10s=1;    // 2015.1.31修正3
          /********************2015.1.31修正2************************/
	  while(1){   
            if(FG_Complex_Single_shot==1)
            {
              ClearWDT(); // Service the WDT 
            }
            else if((FG_Complex_Single_shot==0)&&(m_KeyNo>=1)&&(m_KeyNo<=4))
            {
              key_check();
              ClearWDT(); // Service the WDT 
            }    
            else
            {
              WDT_reinit();
              while(1);
            }
          }
          /*********************************************************/
	}
        
        
        
        //if((TB_5s==0)&&(m_KeyOptSetMode==0)&&(FG_PWRON==1)&&(FLAG_MODE == CONTROL_mode)){
	//  FG_PWRON=0;
	//  PIN_POWER_CONTROL=0;
	// while(1);  
        // }
          
        
      
 }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
