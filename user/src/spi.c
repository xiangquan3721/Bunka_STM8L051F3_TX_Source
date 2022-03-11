#include "spi.h"

void cmt_delay(u16 n)
{
     while(n--);
}

void cmt_spi3_delay_us(void)
{
    u16 n = 8;
    while(n--);
}
void cmt_spi3_delay(void)
{
    u16 n = 4;
    while(n--);
}




#if SPI_AnalogOrHardware == 1

/* SPI相关IO口初始化,MISO->PB7;MOSI->PB6;SCK->PB5;CS->PB4;FCSB->PD0 */
void SPI1_Gpio_Config(void)
{
    SPI_CS_DDR = 1;     /* CS 设置数据方向寄存器 1为输出，0为输入--查看STM8寄存器.pdf P87 */
    SPI_CS_CR1 = 1;     /* 设置推挽输出--查看STM8寄存器RM0031.pdf 10.9 */
    SPI_CS_CR2 = 1;     /* 设置输出频率 1为10M，0为2M--查看STM8寄存器.pdf P89 */

    SPI1_SCK_DDR = 1;   /* SCK output */
    SPI1_SCK_CR1 = 1;
    SPI1_SCK_CR2 = 1;

    SPI1_MOSI_DDR = 1;  /* MOSI output */
    SPI1_MOSI_CR1 = 1;
    SPI1_MOSI_CR2 = 1;

    SPI1_MISO_DDR = 0;  /* MISO input */
    SPI1_MISO_CR1 = 1;  /* in put with pull-up */
    SPI1_MISO_CR2 = 0;

    CMT_FCSB_DDR = 1;   /* FCSB output*/
    CMT_FCSB_CR1 = 1;
    CMT_FCSB_CR2 = 1;

    SPI_TX_EN_DDR = 1;  /* output */
    SPI_TX_EN_CR1 = 1;
    SPI_TX_EN_CR2 = 1;

    SPI1_CS_H;
    SPI_TX_EN = TxDisbale;
}

/* 初始化SPI1 */
void SPI_Config_Init(void)
{
    SPI1_Gpio_Config();

    CLK_PCKENR1 |= 0x10;    /* 开启SPI1时钟 */
    SPI1_CR1_SPE = 0;      //禁止SPI1
    SPI1_CR1_LSBFIRST = 0; //先发送MSB
    SPI1_CR1_BR = 3;       //3,fSYSCLK/16 = 1MHz   Baud = fSYSCLK/(2^(SPI1_CR1_BR+1)) eg.	//000: fSYSCLK/2  001: fSYSCLK/4
    SPI1_CR1_MSTR = 1;     //Master configuration 设置为主模式
    SPI1_CR1_CPOL = 0;     //0: SCK to 1 when idle		空闲状态时SCK为低电平									(MISO和MOSI在CLK的上升沿载入，下降沿取样)
    SPI1_CR1_CPHA = 0;     //0: The first clock transition is the second data capture edge (MISO和MOSI在CLK的上升沿载入，下降沿取样)

    SPI1_CR2_BDM = 0;    //1-line bidirectional data mode selected

    SPI1_CR2_CRCEN = 0;  //0: CRC calculation disabled
    SPI1_CR2_RXONLY = 0; //0: Full duplex (Transmit and receive)
    SPI1_CR2_SSM = 1;    //0: Software slave management disabled
    SPI1_CR2_SSI = 1;    //1: Master mode

    SPI1_ICR_TXIE = 0;    //TXE interrupt masked
    SPI1_ICR_RXIE = 0;    //RXNE interrupt masked
    SPI1_ICR_ERRIE = 0;   //Error interrupt is masked
    SPI1_ICR_WKIE = 0;    //Wakeup interrupt masked
    SPI1_ICR_TXDMAEN = 0; //Tx buffer DMA disabled
    SPI1_ICR_RXDMAEN = 0; //Rx buffer DMA disabled

    SPI1_CR1_SPE = 1; //使能SPI1
}


