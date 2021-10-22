#include  <iostm8l051f3.h>				// CPU型号 
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "uart.h"		// uart
#include "eeprom.h"		// eeprom
#include "adf7012.h"		// RF IC
#include "uart_handle.h"

UINT32 get_timego(UINT32 x_data_his);

unsigned char   Flag_uart_handle = 0;

#define RX_BUFF_MAX 32
#define TX_BUFF_MAX_UART 5

UINT8  UART_RX_BUFF[RX_BUFF_MAX];
UINT8  UART_TX_BUFF_NEW[TX_BUFF_MAX_UART];
static UINT8  RX_COUNT_IN = 0;
static UINT8  RX_COUNT_OUT = 0;
//static UINT8  TX_COUNT_IN = 0;
//static UINT8  TX_COUNT_OUT = 0;
COMM_HANDLE_TYPE COMM_STEP=COMM_IDLE;
UINT32 timeuart,time_keylevel;
extern UINT32  time1ms_count ;
//UINT8 Flag_UART_OPEN=1;
//9600 e 8 1

void UART1_INIT_handle(void)
{	
  
        USART1_CR1 = 0x04;//0x04;							// 1个起始位,8个数据位 
	USART1_CR3 = 0x00;							// 1个停止位 
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;						// 半双工模式
	USART1_BRR2 = 0x01;						// 设置波特率9600
	USART1_BRR1 = 0x1A;//0x1A;						// 3.6864M/9600 = 0x180
	                                                                //16.00M/9600 = 0x683
	                                                               //4.00M/9600 = 0x1a1
	//USART1_CR2 = 0x08;	// 允许发送
        USART1_CR2 = 0x24;    // 允许接收及其中断
        Flag_uart_handle = 1;
        
        RX_COUNT_IN = 0;
	RX_COUNT_OUT = 0;
	//TX_COUNT_IN = 0;
	//TX_COUNT_OUT = 0;
        COMM_STEP=COMM_IDLE;
}
 
void UART1_RX_RXNE_handle(void)
{
    unsigned char dat;
	dat = USART1_DR;
     if(((RX_COUNT_IN+1)%RX_BUFF_MAX)!=RX_COUNT_OUT)//
     {
		        timeuart = time1ms_count;
                        UART_RX_BUFF[RX_COUNT_IN%RX_BUFF_MAX]=dat;
			RX_COUNT_IN++;
			if(RX_COUNT_IN >= RX_BUFF_MAX)
			{
				RX_COUNT_IN = 0;
			}

    }
}

UINT16 GET_READNUM(void)
{
	UINT16 Tp_number=0;
	if(RX_COUNT_OUT > RX_COUNT_IN)     
        {					
	     		 Tp_number = RX_COUNT_IN + RX_BUFF_MAX - RX_COUNT_OUT ;
				}					
				else
				{
					Tp_number = RX_COUNT_IN - RX_COUNT_OUT;
				}
	return  Tp_number;
}



void Uart_handle(void)
{
#ifdef NEWFUN_ADD
  static unsigned char dat[5]={0};
     unsigned char  Tp_i;
    switch(COMM_STEP)
     {
     case COMM_IDLE:
       if(GET_READNUM()==5)
       {
        for(Tp_i=0;Tp_i<5;Tp_i++)
        {
         dat[Tp_i] = UART_RX_BUFF[RX_COUNT_OUT];
         RX_COUNT_OUT = (RX_COUNT_OUT+1)%RX_BUFF_MAX;
        }
        
        if((dat[0]==0x3)&&(dat[1]==0x3)&&((unsigned char)(dat[0]+dat[1]+dat[2]+dat[3])==dat[4]))
        {
            if(FG_10s==1)
            {
              COMM_STEP = COMM_NACK;
            }
            else
            {
            switch(dat[2])
            {
              case 0x01://key and sensor
                if(dat[3]&0x80)
                {
                  Flag_UART_STARTUP = 1;
                }
                else
                {
                  Flag_UART_STARTUP = 0;
                }
                if(dat[3]&0x40)
                {
                  Flag_UART_OPEN = 1;
                }
                else
                {
                  Flag_UART_OPEN = 0;
                }
                if(dat[3]&0x20)
                {
                  Flag_UART_STOP = 1;
                }
                else
                {
                  Flag_UART_STOP = 0;
                }
                if(dat[3]&0x10)
                {
                  Flag_UART_CLOSE = 1;
                }
                else
                {
                  Flag_UART_CLOSE = 0;
                }
                if(dat[3]&0x08)
                {
                  Flag_UART_ONEPOINT = 1;
                }
                else
                {
                  Flag_UART_ONEPOINT = 0;
                }
                if(dat[3]&0x04)
                {
                  Flag_UART_REG = 1;
                }
                else
                {
                  Flag_UART_REG = 0;
                }
                 time_keylevel = time1ms_count;
                COMM_STEP = COMM_ACK;
              break;
              
              
              
               
              //case :
              // break;
               default:
                 COMM_STEP = COMM_NACK;
              break;
            }
            }
        }
        else
        {
          COMM_STEP = COMM_NACK;
        }
        
       }
       else if(GET_READNUM()>5)
       {
         COMM_STEP = COMM_NACK;
       }
       else if((GET_READNUM()<5)&&(GET_READNUM()!=0))
       {
         if(get_timego(timeuart)>200)
         {
            COMM_STEP = COMM_NACK;
         }
       }
         
       
       break;
    
     case COMM_ACK:
       if(get_timego(time_keylevel)>50)
       {
       
       
       UART_TX_BUFF_NEW[0]=0x03;
       
       UART_TX_BUFF_NEW[1]=0x02;
       
       UART_TX_BUFF_NEW[2]=0x00;
       
       UART_TX_BUFF_NEW[3] = UART_TX_BUFF_NEW[0]+UART_TX_BUFF_NEW[1]+UART_TX_BUFF_NEW[2];
       
      for(Tp_i=0;Tp_i<4;Tp_i++)
      {
         Send_char(UART_TX_BUFF_NEW[Tp_i]);
       }
       RX_COUNT_OUT = RX_COUNT_IN;
        COMM_STEP = COMM_IDLE;
       }
       break;
      case COMM_NACK:
        if(get_timego(time_keylevel)>50)
        {
       UART_TX_BUFF_NEW[0]=0x03;
       UART_TX_BUFF_NEW[1]=0x02;
       UART_TX_BUFF_NEW[2]=0x01;
       UART_TX_BUFF_NEW[3] = UART_TX_BUFF_NEW[0]+UART_TX_BUFF_NEW[1]+UART_TX_BUFF_NEW[2];
       for(Tp_i=0;Tp_i<4;Tp_i++)
       {
          Send_char(UART_TX_BUFF_NEW[Tp_i]);
       }
       RX_COUNT_OUT = RX_COUNT_IN;
        COMM_STEP=COMM_IDLE;
        }
       break; 
     
     default:
       break;
     }
#endif
}
