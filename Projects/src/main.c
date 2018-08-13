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
//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l051f3.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "Timer.h"		// 定时器
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断
#include "key_and_Other.h"		// 按键
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  _DI();		// 关全局中断
  RAM_clean(); 		// 清除RAM  
  VHF_GPIO_INIT();
  WDT_init();
  SysClock_Init();
  EXIT_init();
  InitialFlashReg();
  eeprom_sys_load();
  _Init_RAM();
  TIM4_Init();
    while(PIN_test_mode==0){
    PIN_POWER_CONTROL=1;
    PIN_TX_LED=1;
    UART1_INIT();
    _EI();    
    test_mode_control();
    }
  _EI();		// 允许中断	
  beep_init();

  /* Infinite loop */
  while (1)
  {     
        ClearWDT(); // Service the WDT
	key_check();
	time_control();
	
	if((TB_5s==0)&&(m_KeyOptSetMode==0)&&(m_KeyDupli1stTimer==0)&&(FG_PWRON==1)){
	  FG_PWRON=0;
	  PIN_POWER_CONTROL=0;
	  while(1);
//	  TB_5s=50;     //以后硬件电源装配好后  注释掉以下语句
//	  WWDG_CR_WDGA=1;
//	  WWDG_CR_T6=0;   
	}
		
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
