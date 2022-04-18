#include "uart.h"

#if (MCU_SYSCLK == 16000000)
#define BAUD_RATE    0x98
#endif

#if (MCU_SYSCLK == 6000000)
#define BAUD_RATE     0xD9
#endif

#if (MCU_SYSCLK == 4000000)
#define BAUD_RATE     0xE6
#endif

#if (MCU_SYSCLK == 3000000)
#define BAUD_RATE     0xED
#endif


xdata u8 uart0_rx_len = 0;
xdata u8 uart0_tx_len = 0;

xdata u8 UartStatus = FrameHeadSataus;
xdata u8 UartLen = 0;
xdata u8 UartCount = 0;
xdata u8 UART_DATA_buffer[UartBuff_MaxLength] = {0};
xdata u8 UART_DATA_ID98[41] = {0};

xdata __Databits_t Databits_t = {0};
xdata __U1Statues U1Statues = {0};
xdata u8 ACKBack[3] = {0x02, 0x03, 0x00};
xdata u8 U1AckTimer = 0;

xdata u8 FLAG_testNo91=0;
xdata u8 FLAG_testBEEP=0;
xdata u8 FLAG_testNo91_step=0;
xdata u8 FLAG_testNo91SendUart=0;


/***********************************************************************************
函数名称:   void InitUart0_S1BRG(void)
功能描述:   Uart0初始化
		 使用S1BRG作为波特率来源
输入参数:   
返回参数:     
*************************************************************************************/
/*
void Init_Uart0_S1BRG(void)
{
	//PORT_SetP3QuasiBi(BIT0|BIT1|BIT3|BIT4|BIT5);		// 设置 P30,P31作为准双向口
    
	UART0_SetMode8bitUARTVar();			// 8位 可变波特率
	UART0_EnReception();				// 使能UART1接收数据
	
	UART0_SetBRGFromS1BRG();			// 设置波特率来源为 S1BRG
	UART0_SetS1BRGBaudRateX2();			// 设置2x波特率
	UART1_SetS1BRGSelSYSCLK();			// 设置S1BRG时钟输入为Sysclk

    // 设置波特率
	UART1_SetS1BRGValue(S1BRG_BRGRL_9600_2X_24000000_1T); 
	
	UART1_EnS1BRG();					// 开启S1BRG时钟
}
*/

//P119; 波特率baud: TH1 = 256 - (SYSCLK / (baud / ((2^SMOD1 * 2^(SMOD2*2))/32)))
void Init_Uart0_T1(void)
{
    UART0_SetMode8bitUARTVar();			// 8位 可变波特率
	UART0_EnReception();				// 使能UART0接收数据
	
	UART0_SetBRGFromT1();				// 设置波特率来源为 T1
	UART0_SetT1BaudRateX2();			// 设置2x波特率,SMOD1=1,SMOD2=0

	TM_SetT1Mode_2_8BIT_AUTORELOAD();
	TM_SetT1Clock_SYSCLK();
	TM_SetT1Gate_Disable(); 

    // 设置波特率
	TM_SetT1HighByte(BAUD_RATE);
	TM_SetT1LowByte(BAUD_RATE);

	TM_EnableT1();
    INT_EnUART0();			//	使能串口中断
}

void UART1_end(void)
{
    TM_DisableT1();
    INT_DisUART0();
}
/*
//P119; 波特率baud: TH1 = 256 - (SYSCLK / (baud / ((2^SMOD1 * 2^(SMOD2*2))/32)))
void Init_Uart0_T1_ODD(void)
{
    UART0_SetMode9bitUARTVar();			// 9位 可变波特率
	UART0_EnReception();				// 使能UART0接收数据
	 
	UART0_SetBRGFromT1();				// 设置波特率来源为 T1
	UART0_SetT1BaudRateX2();			// 设置2x波特率,SMOD1=1,SMOD2=0

	TM_SetT1Mode_2_8BIT_AUTORELOAD();   // 定时器1工作在8位自动重载定时器/计数模式
	TM_SetT1Clock_SYSCLK();             // T1X12=1,
	TM_SetT1Gate_Disable(); 

    // 设置波特率
#if (MCU_SYSCLK == 16000000)
    TM_SetT1HighByte(T1_BRGRL_9600_2X_16000000_1T);
	TM_SetT1LowByte(T1_BRGRL_9600_2X_16000000_1T);
#endif
    
#if (MCU_SYSCLK == 24000000)
	TM_SetT1HighByte(T1_BRGRL_9600_2X_24000000_1T);
	TM_SetT1LowByte(T1_BRGRL_9600_2X_24000000_1T);
#endif

	TM_EnableT1();
    INT_EnUART0();			//	使能串口中断
}
*/