/*
函数功能：SPI1读CMT2300A寄存器函数,主要用于读CMT2300A状态
函数形参：addr 寄存器地址，p_dat 读取的寄存器状态值
*/
void Cmt_Spi_Read(u8 addr, u8* p_dat)
{
    u8 read = 0;
    CMT_FCSB_H;                 /* CS与FCSB不能同时为低 */
    SPI_TX_EN = TxEnable;       /* 打开发送开关 */

    SPI1_CS_L;
    cmt_delay(4);               /* > 0.5 SCL cycle */

    while (!(SPI1_SR & 0x02));  /* 等待发送空闲 */
    /* r/w = 1 */
    SPI1_DR = (addr | 0x80);      /* read command */

    cmt_delay(16);              /* SPI时钟16分频延时发送一个字节的时间,SPI时钟256分频延时参数为256，128分频为延时参数为128 */

    SPI_TX_EN = TxDisbale;      /* 关闭发送开关,防止接收数据时电气冲突 */

    while (!(SPI1_SR & 0x02));  /* 等待发送空闲 */
    SPI1_DR = 0xff;             /* 发送无关数据,为了产生时钟信号 */

    read = SPI1_DR;                    /* 先清空，防止接收数据错误 */

    while ((SPI1_SR & 0x80));   /* 等待总线空闲 */
    *p_dat = SPI1_DR;           /* 读取接收数据 */

    cmt_delay(4);               /* > 0.5 SCL cycle */
    SPI1_CS_H;
}

/*
函数功能：SPI1写CMT2300A寄存器函数,主要用于将配置写入CMT2300A寄存器
函数形参：addr 寄存器地址，dat 写入的配置数据
*/
void Cmt_Spi_Write(u8 addr, u8 dat)
{
    u8 read = 0;
    CMT_FCSB_H;                 /* CS与FCSB不能同时为低 */
    SPI_TX_EN = TxEnable;       /* 打开发送开关 */

    SPI1_CS_L;
    cmt_delay(4);               /* > 0.5 SCL cycle */

    while (!(SPI1_SR & 0x02));  /* 等待发送空闲 */
    /* r/w = 0 */
    SPI1_DR = (addr&0x7F);      /* write command */

    read = SPI1_DR;                    /* 清空 */

    while (!(SPI1_SR & 0x02));  /* 等待发送空闲 */
    SPI1_DR = dat;              /* 写入数据 */
    while ((SPI1_SR & 0x80));   /* 等待总线空闲 */

    read = SPI1_DR;                    /* 清空 */

    cmt_delay(4);               /* > 0.5 SCL cycle */
    SPI1_CS_H;

    SPI_TX_EN = TxDisbale;      /* 关闭发送开关 */
}

/*
函数功能：SPI1接收数据函数,主要用于读取CMT2300A的FIFO,读取无线接收到的数据
函数形参：p_buf 接收缓冲区;len 接收数据长度
*/
void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len)
{
    u16 i = 0;
    CMT_FCSB_H;
    SPI1_CS_H;
    SPI_TX_EN = TxDisbale;          /* 关闭发送开关 */

    for(i = 0;i < len; i++)
    {
        CMT_FCSB_L;
        /* > 1 SCL cycle */
        cmt_delay(8);

        while (!(SPI1_SR & 0x02));  /* 等待发送空闲 */
        SPI1_DR = 0xff;             /* 发送无关数据,为了产生时钟信号 */

        while (!(SPI1_SR & 0x01));  /* 接收非空 */
        p_buf[i] = SPI1_DR;

        /* > 2 us */
        cmt_delay(16);

        CMT_FCSB_H;

        /* > 4 us */
        cmt_delay(40);
    }
    CMT_FCSB_H;
}

