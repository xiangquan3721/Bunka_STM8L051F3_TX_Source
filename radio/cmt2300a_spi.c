#include "cmt2300a_spi.h"

//void cmt_delay(u16 n)
//{
//     while(n--);
//}

void cmt_spi3_delay_us(void)
{
    xdata u16 n = 4;
    while(n--);
}
void cmt_spi3_delay(void)
{
    xdata u8 n = 1;
    while(n--);
}

#ifndef DEF_Hardware_SPI
void cmt_spi3_init(void)
{
    cmt_spi3_csb_1();
    cmt_spi3_csb_out();
    cmt_spi3_csb_1();   /* CSB has an internal pull-up resistor */

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();   /* SCL has an internal pull-down resistor */

    cmt_spi3_sda_1();
    cmt_spi3_sda_out();
    cmt_spi3_sda_1();

    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();  /* FCSB has an internal pull-up resistor */

    cmt_spi3_delay();
}

void cmt_spi3_send(u8 data8)
{
    xdata u8 i;

    for(i=0; i<8; i++)
    {
        cmt_spi3_scl_0();

        /* Send byte on the rising edge of SCL */
        if(data8 & 0x80)
        {
            cmt_spi3_sda_1();
        }
        else
        {
            cmt_spi3_sda_0();
        }

        //cmt_spi3_delay();

        data8 <<= 1;
        cmt_spi3_scl_1();
        //cmt_spi3_delay();
    }
}

u8 cmt_spi3_recv(void)
{
    xdata u8 i;
    xdata u8 data8 = 0xFF;

    for(i=0; i<8; i++)
    {
        cmt_spi3_scl_0();
        //cmt_spi3_delay();
        data8 <<= 1;

        cmt_spi3_scl_1();

        /* Read byte on the rising edge of SCL */
        if(cmt_spi3_sda_read())
        {
            data8 |= 0x01;
        }
        else
        {
            data8 &= ~0x01;
        }

        //cmt_spi3_delay();
    }

    return data8;
}

void Cmt_Spi_Write(u8 addr, u8 dat)
{
    cmt_spi3_sda_1();
    cmt_spi3_sda_out();

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
//    cmt_spi3_delay();

    /* r/w = 0 */
    cmt_spi3_send(addr&0x7F);

    cmt_spi3_send(dat);

    cmt_spi3_scl_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
//    cmt_spi3_delay();

    cmt_spi3_csb_1();

    cmt_spi3_sda_1();
    cmt_spi3_sda_in();

//    cmt_spi3_fcsb_1();
}

void Cmt_Spi_Read(u8 addr, u8* p_dat)
{
    cmt_spi3_sda_1();
    cmt_spi3_sda_out();

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    //cmt_spi3_delay();

    /* r/w = 1 */
    cmt_spi3_send(addr|0x80);

    /* Must set SDA to input before the falling edge of SCL */
    cmt_spi3_sda_in();

    *p_dat = cmt_spi3_recv();

    cmt_spi3_scl_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    //cmt_spi3_delay();

    cmt_spi3_csb_1();

    cmt_spi3_sda_1();
    cmt_spi3_sda_in();

    //cmt_spi3_fcsb_1();
}
#else
void Spi3Gpio_Init(void)
{
    PORT_SetP1PushPull(BIT5|BIT7);					// 设置P15(MOSI),P17(SPICLK)为准双向口
	PORT_SetP1OpenDrain(BIT6);							// 设置P16(MISO)为准双向口
    P16 = 1;                                            // 输入
	PORT_EnP14P15P16P17PullHigh();
}
void Init_Spi3(void)
{
    // 使能SPI
    SPI_Enable();
	// 设置MASTER
	SPI_SelectMASTERByMSTRbit();
	// 设置SPI时钟
	SPI_SetClock(SPI_CLK_SYSCLK_4);
	// 设置SPICLK初始电平 CPOL=0 低电平
	SPI_SetCPOL_0();	
	// 设置数据传送位序 MSB 高位在前
	SPI_SetDataMSB();
	// 设置采样和改变数据模式 CPHA=0 前沿采样,后沿改变数据
	SPI_SetCPHA_0();
	// 设置IO nSS/P14,MOSI/P15,MISO/P16,SPICLK/P17
	SPI_SetUseP14P15P16P17();

    Spi3Gpio_Init();
}
void cmt_spi3_init(void)
{
    cmt_spi3_csb_1();
    cmt_spi3_csb_out();
    cmt_spi3_csb_1();   /* CSB has an internal pull-up resistor */

    //Spi3Gpio_Init();
    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();  /* FCSB has an internal pull-up resistor */

    cmt_spi3_delay();
}

u8 SPIx_ReadWriteByte(u8 TxData)
{ 
    while(SPSTAT & THRF);
	SPI_SendData(TxData);							// SPI 发送数据
	while(SPI_ChkCompleteFlag()==0);				// 等待SPI传送完成
	SPI_ClearCompleteFlag();						// SPI 清完成标志
	return SPI_GetData();							// 返回接收到的数据
}

void Cmt_Spi_Write(u8 addr, u8 dat)
{
	cmt_spi3_csb_0();
	SPIx_ReadWriteByte(addr&0x7F);
	SPIx_ReadWriteByte(dat);
	cmt_spi3_csb_1();
}

void Cmt_Spi_Read(u8 addr, u8* p_dat)	
{
	cmt_spi3_csb_0();
	SPIx_ReadWriteByte(addr|0x80);
	*p_dat=SPIx_ReadWriteByte(0XFF);
	cmt_spi3_csb_1();
}
#endif

//void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len)
//{
//    xdata u16 i;

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
//    cmt_spi3_fcsb_1();

//    cmt_spi3_csb_1();
//    cmt_spi3_csb_out();
//    cmt_spi3_csb_1();

//    cmt_spi3_scl_0();
//    cmt_spi3_scl_out();
//    cmt_spi3_scl_0();

//    cmt_spi3_sda_out();

//    for(i=0; i<len; i++)
//    {
//        cmt_spi3_fcsb_0();

//        /* > 1 SCL cycle */
//        cmt_spi3_delay();
//        cmt_spi3_delay();

//        cmt_spi3_send(p_buf[i]);

//        cmt_spi3_scl_0();

//        /* > 2 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();

//        cmt_spi3_fcsb_1();

//        /* > 4 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//    }

//    cmt_spi3_sda_in();

//    cmt_spi3_fcsb_1();
//}

//void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len)
//{
//    xdata u16 i;

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
//    cmt_spi3_fcsb_1();

//    cmt_spi3_csb_1();
//    cmt_spi3_csb_out();
//    cmt_spi3_csb_1();

//    cmt_spi3_scl_0();
//    cmt_spi3_scl_out();
//    cmt_spi3_scl_0();

//    cmt_spi3_sda_in();

//    for(i=0; i<len; i++)
//    {
//        cmt_spi3_fcsb_0();

//        /* > 1 SCL cycle */
//        cmt_spi3_delay();
//        cmt_spi3_delay();

//        p_buf[i] = cmt_spi3_recv();

//        cmt_spi3_scl_0();

//        /* > 2 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();

//        cmt_spi3_fcsb_1();

//        /* > 4 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//    }

//    cmt_spi3_sda_in();

//    cmt_spi3_fcsb_1();
//}


