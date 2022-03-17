#ifndef __SPI_H__
#define __SPI_H__

#include "REG_MA82G5Bxx.H"
#include "Type.h"
#include "API_Macro_MA82G5Bxx.H"

#define TxEnable  0
#define TxDisbale 1

#define cmt_spi3_csb_out()      {PORT_SetP1PushPull(BIT4);}
#define cmt_spi3_fcsb_out()     {PORT_SetP2PushPull(BIT2);}
#define cmt_spi3_scl_out()      {PORT_SetP1PushPull(BIT7);}
#define cmt_spi3_sda_out()      {PORT_SetP1PushPull(BIT5);}
#define cmt_spi3_sda_in()       {PORT_SetP1OpenDrain(BIT5);P15 = 1;PORT_EnP14P15P16P17PullHigh();}

#define cmt_spi3_csb_1()        {P14 = 1;}
#define cmt_spi3_csb_0()        {P14 = 0;}

#define cmt_spi3_fcsb_1()       {P22 = 1;}
#define cmt_spi3_fcsb_0()       {P22 = 0;}

#define cmt_spi3_scl_1()        {P17 = 1;}
#define cmt_spi3_scl_0()        {P17 = 0;}

#define cmt_spi3_sda_1()        {P15 = 1;}
#define cmt_spi3_sda_0()        {P15 = 0;}
#define cmt_spi3_sda_read()     P15
void cmt_spi3_init(void);
void Cmt_Spi_Read(u8 addr, u8* p_dat);
void Cmt_Spi_Write(u8 addr, u8 dat);
void Cmt_Spi_Write_Fifo(const u8* p_buf, u16 len);
void Cmt_Spi_Read_Fifo(u8* p_buf, u16 len);
void cmt_spi3_delay(void);
void cmt_spi3_delay_us(void);

#endif