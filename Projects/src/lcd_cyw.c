#include  <iostm8l151c6.h>				// CPU型号 
#include "initial.h"		// 初始化  预定义
#include "Pin_define.h"		// 管脚定义
#include "ram.h"		// RAM定义
#include "ram_cyw.h"		// RAM定义
#include "Timer.h"		// 定时器
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断
#include "key_and_Other.h"	// 按键
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart
#include "lcd_cyw.h"
#include "font_cyw.h"
#include "pcf8563_cyw.h"
#include "eeprom_cyw.h"
#include "ad.h"

#if(ProductID==Hanging_display)//
//页地址设置
#define     PAGE_ADDR_SET   0xb0

//列地址设置
#define     SEG_ADDR_H  0x10
#define     SEG_ADDR_L  0x00


void send_command(int data)
{
   char i;
   PIN_LCD_SEL  = 0;//选中
   PIN_LCD_RS = 0;
   for(i=0;i<8;i++)
   {
     ADF7021_SCLK = 0;
     if(data&0x80)
       ADF7021_SDATA = 1;
     else
       ADF7021_SDATA = 0;
     ADF7021_SCLK = 1;
     data= data <<1;
   }
}

void send_data(int data)
{
   char i;
   PIN_LCD_SEL  = 0;//选中
   PIN_LCD_RS = 1;
   for(i=0;i<8;i++)
   {
     ADF7021_SCLK = 0;
     if(data&0x80)
       ADF7021_SDATA = 1;
     else
       ADF7021_SDATA = 0;
     ADF7021_SCLK = 1;
     data= data <<1;
   }
}


void delay(int i)
{
   int j,k;
   for(j=0;j<i;j++)
     for(k=0;k<110;k++);
}

void lcd_address(uchar page,uchar column)
{
  
   PIN_LCD_SEL  = 0;//选中
   column  = column -1;
   page    = page   -1;
   send_command(0xb0+page);
   send_command(((column>>4)&0x0f)+0x10);
   send_command(column&0x0f);
}





