#include  <iostm8l151c6.h>				// CPU型号 
#include "initial.h"		// 初始化  预定义
#include "Pin_define.h"		// 管脚定义
#include "Timer.h"
#include "ram.h"		// RAM定义
#include "ram_cyw.h"		// RAM定义
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart
#include "lcd_cyw.h"
#include "font_cyw.h"
#include "pcf8563_cyw.h"
#include "key_and_Other_cyw.h"		// 按键
#include "key_and_Other.h"		// 按键
#include "eeprom_cyw.h"		// eeprom
#include "initial_cyw.h"		// 初始化  预定义
#include "ad.h"		        // AD

#if(ProductID==Hanging_display)//


void Refresh_second_send_time(UINT8 x_type)
{
  static UINT8  Tp_last_bit;
  Second_send_STR.times_second_send = time1ms_count;
  Second_send_STR.flag_second_send = 1;
  Second_send_STR.Type_second_send = x_type;
  Tp_last_bit = ID_data.IDL%10;
  Second_send_STR.Interval_second_send = 2300 + (UINT16)Tp_last_bit*200;
  //PIN_LCD_LIGHT = 1;//开背光
  FLAG_POWER =0;
  TB_POWER = 100;//10S
  PIN_POWER_CONTROL = 1;
}


//到了切换的时间了
void Auto_Timer_refresh(UINT8 x_mon)
{
   UINT8 Tp_mon;
   Tp_mon = decimal(x_mon);
   
   if((Tp_mon<13)&&(DISP_DIQU<8))
   auto_open_min =  Area_time[DISP_DIQU][Tp_mon-1][1];
   auto_open_hour =  Area_time[DISP_DIQU][Tp_mon-1][0];
   auto_close_min =  Area_time[DISP_DIQU][Tp_mon-1][3];
   auto_close_hour =  Area_time[DISP_DIQU][Tp_mon-1][2];
}

void openclose_output(void)
{
    //定时器拉低了
  
    if((PIN_POWER_AD == 0)&&(AD_Flag==1))
    {
        ClearWDT(); // Service the WDT
      
        
        
        
        if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))//设置的时候能不能输出信号？
        {
          
            GetTime();//获取时间
          
         
          if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode)) //如果是休眠态由RTC低电平唤醒的 而不是由按键唤醒的NORMAL态需要读取EEPROM里面的参数
          {
            
            eeprom_kaiguan_load();
            eeprom_kaiguanmode_load();
            eeprom_diqu_load();
            Auto_Timer_refresh(now_mon);
           
          }  
          //}
          if(FLAG_MODE == NORMAL_mode)//如果是按键唤醒的NORMAL状态同时RTC报警到达 重新显示下当前时间
          {
             DISP_Refresh();
          }
          
           ClearWDT(); // Service the WDT
          
         
          
          
          if((now_min==open_min)&&(now_hour==open_hour)&&(TIMER_MODE_OPEN == Timer_Mode_SET))
          {
             if(BAT_out == 0)//电压正常
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
           _ReqBuzzer(103,103,0);//蜂鸣器
           Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//电压异常
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
           _ReqBuzzer(40,60,2);//蜂鸣器
            Refresh_second_send_time(Control_code);
            }
          }
           if((now_min==close_min)&&(now_hour==close_hour)&&(TIMER_MODE_CLOSE == Timer_Mode_SET))
          {
             if(BAT_out == 0)//电压正常
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(103,103,2);//蜂鸣器
              Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//电压正常
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(40,60,2);//蜂鸣器
              Refresh_second_send_time(Control_code);
            }
          }
          
          if((now_min==auto_open_min)&&(now_hour==auto_open_hour)&&(TIMER_MODE_OPEN == Timer_Mode_AUTO))
          {
            
             if(BAT_out == 0)//电压正常
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
            _ReqBuzzer(103,103,0);//蜂鸣器
             Refresh_second_send_time(Control_code);
            }
              if(BAT_out == 1)//电压正常
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
            _ReqBuzzer(40,60,2);//蜂鸣器
             Refresh_second_send_time(Control_code);
            }
          }
                                                                       
            if((now_min==auto_close_min)&&(now_hour==auto_close_hour)&&(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
          {
             if(BAT_out == 0)//电压正常
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(103,103,2);//蜂鸣器
              Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//电压正常
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(40,60,2);//蜂鸣器
              Refresh_second_send_time(Control_code);
            }
          }
                                                                       
          if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))//就算计算时间不是报警时间都要关闭 如果系统是被RTC唤醒的
          {
            FLAG_MODE = CONTROL_mode;//设置电源关闭
            TB_POWER =60;// 20;//这句决定在0.02S后会POWER_OFF
            POWER_ON;
            FLAG_POWER = 0;//这个标志防止液晶打开了 由于无线部分导致的关机 '
            if(FG_PWRON==0)
                FG_PWRON = 1;
          }
        
      
        }
        
        
        
          dianciqianya_lcd();
            Write8563(0x01,0x02); //手动清电平
          Alarm8563();//重置报警
        
    }
    
     if( Second_send_STR.flag_second_send == 1)
     {
            //if(get_timego(Second_send_STR.times_second_send)>=  Second_send_STR.Interval_second_send)
          if(FLAG_APP_TX ==0)
            {
            Second_send_STR.flag_second_send = 2;
            Second_send_STR.times_second_send = time1ms_count;
           
            
            }
    }
    
    if( Second_send_STR.flag_second_send == 2)//第一次发送完成后，等待时间到
    {
      while(1)//这个1 2次之间禁止发送
      {
      if(get_timego(Second_send_STR.times_second_send)>=  Second_send_STR.Interval_second_send)
      {
        Second_send_STR.flag_second_send =3;
         Control_code= Second_send_STR.Type_second_send;     
         dd_set_ADF7021_Power_on();
         dd_set_TX_mode();	
         SendTxData();
         break; 
       //  FLAG_POWER = 1;
        //LED_ON;
      }
      }
    }
    
    if(Second_send_STR.flag_second_send == 3)//防止由TIMER唤醒的第二波以后 一直按键没有LED输出
    {
      if(FLAG_APP_TX ==0)
      {
        Second_send_STR.flag_second_send =4;
      }
      TB_POWER = 20; //CYW9月6日改的 和气说后面要停止2S
    }
    
    if(Second_send_STR.flag_second_send == 4)
    {
      while(1)
      {
        power_control();
        ClearWDT();
        if(TB_POWER==0)
        {
          POWER_OFF;
          while(1);
        }
      }
    }
    
    
}


void BEEP_ON_SHORT(void)
{
  //FLAG_beep_CYW = 1;
  //BEEP_COUNT=500;
  
  //TIM3_init();//TEST
   DISP_Refresh();//刷新显示
}

void BEEP_ON_LONG(void)
{
  //FLAG_beep_CYW = 1;
 // BEEP_COUNT=2000;
 
  DISP_Refresh();//刷新显示
}

