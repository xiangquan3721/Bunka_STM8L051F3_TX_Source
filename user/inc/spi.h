#ifndef __SPI_H__
#define __SPI_H__

#include "iostm8l151g4.h"
#include "gpio_defs.h"

#define SPI_AnalogOrHardware    0   /* 0:使用模拟SPI;1:使用硬件SPI */

#define TxEnable  0
#define TxDisbale 1

#define SPI_TX_EN       PC_ODR_ODR5 /* 发送开关，低电平有效 */
#define SPI_TX_EN_DDR   PC_DDR_DDR5
#define SPI_TX_EN_CR1   PC_CR1_C15
#define SPI_TX_EN_CR2   PC_CR2_C25

#if SPI_AnalogOrHardware == 1   /* 硬件 */
#define SPI_CS      PB_ODR_ODR4 //CS
#define SPI_CS_DDR  PB_DDR_DDR4 //方向
#define SPI_CS_CR1  PB_CR1_C14  //类型
#define SPI_CS_CR2  PB_CR2_C24  //输出频率

#define SPI1_CS_L (SPI_CS = 0)
#define SPI1_CS_H (SPI_CS = 1)
#define SPI_CS_TOGGLE() (SPI_CS = ~SPI_CS)

#define SPI1_SCK_DDR    PB_DDR_DDR5 /* SPI1 SCK */
#define SPI1_SCK_CR1    PB_CR1_C15
#define SPI1_SCK_CR2    PB_CR2_C25

#define SPI1_MOSI_DDR   PB_DDR_DDR6 /* SPI1 MOSI*/
#define SPI1_MOSI_CR1   PB_CR1_C16
#define SPI1_MOSI_CR2   PB_CR2_C26

#define SPI1_MISO_DDR   PB_DDR_DDR7 /* SPI1 MISO*/
#define SPI1_MISO_CR1   PB_CR1_C17
#define SPI1_MISO_CR2   PB_CR2_C27

#define CMT_FCSB_DDR    PD_DDR_DDR0 /* FCSB,CMT2300A FIFO控制 */
#define CMT_FCSB_CR1    PD_CR1_C10
#define CMT_FCSB_CR2    PD_CR2_C20

#define CMT_FCSB_H   (PD_ODR_ODR0 = 1)
#define CMT_FCSB_L   (PD_ODR_ODR0 = 0)

void SPI_Config_Init(void);
void Cmt_Spi_Read(u8 addr, u8* p_dat);
void Cmt_Spi_Write(u8 addr, u8 dat);
void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len);
void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len);
void cmt_spi3_delay(void);
void cmt_spi3_delay_us(void);
#endif

#if SPI_AnalogOrHardware == 0   /* 模拟 */
#define cmt_spi3_csb_out()      {PB_DDR_DDR4 = 1;PB_CR1_C14 = 1;PB_CR2_C24 = 1;}
#define cmt_spi3_fcsb_out()     {PD_DDR_DDR0 = 1;PD_CR1_C10 = 1;PD_CR2_C20 = 1;}
#define cmt_spi3_scl_out()      {PB_DDR_DDR5 = 1;PB_CR1_C15 = 1;PB_CR2_C25 = 1;}
#define cmt_spi3_sda_out()      {PB_DDR_DDR6 = 1;PB_CR1_C16 = 1;PB_CR2_C26 = 1;}
#define cmt_spi3_sda_in()       {PB_DDR_DDR6 = 0;PB_CR1_C16 = 0;PB_CR2_C26 = 0;}

#define cmt_spi3_csb_1()        {PB_ODR_ODR4 = 1;}
#define cmt_spi3_csb_0()        {PB_ODR_ODR4 = 0;}

#define cmt_spi3_fcsb_1()       {PD_ODR_ODR0 = 1;}
#define cmt_spi3_fcsb_0()       {PD_ODR_ODR0 = 0;}

#define cmt_spi3_scl_1()        {PB_ODR_ODR5 = 1;}
#define cmt_spi3_scl_0()        {PB_ODR_ODR5 = 0;}

#define cmt_spi3_sda_1()        {PB_ODR_ODR6 = 1;}
#define cmt_spi3_sda_0()        {PB_ODR_ODR6 = 0;}
#define cmt_spi3_sda_read()     PB_IDR_IDR6
void SPI_Config_Init(void);
void Cmt_Spi_Read(u8 addr, u8* p_dat);
void Cmt_Spi_Write(u8 addr, u8 dat);
void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len);
void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len);
void cmt_spi3_delay(void);
void cmt_spi3_delay_us(void);
#endif

#endif