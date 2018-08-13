/***********************************************************************/
/*  FILE        :ram.h                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

extern volatile union{
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
	//************************************************
	#define 	FLAG_BYTE0		RAM_OP1.BYTE	 
	//------------------------------------------------
	#define		FLAG_APP_TX		RAM_OP1.BIT.Bit0	// 
	#define 	FG_KEY_OPEN		RAM_OP1.BIT.Bit1	//
	#define 	FG_KEY_STOP		RAM_OP1.BIT.Bit2	//
	#define 	FG_KEY_CLOSE		RAM_OP1.BIT.Bit3	//
	#define 	FG_KEY_LOGIN		RAM_OP1.BIT.Bit4	//
	#define 	FG_PWRON		RAM_OP1.BIT.Bit5	//
	#define 	FG_1ms		        RAM_OP1.BIT.Bit6	//
	#define 	FG_100ms		RAM_OP1.BIT.Bit7	//
	//************************************************


extern volatile union{
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
	//************************************************
	#define 	FLAG_BYTE1		RAM_OP2.BYTE	 
	//------------------------------------------------
	#define		FLAG_beep		RAM_OP2.BIT.Bit0	// 
	#define 	FG_beep_on		RAM_OP2.BIT.Bit1	//
	#define 	FG_beep_off		RAM_OP2.BIT.Bit2	//
	#define 	FG_LED_on		RAM_OP2.BIT.Bit3	//
	#define 	mb_AutoTxOnOff		RAM_OP2.BIT.Bit4	//
	#define 	mb_AutoTxInhibit	RAM_OP2.BIT.Bit5	//
	#define 	FG_test1		RAM_OP2.BIT.Bit6	//
	#define 	FG_test_mode		RAM_OP2.BIT.Bit7	//
	//************************************************

extern volatile union{
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
	//************************************************
	#define 	FLAG_BYTE_RegSW		RAM_RegSW.BYTE	 
	//------------------------------------------------
	#define		mb_RegSw		RAM_RegSW.BIT.Bit0	// 
	#define 	mb_RegStopSw		RAM_RegSW.BIT.Bit1	//
	#define 	mb_RegOpenSw		RAM_RegSW.BIT.Bit2	//
	#define 	mb_RegCloseSw		RAM_RegSW.BIT.Bit3	//
	#define 	mb_RegVentSw		RAM_RegSW.BIT.Bit4	//
	#define 	m_KeyOptSetOpenStop	RAM_RegSW.BIT.Bit5	//
	#define 	mb_NoPush		RAM_RegSW.BIT.Bit6	//
	#define 	mb_NoPushWait		RAM_RegSW.BIT.Bit7	//
	//************************************************

extern volatile union{
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
	//************************************************
	#define 	FLAG_BYTE_SW		RAM_SW.BYTE	 
	//------------------------------------------------
	#define		mb_OpenSw		RAM_SW.BIT.Bit0	// 
	#define 	mb_StopSw		RAM_SW.BIT.Bit1	//
	#define 	mb_CloseSw		RAM_SW.BIT.Bit2	//
	#define 	FG_d_StopKey		RAM_SW.BIT.Bit3	//
//	#define 	mb_RegVentSw		RAM_SW.BIT.Bit4	//
//	#define 	FG_PWRON		RAM_SW.BIT.Bit5	//
	#define 	m_RegMode		RAM_SW.BIT.Bit6	//
	#define 	m_TimerKeyMonitor	RAM_SW.BIT.Bit7	//
	//************************************************


#define BASE_100ms	 100
#define BASE_976us	 3


//extern UINT8  m_RFNormalBuf[35];
extern UINT8  m_RFNormalBuf[28];
extern uni_rom_id ID_data;
extern UINT8 Control_code;
extern UINT16 txphase;
extern UINT8 txphase_Repeat;
extern UINT8 ID_INT_CODE;

extern UINT8 TIME_BEEP_on;
extern UINT8 TIME_BEEP_off;
extern UINT8 BASE_TIME_BEEP_on;
extern UINT8 BASE_TIME_BEEP_off;
extern UINT8 TIME_BEEP_freq;

extern UINT8 TB_976us;
extern UINT8 TB_100ms;
extern UINT8 TB_5s;
extern UINT8 TIME_KEY_OPEN;
extern UINT16 TIME_KEY_STOP;
extern UINT8 TIME_KEY_CLOSE;
extern UINT16 TIME_KEY_LOGIN;





#define d_Idle	 0//0x8A
#define d_Clear	 0
#define d_On	 1
#define d_Off	 0
#define d_OK	 0
#define d_NG	 1
#define d_KeyNoPush  0xFF
#define d_Time50ms  50
#define d_DupliTime4s  4000
#define d_DupliTime1s  1000
#define d_DupliTime3s  3000
#define d_DupliTime10s 10000
#define d_Time5s 5000
#define d_Time9s 9000
#define d_D1stTime3s 3000
/*		kind of key		*/
#define		d_IdleKey		0					// Idle(N/A)
#define		d_OpenKey		1
#define		d_StopKey		2
#define		d_CloseKey		3
#define		d_VentKey		4



#define _LedOnOff( d_LedOff )   PIN_LED=0;
extern UINT8 m_KeyNew;
extern UINT8 m_KindOfKey;
extern UINT8 m_KeyOld;
extern UINT8 m_ChatterCount;
extern UINT16 m_TimerKey;
extern UINT8 m_KeyNo;
extern UINT8 m_KeyOptSetMode;
extern UINT8 m_KeyOpenCount;
extern UINT8 m_KeyCloseCount;
extern UINT16 m_KeyDupli1stTimer;
extern UINT8 m_KeyOptSetMode;
extern UINT16 m_KeyDupliSetTimeout;
extern UINT8 rom_KeyOpt;
extern UINT8 time_led;