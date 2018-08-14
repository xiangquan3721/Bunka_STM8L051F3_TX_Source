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
#include "key_and_Other_cyw.h"	// 按键
#include "eeprom_cyw.h"		// eeprom

#if(ProductID==Hanging_display)//

UINT8 ack = 0;//应答信号

//uchar TAB_T[]={ 0x31,0x06,0x10,//秒,分,时</P>
//                0x13,0x01,0x07,0x08};//日,星期,月,年. 
//
//#define MIN    0x02 //秒寄存器   
//#define SEC    0x03 //分寄存器   
//#define HOUR   0x04 //时寄存器   
//#define DAY    0x05 //日寄存器   
//#define WEEK   0x06 //周寄存器   
//#define MONTH 0x07 //月寄存器   
//#define YEAR   0x08 //年寄存器   
//#define read_ADD 0xA3 //写器件地址   
//#define write_ADD 0xA2 //读器件地址   
//#define delayNOP(); delay(1);  
//
//
//unsigned char g8563_Store[4]={0x0}; /*时间交换区,全局变量声明*/  
//const unsigned char c8563_Store[4]={0x00,0x59,0x07,0x01}; /*写入时间初值：星期一 07:59:00*/  
//unsigned char F0;
//unsigned char SystemError;
//
//
////--------------------------------------------------------------------------------------------------   
//// 函数名称： iic_start()   
//// 函数功能： 启动I2C总线子程序   
////--------------------------------------------------------------------------------------------------   
//void iic_start(void)  
//{
//  PIN_PCF8563_SDAOUT = 1;           
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();      // 延时5us    
//  PIN_PCF8563_SDAOUT = 0;  
//  delayNOP();  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： iic_stop()   
//// 函数功能： 停止I2C总线数据传送子程序   
////--------------------------------------------------------------------------------------------------   
//void iic_stop(void)  
//{   
//  PIN_PCF8563_SDAOUT = 0;       //时钟保持高，数据线从低到高一次跳变，I2C通信停止   
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();  
//  PIN_PCF8563_SDAOUT = 1;  
//  delayNOP();  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： slave_ACK   
//// 函数功能： 从机发送应答位子程序   
////--------------------------------------------------------------------------------------------------   
//void slave_ACK(void)  
//{  
//  PIN_PCF8563_SDAOUT = 0;      
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();     
//  PIN_PCF8563_SDAOUT = 1;  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： slave_NOACK   
//// 函数功能： 从机发送非应答位子程序，迫使数据传输过程结束   
////--------------------------------------------------------------------------------------------------   
//void slave_NOACK(void)  
//{   
//  PIN_PCF8563_SDAOUT = 1;     
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();  
//  PIN_PCF8563_SDAOUT = 0;  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： check_ACK   
//// 函数功能： 主机应答位检查子程序，迫使数据传输过程结束   
////--------------------------------------------------------------------------------------------------   
//void check_ACK(void)  
//{   
//  PIN_PCF8563_SDAOUT = 1;      // 将p1.0设置成输入，必须先向端口写1   
//  PIN_PCF8563_SCL = 1;  
//  F0 = 0;  
//  
//  PIN_PCF8563_SDA_direc = Input;
//  if(PIN_PCF8563_SDAIN == 1)    // 若SDA=1表明非应答，置位非应答标志F0   
//   F0 = 1;  
//  PIN_PCF8563_SDA_direc = Output;
//  
//  PIN_PCF8563_SCL = 0;  
//}  
//  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： IICSendByte   
//// 入口参数： ch   
//// 函数功能： 发送一个字节   
////--------------------------------------------------------------------------------------------------   
//void IICSendByte(unsigned char ch)  
//{   
//  unsigned char  n=8;     // 向SDA上发送一位数据字节，共八位   
//  while(n--)  
//  {   
//      if((ch&0x80) == 0x80)    // 若要发送的数据最高位为1则发送位1   
//      {  
//       PIN_PCF8563_SDAOUT = 1;    // 传送位1   
//       PIN_PCF8563_SCL = 1;  
//       delayNOP();  
//       PIN_PCF8563_SDAOUT = 0;  
//       PIN_PCF8563_SCL = 0;      
//   }  
//  else  
//   {   
//   PIN_PCF8563_SDAOUT = 0;    // 否则传送位0   
//   PIN_PCF8563_SCL = 1;  
//   delayNOP();  
//   PIN_PCF8563_SCL = 0;   
//   }  
//  ch = ch<<1;    // 数据左移一位   
//}  
//}  
////--------------------------------------------------------------------------------------------------   
//// 函数名称： IICreceiveByte   
//// 返回接收的数据   
//// 函数功能： 接收一字节子程序   
////--------------------------------------------------------------------------------------------------   
//unsigned char IICreceiveByte(void)  
//{  
//unsigned char n=8;    // 从SDA线上读取一上数据字节，共八位   
//unsigned char tdata;  
//while(n--)  
//{  
//   PIN_PCF8563_SDAOUT = 1;  
//   PIN_PCF8563_SCL = 1;  
//   tdata = tdata<<1;    // 左移一位，或_crol_(temp,1)   
//   
//   PIN_PCF8563_SDA_direc = Input;
//   if(PIN_PCF8563_SDAIN == 1)  
//    tdata = tdata|0x01;    // 若接收到的位为1，则数据的最后一位置1   
//  else   
//    tdata = tdata&0xfe;    // 否则数据的最后一位置0  
//  PIN_PCF8563_SDA_direc = Output;
//   PIN_PCF8563_SCL=0;  
//}  
//return(tdata);  
//}  
//
////--------------------------------------------------------------------------------------------------   
//// 用户调用子程序   
//// 函数名称： receiveNbyte   
//// 入口参数： CFG_add寄存器地址地址   
//// 出口参数： receive_da   
//// 函数功能： 接收某个寄存器数据子程序   
////--------------------------------------------------------------------------------------------------   
//unsigned char receive_CFGbyte(unsigned char CFG_add)  
//{   
//unsigned char receive_da;  
//  iic_start();  
//   IICSendByte(write_ADD); //器件写地址   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//IICSendByte(CFG_add); //寄存器地址   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//     iic_start();  
//    IICSendByte(read_ADD); //器件读地址   
//   if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//    receive_da=IICreceiveByte();  
//   slave_NOACK();       // 收到最后一个字节后发送一个非应答位   
//iic_stop();  
//return(receive_da);  
//}  
////--------------------------------------------------------------------------------------------------   
//// 用户调用函数   
//// 函数名称： receive_CFGNbyte   
//// 入口参数： CFG_add寄存器地址地址，n连续读数位，* buff存储区地址   
//// 函数功能： 接收n个寄存器数据子程序   
////--------------------------------------------------------------------------------------------------   
//void receive_CFGNbyte(unsigned char CFG_add, unsigned char n,unsigned char * buff)  
//{   
//unsigned char receive_da,i=0;  
//iic_start();  
//   IICSendByte(write_ADD); //器件写地址   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return;  
//}  
//  IICSendByte(CFG_add); //寄存器地址   
//  check_ACK();  
//  if(F0 == 1)  
//  {  
//     SystemError = 1;  
//     return;  
//  }  
//     iic_start();  
//     IICSendByte(read_ADD); //器件读地址   
//     if(F0 == 1)  
//  {  
//     SystemError = 1;  
//     return;  
//  }  
//    while(n--)  
//{   
//        receive_da=IICreceiveByte();  
//       buff[i++]=receive_da;  
//       slave_ACK();    // 收到一个字节后发送一个应答位   
//    }  
//    slave_NOACK();    // 收到最后一个字节后发送一个非应答位   
//    iic_stop();  
//} 
//
////--------------------------------------------------------------------------------------------------   
//// 用户调用子程序   
//// 函数名称： write_CFGbyte   
//// 入口参数： CFG_add寄存器地址,CFG_data要写入寄存器的数值   
//// 函数功能： 发送n位数据子程序   
////--------------------------------------------------------------------------------------------------   
//void write_CFGbyte(unsigned char CFG_add,unsigned char CFG_data)  
//{            
////unsigned char idata send_da,i=0;   
//    iic_start();                // 启动I2C   
//    IICSendByte(write_ADD);     // 发送器件写地址   
//    check_ACK();                // 检查应答位   
//      if(F0 == 1)  
//    {   
//       SystemError = 1;  
//       return;    // 若非应答表明器件错误或已坏，置错误标志位SystemError   
//    }  
//    IICSendByte(CFG_add);       // 发送寄存器地址   
//    check_ACK();                // 检查应答位   
//       if(F0 == 1)  
//    {   
//      SystemError = 1;  
//      return;    // 若非应答表明器件错误或已坏，置错误标志位SystemError   
//    }  
//      IICSendByte(CFG_data);       // 发送寄存器数据   
//      check_ACK();                // 检查应答位   
//       if(F0 == 1)  
//   {   
//      SystemError = 1;  
//      return;    // 若非应答表明器件错误或已坏，置错误标志位SystemError   
//   }  
//   iic_stop();         // 全部发完则停止   
//}  
////--------------------------------------------------------------------------------------------------   
//// 用户调用函数   
//// 函数名称： P8563_Readtime   
//// 函数功能： 读出时间信息   
////--------------------------------------------------------------------------------------------------   
//void P8563_Readtime()  
//{   
//  unsigned char time[7]={0x0};  
//   receive_CFGNbyte(MIN,0x07,time);  
//   g8563_Store[0]=time[0]&0x7f; /*秒*/  
//   g8563_Store[1]=time[1]&0x7f; /*分*/  
//   g8563_Store[2]=time[2]&0x3f; /*小时*/  
//   g8563_Store[3]=time[4]&0x07; /*星期*/  
//}  
////--------------------------------------------------------------------------------------------------   
//// 用户调用函数   
//// 函数名称： P8563_settime   
//// 函数功能： 写时间修改值   
////--------------------------------------------------------------------------------------------------   
//void P8563_settime()  
//{  
//     unsigned char i;  
//     for(i=2;i<=4;i++) { write_CFGbyte(i,c8563_Store[i-2]); }  //miao fen shi
//     write_CFGbyte(6,c8563_Store[3]);  //weekday
//}  
//
//
//
//


