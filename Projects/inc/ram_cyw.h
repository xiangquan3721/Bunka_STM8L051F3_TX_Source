#define _LedOnOff( d_LedOff )   PIN_LED=0;
#define  key_Antishake  200//80//防抖
#define  key_shortdelay 1200//2500//4000 按键间隔控制
#define  key_fun   4500//5000//长按键案件
#define  key_fast  1400//2400//进入快速加减吗
#define  count_speed 2//10//加减 快键速度
#define BASE_1s	         750//这个1S 不一定是1S
#define key_press_long 1300//2300//2800
#define key_press_short 300//600//1000

//extern volatile union{
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
//}RAM_OP3;
//	//************************************************
//	#define 	FLAG_BYTE2		RAM_OP3.BYTE	 
//	//------------------------------------------------
//	#define		FG_KEY_DECIDE		RAM_OP3.BIT.Bit0	// 
//	#define 	FG_KEY_CLOSETIME		RAM_OP3.BIT.Bit1	//
//	#define 	FG_KEY_NOWTIME		RAM_OP3.BIT.Bit2	//
//	#define 	FG_KEY_OPENTIME		RAM_OP3.BIT.Bit3	//
//	#define 	FG_KEY_DEC		RAM_OP3.BIT.Bit4	//
//	#define 	FG_KEY_ADD	        RAM_OP3.BIT.Bit5	//
//	#define 	FG_LCD_1s		RAM_OP3.BIT.Bit6	//
//	#define 	FG_LCD_SANSUO		RAM_OP3.BIT.Bit7	//
//	//************************************************


extern UINT8 FG_KEY_DECIDE;// 
extern UINT8 FG_KEY_CLOSETIME;//
extern UINT8 FG_KEY_NOWTIME;//
extern UINT8 FG_KEY_OPENTIME;
extern UINT8 FG_KEY_DEC;//
extern UINT8 FG_KEY_ADD;//
extern UINT8 FG_LCD_1s;//
extern UINT8 FG_RTC_1s;
extern UINT8 FG_LCD_SANSUO;//

extern UINT8  FG_100ms_CYW;
extern UINT8 TB_100ms_CYW;
extern UINT16 TB_5S_CYW;

extern UINT8 Read_Buf[32];
extern UINT8 Read_Buf_temp[32];
extern UINT32 COUNT_QIANYA;
extern const unsigned char FONT_BUF_16_16[2048];
//extern unsigned char const c8563_Store[7]; /*写入时间初值：星期一 07:59:00*/  
extern unsigned char g8563_Store[7]; /*时间交换区,全局变量声明*/ 
extern unsigned char now_timer[6];
extern unsigned char auto_open_timer[2];//分时
extern unsigned char auto_close_timer[2];//分时
extern unsigned char open_timer_Store[2];
extern unsigned char close_timer_Store[2];
extern unsigned char last_open_timer[2];//fen shi 这个就是上一次的开时间记录
extern unsigned char last_close_timer[2];//fen shi 这个就是上一次的闭时间记录


extern UINT8 DISP_INDEX;
extern UINT8 DISP_DIQU;
extern UINT8 DISP_GUANGBIAO;
extern UINT8  TIMER_MODE_OPEN;
extern UINT8  TIMER_MODE_CLOSE;
extern UINT8 TIMER_MODE_DISP;
extern UINT8 AREA_TIME[4][6][4];
extern UINT32 KEY_COUNT;
extern UINT8 FLAG_ONPOWER;

extern UINT8 FLAG_MODE;
extern UINT8 COUNT_FAST;
extern UINT8 DISP_SANSUO;
extern UINT8 HIS_MIN;

extern UINT16 TB_1s_CYW;
extern UINT16 TB_POWER;
extern UINT16 BEEP_COUNT;

extern UINT8 FLAG_BACKLIGHT_5S;
extern UINT8 FLAG_BACKLIGHT_1S;
extern UINT8 FLAG_BACKLIGHT_60S;
extern const unsigned char FONT_BUF_8_32[832];
extern const unsigned char FONT_BUF_16_32[1344];
//extern UINT8 COUNT_BACKLIGHT_5S;
extern unsigned char Read_Buf_temp[32];
extern const unsigned char  FONT_BUF_24_32[96];
extern const unsigned char  FONT_BUF_8_16[176];
extern const unsigned char  FONT_BUF_8_24[264];
extern const unsigned char Area_time[8][12][4];
extern UINT8 FLAG_INITLCD;
extern float AD_ave_cyw;
extern float AD_value_cyw;
extern float AD_sum_cyw;
extern unsigned char  AD_Flag;
extern unsigned char  OPEN_Flag;

extern UINT8  FG_KEY_OPEN_CYW;//
extern UINT8  FG_KEY_STOP_CYW;//
extern UINT8  FG_KEY_CLOSE_CYW;//
extern UINT8  FG_KEY_LOGIN_CYW;//
extern UINT8  FLAG_beep_CYW;// 

extern UINT32 KEY_CLOSETIME_COUNT;
extern UINT32 KEY_OPENTIME_COUNT;
extern UINT32 KEY_NOWTIME_COUNT;
extern UINT32 KEY_ADD_COUNT;
extern UINT32 KEY_DEC_COUNT;
extern UINT32 KEY_DECIDE_COUNT;
extern UINT8  FLAG_RTC_RTC;
extern unsigned char  LOW_Flag;
extern UINT16 FLAG_PRESS;
extern UINT8 FLAG_CLOCK;

extern UINT8 FLAG_POWER;//BIT0-lcd part power down  BIT1-wireless part power 
extern UINT32 time1ms_count;

struct Second_send_TPYE
{
  UINT32 times_second_send ;
  UINT8 flag_second_send ;
  UINT8 Type_second_send ;//open close
  UINT16 Interval_second_send ;//送信间隔
  
  
};
extern struct Second_send_TPYE Second_send_STR;
//{
 // UINT32 times_second_send ;
 // UINT8 flag_second_send ;
  
//}