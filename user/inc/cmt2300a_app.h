#ifndef __CMT2300A_APP_H__
#define __CMT2300A_APP_H__

#include "radio.h"
#include "cmt2300a.h"
//#include "cmt2300a_params.h"



#define RF_PACKET_SIZE 32               /* Define the payload size here */


extern u8 g_rxBuffer[RF_PACKET_SIZE];   /* RF Rx buffer */
extern u8 g_txBuffer[RF_PACKET_SIZE];


void Signal_DATA_Decode(u8 NUM_Type,u8 pbuf[]);
void CMT2300A_TX_PACKET(u8 *pBuf,u8 len);
void CMT2300A_RX_ENABLE(void);
void SCAN_RECEIVE_PACKET(void);
void CMT2300A_Set_Freq(u8 freq);


void cmt2300a_tx_test(u8 mode,u8 del);
void RF_Test_Mode(void);
u8 cmt2300a_rx_test(void);

#endif