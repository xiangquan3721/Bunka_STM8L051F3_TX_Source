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
}RAM_RegSW;
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
}RAM_SW;




//UINT8  m_RFNormalBuf[35];
UINT8  m_RFNormalBuf[40];
uni_rom_id ID_data;
uni_rom_id ID_data_add;
UINT8 Control_code;
UINT16 txphase;
UINT8 txphase_Repeat;
UINT8 ID_INT_CODE;
UINT16 txphase_end;

UINT16 TIME_BEEP_on;
UINT8 TIME_BEEP_off;
UINT16 BASE_TIME_BEEP_on;
UINT8 BASE_TIME_BEEP_off;
UINT8 TIME_BEEP_freq;

UINT8 TB_976us;
UINT8 TB_100ms;
UINT8 TB_5s;
UINT8 TIME_KEY_OPEN;
UINT16 TIME_KEY_STOP;
UINT8 TIME_KEY_CLOSE;
UINT16 TIME_KEY_LOGIN;
//UINT16 BAT_value;


UINT8 m_KeyNew;
UINT8 m_KindOfKey;
UINT8 m_KeyOld;
UINT8 m_ChatterCount;
UINT16 m_TimerKey;
UINT8 m_KeyNo;
UINT8 m_KeyOptSetMode;
UINT8 m_KeyOpenCount;
UINT8 m_KeyCloseCount;
UINT16 m_KeyDupli1stTimer;
UINT8 m_KeyOptSetMode;
UINT16 m_KeyDupliSetTimeout;
UINT8 rom_KeyOpt;
UINT16 time_led;
UINT16 m_TimerKeyMonitor;
UINT8 m_KeyCount;
UINT8 m_RegMode;
UINT8 m_RegID[9];
UINT8 m_RegDigit;
UINT16 m_TimerRegMode;