void BEEP_OFF(void)
{
//  if(BEEP_COUNT)
 //  {
 //     BEEP_COUNT--;
 //  }
 //  if(BEEP_COUNT == 0)
 //  {
  //   FLAG_beep_CYW = 0;
 //  }
    //if((FG_LCD_1s == 1)&&((FLAG_MODE ==OPENONOFF_mode)||(FLAG_MODE ==CLOSEONOFF_mode)))//只有如下会闪速
   // {
      
     //  DISP_Refresh();//刷新显示
    //}
}


void OPEN_TIMER_ONOFF(void)
{
  if(FLAG_MODE == NORMAL_mode)
  {
    TIME_10S();
    FLAG_MODE = OPENONOFF_mode;
    Auto_Timer_refresh(now_mon);
    if(TIMER_MODE_OPEN == Timer_Mode_SET)
    {
    now_timer[0] = open_min;
    now_timer[1] = open_hour;//nowtime这个寄存器其实就是缓存一下
    }
    if(TIMER_MODE_OPEN == Timer_Mode_OFF)
    {
      now_timer[0] = 0xff;
      now_timer[1] = 0xff;
    }
    if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
    {
      now_timer[0] =  auto_open_min;
      now_timer[1] = auto_open_hour;
    }
    DISP_SANSUO = 0;//第一次闪烁能进入正常的值
    TIMER_MODE_DISP =TIMER_MODE_OPEN;
    
  }
}

void CLOSE_TIMER_ONOFF(void)
{
  if(FLAG_MODE == NORMAL_mode)
  {
    TIME_10S();
    FLAG_MODE = CLOSEONOFF_mode;
    Auto_Timer_refresh(now_mon);
    if(TIMER_MODE_CLOSE == Timer_Mode_SET)
    {
    now_timer[0] = close_min;
    now_timer[1] = close_hour;//nowtime这个寄存器其实就是缓存一下
    }
    if(TIMER_MODE_CLOSE == Timer_Mode_OFF)
    {
      now_timer[0] = 0xff;
       now_timer[1] = 0xff;
    }
    if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
    {
      now_timer[0] = auto_close_min;
      now_timer[1] = auto_close_hour;
    }
    
      DISP_SANSUO = 0;//第一次闪烁能进入正常的值
      TIMER_MODE_DISP =TIMER_MODE_CLOSE;
      
  }
}


void Clear_Key_Function_Count(void)
{
          KEY_CLOSETIME_COUNT = 0;
          KEY_OPENTIME_COUNT = 0;
          KEY_NOWTIME_COUNT = 0;
          KEY_ADD_COUNT = 0;
          KEY_DEC_COUNT = 0;
          KEY_DECIDE_COUNT=0;
}

void OPEN_LCD_AND_8563(void)
{
  UINT32 Tp_count=0;
  if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))
  {
    if(OPEN_Flag == 0)
    {
         // Delaycyw(178);
      
          OPEN_Flag  =1;//要避免重入
          POWER_ON;
          //TB_POWER = 600;//1min
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          //ClearWDT(); // Service the WDT
          ClearWDT(); // Service the WDT
          //要不要延时等系统稳定
          lcd_init();
          ClearWDT(); // Service the WDT
          eeprom_kaiguan_load();
          ClearWDT(); // Service the WDT
          eeprom_diqu_load();
          ClearWDT(); // Service the WDT
          eeprom_kaiguanmode_load();
          ClearWDT(); // Service the WDT
          eeprom_kaiguanlast_load();//这些顺序都换不得
          ClearWDT(); // Service the WDT
          GetTime();
          ClearWDT(); // Service the WDT
          Auto_Timer_refresh(now_mon);
          ClearWDT(); // Service the WDT
          Init8563();//等报警参数已经OK了 再装RTC及报警
          ClearWDT(); // Service the WDT
         
          
          KEY_COUNT = 0;
          FG_KEY_OPEN_CYW = 0;
          FG_KEY_STOP_CYW = 0;
          FG_KEY_CLOSE_CYW = 0;
          FG_KEY_LOGIN_CYW = 0;
          FG_KEY_DECIDE=0;// 
          FG_KEY_CLOSETIME=0;//
          FG_KEY_NOWTIME=0;//
          FG_KEY_OPENTIME=0;//
          FG_KEY_DEC=0;//
          FG_KEY_ADD=0;
          FLAG_MODE = NORMAL_mode;
          Clear_Key_Function_Count();
          
          
          while(AD_Flag==0)
          {
            ADC2_EOC_INT();
            AD_control();
            Tp_count++;
            if(Tp_count >=90000)
            {
              break;
            }
          }//20150526 有时候触发时液晶背光不亮BUG 
         
          dianciqianya_lcd();//电池欠压表示
         if((AD_Flag==1)&&(BAT_out!=2))
         {
          PIN_LCD_LIGHT = 1;//开背光
         }
         //  if((AD_Flag==1))
         // {
            
         // }
        
         
    }
  }
  else
  {
     
  }
  
}

void SET_PREINSTALL(void)
{
   if(FLAG_MODE == NORMAL_mode)
  {
     //TIME_10S();
   // FLAG_MODE = PREINSTALL_mode;//进入预设模式
    //DISP_SANSUO = 0;//闪烁用来做预设的跳变记号
   
  }
}

void SET_CLOSETIME(void)
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CLOSETIMESET_mode)) //只有普通模式能进 或者本身跳本身 
   //if((FLAG_MODE == CLOSEONOFF_mode)) //只有普通模式能进 或者本身跳本身 
  {
      if(1)//设置模式只有00：00这样能进
    // if(TIMER_MODE_DISP == Timer_Mode_SET)//设置模式只有00：00这样能进
     {
     if(TIMER_MODE_CLOSE == Timer_Mode_SET)
      //if(TIMER_MODE_CLOSE == Timer_Mode_SET) 
     {
        now_timer[0] = close_min;
        now_timer[1] = close_hour;//nowtime这个寄存器其实就是缓存一下
     }
     //if((TIMER_MODE_CLOSE == Timer_Mode_OFF)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
     if((TIMER_MODE_CLOSE == Timer_Mode_OFF)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
     {
       now_timer[0] = last_close_min;
       now_timer[1] = last_close_hour;//nowtime这个寄存器其实就是缓存一下
     }
     //TIMER_MODE_CLOSE = Timer_Mode_SET;
     //eeprom_guanmode_save();
      TIME_10S();
      FLAG_MODE = CLOSETIMESET_mode;//现在时刻设定模式
      DISP_GUANGBIAO = 1;//这个表示小时突出
   }
   }
   // if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CLOSETIMESET_mode)) //只有普通模式能进 或者本身跳本身 
   if((FLAG_MODE == CLOSEONOFF_mode)) //只有普通模式能进 或者本身跳本身 
  {
      //if(TIMER_MODE_CLOSE == Timer_Mode_SET)//设置模式只有00：00这样能进
     if(TIMER_MODE_DISP == Timer_Mode_SET)//设置模式只有00：00这样能进
     {
    
      TIME_10S();
      FLAG_MODE = CLOSETIMESET_mode;//现在时刻设定模式
      DISP_GUANGBIAO = 1;//这个表示小时突出
   }
   }
}