/***********************************************************************************
函数名称:   void INT_UART0(void)
功能描述:UART0 中断服务程序
		 
输入参数:   
返回参数:     
*************************************************************************************/
void INT_UART0(void) interrupt INT_VECTOR_UART0
{
    idata u8 dat = 0;
	_push_(SFRPI);		   //保护SFRPI寄存器值

	SFR_SetPage(0);		   /*设置0页寄存器*/  //S0CON仅0页操作
	if(TI0)					//发送中断内容
	{ 
	   TI0 = 0;	   
	}
	if(RI0)					//接收中断内容
	{
		RI0 = 0;				//清除中断标志
        dat = S0BUF;
        if(dat == '(') SIO_cnt = 0;
        SIO_buff[SIO_cnt] = dat;
        SIO_cnt = (SIO_cnt + 1) & 0x1F;
        if (dat == ')')
        {
            for (dat = 0; dat < SIO_cnt; dat++)
            {
                SIO_DATA[dat] = SIO_buff[dat];
            }
            BIT_SIO = 1; // 标志
            //SIO_TOT = 20;
        }
	}
	_pop_(SFRPI);		   //恢复SFRPI寄存器值
}

/***********************************************************************************
函数名称:void Uart0SendByte(u8 tByte)
功能描述:Uart0发送数据
输入参数:u8 tByte: 待发送的数据
返回参数:     
*************************************************************************************/
void Uart0SendByte(u8 tByte)
{
	bit bES;
	bES = ES0;
	ES0 = 0;
	S0BUF = tByte;
    //TB80 = P;   //校验位
	while(TI0 == 0);
	TI0 = 0;
	ES0 = bES;
}

/* 发送数据 */
void Send_Data(u8 *buff,u8 len)
{
    xdata u8 i = 0;
    for(i=0; i<len; i++)
    {
        Uart0SendByte(buff[i]);
    }
}

unsigned char asc_hex(unsigned char asc) // HEX
{
	xdata u8 i;
	if (asc < 0x3A)
		i = asc & 0x0F;
	else
		i = asc - 0x37;
	return i;
}

unsigned char hex_asc(unsigned char hex)
{
	xdata u8 i;
	hex = hex & 0x0F;
	if (hex < 0x0A)
		i = hex | 0x30;
	else
		i = hex + 0x37;
	return i;
}

unsigned char asc_hex_2(unsigned char asc1, unsigned char asc0)
{
	unsigned char i;
	i = (asc_hex(asc1) << 4) + (asc_hex(asc0) & 0x0F);
	return i;
}


/*************************************************
函数名称: char putchar (char c)   
功能描述: 用于printf 的串口输出程序
输入参数:     char c
输出参数:     
*************************************************/
/*
char putchar (char c)   
{      
	bit bES;
	bES=ES0;
    ES0=0;        
    S0BUF = c;        
    while(TI0==0);        
    TI0=0;        
    ES0=bES;        
    return 0;
}*/

