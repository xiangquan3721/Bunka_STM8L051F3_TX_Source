#ifndef __RAM_H__
#define __RAM_H__
//CPU?????
//?????ADF030???????
//#define TX_TEST_CARRIER_MODE 0
#include "Type.h" //
#include "key_and_Other.h"

extern xdata u16 X_COUNT;
extern xdata u16 X_ERR; //记录错误的个�?
extern xdata u8  X_ERR_CNT;
extern xdata u16 X_ERRTimer;

extern xdata u8 SIO_cnt;
extern xdata u8 SIO_buff[16];
extern xdata u8 SIO_DATA[16];



extern xdata u8 write_flash_buffer[8];



extern xdata u32 PROFILE_CH_FREQ_32bit_200002EC;
//extern xdata const u32 PROFILE_CH1_FREQ_32bit_429HighSpeed;
//extern xdata const u32 PROFILE_CH2_FREQ_32bit_429HighSpeed;

typedef union
{
    u8 un_var;
    struct
    {
        u8 un_var_bit0 : 1;
        u8 un_var_bit1 : 1;
        u8 un_var_bit2 : 1;
        u8 un_var_bit3 : 1;
        u8 un_var_bit4 : 1;
        u8 un_var_bit5 : 1;
        u8 un_var_bit6 : 1;
        u8 un_var_bit7 : 1;
    }Flag;
}Mark_Un;

extern idata Mark_Un mark0_stu;

#define key_sta     mark0_stu.Flag.un_var_bit0
#define Key1_press  1
#define Key2_press  2
#define Key3_press  3
#define Flag_FREQ_Scan   mark0_stu.Flag.un_var_bit1
#define Flag_rx_pream    mark0_stu.Flag.un_var_bit2
#define Flag_set_freq    mark0_stu.Flag.un_var_bit3
#define Flag_rx_data     mark0_stu.Flag.un_var_bit4
#define Flag_tx_en       mark0_stu.Flag.un_var_bit5
#define Flag_TxDone      mark0_stu.Flag.un_var_bit6
#define Flag_RxDone      mark0_stu.Flag.un_var_bit7

extern idata Mark_Un mark1_stu;
#define Flag_test_mode   mark1_stu.Flag.un_var_bit0
#define Flag_test_fm     mark1_stu.Flag.un_var_bit1
#define Flag_test_rssi   mark1_stu.Flag.un_var_bit2
#define Flag_test_pc     mark1_stu.Flag.un_var_bit3
#define key_flag         mark1_stu.Flag.un_var_bit4  

