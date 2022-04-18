#include "ML7345.h"

//#include <stdlib.h>
//#include <stdbool.h> /* For true/false definition                      */
//#include <stdio.h>
#include "spi.h"
#include "gpio.h"
#include "ram.h"
#include "ID_Decode.h"
#include "Type.h"
#include "uart.h"
xdata u8 *txbuf = NULL;
//ROHM demo板 main fre=426.25;Vco Cal Range:425.85 - 431.85.MHz
//TCXO = 24M
xdata u8 Fre_426_075[8] = {0x23,0x08,0x19,0x99,0x23,0x07,0x91,0x11}; //426.075MHz频率设置
xdata u8 Fre_429_350[8] = {0x23,0x0C,0x77,0x77,0x23,0x0B,0xEE,0xEF}; //429.350MHz频率设置
xdata u8 Fre_429_550[8] = {0x23,0x0C,0xBB,0xBC,0x23,0x0C,0x33,0x33}; //429.550MHz频率设置
xdata u8 Fre_426_750[8] = {0x23,0x09,0x00,0x00,0x23,0x08,0x77,0x77}; //426.750MHz频率设置
xdata u8 Fre_429_175[8] = {0x23,0x0c,0x3b,0xbc,0x23,0x0b,0xb3,0x33}; //429.175MHz频率设置

/**Receiver_vent**/ xdata u8 Receiver_vent_Cache = 0;
xdata u32 SPI_Receive_DataForC[7]; //C郿
xdata u8 SPI_RECEIVE_BUFF[40] = {0};

/************Address: 0x20000500, Name: GENERIC_PKT_FRAME_CFG1***************************************/

xdata u8 Radio_Date_Type = 1;
xdata u8 tx_pack_cnt = 0;
xdata u8 Radio_Date_Type_bak=1;
xdata u8 APP_TX_freq=0;

xdata u8 TX_Scan_step=0;
xdata u8 First_TX_Scan=0;
xdata u8 rf_offset = 0;

xdata u8 Freq_SetBuff[8] = {0};
/*
Function: RF Init
Parameter: Null
Return: Null
*/
/* Initialize: 426MHz General Packet(TCXO_ChStep=12.5kHz_DR=1.2kbps_Dev=0.6kHz_GFSK)
   发射功率0dBm */