void display_graphic_8x16(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    PIN_LCD_SEL  = 0;//选中
    for(j=0; j<2; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//不选中
}




/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
    //uchar page_address;
    //uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
   // page_address = 0xb0+page-1;
   // column_address_L =(column&0x0f);
   // column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//选中
    
    for(j=0; j<4; j++)
    {
       // send_command(page_address+j);   /*设置页地址*/
       // send_command(column_address_H); /*设置列地址的高4位*/
       // send_command(column_address_L); /*设置列地址的低4位*/
       lcd_address(page+j/2,column+(j%2)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//不选中
}

void display_graphic_16x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
   // uchar page_address;
  //  uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
    //page_address = 0xb0+page-1;
    //column_address_L =(column&0x0f);
    //column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//选中
    
    for(j=0; j<8; j++)
    {
       // send_command(page_address+j);   /*设置页地址*/
       // send_command(column_address_H); /*设置列地址的高4位*/
       // send_command(column_address_L); /*设置列地址的低4位*/
      lcd_address(page+j/4,column+(j%4)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//不选中
}

void display_graphic_24x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
   // uchar page_address;
  //  uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
    //page_address = 0xb0+page-1;
    //column_address_L =(column&0x0f);
    //column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//选中
    
    for(j=0; j<12; j++)
    {
       // send_command(page_address+j);   /*设置页地址*/
       // send_command(column_address_H); /*设置列地址的高4位*/
       // send_command(column_address_L); /*设置列地址的低4位*/
      lcd_address(page+j/4,column+(j%4)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//不选中
}


//这个函数是从字库芯片里面读取数据 翻转处理数据后显示
void  display_graphic_16x16_FONTIC(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
//    uchar i,j;
//    uchar page_address;
//    uchar column_address_L,column_address_H;
//    
//    ClearWDT(); // Service the WDT
//    
//    page_address = 0xb0+page-1;
//    column_address_L =(column&0x0f);
//    column_address_H =((column>>4)&0x0f)+0x10;
//    //cs1=0;
//    PIN_LCD_SEL  = 0;//选中
//    
//    for(j=0; j<2; j++)
//    {
//        send_command(page_address+j);   /*设置页地址*/
//        send_command(column_address_H); /*设置列地址的高4位*/
//        send_command(column_address_L); /*设置列地址的低4位*/
//        for (i=0; i<16; i++)
//        {
//            if(x_flag == 0)
//            {
//            send_data(*dp);     /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
//            }
//            else
//            {
//              send_data(~(*dp)); 
//            }
//            dp++;
//        }
//    }
//    //cs1=1;
//     PIN_LCD_SEL  = 1;//不选中
    UINT8 DP_NI[32];
    UINT8 i,j;
   // UINT8 page_address;
    //UINT8 column_address_L,column_address_H;
    ClearWDT(); // Service the WDT
    
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[i]&(1<<j))
           {
             DP_NI[j] = DP_NI[j]|(1<<(i));
           }
           else
           {
             DP_NI[j] = DP_NI[j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[8+i]&(1<<j))
           {
             DP_NI[16+j] = DP_NI[16+j]|(1<<(i));
           }
           else
           {
             DP_NI[16+j] = DP_NI[16+j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[16+i]&(1<<j))
           {
             DP_NI[8+j] = DP_NI[8+j]|(1<<(i));
           }
           else
           {
             DP_NI[8+j] = DP_NI[8+j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[24+i]&(1<<j))
           {
             DP_NI[24+j] = DP_NI[24+j]|(1<<(i));
           }
           else
           {
             DP_NI[24+j] = DP_NI[24+j]&(~(1<<(i)));
           }
       }
    }
    
  //  page_address = 0xb0+page-1;
  //  column_address_L =(column&0x0f);
   // column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    
    PIN_LCD_SEL  = 0;//选中
    for(j=0; j<4; j++)
    {
        //send_command(page_address+j);   /*设置页地址*/
        //send_command(column_address_H); /*设置列地址的高4位*/
        //send_command(column_address_L); /*设置列地址的低4位*/
       lcd_address(page+j/2,column+(j%2)*8);
        for (i=0; i<8; i++)
        {
             if(x_flag == 0)
             {     
          send_data(DP_NI[j*16+i]);     /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
             }
             else
             {
          send_data(~DP_NI[j*16+i]);         
             }
           // DP_NI++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//不选中
    
}

void display_graphic_8x24(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    
    PIN_LCD_SEL  = 0;//选中
    for(j=0; j<3; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//不选中
}
void display_graphic_8x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    
    PIN_LCD_SEL  = 0;//选中
    for(j=0; j<4; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//不选中
}
void display_graphic_8x48(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    PIN_LCD_SEL  = 0;//选中
    for(j=0; j<6; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//不选中
}



void display_onetimedata_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//时间的低位和高位
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//越界的不显示
    {
    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[Tp_timemsb*32],x_flag);
    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[Tp_timelsb*32],x_flag);//年的数字
    }
    else//万一错了呢 报错
    {
    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[code_daE_8_32*32],x_flag);
    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[code_xiaor_8_32*32],x_flag);//年的数字   
    }
    
}

//
//void display_onetimedata_gothic_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
//{
//   uchar Tp_timelsb,Tp_timemsb;//时间的低位和高位
//   Tp_timelsb = data%16;
//    Tp_timemsb = data/16;
//
//    if(data<=0x99)//越界的不显示
//    {
//    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[(Tp_timemsb+code_num_MSGothic_8_32)*32],x_flag);
//    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[(Tp_timelsb+code_num_MSGothic_8_32)*32],x_flag);//年的数字
//    }
//    else//万一错了呢 报错
//    {
//    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[code_daE_8_32*32],x_flag);
//    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[code_xiaor_8_32*32],x_flag);//年的数字   
//    }
//    
//}


void display_onetimedata_gothic_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
 
  display_onetimedata_8_32(hang,lie,data,x_flag);
    
}

void display_onetimedata_8_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//时间的低位和高位
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//越界的不显示
    {
    display_graphic_8x16(hang,lie,&FONT_BUF_8_16[Tp_timemsb*16],x_flag);
    display_graphic_8x16(hang,1+lie,&FONT_BUF_8_16[Tp_timelsb*16],x_flag);//年的数字
    }
    else//万一错了呢 报错
    {
       
    }
    
}

void display_onetimedata_8_24(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//时间的低位和高位
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//越界的不显示
    {
    display_graphic_8x24(hang,lie,&FONT_BUF_8_24[Tp_timemsb*24],x_flag);
    display_graphic_8x24(hang,1+lie,&FONT_BUF_8_24[Tp_timelsb*24],x_flag);//年的数字
    }
    else//万一错了呢 报错
    {
       
    }
    
}


void display_oneword_8_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x16(hang,lie,&FONT_BUF_8_16[16*data],x_flag);//中文年
}