//-----------------------------------------------------------------------------------------------
typedef union{
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

typedef union{
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

typedef union{
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

typedef union{
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
extern idata RAM_OP1 RAM_OP1_type;
	#define 	FLAG_BYTE0		RAM_OP1_type.BYTE	 
	//------------------------------------------------
	#define		FLAG_APP_TX		RAM_OP1_type.BIT.Bit0	// 
	#define 	FG_KEY_OPEN		RAM_OP1_type.BIT.Bit1	//
	#define 	FG_KEY_STOP		RAM_OP1_type.BIT.Bit2	//
	#define 	FG_KEY_CLOSE		RAM_OP1_type.BIT.Bit3	//
	#define 	FG_KEY_LOGIN		RAM_OP1_type.BIT.Bit4	//
	#define 	FG_PWRON		RAM_OP1_type.BIT.Bit5	//
	#define 	FG_1ms		        RAM_OP1_type.BIT.Bit6	//
	#define 	FG_100ms		RAM_OP1_type.BIT.Bit7	//
	//************************************************



	//************************************************
extern idata RAM_OP2 RAM_OP2_type;
	#define 	FLAG_BYTE1		RAM_OP2_type.BYTE	 
	//------------------------------------------------
#define FLAG_beep   RAM_OP2_type.BIT.Bit0	// 
#define 	FG_beep_on		RAM_OP2_type.BIT.Bit1	//
#define 	FG_beep_off		RAM_OP2_type.BIT.Bit2	//
#define 	FG_LED_on		RAM_OP2_type.BIT.Bit3	//
#define 	mb_AutoTxOnOff		RAM_OP2_type.BIT.Bit4	//
#define 	mb_AutoTxInhibit	RAM_OP2_type.BIT.Bit5	//
#define 	FG_test1		RAM_OP2_type.BIT.Bit6	//
#define 	FG_test_mode		RAM_OP2_type.BIT.Bit7	//
	//************************************************


	//************************************************
extern idata RAM_RegSW RAM_RegSW_type;
	#define 	FLAG_BYTE_RegSW		RAM_RegSW_type.BYTE	 
	//------------------------------------------------
	#define		mb_RegSw		RAM_RegSW_type.BIT.Bit0	// 
	#define 	mb_RegStopSw		RAM_RegSW_type.BIT.Bit1	//
	#define 	mb_RegOpenSw		RAM_RegSW_type.BIT.Bit2	//
	#define 	mb_RegCloseSw		RAM_RegSW_type.BIT.Bit3	//
	#define 	mb_RegVentSw		RAM_RegSW_type.BIT.Bit4	//
	#define 	m_KeyOptSetOpenStop	RAM_RegSW_type.BIT.Bit5	//
	#define 	mb_NoPush		RAM_RegSW_type.BIT.Bit6	//
	#define 	mb_NoPushWait		RAM_RegSW_type.BIT.Bit7	//
	//************************************************


	//************************************************
extern idata RAM_SW RAM_SW_type;
	#define 	FLAG_BYTE_SW		RAM_SW_type.BYTE	 
	//------------------------------------------------
	#define		mb_OpenSw		RAM_SW_type.BIT.Bit0	// 
	#define 	mb_StopSw		RAM_SW_type.BIT.Bit1	//
	#define 	mb_CloseSw		RAM_SW_type.BIT.Bit2	//
	#define 	FG_d_StopKey		RAM_SW_type.BIT.Bit3	//
    #define     BIT_SIO         RAM_SW_type.BIT.Bit4	//
	#define 	FG_10s        		RAM_SW_type.BIT.Bit5	// 2015.1.31??3
	#define 	FG_BAT		        RAM_SW_type.BIT.Bit6	//
	#define 	FG_Complex_Single_shot	RAM_SW_type.BIT.Bit7	//2015.1.31??2
	//************************************************


#define BASE_100ms	 100
#define BASE_976us	 3

extern xdata u8 TB_51s;
extern xdata u8 TB_sum_5s;
//#define TB_50s	 68//50
//#define TB_51s	 69//51
#define TB_60s	 78//60
#define TB_20s	 20

extern xdata u8  m_RFNormalBuf[40];
extern xdata uni_rom_id ID_data;
extern xdata uni_rom_id ID_data_add;
extern xdata u8 Control_code;
extern xdata u16 txphase;
extern xdata u8 txphase_Repeat;
extern xdata u8 ID_INT_CODE;
extern xdata u16 txphase_end;

extern xdata u16 TIME_BEEP_on;
extern xdata u8 TIME_BEEP_off;
extern xdata u16 BASE_TIME_BEEP_on;
extern xdata u8 BASE_TIME_BEEP_off;
extern xdata u8 TIME_BEEP_freq;

extern xdata u8 TB_976us;
extern xdata u8 TB_100ms;
extern xdata u8 TB_5s;


extern xdata u8 SIO_cnt;
extern xdata u8 SIO_buff[16];
extern xdata u8 SIO_DATA[16];

//extern xdata u16 BAT_value;




#define d_Idle	 0//0x8A
#define d_Clear	 0
#define d_On	 1
#define d_Off	 0
#define d_OK	 0
#define d_NG	 1
#define d_RegAppend	 1
#define d_RegDelete	 2
#define d_KeyNoPush  0xFF
#define d_Time50ms  50
#define d_DupliTime4s  4000
#define d_DupliTime1s  1000
#define d_DupliTime3s  3000
#define d_DupliTime10s 10000
#define d_Time5s 5000
#define d_Time9s 9000
#define d_D1stTime3s 3000
#define d_Time3s  3000
#define d_Time10s 10000
#define d_Time1min 60000
/*		kind of key		*/
#define		d_IdleKey		0					// Idle(N/A)
#define		d_OpenKey		1
#define		d_StopKey		2
#define		d_CloseKey		3
#define		d_VentKey		4
#define		d_RegKey		5
#define		d_ReqStopReg            10

#define		d_ReqIdle		0
#define		d_ReqOpen		1
#define		d_ReqStop		2
#define		d_ReqClose		3
#define		d_ReqVent		4
#define		d_ReqOpenStop	5
#define		d_ReqOpenClose	6
#define		d_ReqOpenVent	7
#define		d_ReqOpenReg	8
#define		d_ReqStopClose	9
#define		d_ReqStopReg 	10
#define		d_ReqCloseReg	11
#define		d_ReqCloseVent	12
#define		d_ReqVentReg    13
#define		d_ReqAutoTxStart 14
#define		d_ReqAutoTxStop	15



#define _LedOnOff( d_LedOff )   PIN_LED=0;
extern xdata u8 m_KeyNew;
extern xdata u8 m_KindOfKey;
extern xdata u8 m_KeyOld;
extern xdata u16 m_ChatterCount;
extern xdata u16 m_TimerKey;
extern xdata u8 m_KeyNo;
extern xdata u8 m_KeyOptSetMode;
extern xdata u8 m_KeyOpenCount;
extern xdata u8 m_KeyCloseCount;
extern xdata u16 m_KeyDupli1stTimer;
extern xdata u8 m_KeyOptSetMode;
extern xdata u16 m_KeyDupliSetTimeout;
extern xdata u8 rom_KeyOpt;
extern xdata u16 time_led;
extern xdata u16 m_TimerKeyMonitor;
extern xdata u8 m_KeyCount;
extern xdata u8 m_RegMode;
extern xdata u8 m_RegID[9];
extern xdata u8 m_RegDigit;
extern xdata u16 m_TimerRegMode;

extern xdata u8 AD_DATA_BUFF[2];
extern xdata u32 RAM_BAT_SUM;
extern xdata u16 RAM_BAT_AVG;
extern xdata u8 RAM_BAT_CNT;
extern xdata u8 BAT_out;
extern xdata u32 BAT_Voltage_value;

extern xdata u16 TIME_Once_twice_switch;   //2015.1.31??4
extern xdata u16 TIME_10s;   //2015.1.31??3
extern xdata u16 key_Value;   //2015.1.31??3

extern xdata u8 TIME_2s_RestTX;  //2015.4.13??
extern xdata u16 TIME_power_on_AD;

void _Init_RAM(void);

#endif
