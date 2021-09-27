#include  <iostm8l051f3.h>				// CPU型号 
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "uart.h"		// uart
#include "eeprom.h"		// eeprom
#include "adf7012.h"		// RF IC

unsigned char   Flag_uart_handle = 0;

//9600 e 8 1

void UART1_INIT_handle(void)
{	
  
        USART1_CR1 = 0x04;							// 1个起始位,8个数据位 
	USART1_CR3 = 0;							// 1个停止位 
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;//0x08;						// 半双工模式
	USART1_BRR2 = 0x01;						// 设置波特率9600
	USART1_BRR1 = 0x1A;						// 3.6864M/9600 = 0x180
	                                                                //16.00M/9600 = 0x683
	                                                               //4.00M/9600 = 0x1a1
	//USART1_CR2 = 0x08;	// 允许发送
        USART1_CR2 = 0x24;    // 允许接收及其中断
        Flag_uart_handle = 1;

}
 
void UART1_RX_RXNE_handle(void)
{
     ;
}

void Uart_handle(void)
{
     ;

}