void display_oneword_8_24(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x24(hang,lie,&FONT_BUF_8_24[24*data],x_flag);//中文年
}

void display_oneword_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x32(hang,lie,&FONT_BUF_8_32[32*data],x_flag);//中文年
}

void display_oneword_16_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_16x16(/*4+16**/hang,lie,&FONT_BUF_16_16[num_addr+32*data],x_flag);//中文年
}

void display_oneword_16_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_16x32(hang,lie,&FONT_BUF_16_32[num_addr+64*data],x_flag);//中文年
}

void display_oneword_24_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_24x32(hang,lie,&FONT_BUF_24_32[num_addr+96*data],x_flag);//中文年
}

uchar caluate_monthtoreason(uchar x_mon)
{
   uchar Tp_mon;
    Tp_mon = x_mon%16 + (x_mon/16)*10;
    if((Tp_mon >= 3) &&(Tp_mon <= 5))
    {
      return 0;//春
    }
    if((Tp_mon >= 6) &&(Tp_mon <= 8))
    {
      return 1;//夏
    }
    if((Tp_mon >= 9) &&(Tp_mon <= 11))
    {
      return 2;//秋
    }
    return 3;//冬
}

//入口data 为当前月份
void display_reason(uchar hang,uchar lie,uchar data,uchar x_flag)
{
    uchar Tp_reason = 0;
    Tp_reason = caluate_monthtoreason(data);
    switch(Tp_reason)
    {
    case 0:display_oneword_16_16(hang,lie,code_chun_season,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,code_xia_season,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,code_qiu_season,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_dong_season,x_flag);
      break;
    default:break;
    }
}

void display_dianci(uchar hang,uchar lie,uchar data,uchar x_flag)
{
  switch(data)
    {
    case 0:display_oneword_16_16(hang,lie,biguashidianliang0,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,biguashidianliang1,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,biguashidianliang2,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,biguashidianliang3,x_flag);
      break;
    default:break;
    }
}

void display_week(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   switch(data)
    {
    case 0:display_oneword_16_16(hang,lie,code_ri,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,code_yue,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,code_huo_week,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_shui_week,x_flag);
      break;
    case 4:display_oneword_16_16(hang,lie,code_mu_week,x_flag);
      break;
     case 5:display_oneword_16_16(hang,lie,code_jin_week,x_flag);
      break;
      case 6:display_oneword_16_16(hang,lie,code_tu_week,x_flag);
      break;
    default:break;
    }
   display_oneword_16_16(hang,lie+2,code_yao_week,x_flag);
   display_oneword_16_16(hang,lie+4,code_ri,x_flag);
}


void display_area(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   switch(data)
    {
    case 0://display_oneword_16x16(hang,lie,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie,code_bei,x_flag);
           display_oneword_16_16(hang,lie+2,code_bei+1,x_flag);
           display_oneword_16_16(hang,lie+4,code_bei+2,x_flag);
      break;
    case 1:
           display_oneword_16_16(hang,lie,code_chong,x_flag);//东北关东
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_shen,x_flag);
           //display_oneword_16x16(hang,lie+6,code_dong,x_flag);
           
      break;
    case 2:display_oneword_16_16(hang,lie,code_jiu,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_zou,x_flag);
           //display_oneword_16x16(hang,lie+6,code_fang,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_zhong,x_flag);
           display_oneword_16_16(hang,lie+2,code_si,x_flag);
           display_oneword_16_16(hang,lie+4,code_guo,x_flag);
           //display_oneword_16x16(hang,lie+6,code_fang,x_flag);
      break;
    case 4://display_oneword_16_16(hang,lie,code_guan,x_flag);
          display_oneword_16_16(hang,lie,code_jin,x_flag);//20150403 关西改为近畿
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           //display_oneword_16_16(hang,lie+4,code_xi,x_flag);
         display_oneword_16_16(hang,lie+4,code_ji,x_flag);
      break;
     case 5:display_oneword_16_16(hang,lie,code_zhong,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_bu,x_flag);
           //display_oneword_16x16(hang,lie+6,code_shen,x_flag);
      break;
      case 6:
           display_oneword_16_16(hang,lie,code_guan,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_dong,x_flag);
     break;
      case 7:
           display_oneword_16_16(hang,lie,code_dong,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_bei,x_flag);
      break;
    default:break;
    }
}

