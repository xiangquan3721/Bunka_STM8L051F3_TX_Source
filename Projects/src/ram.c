/***********************************************************************/
/*  FILE        :ram.c                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include  <iostm8l051f3.h>				// CPU�ͺ� 
#include  <iostm8l151g4.h>				// CPU�ͺ�
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����



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

UINT8 SIO_cnt;
UINT8 SIO_buff[16];
UINT8 SIO_DATA[16];
ADF70XX_REG_T ROM_adf7012_value[4];

const ADF70XX_REG_T Default_adf7012_value[4]={0x088a000,0x00147c01,0x019112c6,0x0021d08f};    //4dBm


UINT8 m_KeyNew;
UINT8 m_KindOfKey;
UINT8 m_KeyOld;
UINT16 m_ChatterCount;
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

UINT8 AD_DATA_BUFF[2];		// A/D Buffers
UINT32 RAM_BAT_SUM=0;
UINT16 RAM_BAT_AVG=0;
UINT8 RAM_BAT_CNT=0;
UINT8 BAT_out=0;
UINT32 BAT_Voltage_value=0;

UINT16 TIME_Once_twice_switch=0;   //2015.1.31����4
UINT16 TIME_10s=0;   //2015.1.31����3
UINT16 key_Value=0;   //2015.1.31����3

UINT8 TIME_2s_RestTX=0;  //2015.4.13����



UINT16 TIME_AUTO_TX;
UINT16 TIME_AUTO_TX_bak;
UINT16 TIME_data;
UINT16 TIME_data_differ;
UINT8 FLAG_AUTO_TX;
UINT8 FLAG_AUTO_TX_stop;
UINT16 rand_data;
UINT8 POWER_ON_PIN_KEY_STOP;
UINT16 srand_TIME;

UINT8 FLAG_srand_data=0;
UINT16 srand_data_AD=0;
UINT32 srand_data_other=0;
UINT16 srand_data;

UINT8 KEY_stop_count=0;  //add 20170120
UINT8 FLAG_StopKey_Open=0;
UINT8 FLAG_StopKey_Close=0;
UINT16 TIME_StopKey_Open_Close=0;











