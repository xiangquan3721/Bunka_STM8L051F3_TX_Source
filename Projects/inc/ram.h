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
	#define 	FLAG_BYTE		RAM_OP1.BYTE	 
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

#define BASE_100ms	 100


//extern UINT8  m_RFNormalBuf[35];
extern UINT8  m_RFNormalBuf[28];
extern uni_rom_id ID_data;
extern UINT8 Control_code;
extern UINT16 txphase;
extern UINT8 txphase_Repeat;
extern UINT8 ID_INT_CODE;

extern UINT8 TB_100ms;
extern UINT8 TB_5s;
extern UINT8 TIME_KEY_OPEN;
extern UINT8 TIME_KEY_STOP;
extern UINT8 TIME_KEY_CLOSE;
extern UINT8 TIME_KEY_LOGIN;