//清屏幕
void clear_clear(void)
{
   unsigned char i,j;
   //ClearWDT(); // Service the WDT
   PIN_LCD_SEL  = 0;//选中
   for(i=0;i<9;i++)
   {
      ClearWDT(); // Service the WDT
      lcd_address(1+i,1);
      for(j=0;j<132;j++)
      {
         send_data(0x00);
      }  
   }
   PIN_LCD_SEL  = 1;//不选中
   
}

//清除一个64*32
void Clear_64_32(UINT8 x_hang,UINT8 x_flag)
{
      display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,x_flag);//小时反显
      display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,x_flag);//小时反显
      display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,x_flag);//小时反显
      display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,x_flag);//小时反显
      display_oneword_8_32(x_hang,lie_5,code_kongbai_8_32,x_flag);
      display_oneword_8_32(x_hang,lie_6,code_kongbai_8_32,x_flag);
      display_oneword_8_32(x_hang,lie_7,code_kongbai_8_32,x_flag);
       display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,x_flag);
}

void menu_linshi(void)/*显示 年 月 日 时 分*/
{
    
    
    
    
    
    display_dianci(0,0,3,0);
    
    display_onetimedata_8_32(1,0,0x20,0);
    display_onetimedata_8_32(1,2,now_year,0);
    display_oneword_16_16(1,4,code_nian,0);
      
    display_reason(1,6,now_mon,0);
    
    display_onetimedata_8_32(2,0,now_mon,0);
    display_oneword_16_16(2,2,code_yue,0);
    display_onetimedata_8_32(2,4,now_day,0);
    display_oneword_16_16(2,6,code_ri,0);
    
    display_onetimedata_8_32(3,2,now_hour,0);
    display_oneword_16_16(3,4,code_maohao,0);
    display_onetimedata_8_32(3,6,now_min,0);
    
    display_week(4,2,now_week,0);
    
    display_area(5,0,DISP_DIQU,0);
    //Tp_timelsb = now_year%16;
   // Tp_timemsb = now_year/16;
    //display_graphic_8x16(1,5,&FONT_BUF[2*16]);
    //display_graphic_8x16(2,5,&FONT_BUF[0*16]);
    //display_graphic_8x16(3,5,&FONT_BUF[Tp_timemsb*16]);
    //display_graphic_8x16(4,5,&FONT_BUF[Tp_timelsb*16]);//年的数字
    //display_graphic_16x16(5,4,&FONT_BUF[num_addr+32*code_nian]);//中文年
    
    
//    Tp_timelsb = now_mon%16;
//    Tp_timemsb = now_mon/16;
//    display_graphic_8x16(1,21,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(2,21,&FONT_BUF[Tp_timelsb*16]);//月的数字
//    display_graphic_16x16(3,20,&FONT_BUF[num_addr+32*code_yue]);//中文月
//    Tp_timelsb = now_day%16;
//    Tp_timemsb = now_day/16;
//    display_graphic_8x16(5,21,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(6,21,&FONT_BUF[Tp_timelsb*16]);//日的数字
//    display_graphic_16x16(7,20,&FONT_BUF[num_addr+32*code_ri]);//中文日
//    
//    Tp_timelsb = now_hour%16;
//    Tp_timemsb = now_hour/16;
//    display_graphic_8x16(1,37,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(2,37,&FONT_BUF[Tp_timelsb*16]);
//    display_graphic_16x16(3,36,&FONT_BUF[num_addr+32*code_maohao]);
//    Tp_timelsb = now_min%16;
//    Tp_timemsb = now_min/16;
//    display_graphic_8x16(5,37,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(6,37,&FONT_BUF[Tp_timelsb*16]);
//    
} 

void display_timeroff(UINT8 x_hang,UINT8 x_data1,UINT8 x_data2,UINT8 x_flag)//x_flag 0-时分正显 1-时分反显 2-时反分正 3-时正分反 
{
   if((x_data1 == 0xff) || (x_data2 == 0xff))
   {
    
     switch(x_flag)
     {
      case 0:
      case 1: 
            display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,x_flag);
            
            display_oneword_8_32(x_hang,lie_5,0,x_flag);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,x_flag);
           break;
     case 2:  
            display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,1);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,1);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,1);
             display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,1);
             display_oneword_8_32(x_hang,lie_5,0,0);
            // display_oneword_8_32(x_hang,lie_5,0,0);
            //display_oneword_8_32(x_hang,lie_5,code_maohao_8_32,0);
            //display_oneword_16_32(x_hang,lie_4,code_O_16_32,0);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,0);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,0);
             display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,0);
          break;
     case 3: 
             display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_5,0,0);
            //display_oneword_8_32(x_hang,lie_5,code_maohao_8_32,0);
            //display_oneword_8_32(x_hang,lie_5,0,1);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,1);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,1);
            display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,1);
          break;
     default :break;
     }
     
   }
   else //万一错了呢
   {
      display_graphic_8x32(x_hang,2,&FONT_BUF_8_32[code_daE_8_32*32],0);
    display_graphic_8x32(x_hang,3,&FONT_BUF_8_32[code_xiaor_8_32*32],0);//年的数字   
   }
}