void SET_OPENTIME(void)
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == OPENTIMESET_mode)) //只有普通模式能进 或者本身跳本身 
   //if((FLAG_MODE == OPENONOFF_mode))
   {
      if(1)//设置模式只有00：00这样能进
    // if(TIMER_MODE_DISP  == Timer_Mode_SET )
      {
      //if(TIMER_MODE_OPEN == Timer_Mode_SET)
      if(TIMER_MODE_OPEN  == Timer_Mode_SET )
     {
        now_timer[0] = open_min;
        now_timer[1] = open_hour;//nowtime这个寄存器其实就是缓存一下
     }
     //if((TIMER_MODE_OPEN == Timer_Mode_OFF)||(TIMER_MODE_OPEN == Timer_Mode_AUTO))
     if((TIMER_MODE_OPEN == Timer_Mode_OFF)||(TIMER_MODE_OPEN == Timer_Mode_AUTO))
     {
       now_timer[0] = last_open_min;
       now_timer[1] = last_open_hour;//nowtime这个寄存器其实就是缓存一下
     }
     
      //TIMER_MODE_OPEN = Timer_Mode_SET;
      //eeprom_kaimode_save();
      TIME_10S();
      FLAG_MODE = OPENTIMESET_mode;//现在时刻设定模式
      
      DISP_GUANGBIAO = 1;//这个表示小时突出
     
   }
   }
     // if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == OPENTIMESET_mode)) //只有普通模式能进 或者本身跳本身 
   if((FLAG_MODE == OPENONOFF_mode))
   {
     // if(TIMER_MODE_OPEN == Timer_Mode_SET)//设置模式只有00：00这样能进
     if(TIMER_MODE_DISP  == Timer_Mode_SET )
      {
    
     
      //TIMER_MODE_OPEN = Timer_Mode_SET;
      //eeprom_kaimode_save();
      TIME_10S();
      FLAG_MODE = OPENTIMESET_mode;//现在时刻设定模式
      
      DISP_GUANGBIAO = 1;//这个表示小时突出
     
   }
   }
}

void SET_NOWTIME(void)//设置当前时间
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == NOWTIMESET_mode)) //只有普通模式能进 或者本身跳本身 
   {
      TIME_60S();
      FLAG_MODE = NOWTIMESET_mode;//现在时刻设定模式
      DISP_GUANGBIAO = 0;//这个表示年突出
      now_timer[0] = now_year;
      now_timer[1] = now_mon;//nowtime这个寄存器其实就是缓存一下
      now_timer[2] = now_day;
      now_timer[3] = now_hour;
      now_timer[4] = now_min;
      now_timer[5] = DISP_DIQU;
      clear_clear();
      menu_setnowtime();//这个是刷新年 月 日 这些固定的点
      DISP_GUANGBIAO = 1;//这个表示年突出
      
  }
}
 
void OPEN_TO_NORMAL(void)
{
       DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//关背光
       if(TIMER_MODE_OPEN == Timer_Mode_SET)//不是自动模式
       {
        if(((now_timer[0]!=open_min)||(now_timer[1]!=open_hour))&&(now_timer[0]!=0XFF)&&(now_timer[1]!=0XFF))//一旦发生改变 重设 不发生就不重设了
        {
         open_min = now_timer[0];
         open_hour = now_timer[1];
         eeprom_kai_save();
         
        // if((open_min!=0xff)&&(open_hour!=0xff))
        // {
         last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
       //  }
         
         //Alarm8563();  
        }
       }
        if(TIMER_MODE_OPEN == Timer_Mode_OFF)//不是自动模式
       {
        if(((now_timer[0]!=open_min)||(now_timer[1]!=open_hour))&&(now_timer[0]==0XFF)&&(now_timer[1]==0XFF))//一旦发生改变 重设 不发生就不重设了
        {
         open_min = now_timer[0];
         open_hour = now_timer[1];
         eeprom_kai_save();
         
        // if((open_min!=0xff)&&(open_hour!=0xff))
        // {
       //  last_open_timer[1]=open_hour;
        //last_open_timer[0]=open_min;
        //eeprom_kaiguanlast_save();
        // }
         
         //Alarm8563();  
        }
       }
       Alarm8563();  //不管什么模式重新加载RTC的报警是必须的
}
void CLOSE_TO_NORMAL(void)
{
   DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//关背光
       if(TIMER_MODE_CLOSE == Timer_Mode_SET)
       {
       if(((now_timer[0]!=close_min)||(now_timer[1]!=close_hour))&&(now_timer[0]!=0XFF)&&(now_timer[1]!=0XFF))//一旦发生改变 重设 不发生就不重设了
       {
         close_min = now_timer[0];
         close_hour = now_timer[1];
          eeprom_guan_save();
        // if((close_min!=0xff)&&(close_hour!=0xff))
         //{
          last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
         eeprom_kaiguanlast_save();
        // }
        
        // Alarm8563();   
       }
       }
       if(TIMER_MODE_CLOSE == Timer_Mode_OFF)
       {
       if(((now_timer[0]!=close_min)||(now_timer[1]!=close_hour))&&(now_timer[0]==0XFF)&&(now_timer[1]==0XFF))//一旦发生改变 重设 不发生就不重设了
       {
         close_min = now_timer[0];
         close_hour = now_timer[1];
          eeprom_guan_save();
        // if((close_min!=0xff)&&(close_hour!=0xff))
         //{
         // last_close_timer[1]=close_hour;
        //last_close_timer[0]=close_min;
         //eeprom_kaiguanlast_save();
        // }
        
        // Alarm8563();   
       }
       }
       Alarm8563(); //不管什么模式重新加载RTC的报警是必须的
}

