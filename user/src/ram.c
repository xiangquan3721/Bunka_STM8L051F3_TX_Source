#include "Type.h"
#include "ram.h"

idata Mark_Un mark0_stu = {0};
idata Mark_Un mark1_stu = {0};

xdata u8 write_flash_buffer[8] = {0};
xdata u32 PROFILE_CH_FREQ_32bit_200002EC = 426075000ul;
//xdata const u32 PROFILE_CH1_FREQ_32bit_429HighSpeed=429350000;//429350000;//429225000;
//xdata const u32 PROFILE_CH2_FREQ_32bit_429HighSpeed=429550000;//429550000;//429237500;

idata RAM_OP1 RAM_OP1_type = {0};
idata RAM_OP2 RAM_OP2_type = {0};
idata RAM_RegSW RAM_RegSW_type = {0};
idata RAM_SW RAM_SW_type = {0};

xdata u8 TB_51s = 0;
xdata u8 TB_sum_5s = 0;


//xdata u8  m_RFNormalBuf[35];
xdata u8  m_RFNormalBuf[40] = {0};
xdata uni_rom_id ID_data = {0};
xdata uni_rom_id ID_data_add = {0};
xdata u8 Control_code = 0;
xdata u16 txphase = 0;
xdata u8 txphase_Repeat = 0;
xdata u8 ID_INT_CODE = 0;
xdata u16 txphase_end = 0;

xdata u16 TIME_BEEP_on = 0;
xdata u8 TIME_BEEP_off = 0;
xdata u16 BASE_TIME_BEEP_on = 0;
xdata u8 BASE_TIME_BEEP_off = 0;
xdata u8 TIME_BEEP_freq = 0;

xdata u8 TB_976us = 0;
xdata u8 TB_100ms = 0;
xdata u8 TB_5s = 0;

xdata u8 SIO_cnt = 0;
xdata u8 SIO_buff[16] = {0};
xdata u8 SIO_DATA[16] = {0};

//xdata u16 BAT_value;


xdata u8 m_KeyNew = 0;
xdata u8 m_KindOfKey = 0;
xdata u8 m_KeyOld = 0;
xdata u16 m_ChatterCount = 0;
xdata u16 m_TimerKey = 0;
xdata u8 m_KeyNo = 0;
xdata u8 m_KeyOptSetMode = 0;
xdata u8 m_KeyOpenCount = 0;
xdata u8 m_KeyCloseCount = 0;
xdata u16 m_KeyDupli1stTimer = 0;
xdata u16 m_KeyDupliSetTimeout = 0;
xdata u8 rom_KeyOpt = 0;
xdata u16 time_led = 0;
xdata u16 m_TimerKeyMonitor = 0;
xdata u8 m_KeyCount = 0;
xdata u8 m_RegMode = 0;
xdata u8 m_RegID[9] = {0};
xdata u8 m_RegDigit = 0;
xdata u16 m_TimerRegMode = 0;

xdata u8 AD_DATA_BUFF[2] = {0};		// A/D Buffers
xdata u32 RAM_BAT_SUM = 0;
xdata u16 RAM_BAT_AVG = 0;
xdata u8 RAM_BAT_CNT = 0;
xdata u8 BAT_out = 0;
xdata u32 BAT_Voltage_value = 0;

xdata u16 TIME_Once_twice_switch = 0;   //2015.1.31??4
xdata u16 TIME_10s = 0;   //2015.1.31??3
xdata u16 key_Value = 0;   //2015.1.31??3

xdata u8 TIME_2s_RestTX = 0;  //2015.4.13??
xdata u16 TIME_power_on_AD = 0;

void _Init_RAM(void)
{
  TB_100ms = BASE_100ms;
  //TB_5s=TB_50s;//50;
  TB_51s=26;//69;
  TB_5s=TB_51s-1;
  
  	/*		Timer		*/
								// General 1s timer
	
	/*		Key		*/
	_SetKeyChatterCount() ;									// Chatter counter set
	m_KeyNew = m_KeyOld = d_KeyNoPush ;
	m_KindOfKey          = d_IdleKey ;
	//mb_Keycheck          = d_Clear ;
	mb_NoPush            = d_On ;
	mb_NoPushWait        = d_Clear ;
	_ClearSpecialMultiKeyState() ;
	m_TimerKey = d_Clear ;
	m_TimerKeyMonitor = d_Clear ;
}
