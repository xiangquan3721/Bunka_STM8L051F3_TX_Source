/***********************************************************************/
/*  FILE        :ram.c                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include  <iostm8l151c6.h>				// CPU型号 
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义



//volatile union{
//	unsigned char BYTE;	
//	struct { 
//		unsigned char	Bit0:	1;
//		unsigned char	Bit1:	1;
//		unsigned char	Bit2:	1;
//		unsigned char	Bit3:	1;
//		unsigned char	Bit4:	1;
//		unsigned char	Bit5:	1;
//		unsigned char	Bit6:	1;
//		unsigned char	Bit7:	1;
//	}BIT; 	
//}RAM_OP1;
//
//volatile union{
//	unsigned char BYTE;	
//	struct { 
//		unsigned char	Bit0:	1;
//		unsigned char	Bit1:	1;
//		unsigned char	Bit2:	1;
//		unsigned char	Bit3:	1;
//		unsigned char	Bit4:	1;
//		unsigned char	Bit5:	1;
//		unsigned char	Bit6:	1;
//		unsigned char	Bit7:	1;
//	}BIT; 	
//}RAM_OP2;
//
//volatile union{
//	unsigned char BYTE;	
//	struct { 
//		unsigned char	Bit0:	1;
//		unsigned char	Bit1:	1;
//		unsigned char	Bit2:	1;
//		unsigned char	Bit3:	1;
//		unsigned char	Bit4:	1;
//		unsigned char	Bit5:	1;
//		unsigned char	Bit6:	1;
//		unsigned char	Bit7:	1;
//	}BIT; 	
//}RAM_RegSW;
//volatile union{
//	unsigned char BYTE;	
//	struct { 
//		unsigned char	Bit0:	1;
//		unsigned char	Bit1:	1;
//		unsigned char	Bit2:	1;
//		unsigned char	Bit3:	1;
//		unsigned char	Bit4:	1;
//		unsigned char	Bit5:	1;
//		unsigned char	Bit6:	1;
//		unsigned char	Bit7:	1;
//	}BIT; 	
//}RAM_SW;

UINT8  FLAG_APP_TX=0;// 
UINT8  FG_KEY_OPEN=0;//
UINT8  FG_KEY_STOP=0;//
UINT8  FG_KEY_CLOSE=0;//
UINT8  FG_KEY_LOGIN=0;//
UINT8  FG_PWRON=0;//
UINT8  FG_1ms=0;//
UINT8  FG_100ms=0;
UINT8  FLAG_beep=0;// 
UINT8  FG_beep_on=0;//
UINT8  FG_beep_off=0;	//
UINT8  FG_LED_on=0;	//
UINT8  mb_AutoTxOnOff=0;		
UINT8  mb_AutoTxInhibit=0;	//
UINT8  FG_test1=0;		//
UINT8  FG_test_mode=0;	
UINT8  mb_RegSw=0; 
UINT8  mb_RegStopSw=0	;
UINT8  mb_RegOpenSw	=0;
UINT8  mb_RegCloseSw	=0;
UINT8  mb_RegVentSw	=0;
UINT8  m_KeyOptSetOpenStop	=0;
UINT8  mb_NoPush		=0;
 UINT8  mb_NoPushWait		=0;
 UINT8  mb_OpenSw	=0; 
UINT8  mb_StopSw	=0;
UINT8  mb_CloseSw	=0;
 UINT8  FG_d_StopKey	=0;
UINT8  BIT_SIO		=0;
// UINT8  FG_PWRON	=0;
UINT8  FG_BAT		=0;
UINT8  FG_BAT_value	=0;

UINT8  FG_10s ;
UINT8  FG_Complex_Single_shot	;


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
//const ADF70XX_REG_T Default_adf7012_value[4]={0x0884000,0x00154dc1,0x011209a6,0x0021d04f};
//2015 03 05 曾工要求把发射功率默认值改为13 到15
const ADF70XX_REG_T Default_adf7012_value[4]={0x0884000,0x00154dc1,0x011209e6,0x0021d04f};
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

UINT8 AD_DATA_BUFF[2];		// A/D Buffers
UINT32 RAM_BAT_SUM=0;
UINT16 RAM_BAT_AVG=0;
UINT8 RAM_BAT_CNT=0;
UINT8 BAT_out=0;
UINT32 BAT_Voltage_value=0;

UINT16 TIME_Once_twice_switch=0;   //2015.1.31修正4
UINT16 TIME_10s=0;   //2015.1.31修正3
UINT16 key_Value=0;   //2015.1.31修正3

UINT8 TIME_2s_RestTX=0;  //2015.4.13修正
UINT8 TB_51s;
UINT8 TB_sum_5s;