void PREINTALL_TO_NORMAL(void)
{
  UINT8 install_open_hour[7] = {0x07,0x07,0xff,0x06,0x06,0xff,0xfe};
  UINT8 install_open_min[7] = {0x00,0x00,0xff,0x30,0x30,0xff,0xfe};
  
  UINT8 install_close_hour[7] = {0x17,0xff,0x17,0x17,0xff,0x17,0xfe};
  UINT8 install_close_min[7] = {0x00,0xff,0x00,0x30,0xff,0x30,0xfe};
  
  
  
  if(DISP_SANSUO == 6)//自动
  {
    FLAG_MODE=NORMAL_mode;//?
     PIN_LCD_LIGHT = 0;//关背光
  }
  else
  {
    FLAG_MODE=NORMAL_mode;
    open_min = install_open_min[DISP_SANSUO];
    open_hour = install_open_hour[DISP_SANSUO];
    if((open_min!=0xff)&&(open_hour!=0xff))
    {
    last_open_timer[1]=open_hour;
    last_open_timer[0]=open_min;
    eeprom_kaiguanlast_save();
    }
    close_min = install_close_min[DISP_SANSUO];
    close_hour = install_close_hour[DISP_SANSUO];
    if((close_min!=0xff)&&(close_hour!=0xff))
    {
    last_close_timer[1]=close_hour;
    last_close_timer[0]=close_min;
    eeprom_kaiguanlast_save();
    }
    eeprom_kai_save();
    eeprom_guan_save();
    Alarm8563();  
  }
  
}


void FUNCTION_DUE(void)
{
  
  if((FLAG_MODE==NOWTIMESET_mode)||(FLAG_MODE==OPENTIMESET_mode)||(FLAG_MODE==CLOSETIMESET_mode))
   {
     if((FLAG_MODE==NOWTIMESET_mode)&&(DISP_GUANGBIAO == 6))
     {
       DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//关背光
       if((now_timer[0]!=now_year)||(now_timer[1]!=now_mon)||(now_timer[2]!=now_day)||(now_timer[3]!=now_hour)||(now_timer[4]!=now_min))//一旦发生改变 重设 不发生就不重设了 这里又是BUG
       {
         //now_min = now_timer[0];
         //now_hour = now_timer[1];
         now_year   = now_timer[0] ;
         now_mon    = now_timer[1] ;//nowtime这个寄存器其实就是缓存一下
         now_day    = now_timer[2] ;
         now_hour   = now_timer[3] ;
         now_min    = now_timer[4] ;
         now_sec  = 0;//设置现在时间的时候秒钟清零
         clear_clear();
         Rewrite8563();
       }
       if(DISP_DIQU != now_timer[5])
       {
          DISP_DIQU  = now_timer[5] ;
          eeprom_diqu_save(); 
          
       }
        //clear_clear();
        Auto_Timer_refresh(now_mon);
        Alarm8563();//定时器LOAD必须在寄存器全部更新完之后进行
     }
     if((FLAG_MODE==OPENTIMESET_mode)&&(DISP_GUANGBIAO == 2))
     {
        TIMER_MODE_OPEN = Timer_Mode_SET;
       eeprom_kaimode_save();//把自动/OFF/SET模式记录了
       OPEN_TO_NORMAL();
       
     }
     
      if((FLAG_MODE==CLOSETIMESET_mode)&&(DISP_GUANGBIAO == 2))
     {
      
        TIMER_MODE_CLOSE= Timer_Mode_SET;
       eeprom_guanmode_save();//把自动/OFF/SET模式记录了
       CLOSE_TO_NORMAL();
       
     }
     
    // if(DISP_GUANGBIAO == 1)
    // {
       DISP_GUANGBIAO++;//变为分凸显
     //}
     
   }
  
  if(FLAG_MODE==OPENONOFF_mode)
  {
    
   //if((open_min!=0xff)&&(open_hour!=0xff))//在被覆盖之前赶紧记了吧
    
    //{
     // last_open_timer[0] = open_min;//记录上一次的开关时间
     // last_open_timer[1] = open_hour;
     // eeprom_kaiguanlast_save();
  // }
    TIMER_MODE_OPEN = TIMER_MODE_DISP;
    eeprom_kaimode_save();//把自动/OFF/SET模式记录了
    OPEN_TO_NORMAL();
  }
  if(FLAG_MODE==CLOSEONOFF_mode)
  {
  //  if((close_min!=0xff)&&(close_hour!=0xff))//在被覆盖之前赶紧记了吧
   
  // {
   //   last_close_timer[0] = close_min;
   //   last_close_timer[1] = close_hour;
   //   eeprom_kaiguanlast_save();
   // }
    TIMER_MODE_CLOSE = TIMER_MODE_DISP;
    eeprom_guanmode_save();//把自动/OFF/SET模式记录了
    CLOSE_TO_NORMAL();
  }
  
  if(FLAG_MODE==PREINSTALL_mode)
  {
    PREINTALL_TO_NORMAL();
  }
  
}

UINT8 decimal(UINT8 x_Data)
{
   UINT8 Tp_data;
   Tp_data = x_Data%16 + (x_Data/16)*10;
   return Tp_data;
}

UINT8 hex(UINT8 x_Data)
{
   UINT8 Tp_data;
   Tp_data = x_Data%10 + (x_Data/10)*16;
   return Tp_data;
}

void CURSOR_CHANGE_ADD(void)
{
   if(FLAG_MODE == PREINSTALL_mode)//只有预设模式有效 在定时器ON/OFF模式DISP_SANSUO为自动跳变
   {
     DISP_SANSUO++;
     if(DISP_SANSUO == 7) DISP_SANSUO=0;
   }
   
}

void CURSOR_CHANGE_DEC(void)
{
   if(FLAG_MODE == PREINSTALL_mode)//只有预设模式有效 在定时器ON/OFF模式DISP_SANSUO为自动跳变
   {
     if(DISP_SANSUO == 0) DISP_SANSUO=7;
     DISP_SANSUO--;
   }
   
}

void ONOFF_OPEN_ADD(void)
{
  
   if(FLAG_MODE == OPENONOFF_mode)//
   {
      TIMER_MODE_DISP++;
     if(TIMER_MODE_DISP > 2)
        TIMER_MODE_DISP = 0;
     
     if(TIMER_MODE_DISP==Timer_Mode_SET)
     {
      // if((open_hour==0xff)||(open_min ==0xff))//是关的话就显示上一次的开时间了
      //   {
              now_timer[1] = last_open_timer[1];
              now_timer[0] = last_open_timer[0];
              
       // }
       // else
       //  {
       //       now_timer[1] = open_hour;
       //      now_timer[0] = open_min;//第一闪
       // }
     }
     if(TIMER_MODE_DISP==Timer_Mode_OFF)
     {
       now_timer[1] = 0xff;
       now_timer[0] = 0xff;
      
     }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        now_timer[1] = auto_open_hour;
        now_timer[0] = auto_open_min;
      }
      DISP_SANSUO = 0;
       TB_1s_CYW = BASE_1s;
       FG_LCD_1s =1;//这三句做显示效果的 为了一按键就有立刻跳变的感觉
     
   }
  
  
}