xdata u32 PROFILE_CH_FREQ_32bit_200002EC_uart = 0;
void PC_PRG(void)								// ???????
{
    xdata uni_rom_id UART_ID_data;
    xdata u8 send_ok[4] = {'(','O','K',')'};
    xdata u8 re_byte = 0;
    xdata u8 send_ack[10] = {0x28,0x57,0x47,0x29,0x00,0x00,0x00,0x00,0x00,0x00};
	
	if (BIT_SIO){
		BIT_SIO = 0;
		//SIO_TOT = 20;
		switch (SIO_DATA[1])
		{
		case 'W': 
			//==================================== ID?葷?
			if (SIO_DATA[2]=='G')				// (WGd1d2d3) 
			{
				UART_ID_data.IDB[0]=0;
				UART_ID_data.IDB[1] = asc_hex_2(SIO_buff[3],SIO_buff[4]);;
				UART_ID_data.IDB[2] = asc_hex_2(SIO_buff[5],SIO_buff[6]);;
				UART_ID_data.IDB[3] = asc_hex_2(SIO_buff[7],SIO_buff[8]);;		 
                ID_data.IDC= UART_ID_data.IDC;	
                IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys+0x3FB,&UART_ID_data.IDB[1],3);                
				Send_Data(send_ok,4);
			}		  		  
		    break;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 ??????              %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'R':   
			//==================================== ID?葷?    //(RGx)
			if (SIO_DATA[2]=='G')		      //????	// (RG)d1d2d3 
			{
				send_ack[0] = 0x28;
				send_ack[1] = 0x52;
				send_ack[2] = 0x47;
				send_ack[3] = 0x29;
				
				send_ack[4] = hex_asc(ID_data.IDB[1] / 16);
				send_ack[5] = hex_asc(ID_data.IDB[1] % 16);
				send_ack[6] = hex_asc(ID_data.IDB[2] / 16);
				send_ack[7] = hex_asc(ID_data.IDB[2] % 16);
				send_ack[8] = hex_asc(ID_data.IDB[3] / 16);
				send_ack[9] = hex_asc(ID_data.IDB[3] % 16);
				Send_Data(send_ack,10);
			}		  		  
		    break;
        }
            
        if(SIO_DATA[1] == 'T' && SIO_DATA[2] == 'E' && SIO_DATA[3] == 'S' && SIO_DATA[4] == 'T' && SIO_DATA[5]==')')
        {
            Flag_test_pc = 1;
            FG_test_mode = 0;
            PIN_TX_LED = 0;
            P20 = 0;
            Send_Data(send_ok,4);
        }
        if(Flag_test_pc == 1)
        {
            switch(SIO_DATA[1])
            {
                case 'S':
                    FG_test_mode = 0;
                    dd_set_ML7345D_Power_on();
                    PROFILE_CH_FREQ_32bit_200002EC = 426075000;
                    RF_ML7345_Init(Fre_426_075,0x15,12);
                    Tx_Data_Test(0);
                    Send_Data(send_ok,4);
                    break;
                case 'E':
                    if(SIO_DATA[2] == 'N' && SIO_DATA[3] == 'D')
                    {
                        Flag_test_pc = 0;
                        ML7345_SetAndGet_State(Force_TRX_OFF);
                        SpiGpio_UnInit();
                        ML7345D_POWER = FG_NOT_allow_out;
                        FG_test_mode = 0; 
                        Send_Data(send_ok,4);
                    }
                    break;
                case 'F':
                    if(SIO_DATA[2]=='M')
                    {
                        FG_test_mode = 1;
                        dd_set_ML7345D_Power_on();
                        PROFILE_CH_FREQ_32bit_200002EC = 426075000;
                        RF_ML7345_Init(Fre_426_075,0x15,12);
                        Tx_Data_Test(1);
                        Send_Data(send_ok,4);
                    }
                    else if (SIO_DATA[2]=='C' && SIO_DATA[3]=='?')
                    {
                        send_ack[0] = '(';
                        send_ack[1] = 'F';
                        send_ack[2] = 'C';
                        send_ack[3] = ')';
                        send_ack[4] = hex_asc(rf_offset / 16);
                        send_ack[5] = hex_asc(rf_offset % 16);
                        Send_Data(send_ack,6);
                    }
                    else if (SIO_DATA[2]=='C' && FG_test_mode == 1)
                    {
                        re_byte = asc_hex_2(SIO_buff[3],SIO_buff[4]);	
                        ML7345_SetAndGet_State(Force_TRX_OFF);				
                        if(re_byte <= 10) //frequency +
                        {
                            rf_offset = re_byte;
                            IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys+Addr_rf_offset,&rf_offset,1);
                            PROFILE_CH_FREQ_32bit_200002EC_uart = 426075000 + 150 * re_byte;
                            ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC_uart,Fre_426_075);
                            ML7345_Frequency_Set(Fre_426_075,1);
                            Send_Data(send_ok,4);
                        }
                        else if(10 < re_byte && re_byte <= 20) //frequency -
                        {
                            rf_offset = re_byte;
                            IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys+Addr_rf_offset,&rf_offset,1);
                            re_byte = re_byte - 10;
                            PROFILE_CH_FREQ_32bit_200002EC_uart = 426075000 - 150 * re_byte;
                            ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC_uart,Fre_426_075);
                            ML7345_Frequency_Set(Fre_426_075,1);
                            Send_Data(send_ok,4);
                        }
                        Tx_Data_Test(1);
                    }
                    break;
                case 'K':
                    if(SIO_DATA[2]=='Y' && SIO_DATA[3]==')')
                    {
                        send_ack[0] = '(';
                        send_ack[1] = 'K';
                        send_ack[2] = 'Y';
                        Key_Sta.un_var = 0;
                        Key_Sta.Flag.un_var_bit0 = PIN_KEY_OPEN;
                        Key_Sta.Flag.un_var_bit1 = PIN_KEY_STOP;
                        Key_Sta.Flag.un_var_bit2 = PIN_KEY_CLOSE;
                        Key_Sta.Flag.un_var_bit3 = PIN_KEY_LOGIN;
                        send_ack[3] = hex_asc((Key_Sta.un_var & 0xff) / 16);
                        send_ack[4] = hex_asc((Key_Sta.un_var & 0xff) % 16);
                        send_ack[5] = ')';
                        Send_Data(send_ack,6);
                    }
                    break;
                case 'P':
                    if(SIO_DATA[2]=='H' && SIO_DATA[5]==')')
                    {
                        if(SIO_DATA[3]=='2' && SIO_DATA[4]=='7')         {PIN_TX_LED = 1;   Send_Data(send_ok,4);}
                        else if(SIO_DATA[3]=='2' && SIO_DATA[4]=='0')    {P20 = 1;          Send_Data(send_ok,4);}
                    }
                    else if(SIO_DATA[2]=='L' && SIO_DATA[5]==')')
                    {
                        if(SIO_DATA[3]=='2' && SIO_DATA[4]=='7')         {PIN_TX_LED = 0;   Send_Data(send_ok,4);}
                        else if(SIO_DATA[3]=='2' && SIO_DATA[4]=='0')    {P20 = 0;          Send_Data(send_ok,4);}
                    }
                    break;
                default:
                    break;          
            }
        }
	}
}