/***********************************************************************/
/*  FILE        :ram.c                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l051f3.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义



volatile union{
	unsigned char BYTE;	
	struct { 
		unsigned char	Bit0:	1;
		unsigned char	Bit1:	1;
		unsigned char	Bit2:	1;
		unsigned char	Bit3:	1;
		unsigned char	Bit4:	1;
		unsigned char	Bit5:	1;
		unsigned char	Bit6:	1;
		unsigned char	Bit7:	1;
	}BIT; 	
}RAM_OP1;

volatile union{
	unsigned char BYTE;	
	struct { 
		unsigned char	Bit0:	1;
		unsigned char	Bit1:	1;
		unsigned char	Bit2:	1;
		unsigned char	Bit3:	1;
		unsigned char	Bit4:	1;
		unsigned char	Bit5:	1;
		unsigned char	Bit6:	1;
		unsigned char	Bit7:	1;
	}BIT; 	
}RAM_OP2;



//UINT8  m_RFNormalBuf[35];
UINT8  m_RFNormalBuf[28];
uni_rom_id ID_data;
UINT8 Control_code;
UINT16 txphase;
UINT8 txphase_Repeat;
UINT8 ID_INT_CODE;

UINT8 TIME_BEEP_on;
UINT8 TIME_BEEP_off;
UINT8 BASE_TIME_BEEP_on;
UINT8 BASE_TIME_BEEP_off;
UINT8 TIME_BEEP_freq;

UINT8 TB_976us;
UINT8 TB_100ms;
UINT8 TB_5s;
UINT8 TIME_KEY_OPEN;
UINT16 TIME_KEY_STOP;
UINT8 TIME_KEY_CLOSE;
UINT16 TIME_KEY_LOGIN;