void ONOFF_CLOSE_ADD(void)
{
  
     if(FLAG_MODE == CLOSEONOFF_mode)//
   {
     
      TIMER_MODE_DISP++;
     if(TIMER_MODE_DISP > 2)
        TIMER_MODE_DISP = 0;
     
     if(TIMER_MODE_DISP==Timer_Mode_SET)
     {
      // if((close_hour==0xff)||(close_min ==0xff))//是关的话就显示上一次的开时间了
     // {
      now_timer[1] = last_close_timer[1];
      now_timer[0] = last_close_timer[0];
     // }
     // else
     // {
      //now_timer[1] = close_hour;
     // now_timer[0] = close_min;//第一闪
     // }
     }
     if(TIMER_MODE_DISP==Timer_Mode_OFF)
     {
     
      now_timer[1] = 0xff;
      now_timer[0] = 0xff;
      
     }
     
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        now_timer[1] = auto_close_hour;
        now_timer[0] = auto_close_min;
      }
      DISP_SANSUO = 0;
       TB_1s_CYW = BASE_1s;
       FG_LCD_1s =1;//这三句做显示效果的 为了一按键就有立刻跳变的感觉
   }
    
}


UINT8 calculate_monandday(UINT8 x_year,UINT8 x_mon)
{
  //返回 当月的天数
  UINT8 Tp_day = 0;
  UINT16 Tp_year=0;
  ClearWDT(); // Service the WDT
  Tp_year = 2000+ decimal(x_year);
  switch(x_mon)
  {    
     case 0x1:    
     case 0x03:    
     case 0x05:   
     case 0x07:    
     case 0x08:    
     case 0x10:    
     case 0x12:Tp_day=31;break;    
     case 0x04:    
     case 0x06:    
     case 0x09:    
     case 0x11:Tp_day=30;break;    
     case 0x02:Tp_day=28+(Tp_year%4==0&&Tp_year%100!=0||Tp_year%400==0);    
     default :break;    
  }
  return  Tp_day;
}


UINT8 DATA_CHANGE_ADD(void)//数据调整
{
   UINT8 Tp_jinzhi;
   UINT8 Tp_max[2] = {23,59};
   UINT8 Tp_sub[2] = {1,0};
   UINT8 Tp_max_now[6] = {99,12,31,23,59,7};
   UINT8 Tp_min_now[6] = {0,  1, 1, 0, 0,0};
   
  Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
  
   if(FLAG_MODE == NOWTIMESET_mode)
  {
      
      Tp_jinzhi  = decimal(now_timer[DISP_GUANGBIAO-1]);
      Tp_jinzhi  =  Tp_jinzhi+1;
      if(Tp_jinzhi > Tp_max_now[DISP_GUANGBIAO-1] )
      {
         Tp_jinzhi = Tp_min_now[DISP_GUANGBIAO-1] ;
      }
      now_timer[DISP_GUANGBIAO-1] = hex(Tp_jinzhi);
      
      Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
      if(now_timer[2] > hex(Tp_max_now[2]))//日期不能错
      {
        now_timer[2] = hex(Tp_max_now[2]);
      }
  }
  
  if((FLAG_MODE == OPENTIMESET_mode)||(FLAG_MODE == CLOSETIMESET_mode))
  {
     if((now_timer[0]==0xff)||(now_timer[1]==0xff))
   {
      return 0;
   }
   
    if((DISP_GUANGBIAO==1)||(DISP_GUANGBIAO==2))//说明现在是小时
    {
      Tp_jinzhi = decimal(now_timer[Tp_sub[DISP_GUANGBIAO-1]]);
      Tp_jinzhi = Tp_jinzhi + 1;
      if(Tp_jinzhi > Tp_max[DISP_GUANGBIAO-1])
      {
         Tp_jinzhi = Tp_jinzhi  - Tp_max[DISP_GUANGBIAO-1] -1;
      }
      now_timer[Tp_sub[DISP_GUANGBIAO-1]] = hex(Tp_jinzhi);
    }
  }
  
  
   return 0;
}