/*
函数功能：SPI1发送数据函数,主要用于将数据送入CMT2300A的FIFO,发送数据
函数形参：p_buf 发送数据缓冲区，len 发送数据长度
*/
void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len)
{
    u16 i = 0;
    u8 read = 0;
    SPI1_CS_H;
    CMT_FCSB_H;
    SPI_TX_EN = TxEnable;         /* 打开发送开关 */

    for(i = 0; i < len; i++)
    {
        CMT_FCSB_L;

        /* > 1 SCL cycle */
        cmt_delay(8);

        while (!(SPI1_SR & 0x02));/* 等待发送空闲 */
        SPI1_DR = p_buf[i];

        read = SPI1_DR;                  /* 清空 */
        /* > 2 us */
        cmt_delay(16);

        CMT_FCSB_H;

        /* > 4 us */
        cmt_delay(32);
    }
    CMT_FCSB_H;
    SPI_TX_EN = TxDisbale;        /* 关闭发送开关 */
}

#endif


/* ************************************************************************ */
#if SPI_AnalogOrHardware == 0
void SPI_Config_Init(void)
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
    SPI_TX_EN_DDR = 1;
    SPI_TX_EN_CR1 = 1;
    SPI_TX_EN_CR2 = 1;
    SPI_TX_EN = 0;
}

void cmt_spi3_send(u8 data8)
{
    u8 i;

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

        cmt_spi3_delay();

        data8 <<= 1;
        cmt_spi3_scl_1();
        cmt_spi3_delay();
    }
}

u8 cmt_spi3_recv(void)
{
    u8 i;
    u8 data8 = 0xFF;

    for(i=0; i<8; i++)
    {
        cmt_spi3_scl_0();
        cmt_spi3_delay();
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

        cmt_spi3_delay();
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

    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    cmt_spi3_delay();

    /* r/w = 0 */
    cmt_spi3_send(addr&0x7F);

    cmt_spi3_send(dat);

    cmt_spi3_scl_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    cmt_spi3_delay();

    cmt_spi3_csb_1();

    cmt_spi3_sda_1();
    cmt_spi3_sda_in();

    cmt_spi3_fcsb_1();
}

void Cmt_Spi_Read(u8 addr, u8* p_dat)
{
    cmt_spi3_sda_1();
    cmt_spi3_sda_out();

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();

    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    cmt_spi3_delay();

    /* r/w = 1 */
    cmt_spi3_send(addr|0x80);

    /* Must set SDA to input before the falling edge of SCL */
    cmt_spi3_sda_in();

    *p_dat = cmt_spi3_recv();

    cmt_spi3_scl_0();

    /* > 0.5 SCL cycle */
    cmt_spi3_delay();
    cmt_spi3_delay();

    cmt_spi3_csb_1();

    cmt_spi3_sda_1();
    cmt_spi3_sda_in();

    cmt_spi3_fcsb_1();
}

void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len)
{
    u16 i;

    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_1();
    cmt_spi3_csb_out();
    cmt_spi3_csb_1();

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();

    cmt_spi3_sda_out();

    for(i=0; i<len; i++)
    {
        cmt_spi3_fcsb_0();

        /* > 1 SCL cycle */
        cmt_spi3_delay();
        cmt_spi3_delay();

        cmt_spi3_send(p_buf[i]);

        cmt_spi3_scl_0();

        /* > 2 us */
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();

        cmt_spi3_fcsb_1();

        /* > 4 us */
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
    }

    cmt_spi3_sda_in();

    cmt_spi3_fcsb_1();
}

void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len)
{
    u16 i;

    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_1();
    cmt_spi3_csb_out();
    cmt_spi3_csb_1();

    cmt_spi3_scl_0();
    cmt_spi3_scl_out();
    cmt_spi3_scl_0();

    cmt_spi3_sda_in();

    for(i=0; i<len; i++)
    {
        cmt_spi3_fcsb_0();

        /* > 1 SCL cycle */
        cmt_spi3_delay();
        cmt_spi3_delay();

        p_buf[i] = cmt_spi3_recv();

        cmt_spi3_scl_0();

        /* > 2 us */
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();

        cmt_spi3_fcsb_1();

        /* > 4 us */
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
        cmt_spi3_delay_us();
    }

    cmt_spi3_sda_in();

    cmt_spi3_fcsb_1();
}

#endif