void RF_ML7345_Init(u8* freq,u8 sync,u8 rx_len)
{
    SpiGpio_Init();
    ML7345_RESETN_SET();    /* Hardware Reset */
    while(1){
        if(ML7345_Read_Reg(0x0Du)&0x01u){   /* Wait Clock stabilization completion */
            break;
        }
    }
    ML7345_Write_Reg(0x00,0x11);    /* Bank0 Set */
    ML7345_Write_Reg(0x01,0xff);    /* Software Reset */
    ML7345_Write_Reg(0x02,0x9f);    /* Clk Enable */
    ML7345_Write_Reg(0x03,0xc3);    /* TCXO_EN */
    ML7345_Write_Reg(0x04,0x03);    /* MSB first,Format D (non Wireless M-Bus, general purpose format) */
    ML7345_Write_Reg(0x05,0x10);    /* CRC Disable,Length field 1-byte mode */
    ML7345_Write_Reg(0x06,0x00);    /* Data Rate: 0x00 1.2kbps; 0x22 4.8kbps */
    ML7345_Write_Reg(0x07,0x15);    /* GFSK,NRZ */
    ML7345_Write_Reg(0x08,0x00);    /* Sync word pattern 1,Manchester Do not inverse polarity */
    ML7345_Write_Reg(0x09,0x00);    /* CH 0 */
    ML7345_Write_Reg(0x0a,0x18);    /* AUTO_TX_EN */
    ML7345_Write_Reg(0x0b,0x88);    /* TRX_OFF */
    ML7345_Write_Reg(0x0c,0x00);    /* FIFO mode */
    ML7345_Write_Reg(0x0d,0x08);    /* [INT_SOURCE_GRP1],Interrupt status for INT0 to INT7 */
    ML7345_Write_Reg(0x0e,0x00);    /* [INT_SOURCE_GRP2],Interrupt status for INT8 to INT15 (RX) */
    ML7345_Write_Reg(0x0f,0x00);    /* [INT_SOURCE_GRP3],Interrupt status for INT16 to INT23 (TX) */
    ML7345_Write_Reg(0x10,0x00);    /* masking interrupt,[INT_EN_GRP1]Interupt mask for INT0 to INT7 */
    ML7345_Write_Reg(0x11,0x00);    /* masking interrupt,[INT_EN_GRP2]Interupt mask for INT8 to INT15 */
    ML7345_Write_Reg(0x12,0x00);    /* masking interrupt,[INT_EN_GRP3]Interupt mask for INT16 to INT23 */
    ML7345_Write_Reg(0x13,0x00);    /* [CRC_ERR_H]CRC error status (high byte) */
    ML7345_Write_Reg(0x14,0x00);    /* [CRC_ERR_M]CRC error status (middle byte)*/
    ML7345_Write_Reg(0x15,0x00);    /* [CRC_ERR_L]CRC error status (low byte)*/
    ML7345_Write_Reg(0x16,0x00);    /* State clear control */
    ML7345_Write_Reg(0x17,0x00);    /* TX FIFO-Full level setting */
    ML7345_Write_Reg(0x18,0x00);    /* TX FIFO-Empty level setting and TX trigger level setting in FAST_TX mode */
    ML7345_Write_Reg(0x19,0x00);    /* RX FIFO-Full level disable and level setting */
    ML7345_Write_Reg(0x1a,0x00);    /* RX FIFO-Empty level disable and level setting (high byte) */

    ML7345_Write_Reg(0x2d,0x06);    /* SLEEP execution and Wake-up operation setting */
    /* Preamble */
    ML7345_Write_Reg(0x3f,0x05);    /* Preamble pattern setting,p198*/

    ML7345_Write_Reg(0x41,0x8B);    /* Enable ED value calculation,bit3=0 ED value constantly updated,bit3=1 ED value acquired at SyncWord detection timing*/

    ML7345_Write_Reg(0x42,0x00);    //TX前导码长度高八位
    ML7345_Write_Reg(0x43,0x34);    //TX前导码长度低八位,不等少于16个位,TX preamble length = (specified value x2) bits
    //-----------------------------------------------------------------------------------------------------
    ML7345_Write_Reg(0x45,0x08);    //接收前导码长度(bit) RX preamble setting and ED threshold check setting
    //-----------------------------------------------------------------------------------------------------
    ML7345_Write_Reg(0x4e,0x00);    /* GPIO0 [output] “L” level */
    ML7345_Write_Reg(0x4f,0x00);    /* GPIO1 [output] “L” level,Upon reset,disable GPIO1 pin is CLK_OUT function */
    ML7345_Write_Reg(0x50,0x00);    /* GPIO2 [output] “L” level */
    ML7345_Write_Reg(0x51,0x00);    /* GPIO3 [output] “L” level */

    ML7345_Write_Reg(0x54,0x14);    /* Channel filter bandwidth setting */

    ML7345_Write_Reg(0x60,0x06); /* Decimation gain setting 提高灵敏度 */

    ML7345_Write_Reg(0x63,0x88);    /* Fine adjustment of load capacitance for oscillation circuits */

    ML7345_Write_Reg(0x67,0x00);    /* 功率设置0dbm */
    ML7345_Write_Reg(0x68,0x00);    /* PA regulator fine adjustment */
    ML7345_Write_Reg(0x69,0x00);    /* PA gain adjustment */

    ML7345_Write_Reg(0x6e,0x5b);    /*5b VCO calibration setting or status indication */

    ML7345_Write_Reg(0x7a,0x00);    //发送包长度高八位
    ML7345_Write_Reg(0x7b,0x0c);    //发送包长度低八位

    ML7345_Write_Reg(0x7d,0x00);    //接收包长度高八位
    ML7345_Write_Reg(0x7e,rx_len);    //接收包长度低八位

    /***************************************************************************************************/

    ML7345_Write_Reg(0x00,0x22);    /* Bank1 Set */
    ML7345_Write_Reg(0x02,0x07);    /* TX data rate conversion setting (high 4bits) */
    ML7345_Write_Reg(0x03,0xd0);    /* TX data rate conversion setting (low byte) */
    ML7345_Write_Reg(0x04,0x00);    /* RX data rate concversion setting 1 (high 4bits) */
    ML7345_Write_Reg(0x05,0x50);    /* RX data rate cnvesrion setting 1 (low byte) */

    ML7345_Write_Reg(0x11,0x27);    /* RSSI offset value setting during low gain operation */

    ML7345_Write_Reg(0x13,0x0c);    /* Scale factor setting for ED value conversion */

    ML7345_Write_Reg(0x1a,0x02);    /* Divide 2,PLL frequency division setting */
    /* 426.075MHz */
    ML7345_Write_Reg(0x1b,freq[0]);    /* TX frequency setting (I counter),p67-69 */
    ML7345_Write_Reg(0x1c,freq[1]);    /* TX frequency setting (F counter high 4bit) */
    ML7345_Write_Reg(0x1d,freq[2]);    /* TX frequency setting (F counter middle byte) */
    ML7345_Write_Reg(0x1e,freq[3]);    /* TX frequency setting (F counter low byte) */
    ML7345_Write_Reg(0x1f,freq[0]);    /* RX frequency setting (I counter) */
    ML7345_Write_Reg(0x20,freq[1]);    /* RX frequency setting (F counter high 4bit)  */
    ML7345_Write_Reg(0x21,freq[2]);    /* RX frequency setting (F counter middle byte) */
    ML7345_Write_Reg(0x22,freq[3]);    /* RX frequency setting (F counter low byte) */

    ML7345_Write_Reg(0x23,0x08);    /* 25KHz,Channel space setting (high byte) */
    ML7345_Write_Reg(0x24,0x88);    /* Channel space setting (low byte) */
    /* SyncWord 0x00005515 */
    ML7345_Write_Reg(0x25,0x08);    /* SyncWord length setting */
    ML7345_Write_Reg(0x26,0x0f);    /* SyncWord enable setting */
    ML7345_Write_Reg(0x27,0x00);    /* SyncWord #1 setting (bit24 to 31) */
    ML7345_Write_Reg(0x28,0x00);    /* SyncWord #1 setting (bit16 to 23) */
    ML7345_Write_Reg(0x29,0x00);    /* SyncWord #1 setting (bit8 to 15) */
    ML7345_Write_Reg(0x2a,sync);    /* SyncWord #1 setting (bit0 to 7) */

    ML7345_Write_Reg(0x2f,0x08);    /* GFSK clock setting x8 clock,GFSK/FSK modulation timing resolution setting */
    ML7345_Write_Reg(0x30,0x00);    /* GFSK frequency deviation setting (high 6bits) */
    
    //GFSK frequency deviation: 0xAE=2.0kHz; 0xC0=2.2kHz
    ML7345_Write_Reg(0x31,0xC0);    /* P71  GFSK frequency deviation:2.2KHz,GFSK frequency deviation setting (low byte) */

    /*(Channel#0 frequency-400khz)426.075:0x23 0x07 0x91 0x11;
    426.25:0x23 0x07 0xcc 0xcc */
    ML7345_Write_Reg(0x4d,freq[4]);    /* VCO calibration low limit frequency setting (I counter),p254 */
    ML7345_Write_Reg(0x4e,freq[5]);    /* VCO calibration low limit frequency setting (F counter high 4bits) */
    ML7345_Write_Reg(0x4f,freq[6]);    /* VCO calibration low limit frequency setting (F counter middle byte) */
    ML7345_Write_Reg(0x50,freq[7]);    /* VCO calibration low limit frequency setting (F counter low byte) */
    ML7345_Write_Reg(0x51,0x04);    /* 6 MHz,VCO calibration upper limit frequency setting */
    ML7345_Write_Reg(0x52,0x5a);    /* VCO calibration low limit value indication and setting */
    ML7345_Write_Reg(0x53,0x66);    /* VCO calibration upper limit value indication and setting */

    ML7345_Write_Reg(0x5c,0x15);    /* 0x10 Demodulator configulation 6 */
    ML7345_Write_Reg(0x5d,0x1b);    /* 0x1b Demodulator configulation 7 */
    ML7345_Write_Reg(0x5e,0x05);    /* 0x05 Demodulator configuration 8 */
    ML7345_Write_Reg(0x5f,0x67);    /* 0x67 Demodulator configulation 9 */
    ML7345_Write_Reg(0x60,0x0c);    /* Demodulator configulation 10 */

    SetReg_Rssi();  //2021.11.17 ROHM提出必要设置,否则读取RSSI偏差大。

    ML7345_Write_Reg(0x00,0x44); //bank2
    ML7345_Write_Reg(0x2a,0x0f); //2019.11.25 ROHM提出设置,设置之后灵敏度提升了2dBm

    /* 以下寄存器值为发送功率必要设置，不然发送功率偏差大 */
    ML7345_Write_Reg(0x00,0x44); //bank2
    ML7345_Write_Reg(0x4f,0x00);

    ML7345_Write_Reg(0x00,0x88); //bank3
    ML7345_Write_Reg(0x2f,0x3f);
    ML7345_Write_Reg(0x0c,0x41);
    ML7345_Write_Reg(0x0d,0x33);
    ML7345_Write_Reg(0x0e,0x54);
    ML7345_Write_Reg(0x14,0x10);
    ML7345_Write_Reg(0x24,0x03);
    ML7345_Write_Reg(0x7e,0x00);

    if((PROFILE_CH_FREQ_32bit_200002EC == 429350000) || (PROFILE_CH_FREQ_32bit_200002EC == 429550000)) ML7345_DataRate_Set_4_8k();
    else    ML7345_DataRate_Set_1_2k();
    /*****************************************************/

    ML7345_Write_Reg(0x00, 0x11);     /* BANK_SEL(BANK0) */
    ML7345_Write_Reg(0x6f, 0x01);     /* VCO_CAL_START(CAL start) */
    while(1){
        if(ML7345_Read_Reg(0x0Du)&0x02u){   /* Wait VCO calibration completion */
            break;
        }
    }
    ML7345_AllStateFlag_Clear(); //清除所有标志
    ML7345_GPIO0TxDoneInt_Enable();
}
/*
void ML7345_MeasurBER_Init(void)
{
    ML7345_Write_Reg(ADDR_BANK_SEL,BANK1_SEL);
    ML7345_Write_Reg(0x0e,0x00);

    ML7345_Write_Reg(ADDR_BANK_SEL,BANK3_SEL);
    ML7345_Write_Reg(0x0d,0x33);

    ML7345_Write_Reg(ADDR_BANK_SEL,BANK0_SEL);
    ML7345_Write_Reg(0x0c,0x40); //50   // DIO_SET, continuous output mode,DCLK is constantly output,no OUTPUT (NOT stop output)
    ML7345_Write_Reg(0x4d,0x80); //80

    ML7345_Write_Reg(0x4E,0x05);    //ML7345D GPIO0 DCLK
    ML7345_Write_Reg(0x51,0x04);    //ML7345D GPIO3 DIO
}*/