UINT8 DATA_CHANGE_ADD30(UINT8 x_flag)
{
   UINT16 Tp_jinzhi;
  if(OPEN_Flag == 0)
  {
    return 0;
  }

   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == ADDDEC30_mode))//常规模式有效
   {
      FLAG_MODE = ADDDEC30_mode;
    //  TIME_1S();
      if(x_flag == 0)
      {
         if((TIMER_MODE_OPEN==Timer_Mode_AUTO)||(TIMER_MODE_OPEN==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=open_hour;
        now_timer[0]=open_min;
      }
      if(x_flag == 1)
      {
        if((TIMER_MODE_CLOSE==Timer_Mode_AUTO)||(TIMER_MODE_CLOSE==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=close_hour;
        now_timer[0] =close_min;
      }
       if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
      TIME_1S();
      Tp_jinzhi = decimal(now_timer[0]) + decimal(now_timer[1])*60;
      Tp_jinzhi = Tp_jinzhi + 30;
      if(Tp_jinzhi > 1439)
      {
        Tp_jinzhi = Tp_jinzhi  - 1439 - 1;
      }
      now_timer[0] = hex(Tp_jinzhi%60);
      now_timer[1] = hex(Tp_jinzhi/60);
      if((x_flag == 0)&&(TIMER_MODE_OPEN==Timer_Mode_SET))
      {
        open_hour = now_timer[1];
        open_min = now_timer[0];
         eeprom_kai_save();
         
        if((open_min!=0xff)&&(open_hour!=0xff))
        {
        last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
        }
       
         Alarm8563();  
      }
      if((x_flag == 1)&&(TIMER_MODE_CLOSE==Timer_Mode_SET))
      {
        close_hour = now_timer[1];
        close_min = now_timer[0];
        if((close_min!=0xff)&&(close_hour!=0xff))
        {
        last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_guan_save();
         Alarm8563();  
      }
   }
    return 1;
}

UINT8 DATA_CHANGE_DEC30(UINT8 x_flag)
{
   UINT16 Tp_jinzhi;
   if(OPEN_Flag == 0)
  {
    return 0;
  }
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == ADDDEC30_mode))//常规模式有效
   {
       FLAG_MODE = ADDDEC30_mode;
     // TIME_1S();
      if(x_flag == 0)
      {
        if((TIMER_MODE_OPEN==Timer_Mode_AUTO)||(TIMER_MODE_OPEN==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=open_hour ;
        now_timer[0]=open_min;
      }
      if(x_flag == 1)
      {
         if((TIMER_MODE_CLOSE==Timer_Mode_AUTO)||(TIMER_MODE_CLOSE==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=close_hour;
        now_timer[0] =close_min;
      }
       if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
      TIME_1S();
      Tp_jinzhi = decimal(now_timer[0]) + decimal(now_timer[1])*60;
      
      if(Tp_jinzhi < 30)
      {
        Tp_jinzhi = 1440 + Tp_jinzhi;
      }
      
      Tp_jinzhi = Tp_jinzhi - 30;
      
      now_timer[0] = hex(Tp_jinzhi%60);
      now_timer[1] = hex(Tp_jinzhi/60);
      if((x_flag == 0)&&(TIMER_MODE_OPEN==Timer_Mode_SET))
      {
        open_hour = now_timer[1];
        open_min = now_timer[0];
        if((open_min!=0xff)&&(open_hour!=0xff))
        {
        last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_kai_save();
         Alarm8563();  
      }
      if((x_flag == 1)&&(TIMER_MODE_CLOSE==Timer_Mode_SET))
      {
        close_hour = now_timer[1];
        close_min = now_timer[0];
        if((close_min!=0xff)&&(close_hour!=0xff))
        {
         last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_guan_save();
         Alarm8563();  
      }
   }
    return 1;
}

UINT8 DATA_CHANGE_DEC(void)//数据调整
{
   UINT8 Tp_jinzhi;
   UINT8 Tp_max[2] = {24,60};
   UINT8 Tp_sub[2] = {1,0};
   UINT8 Tp_max_now[6] = {99,12,31,23,59,7};
   UINT8 Tp_min_now[6] = {0,  1, 1, 0, 0,0};
   Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
   
    if(FLAG_MODE == NOWTIMESET_mode)
  {
      
      Tp_jinzhi  = decimal(now_timer[DISP_GUANGBIAO-1]);
      
      if(Tp_jinzhi <= Tp_min_now[DISP_GUANGBIAO-1] )
      {
         Tp_jinzhi = Tp_max_now[DISP_GUANGBIAO-1] +1 ;
      }
      Tp_jinzhi  =  Tp_jinzhi-1;
      now_timer[DISP_GUANGBIAO-1] = hex(Tp_jinzhi);
      
      
       Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
       if(now_timer[2] > hex(Tp_max_now[2]))//日期不能错
      {
        now_timer[2] = hex(Tp_max_now[2]);
      }
  }
  
  
  if((FLAG_MODE == OPENTIMESET_mode)||(FLAG_MODE == CLOSETIMESET_mode))
  {
   if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
   
  if((DISP_GUANGBIAO==1)||(DISP_GUANGBIAO==2))//说明现在是小时
   {
      Tp_jinzhi = decimal(now_timer[Tp_sub[DISP_GUANGBIAO-1]]);
      if(Tp_jinzhi == 0 )
      {
         Tp_jinzhi = Tp_max[DISP_GUANGBIAO-1];
      }
      Tp_jinzhi = Tp_jinzhi - 1 ;
      now_timer[Tp_sub[DISP_GUANGBIAO-1]] = hex(Tp_jinzhi);
   }
  }
  
   return 0;
}

void SCAN_OPEN(void)
{
  if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN_CYW==0)){
    FG_KEY_OPEN_CYW=1;
    //立马关电源
     if(FLAG_MODE == INIT_mode)
     {
    FLAG_MODE = CONTROL_mode;
    
    TB_POWER = 1000;
   // dianciqianya_lcd();//电池欠压表示
     }
  }
   if((PIN_KEY_OPEN==1)&&(FG_KEY_OPEN_CYW==1)) KEY_COUNT++;
}


void SCAN_CLOSE(void)
{
    if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE_CYW==0)){
    FG_KEY_CLOSE_CYW=1;
    if(FLAG_MODE == INIT_mode)
    {
      FLAG_MODE = CONTROL_mode;//在液晶屏开时 无线操作不进入CONTROL模式
      TB_POWER = 1000;
     
     // dianciqianya_lcd();//电池欠压表示
    }
    //立马关电源
  }
  if((PIN_KEY_CLOSE==1)&&(FG_KEY_CLOSE_CYW==1)) KEY_COUNT++;  
  
}

void SCAN_STOP(void)
{
  if((PIN_KEY_STOP==0)&&(FG_KEY_STOP_CYW==0)){
    FG_KEY_STOP_CYW=1;
    //立马关电源
    if(FLAG_MODE == INIT_mode)
    {
    FLAG_MODE = CONTROL_mode;
    TB_POWER = 1000;
    
   // dianciqianya_lcd();//电池欠压表示
    }
  }
  if((PIN_KEY_STOP==1)&&(FG_KEY_STOP_CYW==1)) KEY_COUNT++;
}

void SCAN_LOGIN(void)
{
   if((PIN_KEY_LOGIN==0)&&(FG_KEY_LOGIN_CYW==0)){
    FG_KEY_LOGIN_CYW=1;
    //立马关电源
    if(FLAG_MODE == INIT_mode)
    {
    FLAG_MODE = CONTROL_mode;
    TB_POWER = 1000;
  
   // dianciqianya_lcd();//电池欠压表示
    }
  }
  if((PIN_KEY_LOGIN==1)&&(FG_KEY_LOGIN_CYW==1)) KEY_COUNT++;
}

UINT8 FLAG_NOWTIME_LONG=0;
void  SCAN_NOWTIME(void)
{
       //现在时间键
   if(PIN_KEY_NOWTIME==0)
   {
     Delayus(key_Antishake);
      if(PIN_KEY_NOWTIME==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_NOWTIME=1;
    KEY_NOWTIME_COUNT++;
     if((FLAG_NOWTIME_LONG==0)&&(KEY_NOWTIME_COUNT > key_fun))
     {
       if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_long;
       //BACKLIGHT_ON();
       SET_NOWTIME();//设置当前时间
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //长 进入关时间设置 这个必须在参数改变之后
       FLAG_NOWTIME_LONG = 1;
       }
     }
     key_touch_retime();
   }
  }
  if((PIN_KEY_NOWTIME==1)&&(FG_KEY_NOWTIME==1))KEY_COUNT++;
  
   if((PIN_KEY_NOWTIME==1)&&(FG_KEY_NOWTIME==1)&&(KEY_NOWTIME_COUNT!=0)) 
  {   
     
     if(KEY_NOWTIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//短 
      // BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//短 
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //长 进入现在时刻的设置模式
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); 
     }
     KEY_NOWTIME_COUNT = 0;
    // Clear_Key_Function_Count();
     FLAG_NOWTIME_LONG = 0;
  }
}




UINT8 FLAG_DECIDE_LONG=0;

void SCAN_DECIDE(void)
{
   if(PIN_KEY_DECIDE==0)
   {
      Delayus(key_Antishake);
      if(PIN_KEY_DECIDE==0)
   {
     //TIME_10S();
     key_touch_retime();
     FG_KEY_DECIDE=1;
    KEY_DECIDE_COUNT++;
    if((FLAG_DECIDE_LONG==0)&&(KEY_DECIDE_COUNT > key_fun))
     {
       //BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //开液晶 初始化时钟
       FLAG_DECIDE_LONG = 1;
     }
  }
  }
  if((PIN_KEY_DECIDE==1)&&(FG_KEY_DECIDE==1))KEY_COUNT++;
  
   if((PIN_KEY_DECIDE==1)&&(FG_KEY_DECIDE==1)&&(KEY_DECIDE_COUNT!=0)) 
  {   
     
     if(KEY_DECIDE_COUNT < key_fun)
     {
       if(FLAG_PRESS==0)
       {
       FLAG_PRESS = key_press_short;
         FUNCTION_DUE();
       
      // BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//短
       }
     }
     else
     {
       //BACKLIGHT_ON();
       //  BEEP_ON_LONG(); //长 开关LCD
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//短 
     }
     KEY_DECIDE_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_DECIDE_LONG = 0;
  }
}


UINT8 FLAG_ADD_ZUHE=0;


void SCAN_ADD(void)
{
   if(PIN_KEY_ADD==0)
   {
    Delayus(key_Antishake);
    if(PIN_KEY_ADD==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_ADD=1;
    KEY_ADD_COUNT++;
    if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_ADD_ZUHE = 1;
    }
    if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_ADD_ZUHE = 2;
    }
    if(KEY_ADD_COUNT>key_fast)
    {
     if(FLAG_PRESS==0)
     {
      FLAG_PRESS=60;
       COUNT_FAST++;
        if(COUNT_FAST >= count_speed) 
        {
          DATA_CHANGE_ADD();
          COUNT_FAST = 0;
          //BACKLIGHT_ON();
          OPEN_LCD_AND_8563();
        }
      BEEP_ON_LONG(); //长 快加
     }
    }
  }
   }
  if((PIN_KEY_ADD==1)&&(FG_KEY_ADD==1))KEY_COUNT++;
  
   if((PIN_KEY_ADD==1)&&(FG_KEY_ADD==1)&&(KEY_ADD_COUNT!=0)) 
  {   
     
     if(KEY_ADD_COUNT < key_fun)
     {
      if(FLAG_PRESS==0)
      {
        FLAG_PRESS = key_press_short;
       if(FLAG_ADD_ZUHE==0)//短加
       {
         DATA_CHANGE_ADD();
         CURSOR_CHANGE_ADD();
         //ONOFF_CHANGE_ADDDEC(0);
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_ADD_ZUHE==1)//开时间加30
       {
         DATA_CHANGE_ADD30(0);//常规模式下加30
         
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_ADD_ZUHE==2)//关时间加30
       {
         DATA_CHANGE_ADD30(1);//常规模式下加30
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
      }
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //长 快加
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //长 快加
     }
     KEY_ADD_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_ADD_ZUHE = 0;
  }
}


UINT8 FLAG_DEC_ZUHE=0;

void SCAN_DEC(void)
{
   if(PIN_KEY_DEC==0)
   {
     Delayus(key_Antishake);
     if(PIN_KEY_DEC==0)
   {
     //TIME_10S();
     key_touch_retime();
    FG_KEY_DEC=1;
    KEY_DEC_COUNT++;
    if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_DEC_ZUHE = 1;
    }
    if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_DEC_ZUHE = 2;
    }
    if(KEY_DEC_COUNT>key_fast)
    {
       if(FLAG_PRESS==0)
       {
       FLAG_PRESS = 60;
         COUNT_FAST++;
        if(COUNT_FAST >= count_speed) 
        {
          DATA_CHANGE_DEC();
          COUNT_FAST = 0;
          //BACKLIGHT_ON();
          OPEN_LCD_AND_8563();
        }
      BEEP_ON_LONG(); //长 快减
       }
    }
  }
   }
  if((PIN_KEY_DEC==1)&&(FG_KEY_DEC==1))KEY_COUNT++;
  
   if((PIN_KEY_DEC==1)&&(FG_KEY_DEC==1)&&(KEY_DEC_COUNT!=0)) //短键松开时处理 长建到时间就处理
  {   
     
     if(KEY_DEC_COUNT < key_fun)
     {
      if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_short;
       if(FLAG_DEC_ZUHE==0)//短减
       {
         DATA_CHANGE_DEC();
         CURSOR_CHANGE_DEC();
         //ONOFF_CHANGE_ADDDEC(1);
         
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_DEC_ZUHE==1)//开时间减30
       {
         DATA_CHANGE_DEC30(0);
        
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//短 
       }
       if(FLAG_DEC_ZUHE==2)//关时间减30
       {
         DATA_CHANGE_DEC30(1);
        
       //  BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//短 
       }
       }
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //长 快加
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //长 快加
     }
     KEY_DEC_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_DEC_ZUHE = 0;
  }
}



