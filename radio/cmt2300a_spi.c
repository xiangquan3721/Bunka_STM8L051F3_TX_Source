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


