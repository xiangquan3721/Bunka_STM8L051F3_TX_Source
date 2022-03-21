#ifndef __CMT2300A_APP_H__
#define __CMT2300A_APP_H__

#include "radio.h"
#include "cmt2300a.h"

/*如果需要将 Demo 程序移植到其他 MCU 平台，需要修改 cmt2300a_hal.h 中的一些宏定义*/
/* ************************************************************************
*  The following need to be modified by user
*  ************************************************************************ */
#define CG2214M6_USE_T            P23
#define CG2214M6_USE_R            P23
#define pin_clk_in            		P23
#define pin_sda_out            P23
#define pin_sda_in            P23
#define TP7_TEST_MODE            		P23
#define Key_Tx_Carrier            P23
#define Key_Tx_Data            P23
#define Key_Rx_Data            		P23
/* ************************************************************************ */

#define RF_PACKET_SIZE 32               /* Define the payload size here */

extern xdata u8 g_rxBuffer[RF_PACKET_SIZE];   /* RF Rx buffer */
extern xdata u8 g_txBuffer[RF_PACKET_SIZE];


void Signal_DATA_Decode(u8 NUM_Type,u8 pbuf[]);
void CMT2300A_TX_PACKET(u8 *pBuf,u8 len);
void CMT2300A_RX_ENABLE(void);
void SCAN_RECEIVE_PACKET(void);
void CMT2300A_Set_Freq(u8 freq);


void cmt2300a_tx_test(u8 mode);
void RF_Test_Mode(void);
u8 cmt2300a_rx_test(void);

#endif