UINT8 FLAG_OPENTIME_ZUHE=0;
UINT8 FLAG_OPENTIME_LONG=0;

void SCAN_OPENTIME(void)
{
   if(PIN_KEY_OPENTIME==0)
   {
    Delayus(key_Antishake);
    if(PIN_KEY_OPENTIME==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_OPENTIME=1;
    KEY_OPENTIME_COUNT++;
     if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_OPENTIME_ZUHE = 1;
    }
     if(PIN_KEY_ADD == 0)
    {
      FLAG_OPENTIME_ZUHE = 2;
    }
     if(PIN_KEY_DEC == 0)
    {
      FLAG_OPENTIME_ZUHE = 3;
    }
      if((FLAG_OPENTIME_LONG==0)&&(KEY_OPENTIME_COUNT > key_fun))
     {
        if(FLAG_PRESS==0)
        {
          FLAG_PRESS = key_press_long;
       //BEEP_ON_LONG(); //长 进入kai时间设置
       FLAG_OPENTIME_LONG = 1;
      if(FLAG_OPENTIME_ZUHE==0)
      {
        SET_OPENTIME();//设置开时间
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); //进入开时间设置
       // BACKLIGHT_ON();
      }
      if(FLAG_OPENTIME_ZUHE==1)
      {
        //SET_PREINSTALL(); //进入开关时刻预置设定 第二版规格书没有提到这个
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); 
      //  BACKLIGHT_ON();
      }
        }
     }
     key_touch_retime();
    }
  }
  if((PIN_KEY_OPENTIME==1)&&(FG_KEY_OPENTIME==1))KEY_COUNT++;
  
   if((PIN_KEY_OPENTIME==1)&&(FG_KEY_OPENTIME==1)&&(KEY_OPENTIME_COUNT!=0)) 
  {   
     
     if(KEY_OPENTIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//短 
       if(FLAG_PRESS==0)
       {
        FLAG_PRESS= key_press_short;
        if(FLAG_OPENTIME_ZUHE==0)//进入开定时器的关和开
       {
        ONOFF_OPEN_ADD();//on off AUTO切换
         OPEN_TIMER_ONOFF();//进入开关开始时间定时器模式
        
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//短 
       }
       if(FLAG_OPENTIME_ZUHE==1)//进入预设值选择
       {
        // BACKLIGHT_ON();
        // BEEP_ON_SHORT();//短 
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_OPENTIME_ZUHE==2)//开始时间+30 由于在ADD键已经处理 不重复处理
       {
       // BACKLIGHT_ON();
         //BEEP_ON_SHORT();//短 
         DATA_CHANGE_ADD30(0);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_OPENTIME_ZUHE==3)//开始时间-30 由于在ADD键已经处理 不重复处理
       {
        // BACKLIGHT_ON();
         //BEEP_ON_SHORT();//短 
         DATA_CHANGE_DEC30(0);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       }
     }
     else
     {
    //  BACKLIGHT_ON();
       //BEEP_ON_LONG(); //长 开关LCD
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); //长 开关LCD
     }
     KEY_OPENTIME_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_OPENTIME_ZUHE = 0;
     FLAG_OPENTIME_LONG = 0;
  }
}




