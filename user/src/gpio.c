#include "gpio.h"


/***********************************************************************************
函数名称:   void InitPort(void)
功能描述:   IO配置
输入参数:   
返回参数:     
*************************************************************************************/
void Init_Port(void)
{ 
    /* KEY OPEN/STOP: P12/P11; PIN_test_mode: P13*/
    PORT_SetP1OpenDrain(BIT1|BIT2|BIT3);                // 设置 P11/P12/P13为开漏输出
    P11 = 1;P12 = 1;P13 = 1;                            // P11/P12/P13设为输入模式
    PORT_EnP10P11P12P13PullHigh();                      // 使能 P10,P11,P12,P13 上拉
    
    /* SPI */
    //PORT_SetP1PushPull(BIT4|BIT5|BIT7);					// 设置P15(MOSI),P17(SPICLK)为准双向口
	//PORT_SetP1OpenDrain(BIT6);							// 设置P16(MISO)为准双向口
    //P16 = 1;                                            // 输入
	//PORT_EnP14P15P16P17PullHigh();						// 使能 P14,P15,P16,P17 上拉
    
    /*KEY CLOSE:P25; BEEP:P20; 登录:P21; ML7345D_GPIO3:P24; 送信LED:P27 */
	PORT_SetP2OpenDrain(BIT1);                          // 设置P21 为开漏输出
    P21 = 1;                                            // P21设为输入模式
    
    PORT_SetP2PushPull(BIT0|BIT7);                      // 设置P20/P27 为推挽输出
    
    PORT_SetP2OpenDrain(BIT5);
    P25 = 1;                                            // 设置P25为输入
    
    PORT_EnP20P21P22P23PullHigh();                      // 使能 P20,P21,P22,P23 上拉
	PORT_EnP24P25P26P27PullHigh();			            // 使能 P24,P25,P26,P27 上拉
    P20 = 0;

    /* ML7345_RESETN:P34; ML7345D_POWER:P35; */
    PORT_SetP3PushPull(BIT5);                      // 设置P34/P35 为推挽输出
    
    /* PIN_POWER_CONTROL:P40 */
    PORT_SetP4PushPull(BIT0);                           // 设置P40为推挽输出
    
    //////////////////////test/////////////////////////
    //PORT_SetP6PushPull(BIT0);   //CLK OUT
    //AUXR0 &= ~(P60OC0|P60OC1);
    //AUXR0 |= (0x80|P60FD);      //MCK/2 output 
    //////////////////////test/////////////////////////
   
    ML7345_RESETN = 0;
    PIN_TX_LED = 0;
    PIN_POWER_CONTROL = 0;
    ML7345D_POWER = FG_NOT_allow_out;
    
    PORT_SetP2OpenDrain(BIT2|BIT3|BIT4|BIT6);           //未用IO口全部设为输入
    P22=1;P23=1;P24=1;P26=1;
    PORT_SetP3InputOnly(BIT2);
    PORT_SetP4OpenDrain(BIT1);
    P41=1;
}

void SpiGpio_Init(void)
{
    PORT_SetP1PushPull(BIT4|BIT5|BIT7);					// 设置P15(MOSI),P17(SPICLK)为准双向口
	PORT_SetP1OpenDrain(BIT6);							// 设置P16(MISO)为准双向口
    P16 = 1;                                            // 输入
	PORT_EnP14P15P16P17PullHigh();
    PORT_SetP3PushPull(BIT4);
}

void SpiGpio_UnInit(void)
{
    PORT_SetP1OpenDrain(BIT4|BIT5|BIT6|BIT7);
    P16 = 0;                                            // 输入
    P14 = 0;P15 = 0;P17 = 0;
    
    PORT_SetP3InputOnly(BIT4);
}


/***********************************************************************************
函数名称:   void InitINT0(void)
功能描述:   INT0初始化
输入参数:   
返回参数:  
用于ML7345D 发送接收完成中断。
*************************************************************************************/
/*
void Init_INT0(void)
{
	INT_SetINT0P32();						//设置INT0引脚P32
	INT_SetINT0_DetectFallingEdge();		//设置INT0外部中断检测方式为下降沿检测
	//INT_SetINT0_DetectRisingEdge();
    INT_SetINT0Filter_Sysclk_x3();			//设置INT0滤波为（sysclk）*3
}
*/

/***********************************************************************************
函数名称:   void InitINT1(void)
功能描述:   INT1初始化
输入参数:   
返回参数:   
ML7345D BER测试。
*************************************************************************************/
void Init_INT1(void)
{
	INT_SetINT1P33();						//设置INT1引脚P33
	//INT_SetINT1_DetectRisingEdge();		
    INT_SetINT1_DetectFallingEdge();        //设置INT1外部中断检测方式为下降沿检测
	INT_SetINT1Filter_Sysclk_x3();			//设置INT1滤波为（sysclk）*3
}


/***********************************************************************************
函数名称:   void INT_INT0(void)	
功能描述:INT0中断服务程序
输入参数:   
返回参数: 

用于ML7345D发送接收完成中断。

*************************************************************************************/
void INT_INT0(void)		interrupt INT_VECTOR_INT0
{
    ML7345_TRX_Del();
}


/***********************************************************************************
函数名称:   void INT_INT1(void)	
功能描述:INT1中断服务程序
输入参数:   
返回参数:    

ML7345D BER测试。

*************************************************************************************/
void INT_INT1(void)		interrupt INT_VECTOR_INT1
{
    ML7345_TRX_Del();
}


/***********************************************************************************
函数名称:   void InitInterrupt(void)
功能描述:   中断初始化
输入参数:    
返回参数:     
*************************************************************************************/
void Init_Interrupt(void)
{
    Init_INT1();
	INT_EnINT1();			//	使能INT1中断
}


/*
u8 key_scan(void)
{
    if((PIN_KEY_OPEN==0 | PIN_KEY_STOP==0 | PIN_KEY_CLOSE==0 | PIN_KEY_LOGIN==0))
    {
        delay_ms(50);
        if((PIN_KEY_OPEN==0 | PIN_KEY_STOP==0 | PIN_KEY_CLOSE==0 | PIN_KEY_LOGIN==0) && key_flag == 0)
        {
            key_flag = 1;
            if(PIN_KEY_OPEN==0)         return 2;
            else if (PIN_KEY_STOP==0)   return 3;
            else if (PIN_KEY_CLOSE==0)  return 4;
            else if (PIN_KEY_LOGIN==0)  return 5;
            else return 1;
        }
        else return 0;
            
    }
    else if(PIN_KEY_OPEN==1 && PIN_KEY_STOP==1 && PIN_KEY_CLOSE==1 && PIN_KEY_LOGIN==1)
    {
        key_flag = 0;
        return 0;
    }
    return 0;    
}*/


