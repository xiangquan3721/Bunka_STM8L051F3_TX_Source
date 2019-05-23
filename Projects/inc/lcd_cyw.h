#define INIT_mode  0
#define NORMAL_mode 1
#define CONTROL_mode 2
#define NOWTIMESET_mode 3
#define OPENTIMESET_mode 4
#define CLOSETIMESET_mode 5
#define OPENONOFF_mode 6
#define CLOSEONOFF_mode 7
#define PREINSTALL_mode 8
#define AOTU_mode 9 
#define ADDDEC30_mode 10

#define Timer_Mode_SET 0
#define Timer_Mode_OFF 1 
#define Timer_Mode_AUTO 2

#define Normal_hang_1  4//正常显示情况下的行1
#define Normal_hang_2  53//正常显示情况下的行2
#define Normal_hang_3  101//正常显示情况下的行3
#define lie_1 1//第一列
#define lie_2 2//第二列
#define lie_3 3//第三列
#define lie_4 4//第四列
#define lie_5 5//第五列
#define lie_6 6//第六列
#define lie_7 7//第七列
#define lie_8 8//第七列
#define nowtimeset_hang_1  4//设置现在时间行1
#define nowtimeset_hang_2  36//设置现在时间行2
#define nowtimeset_hang_3  68//设置现在时间行3
#define nowtimeset_hang_4  108//设置现在时间行3
#define Normal_hang_2_1_0816  69
#define Normal_hang_3_1_0816  117
#define Normal_hang_2_1_0824  61
#define Normal_hang_3_1_0824  109

void menu_linshi(void);
void lcd_init(void); 
void delay(int i);

void menu_normal(void);
void menu_second(void);
void DISP_Refresh(void);
void lcd_backlight(void);
uchar caluate_monthtoreason(uchar x_mon);
void clear_clear(void);
void menu_setnowtime(void);
void dianciqianya_lcd(void);
void display_nowtime(void);
void key_touch_retime(void);
void Power_Low(void);

void lcd_checker(unsigned char data0);
void GrRectFIllBolymin(uchar lucXMin, uchar lucXMax, uchar lucYMin, uchar lucYMax, uchar lbFillColor, uchar lGlowRightmostColumn);