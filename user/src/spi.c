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


/* SPI相关IO口初始化,MISO->PB7;MOSI->PB6;SCK->PB5;CS->PB4 */
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

    SPI1_CS_H;
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

}

/*
函数功能：SPI1写CMT2300A寄存器函数,主要用于将配置写入CMT2300A寄存器
函数形参：addr 寄存器地址，dat 写入的配置数据
*/
void Cmt_Spi_Write(u8 addr, u8 dat)
{

}

/*
函数功能：SPI1接收数据函数,主要用于读取CMT2300A的FIFO,读取无线接收到的数据
函数形参：p_buf 接收缓冲区;len 接收数据长度
*/
void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len)
{

}

/*
函数功能：SPI1发送数据函数,主要用于将数据送入CMT2300A的FIFO,发送数据
函数形参：p_buf 发送数据缓冲区，len 发送数据长度
*/
void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len)
{

}