UINT8 FLAG_CLOSETIME_LONG=0;
UINT8 FLAG_CLOSETIME_ZUHE=0;

void SCAN_CLOSETIME(void)
{
   if(PIN_KEY_CLOSETIME==0)
   {
      Delayus(key_Antishake);
      if(PIN_KEY_CLOSETIME==0)
   {
     //TIME_10S();
     key_touch_retime();
    FG_KEY_CLOSETIME=1;
    KEY_CLOSETIME_COUNT++;
     if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_CLOSETIME_ZUHE = 1;
    }
     if(PIN_KEY_ADD == 0)
    {
      FLAG_CLOSETIME_ZUHE = 2;
    }
     if(PIN_KEY_DEC == 0)
    {
      FLAG_CLOSETIME_ZUHE = 3;
    }
     if((FLAG_CLOSETIME_LONG==0)&&(KEY_CLOSETIME_COUNT > key_fun))
     {
       if(FLAG_PRESS == 0)
       {
        FLAG_PRESS = key_press_long; 
       FLAG_CLOSETIME_LONG = 1;
       if(FLAG_CLOSETIME_ZUHE == 0)
       {
          SET_CLOSETIME();
          OPEN_LCD_AND_8563();
           BEEP_ON_LONG(); //长 进入关时间设置
          // BACKLIGHT_ON();
       }
       if(FLAG_CLOSETIME_ZUHE == 1)//进入时刻预设 由于已经处理了 空白了 不做重复处理
       {
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_LONG(); //长 进入关时间设置
       }
       }
     }
     key_touch_retime();
    }
  }
  if((PIN_KEY_CLOSETIME==1)&&(FG_KEY_CLOSETIME==1))KEY_COUNT++;
  
   if((PIN_KEY_CLOSETIME==1)&&(FG_KEY_CLOSETIME==1)&&(KEY_CLOSETIME_COUNT!=0)) //松开后1次
  {   
     
     if(KEY_CLOSETIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//短
       if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_short;
           
        if(FLAG_CLOSETIME_ZUHE==0)//进入关定时器的关和开
       {
         ONOFF_CLOSE_ADD();//on off AUTO切换
         CLOSE_TIMER_ONOFF();
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_CLOSETIME_ZUHE==1)//进入预设值选择 由于在OPENTIME键已经处理 不做重复处理
       {
         
         //BEEP_ON_SHORT();//短 
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_CLOSETIME_ZUHE==2)//开始时间+30 由于在ADD键已经处理 不重复处理
       {
        
         //BEEP_ON_SHORT();//短 
         //BACKLIGHT_ON();
         DATA_CHANGE_ADD30(1);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       if(FLAG_CLOSETIME_ZUHE==3)//开始时间-30 由于在ADD键已经处理 不重复处理
       {
         
        // BEEP_ON_SHORT();//短 
         //BACKLIGHT_ON();
         DATA_CHANGE_DEC30(1);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//短 
       }
       }
     }
     else
     {
     //BACKLIGHT_ON();
       // BEEP_ON_LONG(); 
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); 
     }
     KEY_CLOSETIME_COUNT = 0;
    // Clear_Key_Function_Count();
    FLAG_CLOSETIME_LONG = 0;
    FLAG_CLOSETIME_ZUHE = 0;
  }
}


void power_control(void)
{
  if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CONTROL_mode))//只有NORMAL_mode CONTROL_mode会关屏 bunengping
  //CONTROL MODE 由向工那边控制关屏 2015 03 06修改 
  {
     if(FG_100ms_CYW)
    {
     FG_100ms_CYW = 0;
    if(TB_POWER)
     TB_POWER -- ;
     
     } 
  }
  if((TB_POWER == 0)/*&&(m_KeyOptSetMode==0)&&(FG_PWRON==1)&&(!_GetRegMode())*//*||(BAT_out==2)*/)//如果电压低到2.2V以下 无线不能动作 液晶也不显示 背光不亮 开机只提示更换电池
   {
      // POWER_OFF;
      FLAG_POWER = 1;
   }

 
}


/*扫描键盘*/
UINT8 key_scan(void)
{
   // if((PIN_KEY_OPEN==0)||(PIN_KEY_STOP==0)||(PIN_KEY_CLOSE==0))
   //  return 0; 
  
       ClearWDT();
       SCAN_OPEN();
       ClearWDT();
       SCAN_CLOSE();
       ClearWDT();
       SCAN_STOP();
       ClearWDT();
       SCAN_LOGIN();
       ClearWDT();
       
       SCAN_CLOSETIME();
       ClearWDT();
       SCAN_NOWTIME();
       ClearWDT();
       //SCAN_LOGIN();
       ClearWDT();
       SCAN_OPENTIME();
       ClearWDT();
       SCAN_DEC();
       ClearWDT();
       SCAN_ADD();
       ClearWDT();
       SCAN_DECIDE();
        ClearWDT();
        
       
       if(KEY_COUNT >= key_shortdelay)
      {
        // Tone_OFF();
          KEY_COUNT = 0;
          FG_KEY_OPEN_CYW = 0;
          FG_KEY_STOP_CYW = 0;
          FG_KEY_CLOSE_CYW = 0;
          FG_KEY_LOGIN_CYW = 0;
          FG_KEY_DECIDE=0;// 
          FG_KEY_CLOSETIME=0;//
          FG_KEY_NOWTIME=0;//
          FG_KEY_OPENTIME=0;//
          FG_KEY_DEC=0;//
          FG_KEY_ADD=0;
           Clear_Key_Function_Count();
          //if(FLAG_MODE!=CONTROL_mode)
          //TB_POWER = 600;//1min 有键按到
      }
      ClearWDT();
      BEEP_OFF();
      
      //if(FLAG_MODE != CONTROL_mode)//如果不加这句会影响CONTROL模式的无线关断
     // {
      if((TB_5s==0)&&(TB_5S_CYW == 0))//51;  //5.1秒  add 2015 04 21  cyw  为了避免5S后不能恢复使能无线在液晶触发的CPU上电中
      {
         TB_5S_CYW=69;//20170725//TB_51s;//51;  //5.1秒
      }
     // }
    
  return 0; 
}
#endif