//void Delayus(unsigned int timer)
//{
//  unsigned int x;            //延时T=(timer)us     //SYSCLK=20M
 // for(x=0;x<26*timer;x++);    //特别说明：该行采用XC32的1级优化，C编译器优化后延时函数的延时时间被改变了，请注意。    时间=0.7us+timer*1.2us

//}

//void Mack(void) //接收应答信号
//{
// //SDA = 1;
// //ack=ack;
// //ack=ack;
// Delayus(1);
// PIN_PCF8563_SDA_direc = Input;
// //ack=ack;
// //ack=ack;
// Delayus(10);
// Delayus(5); //>4.7us
// PIN_PCF8563_SCL = 1;
// Delayus(4); //>4us
// Delayus(4);
// Delayus(4);
// //SDAIO = 1;
// if(PIN_PCF8563_SDAIN == 1)
//     ack = 0;
// else
//     ack = 1; //用ASK=1为有应答信号
// PIN_PCF8563_SCL = 0;
// //ack=ack;
// //ack=ack;
// Delayus(1);
// PIN_PCF8563_SDA_direc = Output;
// Delayus(10);
//}
//
//
//void send_byte(UINT8 c)
//{
// UINT8 bit_count;
// for(bit_count = 0;bit_count < 8;bit_count++)
//     {
//      if((c << bit_count) & 0x80) PIN_PCF8563_SDAOUT = 1;
//      else  PIN_PCF8563_SDAOUT = 0;
//      //ack=ack;
//      Delayus(5); //>4.7us
//      PIN_PCF8563_SCL = 1;
//      Delayus(4); //>4us
//      PIN_PCF8563_SCL = 0;
//     }
// Mack();//等待回应
//}
//
//void start_i2c(void)
//{
//    PIN_PCF8563_SDAOUT=1; //发送启始条件的数据信号
//    //ack=ack;
//    //ack=ack;
//    Delayus(1);
//    PIN_PCF8563_SCL=1;
//    Delayus(5);  //>4.7us
//    PIN_PCF8563_SDAOUT=0; //发送起始信号
//    Delayus(4);  //>4us
//    PIN_PCF8563_SCL=0; //钳住I2C总线,准备发送数据或接收数据
//    //ack=ack;
//    //ack=ack;
//    Delayus(1);
// }
//
//void stop_i2c(void)
//{
//   PIN_PCF8563_SDAOUT = 0; //发送结束条件的数据信号
//   Delayus(5);  //>4.7us
//   PIN_PCF8563_SCL = 1;
//   Delayus(4);//>4us
//   PIN_PCF8563_SDAOUT = 1;
//   Delayus(5);  //>4.7us
//}
//
//
//UINT8 receive_byte(void)
//{
// UINT8 retc, bit_count;
// retc = 0;
// for(bit_count = 0;bit_count < 8;bit_count++)
//     {
//     // ack=ack;
//       Delayus(1);
//      PIN_PCF8563_SCL = 0;
//      Delayus(5);  //>4.7us
//      //SDA =1;
//      PIN_PCF8563_SCL = 1;
//      Delayus(5); //>4.7us
//      retc = retc << 1;
//      if(PIN_PCF8563_SDAIN == 1)
//          retc = retc + 1;
//     }
// PIN_PCF8563_SCL = 0;
// //ack=ack;
// //ack=ack;
//  Delayus(1);
// return(retc);
//}
//
////==============Write()写N字节数据=================//
//
//void Write_pcf8563(UINT8 *s,UINT8 suba,UINT8 n)  //24LC16B
//
//{
//     UINT8 i;
// 
//    start_i2c(); //启动总线
//
//    send_byte(0xa2);//发送器件地址
//
//    send_byte(suba); //发送字地址
//
//    for (i = 0;i < n;i++)
//     
//    {
//      
//       send_byte(*s); //发送字节数据
//     
//       s++;
//     
//    }
// 
//    stop_i2c(); //发送停止位
//
//}
//
//void N0ack(char a) //发送应答位
//{
// PIN_PCF8563_SDA_direc = Output;
// //ack=ack;
// Delayus(10);
// if(a==0)PIN_PCF8563_SDAOUT = 0;
// else  PIN_PCF8563_SDAOUT = 1;
// Delayus(5);  //>4.7us
// PIN_PCF8563_SCL = 1;
// Delayus(4);//>4us
// PIN_PCF8563_SCL = 0;
//}
//
//void Read_pcf8563(UINT8 *s,UINT8 suba,UINT8 n)
//
//{
// UINT8 i;
// 
//   start_i2c(); //启动总线
//
//   send_byte(0xa2);//发送器件地址
//
//   send_byte(suba); //发送字地址
//
//   start_i2c(); //重新启动总线
//
//   send_byte(0xa3); //发送读命令和器件地址
//
//   for(i = 0;i < n - 1;i++)
//     
//   {
//      
//     PIN_PCF8563_SDA_direc = Input;
//     
//      Delayus(10);
//     
//     *s = receive_byte(); //获得数据
//     
//     s++;
//      
//     N0ack(0); //发送应答信号
//    
//   }
// 
//     PIN_PCF8563_SDA_direc = Input;
//   
//   Delayus(10);
//   
//     *s = receive_byte(); //获得数据
//
//     N0ack(1); //发送非应答位
//
//     stop_i2c(); //发送停止位
//}
//
//
// void Read_Time(void)
// 
// {
//   unsigned char  time_arr[7] = {0};
//   Read_pcf8563(&time_arr[0],0x02,7);
//          
//   g8563_Store[0]= time_arr[0]&0x7F;
//          
//   g8563_Store[1]= time_arr[1]&0x7F;
//          
//   g8563_Store[2]= time_arr[2]&0x3F;
//          
//   g8563_Store[3]= time_arr[3]&0x3F;
//          
//   g8563_Store[4]= time_arr[4]&0x07;
//          
//   g8563_Store[5]=time_arr[5]&0x1F;
//          
//   g8563_Store[6]= time_arr[6];
// }
//
//
// void Set_Time(void)
//
//{
//     
//                             /*秒、  分  、时、日期、星期、月、年 */
//    unsigned char c8563_Store[7]={0x00,0x59,0x07,0x01,0x01,0x01,0x14}; /*写入时间初值：星期一 07:59:00*/  
//    UINT8 data_i[2]={0x00,0x00};
//    
//     Write_pcf8563(&data_i[0],0x00,2);
//  //控制状态寄存器        
//     Delayus(10);
//          
//     Write_pcf8563(&c8563_Store[0],0x02,7);
//}


