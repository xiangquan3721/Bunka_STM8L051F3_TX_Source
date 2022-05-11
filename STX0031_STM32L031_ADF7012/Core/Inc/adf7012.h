/***********************************************************************/
/*  FILE        :adf7012.h                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#ifndef ADF7012_H_
#define ADF7012_H_

void dd_write_7021_reg(unsigned char* reg_bytes);
void dd_set_ADF7021_Power_on(void);
void dd_set_TX_mode(void);
void dd_set_ADF7021_Power_on_Init(void);

#endif