
void Init8563(void);
void GetTime(void);
void Rewrite8563(void);
uchar Read8563(uchar ucAddr);
void Write8563(uchar ucAddr,uchar ucData) ;
void Alarm8563(void);
void real_time(void);

#define  now_sec g8563_Store[0]
#define  now_min g8563_Store[1] 
#define  now_hour g8563_Store[2]
#define  now_day g8563_Store[3]
#define  now_week g8563_Store[4]
#define  now_mon g8563_Store[5]
#define  now_year g8563_Store[6]
#define  open_hour open_timer_Store[1]//0x0-0x23人工设置的小时 0x24-0x47自动出来的小时 0XFF-时钟关
#define  open_min open_timer_Store[0]//
#define  close_hour close_timer_Store[1]
#define  close_min close_timer_Store[0]
#define  auto_open_hour  auto_open_timer[1]
#define  auto_open_min auto_open_timer[0]
#define  auto_close_hour  auto_close_timer[1]
#define  auto_close_min auto_close_timer[0]
#define  last_open_hour  last_open_timer[1]
#define  last_open_min   last_open_timer[0]
#define  last_close_hour last_close_timer[1]
#define  last_close_min last_close_timer[0]