void display_nowtime(void)
{
   if(FLAG_MODE==NOWTIMESET_mode)
   {

  //   display_oneword_8_32(nowtimeset_hang_3,lie_1,code_kongbai_8_32,0);//
   //  display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
    //  display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
    //  display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
     // display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      // display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,0);//
   }
   else
   {
     display_onetimedata_8_32(Normal_hang_1,lie_2,now_hour,0);
    display_oneword_8_32(Normal_hang_1,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_1,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_1,lie_6,now_min,0);
   }
}

void menu_normal(void)   //正常显示屏 显示现在时间 开时间 闭时间
{

  //UINT8 CHAR[]={41,1}; 
    clear_clear();
  
    display_onetimedata_8_32(Normal_hang_1,lie_2,now_hour,0);
    display_oneword_8_32(Normal_hang_1,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_1,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_1,lie_6,now_min,0);
    
    if(TIMER_MODE_OPEN==Timer_Mode_SET)
    {
    display_onetimedata_8_32(Normal_hang_2,lie_2,open_hour,0);
    display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_2,lie_6,open_min,0);
    display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,0);
    }
    if(TIMER_MODE_OPEN==Timer_Mode_OFF)
    {
    display_timeroff(Normal_hang_2,open_hour,open_min,0);
    }
    if(TIMER_MODE_OPEN==Timer_Mode_AUTO)
    {
    display_oneword_24_32(Normal_hang_2,lie_1,code_zidong_24_32,0);//小时反显
    display_onetimedata_8_24(Normal_hang_2_1_0824,lie_4,auto_open_hour,0);
    display_oneword_8_24(Normal_hang_2_1_0824,lie_6,code_maohao_8_24,0);
    display_onetimedata_8_24(Normal_hang_2_1_0824,lie_7,auto_open_min,0);
    }
    
    if(TIMER_MODE_CLOSE==Timer_Mode_SET)
    {
    display_onetimedata_8_32(Normal_hang_3,lie_2,close_hour,0);
    display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_3,lie_6,close_min,0);
    display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,0);
    }
    if(TIMER_MODE_CLOSE==Timer_Mode_OFF)
    {
    display_timeroff(Normal_hang_3,close_hour,close_min,0);
    }
    if(TIMER_MODE_CLOSE==Timer_Mode_AUTO)
    {
     display_oneword_24_32(Normal_hang_3,lie_1,code_zidong_24_32,0);//小时反显
    display_onetimedata_8_24(Normal_hang_3_1_0824,lie_4,auto_close_hour,0);
    display_oneword_8_24(Normal_hang_3_1_0824,lie_6,code_maohao_8_24,0);
    display_onetimedata_8_24(Normal_hang_3_1_0824,lie_7,auto_close_min,0); 
    } 
    
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,1,Read_Buf_temp,0);
//   CHAR[0]=19;
//   CHAR[1]=4;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,3,Read_Buf_temp,0);
//   CHAR[0]=38;
//   CHAR[1]=27;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,5,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=31;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,7,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=30;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,1,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=34;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,3,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=36;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,5,Read_Buf_temp,0);
}

void menu_dispdianci(void)
{
    
    display_oneword_16_16(30,1,code_diancigenhuan,0);
    display_oneword_16_16(30,3,code_diancigenhuan+1,0);
    display_oneword_16_16(30,5,code_diancigenhuan+2,0);
    
    display_oneword_16_16(46,1,code_diancigenhuan+3,0);
    display_oneword_16_16(46,3,code_diancigenhuan+4,0);
    display_oneword_16_16(46,5,code_diancigenhuan+5,0);
    display_oneword_16_16(46,7,code_diancigenhuan+6,0);
     ClearWDT(); // Service the WDT
     
    display_oneword_16_16(62,1,code_diancigenhuan+7,0);
    display_oneword_16_16(62,3,code_diancigenhuan+8,0);
    display_oneword_16_16(62,5,code_diancigenhuan+9,0);
    display_oneword_16_16(62,7,code_diancigenhuan+10,0);
    //display_oneword_16_16(62,7,code_diancigenhuan+11,0);
    //display_oneword_16_16(78,1,code_diancigenhuan+12,0);
   // display_oneword_16_16(78,3,code_diancigenhuan+13,0);
    
}



