using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;

using System.Management;
//using BarTender;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        //private static BarTender.Application btApp = new BarTender.Application();
        //private static BarTender.Format btFormat = new BarTender.Format();

        public int R_cnt = 0;//接收计数
        public int S_cnt = 0;//发送计数
        public bool Sending_Flag = false;//正在发送文件标志
        public string str_Rec;//用于数据接收显示时缓存
        public bool Flag_PCBMAC = false, Flag_SSID = false;
        public int No_step = 0;

        /// <summary>
        /// 文件
        /// </summary>
        private static FileStream fs = null;
        private static long index = 0;
        private static long blockCount;
        private static int size = 4095;//4095+1=2M
        string filename;//文件名
        ///
        
        /// <summary>
        /// 委托用于接收显示
        /// </summary>
        /// <param name="InputBuf"></param>
        //声明了一个delegate 类型
        public delegate void Displaydelegate(byte[] InputBuf);
        //声明了一个delegate 对象
        public Displaydelegate disp_delegate;
        //将串口接收到的数据显示到textBox1上
        public void DispUI(byte[] InputBuf)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();
            if (display16.Checked == true)
            {
                foreach (byte b in InputBuf)
                {
                    //将数值转换成16进制数并追加一个空格并显示到textBox1上
                    receivebuf.AppendText(b.ToString("X2") + " ");
                }
            }
            else
            {
                //直接将数值转换成字符串并显示并显示到textBox1上
                receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms 扫码枪:";//2005-11-5 13:21:25 000
                receivebuf.AppendText(System.Text.Encoding.Default.GetString(InputBuf));
                receivebuf.Text = receivebuf.Text + "\r\n";

                UART1textBox.Text = System.Text.Encoding.Default.GetString(InputBuf);
                Bar_code_scan();
                
            }
        }

        //声明了一个delegate 类型
        public delegate void Displaydelegate2(byte[] InputBuf2);
        //声明了一个delegate 对象
        public Displaydelegate2 disp_delegate2;
        //将串口接收到的数据显示到textBox1上
        public void DispUI2(byte[] InputBuf2)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();
            if (display16.Checked == true)
            {
                foreach (byte b in InputBuf2)
                {
                    //将数值转换成16进制数并追加一个空格并显示到textBox1上
                    receivebuf.AppendText(b.ToString("X2") + " ");
                }
            }
            else
            {
                String str_re = System.Text.Encoding.Default.GetString(InputBuf2);
                int str_start = str_re.IndexOf("(");
                if (str_start == 0)
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms PCB Uart Receive:";//2005-11-5 13:21:25 000
                //直接将数值转换成字符串并显示并显示到textBox1上
                receivebuf.AppendText(System.Text.Encoding.Default.GetString(InputBuf2));
                //receivebuf.Text = receivebuf.Text + "\r\n";

                UART2textBox.AppendText(System.Text.Encoding.Default.GetString(InputBuf2));
                SCX1801_uart_TRX();
            }
        }

        public void Bar_code_scan( )
        {
            String str_data = UART1textBox.Text;
            String str_data1;
            if (No_step == 0)
            {
                MessageBox.Show("请操作送信机，送信", "错误");
            }
            else if(No_step>=1)
            {
                str_data1 = str_data.Substring(0, 8);
                if (str_data1 == ID_Box.Text.ToString())
                {
                    No_step++;
                    UART1textBox.Text = "";
                    if (No_step>=4)
                    {
                        timer3.Interval = 10;
                        timer3.Enabled = true;
                        timer3.Start();   //定时器开始工作
                        No_step = 50;
                    }
                }
                else
                {
                    MessageBox.Show("ID 错误", "错误");
                    ID_Box.Text = "";
                    receivebuf.Text = receivebuf.Text + "ID NG\r\n";
                    No_step = 0;
                }
            }
        }
        public void SCX1801_uart_TRX( )
        {
            String str_boot = UART2textBox.Text;

                int place = str_boot.IndexOf("(ID:");
                int str_END = str_boot.IndexOf("\r\n");
                if ((place != -1)&&(str_END != -1)&&(str_boot.Length>=12))
                {
                    ID_Box.Text= str_boot.Substring(place+4, 8);
                    if (Convert.ToInt32(ID_Box.Text, 10) == 0)
                    {
                        MessageBox.Show("ID错误,不能为0", "错误");
                        ID_Box.Text = "";
                        No_step = 0;
                    }
                    else
                        No_step = 1;
                    UART2textBox.Text = "";
                }

        }

        private void Label_select_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (open_close_UART2.Text == "关闭")
            {
                if (Label_select.Text.Contains("文化"))
                {
                    UART2textBox.Text = "";
                    serialPort2.Write("(WD0)");
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms PCB Uart write:" + "(WD0) 文化送信机\r\n";
                    timer3.Interval = 500;
                    timer3.Enabled = true;
                    timer3.Start();   //定时器开始工作
                    No_step = 60;
                }
                else if (Label_select.Text.Contains("新生精机"))
                {
                    UART2textBox.Text = "";
                    serialPort2.Write("(WD1)");
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms PCB Uart write:" + "(WD1) 新生精机送信机\r\n";
                    timer3.Interval = 500;
                    timer3.Enabled = true;
                    timer3.Start();   //定时器开始工作
                    No_step = 61;
                }
            }
            else
                MessageBox.Show("COM端口没有打开", "错误");
        }

        public void SCX1801_WriteRead_BatPrint()
        {
            string str_res, str_res1;
            int place = 0;
            switch (No_step)
            {
                case 0:
                    MessageBox.Show("请操作送信机，送信", "错误");
                    break;
                case 10:   //Write
                    str_res = "MAC -W " + PCBMACTextBox.Text + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 11;
                    timer3.Interval = 200;
                    break;
                case 11:
                    str_res = UART2textBox.Text.ToString();
                    str_res1 = str_res.Substring(22, 7);
                    timer3.Interval = 30;
                    if ((str_res1=="Set MAC")||(str_res1 == "set MAC"))
                        No_step = 12;
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("写 管理番号 错误", "错误");
                    }
                    break;
                case 12:
                    str_res = "DEVICE_CODE -W " + DEVICETextBox.Text + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 13;
                    timer3.Interval = 200;
                    break;
                case 13:
                    str_res = UART2textBox.Text.ToString();
                    str_res1 = str_res.Substring(30, 15);
                    timer3.Interval = 30;
                    if ((str_res1 == "set DEVICE_CODE")|| (str_res1 == "Set DEVICE_CODE"))
                        No_step = 14;
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("写 机器ID 错误", "错误");
                    }
                    break;
                case 14:
                    if (Label_select.Text.ToString() == "SCX1801")
                    {
                        str_res = "SSID -W " + SSIDTextBox.Text + "\r\n";
                        UART2textBox.Text = "";
                        receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                        serialPort2.Write(str_res);
                        No_step = 15;
                        timer3.Interval = 200;
                    }
                    else
                    {
                        timer3.Interval = 30;
                        No_step = 20;
                    }
                    break;
                case 15:
                    str_res = UART2textBox.Text.ToString();
                    str_res1 = str_res.Substring(19, 8);
                    timer3.Interval = 30;
                    if ((str_res1 == "set SSID") || (str_res1 == "Set SSID"))
                        No_step = 16;
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("写 SSID 错误", "错误");
                    }
                    break;
                case 16:
                    str_res = "PWD -W " + KEYTextBox.Text + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 17;
                    timer3.Interval = 200;
                    break;
                case 17:
                    str_res = UART2textBox.Text.ToString();
                    str_res1 = str_res.Substring(18, 7);
                    timer3.Interval = 30;
                    if ((str_res1 == "set PWD") || (str_res1 == "Set PWD"))
                        No_step = 20;
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("写 KEY 错误", "错误");
                    }
                    break;
                case 20:  //Read
                    str_res = "MAC" + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 21;
                    timer3.Interval = 350;
                    break;
                case 21:
                    str_res = UART2textBox.Text.ToString();
                    str_res = str_res.ToUpper();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("MAC: ");
                    if (place != -1)
                    {
                        PCBMACTextBox.Text = str_res.Substring(place + 5, 2) + str_res.Substring(place + 8, 2) + str_res.Substring(place + 11, 2) + str_res.Substring(place + 14, 2) + str_res.Substring(place + 17, 2) + str_res.Substring(place + 20, 2);
                        No_step = 22;
                    }
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("读 管理番号 错误", "错误");
                    }
                    break;
                case 22:
                    str_res = "DEVICE_CODE" + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 23;
                    timer3.Interval = 350;
                    break;
                case 23:
                    str_res = UART2textBox.Text.ToString();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("DEVICE_CODE: ");
                    if (place != -1)
                    {
                        DEVICETextBox.Text = str_res.Substring(place+13, 12);
                        No_step = 24;
                    }
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("读 机器ID 错误", "错误");
                    }
                    break;
                case 24:
                    if (Label_select.Text.ToString() == "SCX1801")
                    {
                        str_res = "SSID" + "\r\n";
                        UART2textBox.Text = "";
                        receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                        serialPort2.Write(str_res);
                        No_step = 25;
                        timer3.Interval = 350;
                    }
                    else
                    {
                        timer3.Interval = 30;
                        No_step = 30;
                    }
                    break;
                case 25:
                    str_res = UART2textBox.Text.ToString();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("SSID: ");
                    if (place != -1)
                    {
                        SSIDTextBox.Text = str_res.Substring(place+6, 8);
                        No_step = 26;
                    }
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("读 SSID 错误", "错误");
                    }
                    break;
                case 26:
                    str_res = "PWD" + "\r\n";
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + DateTime.Now.ToString() + " " + DateTime.Now.Millisecond.ToString() + "ms SCX1801 write:" + str_res;
                    serialPort2.Write(str_res);
                    No_step = 27;
                    timer3.Interval = 350;
                    break;
                case 27:
                    str_res = UART2textBox.Text.ToString();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("PWD: ");
                    if (place != -1)
                    {
                        KEYTextBox.Text = str_res.Substring(place+5, 8);
                        No_step = 30;
                    }
                    else
                    {
                        No_step = 200;
                        MessageBox.Show("读 KEY 错误", "错误");
                    }
                    break;
                case 30:  //打印
                    UART2textBox.Text = "";
                    StartButton_Click(null, null);
                    receivebuf.BackColor = System.Drawing.Color.LawnGreen;
                    timer3.Interval = 600;
                    No_step = 200;
                    break;
                case 50:  //ID ok
                    UART2textBox.Text = "";
                    receivebuf.Text = receivebuf.Text + "ID ok\r\n";
                    receivebuf.BackColor = System.Drawing.Color.LawnGreen;
                    timer3.Interval = 600;
                    No_step = 200;
                    break;
                case 60:
                    str_res = UART2textBox.Text.ToString();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("(WD)0");
                    No_step = 200;
                    if (place == -1)
                    {   
                        MessageBox.Show("ID解码器没有找到", "错误");
                    }
                    break;
                case 61:
                    str_res = UART2textBox.Text.ToString();
                    timer3.Interval = 30;
                    place = str_res.IndexOf("(WD)1");
                    No_step = 200;
                    if (place == -1)
                    {
                        MessageBox.Show("ID解码器没有找到", "错误");
                    }
                    break;
                case 200:  //退出
                    UART2textBox.Text = "";
                    timer3.Stop();   //关闭定时器
                    timer3.Enabled = false;
                    No_step = 0;
                    receivebuf.BackColor = System.Drawing.Color.Black;
                    break;
                default:
                    break;
            }
        }
        private void timer3_Tick(object sender, EventArgs e)
        {
            try
            {
                SCX1801_WriteRead_BatPrint();
            }
            catch (Exception ex)
            {

            }
        }

        public void LOT_create()
        {
            int data_Year, data_Month, data_Day;
            string str_Month, str_Day;
            DateTime dt = DateTime.Now;

            data_Year = dt.Year % 100;
            data_Month = dt.Month;
            data_Day = dt.Day;
            if(data_Month==10)
                str_Month = "X";
            else if (data_Month == 11)
                str_Month = "Y";
            else if (data_Month == 12)
                str_Month = "Z";
            else
                str_Month = data_Month.ToString();
            if (data_Day<=9)
                str_Day="0"+ data_Day.ToString();
            else
                str_Day = data_Day.ToString();
            LOTTextBox.Text = data_Year.ToString() + str_Month.ToString() + str_Day.ToString();
            int a = 1;
            MessageBox.Show("请确认LOT:"+"" + LOTTextBox.Text + ""+",如果不正确，请退出该软件后修改电脑时间后再使用","提示");
        }
        public string CheckRandomCode()
        {
            string _zimu = "ABCDEFGHJKLMNPQRSTUVWXYZabcdefghjkmnpqrstuvwxyz23456789";//要随机的字母
            Random _rand = new Random(~unchecked((int)DateTime.Now.Ticks)); //随机类
            string _result = "";
            int n = _zimu.Length;
            for (int i = 0; i < 20; i++) //循环20次，生成20位数字
            {
                _result += _zimu[_rand.Next(0, n)]; //通过索引下标随机

            }
            return _result;
        }

        //声明了一个delegate 类型
        public delegate void StopSenddelegate();
        public void DispStopSend()
        {
            SendFile.Enabled = true;// 
            send.Enabled = true;//"发送"按键使能
            timersend.Enabled = true;//失效       
        }

        //声明了一个delegate1 类型
        public delegate void SendOkdelegate();
        public void DispSendOk()
        {
            SendFile.Enabled = true;//
            send.Enabled = true;//"发送"按键使能
            timersend.Enabled = true;//失效  
            sendprogressBar.Step = 100;//设置progressBar1的增值为1
            sendprogressBar.PerformStep();//使用PerformStep方法按Step值递增 
            sendpercentage.Text = "100%";        
        }

        //声明了一个delegate1 类型
        public delegate void Sendingdelegate();
        public void DispSending()
        {
            sendprogressBar.Step = (int)(size  * 100 / fs.Length);//设置progressBar1的增值为
            sendprogressBar.PerformStep();//使用PerformStep方法按Step值递增 
            sendpercentage.Text = ((int)((size * index) * 100 / fs.Length)).ToString() + '%';
        }

        /// <summary>
        /// 线程实现函数
        /// </summary>
        //thread开启线程要求：该方法参数只能有一个，且是object类型
        public void sendfile()
        {
            fs = new FileStream(filename, FileMode.Open, FileAccess.Read);
            blockCount = (fs.Length - 1) / size + 1;
            for (;;)
            {
                if (Sending_Flag == false)//正在发送文件标志
                {
                    //创建一个delegate 对象
                    StopSenddelegate StopSenddelegate = new StopSenddelegate(DispStopSend);
                    Invoke(StopSenddelegate);// 委托
                    break;
                }
                if (index == blockCount - 1)//判断是否最后一次发送数据块
                {
                    byte[] bArr = new byte[fs.Length - (size * index) + 1];
                    fs.Read(bArr, 1, bArr.Length - 1);
                    index = 0;
                    serialPort1.Write(bArr, 0, bArr.Length);
                    //创建一个delegate 对象
                    SendOkdelegate SendOkdelegate = new SendOkdelegate(DispSendOk);
                    Invoke(SendOkdelegate);// 委托
                    S_cnt += bArr.Length;//发送计数
                    break;
                }
                else
                {
                    byte[] bArr = new byte[size + 1];//创建一个4Kb的byte[]
                    fs.Read(bArr, 1, size);//每次读入4Kb
                    index++;
                    serialPort1.Write(bArr, 0, bArr.Length);//每次发送4Kb
                    //创建一个delegate 对象
                    Sendingdelegate Sendingdelegate = new Sendingdelegate(DispSending);
                    Invoke(Sendingdelegate);
                    S_cnt += bArr.Length;//发送计数
                }
            }
        }
        /// <summary>
        /// 
        /// </summary>
        public Form1()
        {
            //创建一个delegate 对象
            disp_delegate = new Displaydelegate(DispUI);
            //创建一个delegate 对象
            disp_delegate2 = new Displaydelegate2(DispUI2);
            InitializeComponent();
        }
        /// <summary>
        /// 打开软件处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                //获取打印机
                foreach (string printer in System.Drawing.Printing.PrinterSettings.InstalledPrinters)
                {
                    InitprinterComboBox.Items.Add(printer);
                }
                InitprinterComboBox.SelectedIndex = 0;

                //int i;
                ///开定时器2
                timer2.Enabled = true;
                timer2.Interval = 100;  //定时器时间间隔
                timer2.Start();   //定时器开始工作

                //LOT_create();
                //PCBMACTextBox.Text = "";
                //DEVICETextBox.Text = "";
                //SSIDTextBox.Text = "";
                //KEYTextBox.Text = "";
                ///
                //获取端口名字 使用前需要添加 using System.IO.Ports;
                string[] PortName = SerialPort.GetPortNames();
                Array.Sort(PortName);//给端口名称排序
                com.Items.Clear();
                baudrate.Text = "115200";
                stopbit.Text = "1";
                databit.Text = "8";
                check.Text = "无";

                PCB_uart.Items.Clear();
                baudrate2.Text = "9600";
                stopbit2.Text = "1";
                databit2.Text = "8";
                check2.Text = "无";

                comstats.Text = "Close";
                sendpercentage.Text = "0%";
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                S_cnt = 0;//发送计数 
                R_cnt = 0;//接收计数 
                lblRCount.Text = "0";
                lblSCount.Text = "0";
                comstats.Text = "Close";
                ////因为存储在comboBox2中的数值都为字符串，所以需要将端口号转换为10进制数值
                /////////////波特率
                //serialPort1.BaudRate = Convert.ToInt32(baudrate.Text, 10);
                /////////////停止位
                //if (Convert.ToInt32(stopbit.Text, 10) == 1)
                //{
                //    serialPort1.StopBits = (StopBits)1;
                //}
                //else if (Convert.ToInt32(stopbit.Text, 10) == 2)
                //{
                //    serialPort1.StopBits = (StopBits)2;
                //}
                //else
                //{
                //    serialPort1.StopBits = (StopBits)3;
                //}
                /////////////数据位
                //serialPort1.DataBits = Convert.ToInt32(databit.Text, 10);
                /////////////奇偶校验
                //if (check.Text.Contains("奇校验"))
                //{
                //    serialPort1.Parity = (Parity)1;
                //}
                //else if (check.Text.Contains("偶校验"))
                //{
                //    serialPort1.Parity = (Parity)2;
                //}
                //else
                //{
                //    serialPort1.Parity = (Parity)0;
                //}
                //////////////////自动连接
                //for ( i = 0; i < PortName.Length; i++)
                //{
                //    try
                //    {
                //        com.Items.Add(PortName[i]);//给comboBox1添加选项
                //        com.Text = PortName[i];
                //        serialPort1.PortName = com.Text;//更改端口名称
                //        serialPort1.Open();//打开串口
                //        opencom.Enabled = false;//"打开串口"按键失效
                //        closecom.Enabled = true;//"关闭串口"按键使能
                //        send.Enabled = true;//"发送"按键使能
                //        baudrate.Enabled = false;
                //        stopbit.Enabled = false;
                //        databit.Enabled = false;
                //        check.Enabled = false;
                //        timersend.Enabled = true;//失效
                //        SendFile.Enabled = true;//"发送文件"按键使能
                //        OpenFile.Enabled = true;//"打开文件"按键使能
                //        comstats.Text="Open" + ' ' + com.Text+' '+ baudrate.Text + ' ' + stopbit.Text + ' ' + databit.Text + ' ' + check.Text;
                //        break;
                //    }
                //    catch (Exception)
                //    {
                //        continue;
                //    }
                //}
                /////////////////
                //if(i== PortName.Length)
                //{
                //    opencom.Enabled = true;//"打开串口"按键使能
                //    closecom.Enabled = false;//"关闭串口"按键失效
                //    send.Enabled = false;//"发送"按键失效
                //    baudrate.Enabled = true;//使能
                //    stopbit.Enabled = true;//使能
                //    databit.Enabled = true;//使能
                //    check.Enabled = true;//使能
                //    timersend.Enabled = false;//失效
                //    timersend.Checked = false;
                //    SendFile.Enabled = false;//"发送文件"按键失效
                //    OpenFile.Enabled = false;//"打开文件"按键失效
                //} 
            }
            catch (Exception)
            {
                //opencom.Enabled = true;//"打开串口"按键使能
                //closecom.Enabled = false;//"关闭串口"按键失效
                //send.Enabled = false;//"发送"按键失效
                //baudrate.Enabled = true;//使能
                //stopbit.Enabled = true;//使能
                //databit.Enabled = true;//使能
                //check.Enabled = true;//使能
                //timersend.Enabled = false;//失效
                //timersend.Checked = false;
                //SendFile.Enabled = false;//"发送文件"按键失效
                //OpenFile.Enabled = false;//"打开文件"按键失效
            }
        }
        /// <summary>
        /// 接收处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int n = serialPort1.BytesToRead;//串口缓存中数据的个数
            Byte[] InputBuf = new Byte[n];
            try
            {
                //读取串口缓存中的数据并存放到InputBuf数组中
                serialPort1.Read(InputBuf, 0, serialPort1.BytesToRead);
                //将当前线程挂起50ms
                System.Threading.Thread.Sleep(50);
                //执行委托
                this.Invoke(disp_delegate, InputBuf);
                R_cnt += serialPort1.BytesToRead;//接收计数 
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void serialPort2_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int n = serialPort2.BytesToRead;//串口缓存中数据的个数
            Byte[] InputBuf2 = new Byte[n];
            try
            {
                //读取串口缓存中的数据并存放到InputBuf数组中
                serialPort2.Read(InputBuf2, 0, serialPort2.BytesToRead);
                //将当前线程挂起50ms
                System.Threading.Thread.Sleep(200);
                //执行委托
                this.Invoke(disp_delegate2, InputBuf2);
                R_cnt += serialPort2.BytesToRead;//接收计数 
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            try
            {
                DateTime dt = DateTime.Now;
                datatime.Text = dt.ToString();//2005-11-5 13:21:25
                lblRCount.Text = R_cnt.ToString();
                lblSCount.Text = S_cnt.ToString();
            }
            catch (Exception ex)
            {

            }
        }
        
        /// <summary>
        /// 点击串口下拉框
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void com_Click(object sender, EventArgs e)
        {
            try
            {
                ////获取端口名字 使用前需要添加 using System.IO.Ports;
                //string[] PortName = SerialPort.GetPortNames();
                //Array.Sort(PortName);//给端口名称排序[]
                //com.Items.Clear();
                //if (serialPort1.IsOpen)
                //{
                //    serialPort1.Close();
                //    open_close_UART1.Text = "打开";
                //    opencom.Enabled = true;//"打开串口"按键使能
                //    closecom.Enabled = false;//"关闭串口"按键失效
                //    send.Enabled = false;//"发送"按键失效
                //    baudrate.Enabled = true;//使能
                //    stopbit.Enabled = true;//使能
                //    databit.Enabled = true;//使能
                //    check.Enabled = true;//使能
                //    timersend.Enabled = false;//失效
                //    timersend.Checked = false;
                //    SendFile.Enabled = false;//"发送文件"按键失效
                //    OpenFile.Enabled = false;//"打开文件"按键失效
                //}
                //for (int i = 0; i < PortName.Length; i++)
                //{
                //    com.Items.Add(PortName[i]);//给comboBox1添加选项
                //}

                com.Items.Clear();
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                    open_close_UART1.Text = "打开";
                }
                using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from Win32_PnPEntity"))
                {
                    var hardInfos = searcher.Get();
                    int index = 1;
                    foreach (var hardInfo in hardInfos)
                    {
                        if (hardInfo.Properties["Name"].Value != null && hardInfo.Properties["Name"].Value.ToString().Contains("(COM"))
                        {
                            String strComName = hardInfo.Properties["Name"].Value.ToString();
                            com.Items.Add(strComName); ;//给comboBox1添加选项,串口设备名称及串口号
                            index += 1;
                        }
                    }
                }
            }
            catch (Exception ex)
            {

            }
        }

        private void PCB_uart_Click(object sender, EventArgs e)
        {
            try
            {
                ////获取端口名字 使用前需要添加 using System.IO.Ports;
                //string[] PortName = SerialPort.GetPortNames();
                //Array.Sort(PortName);//给端口名称排序[]
                //PCB_uart.Items.Clear();
                //if (serialPort2.IsOpen)
                //{
                //    serialPort2.Close();
                //    open_close_UART2.Text = "打开";
                //    baudrate.Enabled = true;//使能
                //    stopbit.Enabled = true;//使能
                //    databit.Enabled = true;//使能
                //    check.Enabled = true;//使能
                //}
                //for (int i = 0; i < PortName.Length; i++)
                //{
                //    PCB_uart.Items.Add(PortName[i]);//给comboBox1添加选项
                //}

                PCB_uart.Items.Clear();
                if (serialPort2.IsOpen)
                {
                    serialPort2.Close();
                    open_close_UART2.Text = "打开";
                }
                using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from Win32_PnPEntity"))
                {
                    var hardInfos = searcher.Get();
                    int index = 1;
                    foreach (var hardInfo in hardInfos)
                    {
                        if (hardInfo.Properties["Name"].Value != null && hardInfo.Properties["Name"].Value.ToString().Contains("(COM"))
                        {
                            String strComName = hardInfo.Properties["Name"].Value.ToString();
                            PCB_uart.Items.Add(strComName); ;//给comboBox1添加选项,串口设备名称及串口号
                            index += 1;
                        }
                    }
                }

            }
            catch (Exception ex)
            {

            }
        }

        private void open_close_UART1_Click(object sender, EventArgs e)
        {
            try
            {
                if (open_close_UART1.Text == "打开")
                {
                    String strComName = com.Text;//更改端口名称
                    int p = strComName.IndexOf('(');
                    serialPort1.PortName = strComName.Substring(p + 1, strComName.Length - p - 2); //截取串口号 
                    //serialPort1.PortName = com.Text;//更改端口名称
                    
                                                    ///////////波特率
                    serialPort1.BaudRate = Convert.ToInt32(baudrate.Text, 10);
                    ////////////停止位
                    if (Convert.ToInt32(stopbit.Text, 10) == 1)
                    {
                        serialPort1.StopBits = (StopBits)1;
                    }
                    else if (Convert.ToInt32(stopbit.Text, 10) == 2)
                    {
                        serialPort1.StopBits = (StopBits)2;
                    }
                    else
                    {
                        serialPort1.StopBits = (StopBits)3;
                    }
                    ////////////数据位
                    serialPort1.DataBits = Convert.ToInt32(databit.Text, 10);
                    ////////////奇偶位
                    if (check.Text.Contains("奇校验"))
                    {
                        serialPort1.Parity = (Parity)1;
                    }
                    else if (check.Text.Contains("偶校验"))
                    {
                        serialPort1.Parity = (Parity)2;
                    }
                    else
                    {
                        serialPort1.Parity = (Parity)0;
                    }
                    /////////////
                    serialPort1.Open();//打开串口
                    open_close_UART1.Text = "关闭";
                }
                else
                {
                    serialPort1.Close();//关闭串口
                    open_close_UART1.Text = "打开";
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("端口错误，请检查端口", "错误");
            }
        }

        private void open_close_UART2_Click(object sender, EventArgs e)
        {
            try
            {
                if (open_close_UART2.Text == "打开")
                {
                    String strComName = PCB_uart.Text;//更改端口名称
                    int p = strComName.IndexOf('(');
                    serialPort2.PortName = strComName.Substring(p + 1, strComName.Length - p - 2); //截取串口号                                                        
                    //serialPort2.PortName = PCB_uart.Text;//更改端口名称

                    ///////////波特率
                    serialPort2.BaudRate = Convert.ToInt32(baudrate2.Text, 10);
                    ////////////停止位
                    if (Convert.ToInt32(stopbit2.Text, 10) == 1)
                    {
                        serialPort2.StopBits = (StopBits)1;
                    }
                    else if (Convert.ToInt32(stopbit2.Text, 10) == 2)
                    {
                        serialPort2.StopBits = (StopBits)2;
                    }
                    else
                    {
                        serialPort2.StopBits = (StopBits)3;
                    }
                    ////////////数据位
                    serialPort2.DataBits = Convert.ToInt32(databit2.Text, 10);
                    ////////////奇偶位
                    if (check2.Text.Contains("奇校验"))
                    {
                        serialPort2.Parity = (Parity)1;
                    }
                    else if (check2.Text.Contains("偶校验"))
                    {
                        serialPort2.Parity = (Parity)2;
                    }
                    else
                    {
                        serialPort2.Parity = (Parity)0;
                    }
                    /////////////
                    serialPort2.Open();//打开串口
                    open_close_UART2.Text = "关闭";
                    Label_select_SelectedIndexChanged(null, null);
                }
                else
                {
                    serialPort2.Close();//关闭串口
                    open_close_UART2.Text = "打开";
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("端口错误，请检查端口", "错误");
            }
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            string LOT_string = LOTTextBox.Text;
            string PCBMAC_string = PCBMACTextBox.Text;
            string DEVICE_string = DEVICETextBox.Text;
            string SSID_string = SSIDTextBox.Text;
            string KEY_string = KEYTextBox.Text;

            if (Label_select.Text.ToString() == "SCX1801A")
            {
                SSID_string = "";
                KEY_string = "";
            }

            InitprinterComboBox.Enabled = false;
            PrintLabNum.Enabled = false;

            //判断两次SN号是否相等，若不相等则进行生成条形码和打印
            if (((Label_select.Text.ToString() == "SCX1801")&&(LOT_string != string.Empty) && (PCBMAC_string != string.Empty) && (DEVICE_string != string.Empty) && (SSID_string != string.Empty) && (KEY_string != string.Empty))||
                ((Label_select.Text.ToString() == "SCX1801A") && (LOT_string != string.Empty) && (PCBMAC_string != string.Empty) && (DEVICE_string != string.Empty)))
            {
                try
                {
                    //btFormat = btApp.Formats.Open(AppDomain.CurrentDomain.BaseDirectory + "SCX1801.btw", false, "");

                    ////向bartender模板传递变量,LOT为条形码数据的一个共享名称
                    //btFormat.SetNamedSubStringValue("LOT", LOT_string);
                    ////向bartender模板传递变量,PCBMAC为条形码数据的一个共享名称
                    //btFormat.SetNamedSubStringValue("PCBMAC", PCBMAC_string);
                    ////向bartender模板传递变量,DEVICE为条形码数据的一个共享名称
                    //btFormat.SetNamedSubStringValue("DEVICE", DEVICE_string);
                    ////向bartender模板传递变量,SSID为条形码数据的一个共享名称
                    //btFormat.SetNamedSubStringValue("SSID", SSID_string);
                    ////向bartender模板传递变量,KEY为条形码数据的一个共享名称
                    //btFormat.SetNamedSubStringValue("KEY", KEY_string);

                    ////选择打印机
                    //btFormat.Printer = InitprinterComboBox.Text;

                    ////设置打印份数
                    //int CopiesOfLabel = Int32.Parse(this.PrintLabNum.Text.ToString());
                    //btFormat.IdenticalCopiesOfLabel = CopiesOfLabel;

                    ////设置打印时是否跳出打印属性
                    //btFormat.PrintOut(false, false);

                    ////退出时是否保存标签
                    //btFormat.Close(BarTender.BtSaveOptions.btDoNotSaveChanges);

                }
                catch (Exception ex)
                {
                    MessageBox.Show("错误信息: " + ex.Message);
                    return;
                }
            }

            InitprinterComboBox.Enabled = true;
            PrintLabNum.Enabled = true;
        }


        //界面退出时同步退出bartender进程
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //btApp.Quit(BarTender.BtSaveOptions.btDoNotSaveChanges);
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            if (No_step == 0)
            {
                MessageBox.Show("没有识别到SCX1801 PCB", "错误");
            }
            else
            {
                timer3.Interval = 100;
                timer3.Enabled = true;
                timer3.Start();   //定时器开始工作
                No_step = 20;
            }
        }

        private void receivebuf_TextChanged(object sender, EventArgs e)
        {
            this.receivebuf.SelectionStart = this.receivebuf.Text.Length;
            this.receivebuf.ScrollToCaret();
        }








        /// <summary>
        /// 打开串口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = com.Text;//更改端口名称
                //因为存储在comboBox2中的数值都为字符串，所以需要将端口号转换为10进制数值
                ///////////波特率
                serialPort1.BaudRate = Convert.ToInt32(baudrate.Text, 10);
                ////////////停止位
                if (Convert.ToInt32(stopbit.Text, 10) == 1)
                {
                    serialPort1.StopBits = (StopBits)1;
                }
                else if (Convert.ToInt32(stopbit.Text, 10) == 2)
                {
                    serialPort1.StopBits = (StopBits)2;
                }
                else
                {
                    serialPort1.StopBits = (StopBits)3;
                }
                ////////////数据位
                serialPort1.DataBits = Convert.ToInt32(databit.Text, 10);
                ////////////奇偶位
                if (check.Text.Contains("奇校验"))
                {
                    serialPort1.Parity = (Parity)1;
                }
                else if (check.Text.Contains("偶校验"))
                {
                    serialPort1.Parity = (Parity)2;
                }
                else
                {
                    serialPort1.Parity = (Parity)0;
                }
                /////////////
                serialPort1.Open();//打开串口
                opencom.Enabled = false;//"打开串口"按键失效
                closecom.Enabled = true;//"关闭串口"按键使能
                send.Enabled = true;//"发送"按键使能
                baudrate.Enabled = false;
                stopbit.Enabled = false;
                databit.Enabled = false;
                check.Enabled = false;
                timersend.Enabled = true;//失效
                SendFile.Enabled = true;//"发送文件"按键使能
                OpenFile.Enabled = true;//"打开文件"按键使能
                comstats.Text = "Open" + ' ' + com.Text + ' ' + baudrate.Text + ' ' + stopbit.Text + ' ' + databit.Text + ' ' + check.Text;
                sendpercentage.Text = "0%";
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                S_cnt = 0;//发送计数 
                R_cnt = 0;//接收计数 
                lblRCount.Text = "0";
                lblSCount.Text = "0";
            }
            catch (Exception ex)
            {
                MessageBox.Show("端口错误，请检查端口", "错误");
            }
        }
        /// <summary>
        /// 关闭串口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();//关闭串口
                opencom.Enabled = true;//"打开串口"按键使能
                closecom.Enabled = false;//"关闭串口"按键失效
                send.Enabled = false;//"发送"按键失效
                baudrate.Enabled = true;//使能
                stopbit.Enabled = true;//使能
                databit.Enabled = true;//使能
                check.Enabled = true;//使能
                timersend.Enabled = false;//失效
                timersend.Checked = false;
                SendFile.Enabled = false;//"发送文件"按键失效
                OpenFile.Enabled = false;//"打开文件"按键失效
                comstats.Text = "Close";
                sendpercentage.Text = "0%";
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                S_cnt = 0;//发送计数 
                R_cnt = 0;//接收计数 
                lblRCount.Text = "0";
                lblSCount.Text = "0";
            }
            catch (Exception ex)
            {
             
            }
        }
        /// <summary>
        /// 点击发送按键处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                if (sendbuf.Text.Trim() == String.Empty)
                {
                    MessageBox.Show("发送数据不能为空");
                    return;
                }
                if (send16.Checked == true)//选择16进制发送时
                {
                    List<byte> buf = new List<byte>();//填充到这个临时列表中
                    //使用正则表达式获取textBox2中的有效数据
                    MatchCollection mc = Regex.Matches(sendbuf.Text, @"(?i)[\da-f]{2}");
                    //将mc转换为16进制数据并添加到buf列表中
                    foreach (Match m in mc)
                    {
                        byte data = Convert.ToByte(m.Value, 16);
                        buf.Add(data);
                    }
                    ///////////处理最后一位为奇数时
                    if ((sendbuf.Text.Length % 2) != 0)
                    {
                        MatchCollection mc1 = Regex.Matches(sendbuf.Text, @"(?i)[\da-f]{1}");
                        for (int i = 0; i < mc1.Count; i++)
                        {
                            byte data = Convert.ToByte(mc1[i].Groups[0].Value, 16);
                            if (i > (mc1.Count - 2))
                            {
                                buf.Add(data);
                            }
                        }
                    }
                    /////////////    
                    if (sendnewline.Checked == true)//选择发送新行时
                    {
                        buf.Add(0x0d);
                        buf.Add(0x0a);
                    }
                    //将buf列表转换为数组并通过串口发送出去
                    serialPort1.Write(buf.ToArray(), 0, buf.Count);
                    S_cnt += buf.Count;//发送计数
                }
                else//如果选择字符发送模式
                {
                    if (sendnewline.Checked == true)//选择发送新行时
                    {
                        string res = sendbuf.Text + "\r\n";
                        byte[] byteArray = System.Text.Encoding.Default.GetBytes(res);
                        serialPort1.Write(byteArray, 0, byteArray.Length);
                        S_cnt += byteArray.Length;//发送计数 
                    }
                    else
                    {
                        byte[] byteArray = System.Text.Encoding.Default.GetBytes(sendbuf.Text);
                        serialPort1.Write(byteArray, 0, byteArray.Length);
                        S_cnt += byteArray.Length;//发送计数 
                    }
                    
                }
            }
            catch (Exception ex)
            {
                
            }
        }

        /// <summary>
        /// 发送区输入内容判断
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            try
            {
                if (send16.Checked == true)//选择16进制发送时
                {
                    if (
                            (
                                ((e.KeyChar) >= '0') &&
                                ((e.KeyChar) <= '9')
                            )
                        || (
                                ((e.KeyChar) >= 'a') &&
                                ((e.KeyChar) <= 'f')
                           )
                        || (
                                ((e.KeyChar) >= 'A') &&
                                ((e.KeyChar) <= 'F')
                           )
                        || ((e.KeyChar) == '\b')
                       )
                    {

                    }
                    else
                    {
                        MessageBox.Show("请输出正确的格式 0-9 a-f A-F例如01 06 0a");
                    }
                    e.Handled = "0123456789ABCDEF".IndexOf(char.ToUpper(e.KeyChar)) < 0;
                }
            }
            catch (Exception ex)
            {
               
            }

        }
        /// <summary>
        /// 清空接收区的内容
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                receivebuf.Clear();
            }
            catch (Exception ex)
            {
               
            }
        }
        /// <summary>
        /// 清空发送区的内容
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                sendbuf.Clear();
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                sendpercentage.Text = "0%";
            }
            catch (Exception ex)
            {
                
            }
        }

        /// <summary>
        /// 接收背景颜色改变
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void receivedisplaycolor_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                if (receivedisplaycolor.Checked == true)
                {

                    this.receivebuf.BackColor = System.Drawing.Color.White;
                    this.receivebuf.ForeColor = System.Drawing.Color.Black;
                }
                else
                {
                    this.receivebuf.BackColor = System.Drawing.Color.Black;
                    this.receivebuf.ForeColor = System.Drawing.Color.LawnGreen;
                }
            }
            catch (Exception ex)
            {
               
            }
        }
        /// <summary>
        /// 保存窗口函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void savefile_Click(object sender, EventArgs e)
        {
            try
            {
                string name = this.receivebuf.Text; //文件名
                string content = this.receivebuf.Text; //文件内容
                string path = string.Empty; //文件路径
                if (receivebuf.Text.Trim() == String.Empty)//为空
                {
                    MessageBox.Show("数据缓冲为空");
                    return;
                }
                SaveFileDialog save = new SaveFileDialog();
                if (save.ShowDialog() == DialogResult.OK)
                {
                    path = save.FileName;
                    path = path + ".txt";
                }
                if (path != string.Empty)
                {
                    using (System.IO.FileStream file = new System.IO.FileStream(path, System.IO.FileMode.Create, System.IO.FileAccess.Write))
                    {
                        using (System.IO.TextWriter text = new System.IO.StreamWriter(file, System.Text.Encoding.Default))
                        {
                            text.Write(content);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
               
            }
        }
        /// <summary>
        /// 接收显示格式
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void display16_CheckedChanged(object sender, EventArgs e)
        {
            if (display16.Checked == true)
            {
                str_Rec= receivebuf.Text;
                byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(receivebuf.Text);
                string hexOutput = " ";
                for(int i=0;i< byteArray.Length;i++)
                {
                    hexOutput += byteArray[i].ToString("X2") + " ";

                }
                receivebuf.Text = hexOutput;
            }
            else
            {
                receivebuf.Text = str_Rec;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                if (sendbuf.Text.Trim() == String.Empty)//为空
                {
                    return;
                }
                if (send16.Checked == true)//选择16进制发送时
                {
                    List<byte> buf = new List<byte>();//填充到这个临时列表中
                                                        //使用正则表达式获取textBox2中的有效数据
                    MatchCollection mc = Regex.Matches(sendbuf.Text, @"(?i)[\da-f]{2}");
                    //将mc转换为16进制数据并添加到buf列表中
                    foreach (Match m in mc)
                    {
                        byte data = Convert.ToByte(m.Value, 16);
                        buf.Add(data);
                    }
                    ///////////处理最后一位为奇数时
                    if ((sendbuf.Text.Length % 2) != 0)
                    {
                        MatchCollection mc1 = Regex.Matches(sendbuf.Text, @"(?i)[\da-f]{1}");
                        for (int i = 0; i < mc1.Count; i++)
                        {
                            byte data = Convert.ToByte(mc1[i].Groups[0].Value, 16);
                            if (i > (mc1.Count - 2))
                            {
                                buf.Add(data);
                            }
                        }
                    }
                    /////////////    
                    if (sendnewline.Checked == true)//选择发送新行时
                    {
                        buf.Add(0x0d);
                        buf.Add(0x0a);
                    }
                    //将buf列表转换为数组并通过串口发送出去
                    serialPort1.Write(buf.ToArray(), 0, buf.Count);
                    S_cnt += buf.Count;//发送计数 
                }
                else//如果选择字符发送模式
                {
                    if (sendnewline.Checked == true)//选择发送新行时
                    {
                        string res = sendbuf.Text + "\r\n";
                        byte[] byteArray = System.Text.Encoding.Default.GetBytes(res);
                        serialPort1.Write(byteArray, 0, byteArray.Length);
                        S_cnt += byteArray.Length;//发送计数 
                    }
                    else
                    {
                        byte[] byteArray = System.Text.Encoding.Default.GetBytes(sendbuf.Text);
                        serialPort1.Write(byteArray, 0, byteArray.Length);
                        S_cnt += byteArray.Length;//发送计数 
                    }
                }
            }
            catch (Exception ex)
            {
                
            }
        }
        /// <summary>
        /// 发送区输入内容判断
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void txtSendDelay_KeyPress(object sender, KeyPressEventArgs e)
        {
            try
            {
                if (
                       (
                            ((e.KeyChar) >= '0') &&
                            ((e.KeyChar) <= '9')
                       )
                       || ((e.KeyChar) == '\b')
                   )
                {

                }
                else
                {
                    MessageBox.Show("请输出正确的格式 0-9");
                }
                e.Handled = "0123456789".IndexOf(char.ToUpper(e.KeyChar)) < 0;
            }
            catch (Exception ex)
            {
                
            }
        }
        /// <summary>
        /// 定时发送实现函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timersend_CheckedChanged(object sender, EventArgs e)
        {
            int timer;
            try
            {
                Int32.TryParse(SendDelay.Text,out timer);
                if (timersend.Checked == true)
                {
                    if (timer == 0)////转换为int类型 
                    {
                        MessageBox.Show("请输入定时时间");
                        timersend.Checked = false;
                        return;
                    }
                    timer1.Enabled = true;
                    timer1.Interval = timer; //定时器时间间隔 
                    timer1.Start();   //定时器开始工作
                }
                else
                {
                    timer1.Enabled = false;
                    timer1.Stop();
                }
            }
            catch (Exception ex)
            {
                
            }
        }

        /// <summary>
        /// 清空计数函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void clrcnt_Click(object sender, EventArgs e)
        {
            try
            {
                S_cnt = 0;//发送计数 
                R_cnt = 0;//接收计数 
                lblRCount.Text = "0";
                lblSCount.Text = "0";
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                sendpercentage.Text = "0%";
            }
            catch (Exception ex)
            {
              
            }
        }
        /// <summary>
        /// 打开文件函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenFile_Click(object sender, EventArgs e)
        {
            try
            {
                //首先，实例化对话框类实例
                OpenFileDialog openDialog = new OpenFileDialog();
                //然后，判断如果当前用户在对话框里点击的是OK按钮的话。
                if (DialogResult.OK == openDialog.ShowDialog())
                {
                    //将打开文件对话框的FileName属性传递到你的字符串进行处理
                    filename = openDialog.FileName;
                }
            }
            catch (Exception ex)
            {
               
            }
        }
        /// <summary>
        /// 发送文件函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SendFile_Click(object sender, EventArgs e)
        {
            try
            {
                if (filename == null)
                {
                    MessageBox.Show("请选择要发送的文件");
                    return;
                }
                SendFile.Enabled = false;//发送文件键失效
                send.Enabled = false;//"发送"按键失效
                timersend.Checked = false;
                timersend.Enabled = false;//失效
                if (Sending_Flag == false)//正在发送文件标志
                {
                    Sending_Flag = true;
                }
                Thread t = new Thread(new ThreadStart(sendfile));//创建了线程还未开启
                t.Start();//用来给函数传递参数，开启线程
                sendprogressBar.Value = 0;//设置进度条的初始值 
                sendprogressBar.Minimum = 0;//设置progressBar1控件的Minimum值为0 
                sendprogressBar.Maximum = 100;//设置progressBar1的Maximum值为500 
                sendpercentage.Text = "0%";
                index = 0;
            }
            catch (Exception ex)
            {
                SendFile.Enabled = true;//
                send.Enabled = true;//"发送"按键使能
                timersend.Enabled = true;//失效
                return;
            }
        }
        /// <summary>
        /// 停止发送函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void stopsend_Click(object sender, EventArgs e)
        {
            if (Sending_Flag == true)//正在发送文件标志
            {
                Sending_Flag = false;//正在发送文件标志
            }
        }

        private void baudrate_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void datatime_Click(object sender, EventArgs e)
        {

        }

        private void com_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void PCB_uart_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void ID_Box_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

    }
}
