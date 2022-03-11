#include "cmt2300a_app.h"


u32 SPI_Receive_DataForC[7];
u32 DATA_Packet_ID = 0;
u8 DATA_Packet_Contro_buf = 0;

u8 g_rxBuffer[RF_PACKET_SIZE] = {0};   /* RF Rx buffer */
u8 g_txBuffer[RF_PACKET_SIZE] = {0};

void delay(u32 n)
{
    while(n--);
}

void CMT2300A_TX_PACKET(u8 *pBuf,u8 len)
{
    CG2214M6_USE_T;
    CMT2300A_GoStby();
	CMT2300A_ClearInterruptFlags();
	CMT2300A_ClearTxFifo();
	CMT2300A_EnableWriteFifo();

	CMT2300A_WriteFifo(pBuf, len); // 写 TX_FIFO
	CMT2300A_GoTx(); // 启动发送
}



void CMT2300A_RX_ENABLE(void)
{
    CG2214M6_USE_R;
    CMT2300A_GoStby();
	/* Must clear FIFO after enable SPI to read or write the FIFO */
    CMT2300A_EnableReadFifo();
	CMT2300A_ClearInterruptFlags();
	CMT2300A_ClearRxFifo();
  	CMT2300A_GoRx();

}

void CMT2300A_Set_Freq(u8 freq)
{
    CMT2300A_GoStby();
    if(freq)
    {
        CMT2300A_SetFrequencyStep(20);
        system_delay_ms(10);
        CMT2300A_SetFrequencyChannel(62);
    }
    else
    {
        //CMT2300A_SetFrequencyStep(1);
        system_delay_ms(10);
        CMT2300A_SetFrequencyChannel(0);
    }
    CMT2300A_GoSleep();
}

void SCAN_RECEIVE_PACKET(void)
{
    if(CMT2300A_ReadGpio2())
    {
        CMT2300A_GoStby();
		/* The length need be smaller than 32 */
		CMT2300A_ReadFifo(g_rxBuffer, RF_PACKET_SIZE);
    }


}


void Signal_DATA_Decode(u8 NUM_Type,u8 pbuf[])
{
    u32 data_in;
    u16 data_out;
    u16 data_NRZ[7];
    u8 i, j,i_value;
    for (i = 0; i < 7; i++)
    {
        SPI_Receive_DataForC[i] = (u32)pbuf[i * 4 + 3] |
                                  (u32)pbuf[i * 4 + 4] << 8 |
                                  (u32)pbuf[i * 4 + 5] << 16 |
                                  (u32)pbuf[i * 4 + 6] << 24;
    }
	if((NUM_Type==0)||(NUM_Type==1))i_value=3;
	else if(NUM_Type==2)i_value=7;
    for (i = 0; i < i_value; i++)
    {
        if ((NUM_Type == 0)||(NUM_Type == 2))
            data_in = SPI_Receive_DataForC[i];
        else
            data_in = SPI_Receive_DataForC[i + 3];
        data_out = 0;
        data_in = data_in >> 1;
        for (j = 0; j < 16; j++)
        {
            data_out = data_out << 1;
            if (data_in & 0x00000001)
                data_out += 1;
            data_in = data_in >> 2;
        }
        data_NRZ[i] = data_out;
    }
	if((NUM_Type==0)||(NUM_Type==1))
	{
	    //if (data_NRZ[2] == ((data_NRZ[0] + data_NRZ[1]) & 0xFFFF))
	    {
	        DATA_Packet_ID = (data_NRZ[1] & 0x00FF) * 65536 + data_NRZ[0];
	        DATA_Packet_Contro_buf = (data_NRZ[1] & 0xFF00) >> 8;
	    }
	}
}


void set_tx(void)
{
    CG2214M6_USE_T;
    CMT2300A_Gpio3_DDR = 1;    //输出
    CMT2300A_Gpio3_CR1 = 1;
    CMT2300A_Gpio3_CR2 = 1;
    CMT2300A_EnableTxDin(TRUE); /* TRUE:选择为DIN;FALSE:选择为DOUT */
    CMT2300A_ConfigTxDin(CMT2300A_TX_DIN_SEL_GPIO3); /* 选择发射数据从GPIO3输入 */
}
void set_rx(void)
{
    CG2214M6_USE_R;
    CMT2300A_Gpio3_DDR = 0;    //输入
    CMT2300A_Gpio3_CR1 = 0;
    CMT2300A_Gpio3_CR2 = 0;
    CMT2300A_EnableTxDin(FALSE);
    CMT2300A_GoRx();
}

void cmt2300a_tx_test(u8 mode)
{
    if(mode)
    {
        if(pin_clk_in == 1)
        {
            pin_sda_out = !pin_sda_out;
            delay(100);
        }
    }
}

u8 cmt2300a_rx_test(void)
{
    u8 i;
    u8 data8 = 0xFF;
    set_rx();
    for(i=0; i<8; i++)
    {
        delay(3);
        data8 <<= 1;
        if(pin_sda_in)
        {
            data8 |= 0x01;
        }
        else
        {
            data8 &= ~0x01;
        }

        delay(3);
    }

    return data8;
}


void RF_Test_Mode(void)
{
    u8 Tx_Rx_mode = 0;
    u8 at = 0;

    if(TP7_TEST_MODE == 1)
    {
        RF_Init_TestMode(); /* RF测试模式初始化 */
        if(FALSE==CMT2300A_IsExist()) {
            while(1);  //初始化失败
        }
    }

    while(TP7_TEST_MODE == 1)
    {
        if(Key_Tx_Carrier == 0)  /* 发载波 (需频偏2.5k)*/
        {
            set_tx();
            CMT2300A_SetFrequencyChannel(1); //Freq = 426.075MHz+2.5KHz*1*1
            Tx_Rx_mode = 1;
            pin_sda_out = 0;
        }
        if(Key_Tx_Data == 0)    /* 发数据 */
        {
            set_tx();
            CMT2300A_SetFrequencyChannel(0);
            Tx_Rx_mode = 2;
            at = 0;
        }
        if(Key_Rx_Data == 0)    /* 停止 */
        {
            Tx_Rx_mode = 3;
        }
        if(Tx_Rx_mode == 1)     /* 发载波 */
        {
            cmt2300a_tx_test(0);
            if(at == 0)
            {
                at = 1;
                CMT2300A_GoTx();
            }
        }
        if(Tx_Rx_mode == 2)     /* 发数据 */
        {
            cmt2300a_tx_test(1);

            if(at == 0)
            {
                at = 1;
                CMT2300A_GoTx();
            }
        }
        if(Tx_Rx_mode == 3)
        {
            at = 0;
            CMT2300A_GoSleep();
        }
    }
}