void menu_setnowtime(void)
{
  // clear_clear();
  
  if(DISP_GUANGBIAO == 0)
   {
       display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
       display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
       display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0); 
       display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
   }
   if(DISP_GUANGBIAO == 1)//年反
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],1);//小时反显
      
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//小时反显
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//小时反显
       
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
   if(DISP_GUANGBIAO == 2)//月反
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],1);//小时反显
      //display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 3)//日反
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],1);//小时反显
      //display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 4)//时反
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],1);
      display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,1);//
     // display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 5)//分反
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
    //  
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],1);
      display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,1);//
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 6)//地区反
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//小时反显
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//小时反显
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//小时反显
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
    //  display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
    //  display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
       display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,0);//
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,1);
     // display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,1);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,1);
      display_oneword_16_16(nowtimeset_hang_4,lie_1,code_kongbai,1);
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],1);
      display_oneword_16_16(nowtimeset_hang_4,lie_8,code_kongbai,1);
   }
}

void  menu_setopentime(void)
{
   if(DISP_GUANGBIAO == 0)
   {
     
   }
   if(DISP_GUANGBIAO == 1)
   {
       display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,0);//小时反显
     display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],1);//小时反显
      //display_oneword_8_32(1,4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);//小时反显
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],0);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,0);
      //display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],2);//对于OFF不允许设置的
   }
   if(DISP_GUANGBIAO == 2)
   {
     display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,0);//小时反显
     display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],0);//分反显
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,0);
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,1);
      //display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],3);//对于OFF不允许设置的
   }
   
}

void  menu_setclosetime(void)
{
   if(DISP_GUANGBIAO == 0)
   {
     
   }
   if(DISP_GUANGBIAO == 1)
   {
     
     display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,0);//小时反显
     display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],1);//小时反显
    //  display_oneword_8_32(2,4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);//小时反显
      display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],0);
      display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,0);
      //display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],2);//对于OFF不允许设置的
   }
   if(DISP_GUANGBIAO == 2)
   {
      display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,0);//小时反显
     display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],0);//分反显
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,0);
      display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,1);
     // display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],3);//对于OFF不允许设置的
   }
   
}
void menu_preinstall(void)
{
  UINT8 install_open_hour[7] = {0x07,0x07,0xff,0x06,0x06,0xff,0xfe};
  UINT8 install_open_min[7] = {0x00,0x00,0xff,0x30,0x30,0xff,0xfe};
  
  UINT8 install_close_hour[7] = {0x17,0xff,0x17,0x17,0xff,0x17,0xfe};
  UINT8 install_close_min[7] = {0x00,0xff,0x00,0x30,0xff,0x30,0xfe};
  
  if(DISP_SANSUO == 6)//自动
  {
          // display_oneword(4,2,code_kongbai,1);
          // display_oneword(4,4,code_zi_auto,1);
          // display_oneword(4,6,code_dong_auto,1);
         //  display_oneword(7,2,code_kongbai,1);
         //  display_oneword(7,4,code_zi_auto,1);
         //  display_oneword(7,6,code_dong_auto,1);
           
         display_oneword_16_32(Normal_hang_2,lie_2,code_zi_auto_16_32,1);  
         display_oneword_16_32(Normal_hang_2,lie_4,code_kongbai_16_32,1);
         display_oneword_16_32(Normal_hang_2,lie_6,code_dong_auto_16_32,1);  
         display_oneword_16_32(Normal_hang_3,lie_2,code_zi_auto_16_32,1);
         display_oneword_16_32(Normal_hang_3,lie_4,code_kongbai_16_32,1);
         display_oneword_16_32(Normal_hang_3,lie_6,code_dong_auto_16_32,1); 
  }
  else//非自动
  {
           display_onetimedata_8_32(Normal_hang_2,lie_2,install_open_hour[DISP_SANSUO],1);//全反
           display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);
           display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,1);
           display_onetimedata_8_32(Normal_hang_2,lie_6,install_open_min[DISP_SANSUO],1);
           
           //display_timeroff(Normal_hang_2,install_open_hour[DISP_SANSUO],install_open_min[DISP_SANSUO],1);
           
           display_onetimedata_8_32(Normal_hang_3,lie_2,install_close_hour[DISP_SANSUO],1);//全反
           display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);
           display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,1);
           display_onetimedata_8_32(Normal_hang_3,lie_6,install_close_min[DISP_SANSUO],1);
          
           //display_timeroff(Normal_hang_3,install_close_hour[DISP_SANSUO],install_close_min[DISP_SANSUO],1);
  }
  
}


