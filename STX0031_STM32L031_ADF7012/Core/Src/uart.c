/***********************************************************************/
/*  FILE        :Uart.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include  <iostm8l051f3.h>				// CPU型号 
#include "main.h"
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "uart.h"		// uart
#include "eeprom.h"		// eeprom
#include "adf7012.h"		// RF IC

extern IWDG_HandleTypeDef hiwdg;
extern UART_HandleTypeDef huart2;

#define	TXD1_enable	(USART1_CR2 = 0x08)		// 允许发送	
#define RXD1_enable	(USART1_CR2 = 0x24)		// 允许接收及其中断	
//********************************************
//void UART1_INIT(void){	// 
////        PIN_UART_TX_direc = Output;
////        PIN_UART_TX_CR1 = 1;
//        //SYSCFG_RMPCR1_USART1TR_REMAP=2;
//	USART1_CR1 = 0;							// 1个起始位,8个数据位 
//	USART1_CR3 = 0;							// 1个停止位 
//	USART1_CR4 = 0;
//	USART1_CR5 = 0x00;//0x08;						// 半双工模式
//	USART1_BRR2 = 0x01;						// 设置波特率9600
//	USART1_BRR1 = 0x1A;						// 3.6864M/9600 = 0x180
//	                                                                //16.00M/9600 = 0x683
//	                                                               //4.00M/9600 = 0x1a1
//	//USART1_CR2 = 0x08;	// 允许发送
//        USART1_CR2 = 0x24;    // 允许接收及其中断
//	
//        //USART1_CR2 = 0x2C;    //允许发送 .   允许接收及其中断
//} 
//void UART1_end(void){		// 
//        //SYSCFG_RMPCR1_USART1TR_REMAP=0;
//	USART1_CR1 = 0;							// 1个起始位,8个数据位 
//	USART1_CR3 = 0;							// 1个停止位 
//	USART1_CR4 = 0;
//	USART1_CR5 = 0x00;						// 半双工模式
//	USART1_BRR2 = 0x00;						// 设置波特率9600
//	USART1_BRR1 = 0x00;						// 3.6864M/9600 = 0x180
//	                                                                //16.00M/9600 = 0x683
//        USART1_CR2 = 0x00;    //禁止串口
//} 

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){		// RXD中断服务程序 
	unsigned char dat;
	dat = rx_data[0];							// 接收数据
	
	if (dat=='(')  SIO_cnt = 0;
	SIO_buff[SIO_cnt] = dat;
	SIO_cnt = (SIO_cnt + 1) & 0x1F;
	if (dat==')'){
		for (dat=0;dat<SIO_cnt;dat++) {
			SIO_DATA[dat] = SIO_buff[dat];
		}
		BIT_SIO = 1;						// 标志
		//SIO_TOT = 20;	
	}
	UART_Start_Receive_IT(&huart2,rx_data,1);
} 
//--------------------------------------------
void Send_char(unsigned char ch){			// 发送字符
//	TXD1_enable;							// 允许发送	
//	while(!USART1_SR_TXE);
//	USART1_DR = ch;							// 发送
//	while(!USART1_SR_TC);					// 等待完成发送
//	RXD1_enable;							// 允许接收及其中断	
	
	HAL_UART_Transmit(&huart2,&ch,1,3000);
	UART_Start_Receive_IT(&huart2,rx_data,1);
}

unsigned char hex_asc(unsigned char hex)
{
	unsigned char i;
	hex = hex & 0x0F;
	if (hex < 0x0A) i = hex | 0x30;
	else i = hex + 0x37;
	return i;
}
unsigned char asc_hex_2(unsigned char asc1,unsigned char asc0)
{                                    
	unsigned char i; 
	i = (asc_hex(asc1) << 4) + (asc_hex(asc0) & 0x0F);
	return i;
} 
unsigned char asc_hex(unsigned char asc)	// HEX
{
	unsigned char i;
	if (asc < 0x3A) i = asc & 0x0F; 
	else i = asc - 0x37;
	return i;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

uint16_t FRE_NOW_bit;
int16_t  FRE_NOW_int;
#define MAX_LEVEL 21
const int8_t FRE_move[MAX_LEVEL] = {0,1,2,3,4,5,6,7,8,9,10,
                              -1,-2,-3,-4,-5,-6,-7,-8,-9,-10};

uint8_t Command_S=0,Command_FM=0,Command_END=0;
															
void PC_PRG(void)								// 串口命令
{
        uni_rom_id UART_ID_data;
	unsigned char  i,j;
	unsigned char  d3,d2,d1,d0;
	
	if (BIT_SIO){
		BIT_SIO = 0;
		//SIO_TOT = 20;
		switch (SIO_DATA[1]){
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 写操作               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'W': 
			//==================================== ID配置
			if (SIO_DATA[2]=='G')				// (WGd1d2d3) 
			{
				d1  = asc_hex_2(SIO_buff[3],SIO_buff[4]);
				d2  = asc_hex_2(SIO_buff[5],SIO_buff[6]);
				d3  = asc_hex_2(SIO_buff[7],SIO_buff[8]);
				
				UART_ID_data.IDB[0]=d3;
				UART_ID_data.IDB[1] = d2;
				UART_ID_data.IDB[2] = d1;
				UART_ID_data.IDB[3] = 0;		
                                ID_data.IDL= UART_ID_data.IDL;				
				//-------------------------------- 保存
				HAL_FLASHEx_DATAEEPROM_Unlock();
				WriteByteToFLASH(addr_eeprom_sys+0x10,d1);
				WriteByteToFLASH(addr_eeprom_sys+0x10,d1);
				WriteByteToFLASH(addr_eeprom_sys+0x11,d2);
				WriteByteToFLASH(addr_eeprom_sys+0x12,d3);
				HAL_FLASHEx_DATAEEPROM_Lock();
				
			
				
				//-------------------------------返回  (WG)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'G';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
			}		  
			//==================================== ADF7012
			if (SIO_DATA[2]=='H')				// (WHxd0d1d2d3) 
			{
			        i = asc_hex_2(0x30,SIO_buff[3]);
				d0 = asc_hex_2(SIO_buff[4],SIO_buff[5]);
				d1 = asc_hex_2(SIO_buff[6],SIO_buff[7]);
				d2 = asc_hex_2(SIO_buff[8],SIO_buff[9]);
				d3 = asc_hex_2(SIO_buff[10],SIO_buff[11]);
				
	                        //write Rx
                                ROM_adf7012_value[i].byte[0] = d0;
				ROM_adf7012_value[i].byte[1] = d1;
				ROM_adf7012_value[i].byte[2] = d2;
				ROM_adf7012_value[i].byte[3] = d3;
                                dd_write_7021_reg(&ROM_adf7012_value[i].byte[0]);
                                Delayus(25);  //delay 40us
									
				//-------------------------------- 保存
				j=0x20+i*4;
				HAL_FLASHEx_DATAEEPROM_Unlock();
				WriteByteToFLASH(addr_eeprom_sys+j,d0);
				WriteByteToFLASH(addr_eeprom_sys+j+1,d1);
				WriteByteToFLASH(addr_eeprom_sys+j+2,d2);
				WriteByteToFLASH(addr_eeprom_sys+j+3,d3);
				HAL_FLASHEx_DATAEEPROM_Lock();
				
				//ClearWDT(); // Service the WDT
				HAL_IWDG_Refresh(&hiwdg);
				//-------------------------------返回  (WHx)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'H';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);		
				Send_char(SIO_buff[3]);
				
			}		  
		        break;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 读操作               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'R':   
			//==================================== ID配置    //(RGx)
			if (SIO_DATA[2]=='G')		      //回复	// (RG)d1d2d3 
			{
			  	d1 = '(';
				d2 = 'R';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'G';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				     i = 2;
			  do{
			  	 d1 = hex_asc(ID_data.IDB[i] / 16);
				   d2 = hex_asc(ID_data.IDB[i] % 16);
				   Send_char(d1);
				   Send_char(d2);
				}
				while(i--);
			}		  
			//==================================== ADF7012   //(RHx)
			if (SIO_DATA[2]=='H')				// (RH)d0d1d2d3 
			{
			        i = asc_hex_2(0x30,SIO_buff[3]);
			  	d1 = '(';
				d2 = 'R';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'H';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);	
				for (j=0;j<4;j++){
			  	   d1 = hex_asc(ROM_adf7012_value[i].byte[j] / 16);
				   d2 = hex_asc(ROM_adf7012_value[i].byte[j] % 16);
				   Send_char(d1);
				   Send_char(d2);					   
				}
                        }			  
		        break;	
		case 'F':
			if(SIO_DATA[2]=='M')
			{
			 Command_FM = 1;
			  d1 = '(';
				d2 = 'O';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'K';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
			}
			if((SIO_DATA[2]=='C')&&(SIO_buff[3]=='?'))
			{
				
					FRE_NOW_bit = (ROM_adf7012_value[0].byte[3]>>2 )|((ROM_adf7012_value[0].byte[2]&0x1f)<<6);
				if((FRE_NOW_bit&0x400)!=0)
				{
					
					FRE_NOW_bit = (~FRE_NOW_bit);
					FRE_NOW_bit = FRE_NOW_bit&0x7ff;
					FRE_NOW_bit = FRE_NOW_bit+1;
					FRE_NOW_int = ~(FRE_NOW_bit)+1;
					//FRE_NOW_int = FRE_NOW_bit;
				}
				else//+
				{
					FRE_NOW_int = (int16_t)FRE_NOW_bit;
				}
				
		    for(FRE_NOW_bit= 0;FRE_NOW_bit<MAX_LEVEL;FRE_NOW_bit++)
				{
					if(FRE_move[FRE_NOW_bit] == FRE_NOW_int)
					{
						break;
					}
				}
				
				d1 = '(';
				d2 = 'F';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'C';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				d1 = hex_asc(FRE_NOW_bit / 16);
				d2 = hex_asc(FRE_NOW_bit % 16);
				Send_char(d1);
				Send_char(d2);
				
			}
			if((SIO_DATA[2]=='C')&&(SIO_buff[3]!='?'))
			{
				i = asc_hex_2(SIO_buff[3],SIO_buff[4]);
				if(i >= MAX_LEVEL) break;
				
				ROM_adf7012_value[0]=Default_adf7012_value[0];
				
			
				
//				FRE_NOW_bit = (ROM_adf7012_value[0].byte[3]>>2 )|((ROM_adf7012_value[0].byte[2]&0x1f)<<6);
//				if((FRE_NOW_bit&0x400)!=0)
//				{
//					
//					FRE_NOW_bit = (~FRE_NOW_bit);
//					FRE_NOW_bit = FRE_NOW_bit&0x7ff;
//					FRE_NOW_bit = FRE_NOW_bit+1;
//					FRE_NOW_int = ~(FRE_NOW_bit)+1;
//					//FRE_NOW_int = FRE_NOW_bit;
//				}
//				else//+
//				{
//					FRE_NOW_int = (int16_t)FRE_NOW_bit;
//				}
				FRE_NOW_int = 0;
				
				FRE_NOW_int = FRE_NOW_int + FRE_move[i];
				if(FRE_NOW_int > 1023) FRE_NOW_int = 1023;
				if(FRE_NOW_int < -1023) FRE_NOW_int = -1023;
				if(FRE_NOW_int >= 0)
				{
					FRE_NOW_bit = FRE_NOW_int;
				}
				else
				{
					FRE_NOW_bit = ~(0-FRE_NOW_int)+1;
				}
				
				ROM_adf7012_value[0].byte[3]= ((FRE_NOW_bit&0x3f)<<2)|(ROM_adf7012_value[0].byte[3]&0X03);
				ROM_adf7012_value[0].byte[2]= ((FRE_NOW_bit&0x7c0)>>6)|(ROM_adf7012_value[0].byte[2]&0XE0);
				
				 dd_write_7021_reg(&ROM_adf7012_value[0].byte[0]);
				
				HAL_FLASHEx_DATAEEPROM_Unlock();
				WriteByteToFLASH(addr_eeprom_sys+0x20,ROM_adf7012_value[0].byte[0]);
				WriteByteToFLASH(addr_eeprom_sys+0x20+1,ROM_adf7012_value[0].byte[1]);
				WriteByteToFLASH(addr_eeprom_sys+0x20+2,ROM_adf7012_value[0].byte[2]);
				WriteByteToFLASH(addr_eeprom_sys+0x20+3,ROM_adf7012_value[0].byte[3]);
				HAL_FLASHEx_DATAEEPROM_Lock();
				
				d1 = '(';
				d2 = 'O';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'K';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				
			}
			 break;
		case 'S':
			 Command_S = 1;
			  d1 = '(';
				d2 = 'O';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'K';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
			break;
		case 'E':
			if((SIO_DATA[2]=='N')&&(SIO_DATA[3]=='D'))
			{
			 Command_END = 1;
			  d1 = '(';
				d2 = 'O';
				Send_char(d1);
				Send_char(d2);		
				d1 = 'K';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
			}
			break;
			
			
		default:
			break;
                        
		}
	}
}