//#define iic_delay Delayus(20)
#define iic_delay Delayus(1)//和气反映按键丢的问题IIC 提速

 void Start(void) 
 { 
      PIN_PCF8563_SDAOUT=1; 
      PIN_PCF8563_SCL=1; 
      iic_delay;
      PIN_PCF8563_SDAOUT=0; 
      iic_delay;
 } 

void Stop(void) 
 { 
    PIN_PCF8563_SDAOUT=0; 
    PIN_PCF8563_SCL=1; 
    iic_delay;
    PIN_PCF8563_SDAOUT=1; 
    iic_delay;
} 

void Reack(void) 
 { 
    uchar i=0; 
    PIN_PCF8563_SDA_direc = Input;
    iic_delay;
    PIN_PCF8563_SCL=1; //准备检测SDA Delay5us(); 
    while((PIN_PCF8563_SDAIN==1)&&(i<100))
    {
      i++;//SDA=0为应该信号,SDA=1为非应答</P>
    }
    PIN_PCF8563_SDA_direc = Output;
    iic_delay;
    PIN_PCF8563_SCL=0; //准备下一变化数据</P>
 } 

void WriteByte(uchar ucByte) 
 { 
    uchar i; 
    PIN_PCF8563_SCL=0; 
    for(i=0;i<8;i++) 
    { 
      if(ucByte&0x80)//先写入高位</P>
      {
        PIN_PCF8563_SDAOUT=1;
      }
      else
      {
         PIN_PCF8563_SDAOUT=0;
      }
      PIN_PCF8563_SCL=1; 
      iic_delay;
      PIN_PCF8563_SCL=0; 
      ucByte<<=1; 
    } 
    PIN_PCF8563_SDAOUT=1; //释放数据线</P>
 } 