void menu_openonoff(void)
{
 // if(FG_LCD_1s==1)
 // {
  //  FG_LCD_1s = 0;
    
   
    
    DISP_SANSUO++;
    
    
    
    
      if(TIMER_MODE_DISP==Timer_Mode_SET)
      {
       
      display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,1);
      display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],1);//小时反显
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,1);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_OFF)
      {
      display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        Clear_64_32(Normal_hang_2,1);
        display_oneword_24_32(Normal_hang_2,lie_1,code_zidong_24_32,1);//小时反显
        display_onetimedata_8_24(Normal_hang_2_1_0824,lie_4,now_timer[1],1);
        display_oneword_8_24(Normal_hang_2_1_0824,lie_6,code_maohao_8_24,1);
        display_onetimedata_8_24(Normal_hang_2_1_0824,lie_7,now_timer[0],1);
      }
    
//  }
}

void menu_closeonoff(void)
{
  //if(FG_LCD_1s==1)
 // {
   // FG_LCD_1s = 0;
    
   
    
    DISP_SANSUO++;
    
  
    
    
      if(TIMER_MODE_DISP==Timer_Mode_SET)
      {
       display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,1);
        display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],1);//小时反显
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);
       display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,1);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],1);
       display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_OFF)
      {
      display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        Clear_64_32(Normal_hang_3,1);
        display_oneword_24_32(Normal_hang_3,lie_1,code_zidong_24_32,1);//小时反显
        display_onetimedata_8_24(Normal_hang_3_1_0824,lie_4,now_timer[1],1);
        display_oneword_8_24(Normal_hang_3_1_0824,lie_6,code_maohao_8_24,1);
        display_onetimedata_8_24(Normal_hang_3_1_0824,lie_7,now_timer[0],1);
      }
  //  }
  
}




void DISP_Refresh(void)
{
  ClearWDT(); // Service the WDT
  switch(FLAG_MODE)
  {
  case NORMAL_mode:
  case ADDDEC30_mode:
       menu_normal();break;
  case NOWTIMESET_mode:
       menu_setnowtime();break;
  case OPENTIMESET_mode:
       menu_setopentime();break;
  case CLOSETIMESET_mode:
       menu_setclosetime();break;
  case PREINSTALL_mode:
       menu_preinstall();break;
  case OPENONOFF_mode:
       menu_openonoff();break;
  case CLOSEONOFF_mode:
       menu_closeonoff();break;
  default:break;       
  }
  
  if(FG_LCD_1s== 1)
  {
     FG_LCD_1s =0;
  }
}



void lcd_backlight(void)
{ 
   if((FLAG_MODE!= INIT_mode)&&(FLAG_MODE!= CONTROL_mode))
   {
   
     
      
     //if(FLAG_BACKLIGHT_5S)
   //{
      
   //    PIN_LCD_LIGHT = 1;//开背光
  // }
  // else
   //{
    //  PIN_LCD_LIGHT = 0;//关背光
  //}
     
    

     
      if(FLAG_MODE!= NORMAL_mode)
      {
        if((AD_Flag==1)&&(BAT_out!=2))
          {
             PIN_LCD_LIGHT = 1;//开背光
          }
        switch(FLAG_MODE)
        { 
       
         case OPENTIMESET_mode: 
          case CLOSETIMESET_mode: 
        case OPENONOFF_mode:
          case CLOSEONOFF_mode:
          if(FLAG_BACKLIGHT_5S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//关背光
          TB_POWER =150;
          DISP_Refresh();
        }
             break;
        
        case ADDDEC30_mode:  
          if(FLAG_BACKLIGHT_1S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//关背光
          TB_POWER =150;
          DISP_Refresh();
        }
          break;
        
         case NOWTIMESET_mode: 
        if(FLAG_BACKLIGHT_60S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//关背光
          TB_POWER =150;
          DISP_Refresh();
        }
        break;
        
        default:break;
        }
        
      }
     
   }
   
}