void Tx_Data_Test(u8 mode)
{
    ML7345_Write_Reg(0x00, 0x11);     /* BANK_SEL(BANK0) */
    switch(mode)
    {
        /* 发送：载波 */
        case 0: ML7345_Write_Reg(ADDR_RF_TEST_MODE,0x21);break;

        /* 发送：0101 */
        case 1:ML7345_Write_Reg(ADDR_RF_TEST_MODE,0x11);break;

        /* 发送：0 */
        case 2:ML7345_Write_Reg(ADDR_RF_TEST_MODE,0x09);break;

        /* 发送：1 */
        case 3: ML7345_Write_Reg(ADDR_RF_TEST_MODE,0x05);break;

         /* 发送：随机 */
        default:
            ML7345_Write_Reg(ADDR_RF_TEST_MODE,0x03);
         break;
    }
    ML7345_SetAndGet_State(TX_ON);
}


void ML7345_TRX_Del(void)
{
    idata u8 reg = 0;
    
    reg = ML7345_Read_Reg(ADDR_INT_SOURCE_GRP3);
    if(((reg & 0x01) == 0x01) && (reg != 0xff))
    {
        Flag_TxDone = 1;
        ML7345_StateFlag_Clear(TX_DONE_FLAG);
        if(FLAG_APP_TX == 1)
        {
            if(txphase_Repeat < 3 && Flag_TxDone == 1)
            {
                Flag_TxDone = 0;
                ML7345_AutoTx_Data(m_RFNormalBuf,txphase_end);
                txphase_Repeat++;
            }
            else if(txphase_Repeat == 3 && Flag_TxDone == 1)
            {
                Flag_TxDone = 0;
                FLAG_APP_TX = 0;
                if(FG_d_StopKey == 0)   PIN_TX_LED = 0;
                ML7345_SetAndGet_State(Force_TRX_OFF);
                ML7345_RESETN = 0;
                SpiGpio_UnInit();
                ML7345D_POWER = FG_NOT_allow_out;
            }
        }
    }
}

void dd_set_ML7345D_Power_on(void)
{
    if(ML7345D_POWER == FG_NOT_allow_out)
	{
		ML7345D_POWER = FG_allow_out;  
        delay_ms(2);
        //RF_ML7345_Init(Fre_426_075,0x15,12);
	}
}
/*
void dd_set_ML7345D_Power_on_Init(void)
{
    if(ML7345D_POWER == FG_NOT_allow_out)
	{
		ML7345D_POWER = FG_allow_out;  
        delay_ms(2);
        RF_ML7345_Init(Fre_426_075,0x15,12);
	}
}*/