uchar ReadByte(void) 
 { 
    uchar i,ucByte=0; 
    
     PIN_PCF8563_SDA_direc = Input;
    iic_delay;
    
    PIN_PCF8563_SCL=0; 
    for(i=0;i<8;i++) 
    { 
        ucByte<<=1; 
       if(PIN_PCF8563_SDAIN) 
          ucByte++; 
       PIN_PCF8563_SCL=1; 
       iic_delay;
      PIN_PCF8563_SCL=0; 
    } 
    
     PIN_PCF8563_SDA_direc = Output;
    iic_delay;
    
    return ucByte; 
 } 

void Write8563(uchar ucAddr,uchar ucData) 
 { 
       iic_delay;
      Start(); 
      WriteByte(0xa2); 
      Reack(); 
      WriteByte(ucAddr); 
      Reack(); 
      WriteByte(ucData); 
      Reack(); 
      Stop(); 
} 

uchar Read8563(uchar ucAddr) 
 { 
      uchar ucData; 
       iic_delay;
      Start(); 
      WriteByte(0xa2); //写器件地址</P>
      Reack(); 
      WriteByte(ucAddr); //写字节地址</P>
      Reack(); 
      Start(); 
      WriteByte(0xa3); //写器件地址,最低为1表示读</P>
      Reack(); 
      ucData=ReadByte(); //写字节地址</P>
      Stop(); 
      return ucData; //读数据</P>
} 