//按键触发的退出倒计时复位
void key_touch_retime(void)
{
        switch(FLAG_MODE)
        { 
          case NORMAL_mode:
          case OPENTIMESET_mode: 
          case CLOSETIMESET_mode: 
          case OPENONOFF_mode:
          case CLOSEONOFF_mode:
          TIME_10S();
          break;
        
          case ADDDEC30_mode:  
          TIME_1S();
          break;
        
          case NOWTIMESET_mode: 
          TIME_60S();
          break;
        
          default:break;
        }
}




//液晶初始化
void  lcd_init(void)
{
   if(FLAG_INITLCD == 0)
   {
   FLAG_INITLCD = 1;
   PIN_LCD_SEL  = 0;//选中
   PIN_LCD_RST  = 0;//低电平复位
   delay(100);
   PIN_LCD_RST  = 1;//复位完毕
   delay(20);
   send_command(0xe2);//软件复位
   delay(5);
   send_command(0x2c);//升压1
   delay(5);
   send_command(0x2e);//升压2
   delay(5);
   send_command(0x2f);//升压3
   delay(5);
   send_command(0x24);//粗调对比度
   send_command(0x81);/*微调对比度*/
   send_command(0x1a);/*微调对比度的值，可设置范围0～63*/
   send_command(0xa2);/*1/9偏压比（bias）*/
   send_command(0xc8);/*行扫描顺序：从上到下*/
   send_command(0xa1);/*列扫描顺序：从左到右*/
   send_command(0x40);//显示初始行设置
   send_command(0xaf); /*开显示*/
   
   clear_clear();
   //display_dianci(0,0,3,0);//电池与模式无关
   
   PIN_LCD_LIGHT = 0;//关背光
   PIN_LCD_SEL  = 1;//不选中
   
   FLAG_POWER = 0;//这个标志防止液晶打开了 由于无线部分导致的关机 '
   
   if(FG_PWRON==0)
     FG_PWRON = 1;
   }
}

void Power_Low(void)
{
   if((BAT_out==2)&&(AD_Flag==1))//欠压
   {
     PIN_LCD_LIGHT = 0;//关背光
            POWER_OFF;
            FLAG_POWER = 1;
            while(1);
   }
}


void dianciqianya_lcd(void)
{
   //UINT16 Tp_Count=0;
  // while(AD_Flag == 0)//没算好小等一下
   //{
   //    Tp_Count++;
    //   ADC2_EOC_INT();
     //  AD_control();
     //  if(Tp_Count ==0)
     //  {
     //    break;
     //  }
  // }
  
  
   if((BAT_out!=0)&&(AD_Flag==1))//欠压
     {
        if(LOW_Flag == 0)
        {
          LOW_Flag = 1;
       POWER_ON;
         TB_POWER = 50;//10second
         lcd_init();
        // PIN_LCD_LIGHT = 1;//kai背光
        
          clear_clear();
         
          
          menu_dispdianci();
          
         if(BAT_out == 2)//如果无线都不工作了液晶也不动
         {
            PIN_LCD_LIGHT = 0;//关背光
            POWER_OFF;
            FLAG_POWER = 1;
            while(1);
         }
          else
          {
              if(FLAG_MODE != CONTROL_mode)//只有正常开
              {
            PIN_LCD_LIGHT = 1;//开背光
              }
          }
         
             while(1)
             {
                
                
                COUNT_QIANYA++;
                ClearWDT(); // Service the WDT
                
                 if(FLAG_MODE == CONTROL_mode)
                  {
                    TB_POWER =  0 ;
                    FLAG_POWER=1;//可以关屏
                    break;
                    
                  }
                
                if(COUNT_QIANYA >= 156000)
                {
                 
                  //2015 03 06 修改 显示完低电压报警换电池后马上关电源  避免出现下次低电压不报警的情况
                  //TB_POWER = 50;//10second
                  if(FLAG_MODE == NORMAL_mode)
                  {
                    TB_POWER = 50;//15second  5sencond ->10sencond 20150526
                  }
                
                  
                  clear_clear();
                  PIN_LCD_LIGHT = 0;//关背光
                 break;
                 
                }
             }
          
        }
     }
  
}

#endif