void Alarm8563(void)
{
  UINT16 Tp_opentime,Tp_closetime,Tp_nowtime;
  UINT8 Tp_mon=0;//,Tp_Data;
  UINT8 Tp_flag = 0;// 0-不做任何设置 1-设置OPEN  2-设置CLOSE
  
  ClearWDT(); // Service the WDT
  
  
 
  
  
  
  if((TIMER_MODE_OPEN == Timer_Mode_SET)||(TIMER_MODE_OPEN == Timer_Mode_OFF))
  {
     Tp_opentime = (decimal(open_hour))*60+decimal(open_min);
  }
  if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
  {
    Tp_opentime = (decimal(auto_open_hour))*60+decimal(auto_open_min);
  }
   if((TIMER_MODE_CLOSE == Timer_Mode_SET)||(TIMER_MODE_CLOSE == Timer_Mode_OFF))
  {
    Tp_closetime = (decimal(close_hour))*60+decimal(close_min);
  }
   if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
   {
     Tp_closetime = (decimal(auto_close_hour))*60+decimal(auto_close_min);
   }
  Tp_nowtime = (decimal(now_hour))*60+decimal(now_min);
  
  
   if((TIMER_MODE_OPEN == Timer_Mode_AUTO)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
  {
    //如果
    if(decimal(now_day)==calculate_monandday(now_year,now_mon))//现在是最后一天了
    {
       if(((Tp_nowtime >= Tp_opentime)||(Tp_opentime > 1440))&&((Tp_nowtime >= Tp_closetime)||(Tp_closetime>1440)))//所有的都报过警了 
       {
          Tp_mon = decimal(now_mon) + 1; 
          if(Tp_mon >= 13)
            Tp_mon = 1;
          Auto_Timer_refresh(hex(Tp_mon));
          
          if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
           {
                Tp_opentime = (decimal(auto_open_hour))*60+decimal(auto_open_min);
           }
           if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
           {
                Tp_closetime = (decimal(auto_close_hour))*60+decimal(auto_close_min);
           }
          
       }  
    }
  }
  
  
  ClearWDT(); // Service the WDT
  
  
  if(Tp_opentime!=Tp_closetime)//如果开关在同一时间 还有意义吗？ 如果要动作 第一次上电 要误动作？
  {
  //双关没意义
   if((Tp_opentime > 1440)&&(Tp_closetime < 1440)) //开被关
  {
    Tp_flag = 2;//设置CLOSE为最近的报警时间
  }
  if((Tp_closetime > 1440)&&(Tp_opentime < 1440)) //开被关
  {
    Tp_flag = 1;//设置OPEN为最近的报警时间
  }
  if((Tp_closetime < 1440)&&(Tp_opentime < 1440))//开关寄存器都没有OFF的话 应该设置离当前时刻最近的而且是将来的时刻为报警时刻
  {
    if((Tp_nowtime<Tp_opentime)&&(Tp_nowtime<Tp_closetime))//如果开关时刻都是将来时刻 设置进的
    {
        if(Tp_opentime>Tp_closetime)//Tp_opentime>Tp_closetime>Tp_nowtime
        {
          Tp_flag = 2;//设置CLOSE为最近的报警时间
        }
        else
        {
          Tp_flag = 1;//设置OPEN为最近的报警时间
        }
    }
     if((Tp_nowtime>Tp_opentime)&&(Tp_nowtime>Tp_closetime))//如果开关时刻都是第二天的时刻 设置小的
     {
        if(Tp_opentime>Tp_closetime)//Tp_opentime>Tp_closetime>Tp_nowtime
        {
          Tp_flag = 2;//设置CLOSE为最近的报警时间
        }
        else
        {
          Tp_flag = 1;//设置OPEN为最近的报警时间
        }
     }
     if((Tp_nowtime>Tp_opentime)&&(Tp_nowtime<Tp_closetime))
     {
       Tp_flag = 2;//设置CLOSE为最近的报警时间
     }
    if((Tp_nowtime<Tp_opentime)&&(Tp_nowtime>Tp_closetime))
     {
       Tp_flag = 1;//设置OPEN为最近的报警时间
     }
    if(Tp_nowtime == Tp_opentime)//这种情况是RTC刚报完开的警 把关时刻放进去 前四种是设置参数时重置 后两种是报完警后重置
     {
        Tp_flag = 2;//设置CLOSE为最近的报警时间
     }
    if(Tp_nowtime == Tp_closetime)//这种情况是RTC刚报完关的警 把开时刻放进去 前四种是设置参数时重置 后两种是报完警后重置
     {
         Tp_flag = 1;//设置OPEN为最近的报警时间
     }
  }
  }
  ClearWDT(); // Service the WDT
  
  
 // Write8563(0x00,0x20); //停时钟
  if(Tp_flag == 1)//计算结果是开时间放进寄存器
  {
 // Write8563(0x00,0x20); 
  if(TIMER_MODE_OPEN == Timer_Mode_SET)
  {
     Write8563(0x09,open_min); //分报警
     Write8563(0x0A,open_hour); //时报警
  }
  if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
  {
     Write8563(0x09,auto_open_min); //分报警
     Write8563(0x0A,auto_open_hour); //时报警
  }
  Write8563(0x0B,0X80); //每月1日报警关闭日报警
  Write8563(0x0C,0X80);//关闭周报警
 
  }
  if(Tp_flag == 2)//计算结果是闭时间放进寄存器
  {
 // Write8563(0x00,0x20);
   if(TIMER_MODE_CLOSE == Timer_Mode_SET)
   {
     Write8563(0x09,close_min); //分报警
     Write8563(0x0A,close_hour); //时报警
   }
   if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
   {
     Write8563(0x09,auto_close_min); //分报警
     Write8563(0x0A,auto_close_hour); //时报警
   }
   Write8563(0x0B,0X80); //每月1日报警关闭日报警
   Write8563(0x0C,0X80);//关闭周报警
 // Write8563(0x00,0x00);
//  Write8563(0x0b,0x00); //分报警
 // Write8563(0x0c,0x00); //时报警
  }
  if(Tp_flag == 0)//禁止所有报警 当开=闭 也不报 这个要不要 待定
  {
     Write8563(0x09,0x80); //分报警
     Write8563(0x0A,0x80); //时报警
     Write8563(0x0B,0X80); //每月1日报警关闭日报警
     Write8563(0x0C,0X80);//关闭周报警
  }
  // Write8563(0x00,0x00); //停时钟
  //最后如果是AUTO模式
  //Tp_Data= Read8563(1);
   //  if((Tp_Data&0x02)==0)//这样表示PCF8563没有被设置
    //  {  
    //      Rewrite8563();
    //   }
   Auto_Timer_refresh(now_mon);//即使实时时钟是按照下个月的在LOAD了 但是显示还是当月的直到过完24点 不能乱啊 所以重新装载
}


void Init8563(void) 
 { 
      
   /*秒、  分  、时、日期、星期、月、年 */
   unsigned char c8563_Store[7]={0x00,0x00,0x00,0x24,0x05,0x10,0x14}; /*写入时间初值：星期一 07:59:00*/  
   
      uchar i,ucAddr=0x02,Tp_data; 
       FLAG_RTC_RTC = 1;//这个不重入
      Tp_data = Read8563(1);
      if((Tp_data&0x02)==0)//这样表示PCF8563没有被设置
      {  
        
       ClearWDT(); // Service the WDT   
      //ClearWDT(); // Service the WDT
     // Write8563(0x00,0x20); 
      Write8563(0x01,0x02); 
     
      for(i=0;i<7;i++) 
      { 
        Write8563(ucAddr,c8563_Store[i]); 
        ucAddr++; 
      }
      
       FLAG_RTC_RTC = 0;
      GetTime();
       FLAG_RTC_RTC = 1;
      ClearWDT(); // Service the WDT   
       Auto_Timer_refresh(now_mon);
       ClearWDT(); // Service the WDT   
      Alarm8563();
     Write8563(0x00,0x00);
     
      }
      
       FLAG_RTC_RTC = 0;
      
      
 } 
 
 
 //有手动设置时更改
void Rewrite8563(void) 
 { 
      
   /*秒、  分  、时、日期、星期、月、年 */
   
      uchar i,ucAddr=0x02; 
      
      ClearWDT(); // Service the WDT
     // Write8563(0x00,0x20); 
      FLAG_RTC_RTC = 1;
      //Write8563(0x00,0x20);//停时钟
     // Write8563(0x01,0x02); 
      Write8563(0x01,0x02); 
      for(i=0;i<7;i++) 
      { 
        Write8563(ucAddr,g8563_Store[i]); 
        ucAddr++; 
      } 
      Write8563(0x00,0x00);
      FLAG_RTC_RTC = 0;
 } 
 
 
void GetTime(void) 
 { 
      uchar i,ucAddr=0x02; 
      uchar *pTime=g8563_Store; 
      
      ClearWDT(); // Service the WDT
      
      
      if(FLAG_RTC_RTC ==1)
      {
         return;
      }
      
     
      FLAG_RTC_RTC = 1;
      for(i=0;i<7;i++) 
      { 
          pTime[i]=Read8563(ucAddr); 
          ucAddr++; 
      } 
      pTime[0]&=0x7f; //屏蔽无效位</P>
      pTime[1]&=0x7f; 
      pTime[2]&=0x3f; 
      pTime[3]&=0x3f; 
      pTime[4]&=0x07; 
      pTime[5]&=0x1f; 
     FLAG_RTC_RTC = 0;
      FLAG_CLOCK =1;
} 

void real_time(void)
{
  uchar Tp_data,i;
   unsigned char c8563_Store[7]={0x00,0x00,0x00,0x24,0x05,0x10,0x14}; /*写入时间初值：星期一 07:59:00*/  
  
    
  
  if((FLAG_MODE!= INIT_mode)&&(FLAG_MODE!= CONTROL_mode))
   {
       if(FG_RTC_1s == 1)
       {
          
         Tp_data = Read8563(1);
        if((Tp_data&0x02)==0)//这样表示PCF8563没有被设置
        {  
          Rewrite8563();
           Write8563(0x01,0x02); 
          return;
        }
         GetTime();
        FG_RTC_1s = 0;
        if(HIS_MIN!=now_min)
        {
          display_nowtime();
           HIS_MIN = now_min;
           Auto_Timer_refresh(now_mon);//刷新自动报警的时间 20150505
        }
       // FLAG_PRESS =0;//so long so clear
         
       }
   }
  if((decimal(now_sec)>=60)||(decimal(now_min)>=60)||(decimal(now_hour)>=24)||(decimal(now_day)>=32)||(decimal(now_mon)>=13)||(decimal(now_year)>=100)\
    ||(decimal(now_day)==0)||(decimal(now_mon)==0))
    
  {
     if(FLAG_CLOCK==1)
     {
    for(i=0;i<7;i++) 
      { 
        g8563_Store[i]=c8563_Store[i]; 
      
      }
     
    Rewrite8563();
     }
  }
  if(DISP_DIQU>=8)
  {
     DISP_DIQU = 0;
     eeprom_diqu_save();
  }
 
}

#endif

