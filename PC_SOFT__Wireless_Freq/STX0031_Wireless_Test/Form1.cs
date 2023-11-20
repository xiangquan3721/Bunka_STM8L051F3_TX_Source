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
using System.Globalization;
using System.Management;

namespace OK06_Wireless_Test
{
    public partial class Form1 : Form
    {
        public const int RY_count_DEF = 4;   //测试项目数量
        public const int RY_number_DEF = 8;  //6路继电器板
                                                            //Y1 Y2 Y3 Y4 Y5 Y6 Y7 Y8
        int [,]RY_data=new int[RY_count_DEF, RY_number_DEF]{{ 1, 0, 0, 0, 5, 6, 0, 0},
                                                            { 1, 2, 0, 0, 5, 6, 0, 0},  //OPEN按键
                                                            { 1, 0, 3, 0, 5, 6, 0, 0},  //STOP按键
                                                            { 1, 0, 0, 4, 5, 6, 0, 0},  //CLOSE按键
                                                            };
                                                 //Y1 Y2 Y3 Y4 Y5 Y6 Y7 Y8
        int[] RY_reset1 = new int[RY_number_DEF] { 1, 0, 0, 0, 5, 6, 0, 0 };
        int[] RY_reset2 = new int[RY_number_DEF] { 0, 0, 0, 0, 0, 0, 0, 0 };
        byte[] tx_data = new byte[RY_number_DEF*2 + 9]{ 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,    //head
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    //data RY_number*2
                                                    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00 };  //crc16
        double[] I_MAX_DEF = new double[RY_count_DEF] { 0.002, 17.0, 6.0, 17.0 };
        double[] I_MIN_DEF = new double[RY_count_DEF] { 0.0  , 12.0, 2.5, 12.0 };
        double[] Freq_MAX_DEF = new double[RY_count_DEF] { 0.0, 0.0011, 0.0, 0.0 };
        double[] Freq_MIN_DEF = new double[RY_count_DEF] { 0.0, 0.0011, 0.0, 0.0 };
        double[] PA_MAX_DEF = new double[RY_count_DEF] { 0.0, 5.0, 0.0, 0.0 };
        double[] PA_MIN_DEF = new double[RY_count_DEF] { 0.0, -5.0,0.0, 0.0 };
        double freqnum_bak;
        int RY_count = 0, RY_repeat = 0;
        int OK_count = 0, NG_count = 0;
        string ID_HEX;
        int ID_DEC;
        int AutoTest_Step = 0;
        int flag_auto_start = 0;
        int flag_rx_done = 0;
        int rx_offset = 0;
        int tx_cmd = 0;
        int flag_err = 0;
        int rx_ack_num = 0;
        int flag_one = 0;
        byte[] InputData = new byte[64];
        Color BackClolor_ON = Color.LightSteelBlue;
        Color BackClolor_OFF = Color.Gainsboro;
        ModbusCRC16 CRC16 = new ModbusCRC16();
        CVisaOpt_Option cvisa_opt = new CVisaOpt_Option();
        Freq_stu freq_opt_stu = new Freq_stu();
        Source_stu source_opt_stu = new Source_stu();
        public Form1()
        {
            InitializeComponent();
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            Display_Results.Text = " ";

            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);//必须手动添加事件处理程序
            serialPort2.DataReceived += new SerialDataReceivedEventHandler(port2_DataReceived);
            serialPort3.DataReceived += new SerialDataReceivedEventHandler(port3_DataReceived);
            
            source_opt_stu = cvisa_opt.SourceOpt_Init("RSA3");
            if (source_opt_stu.err == 3)
            {
                DP_FreqON.Checked = true;
                DP_FreqON.Enabled = true;
                DP_FreqON.BackColor = Color.LightGreen;
                DP_FreqOFF.Enabled = false;
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 成功连接频谱仪：\r\n");
                DP_DataRecord.AppendText(source_opt_stu.source_name + "\r\n");
                cvisa_opt.Opt_Set("RSA3", "ON");
            }
            else {
                flag_err = 3;
                MessageBox.Show("出错：未找到频谱仪 RSA3xxx！");
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 错误：未找到频谱仪 RSA3xxx\r\n");
                DP_FreqON.Checked = false;
                DP_FreqON.Enabled = false;
                DP_FreqOFF.Enabled = true;
            }
            /*
            source_opt_stu = cvisa_opt.SourceOpt_Init("DSG3");
            if (source_opt_stu.err == 3)
            {
                DP_SignalON.Checked = true;
                DP_SignalON.Enabled = true;
                DP_SignalON.BackColor = Color.LightGreen;
                DP_SignalOFF.Enabled = false;
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 成功连接信号源：\r\n");
                DP_DataRecord.AppendText(source_opt_stu.source_name + "\r\n");
                cvisa_opt.Opt_Set("DSG3", "ON");
            }
            else
            {
                flag_err = 4;
                MessageBox.Show("出错：未找到仪器！");
                DP_SignalON.Checked = false;
                DP_SignalON.Enabled = false;
                DP_SignalOFF.Enabled = true;
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 错误：未找到信号源 DSG3xxx\r\n");
            }*/
            source_opt_stu = cvisa_opt.SourceOpt_Init("DM3");
            if (source_opt_stu.err == 3)
            {
                DP_DMMON.Checked = true;
                DP_DMMON.Enabled = true;
                DP_DMMON.BackColor = Color.LightGreen;
                DP_DMMOFF.Enabled = false;
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 成功连接数字万用表：\r\n");
                DP_DataRecord.AppendText(source_opt_stu.source_name + "\r\n");
                cvisa_opt.Opt_Set("DM3", "I");
            }
            else
            {
                flag_err = 5;
                MessageBox.Show("出错：未找到数字万用表 DM3xxx！");
                DP_DMMON.Checked = false;
                DP_DMMON.Enabled = false;
                DP_DMMOFF.Enabled = true;
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 错误：未找到数字万用表 DM3xxx\r\n");
            }
        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收处理
        {
            int rx_cnt = 0;
            byte[] InputBuf = new byte[64];
            rx_cnt = serialPort1.BytesToRead;
            if (rx_cnt > 64) rx_cnt = 64;
            serialPort1.Read(InputBuf, 0, rx_cnt);

            //01 10 00 00 00 02 41 C8
            for (int j = 0; j < rx_cnt; j++)
            {
                if (InputBuf[j] == 0x01 || InputData[0] == 0x01) //帧头
                {
                    for (int k = 0; k < rx_cnt - j; k++)
                    {
                        if (k + rx_offset >= 64)
                        {
                            j = 0;
                            rx_cnt = 0;
                            rx_offset = 0;
                            InputData[0] = 0x00;
                            break;
                        }
                        InputData[k + rx_offset] = InputBuf[k + j];
                        if (k + rx_offset + 1 == rx_ack_num) //接收完整ACK
                        {
                            rx_ack_num = 0;
                            rx_offset = 0;
                            InputData[0] = 0x00;
                            flag_rx_done = 1;
                            break;
                        }
                    }
                    if (flag_rx_done != 1) rx_offset += rx_cnt - j; //如果没有接收完成，下一包数据继续放入InputData。
                    break;
                }
            }
            string strdata = "";
            for (int i = 0; i < rx_cnt; i++)
            {
                strdata += InputBuf[i].ToString("X2") + " ";
            }
            this.BeginInvoke(new Action(() =>
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口接收数据：");
                DP_DataRecord.AppendText(strdata + "\r\n");
            }));

            if (flag_rx_done == 1)
            {
                flag_rx_done = 0;
                this.BeginInvoke(new Action(() =>
                {
                    Uart1ReciceData_Check(InputData);
                }));
            }
        }

        private void Uart1ReciceData_Check(byte[] buff)
        {
            EnDis_Timer1(false); 
            switch (tx_cmd)
            { 
                case 1:
                case 2:
                case 3: //应答;01 10 00 00 00 20 C1 D1
                    tx_cmd = 0;
                    if (buff[1] == 0x10 && buff[6] == 0xC1 && buff[7] == 0xCF)
                    {
                        //DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器模块应答正确！");
                    }
                    else
                    {
                        flag_err = 1;
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器模块应答错误！\r\n");
                    }
                    break;

                case 4: //应答口1 输入0：01 04 02 00 00 B9 30 //输入1：01 04 02 00 01 78 F0
                    tx_cmd = 0;
                    if (buff[1] == 0x04 && buff[4] == 0x00 && buff[5] == 0xB9 && buff[6] == 0x30)
                    {
                        flag_err = 1;
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 灵敏度测试 NG\r\n");
                    }
                    else if (buff[1] == 0x04 && buff[4] == 0x01 && buff[5] == 0x78 && buff[6] == 0xF0)
                    {
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 灵敏度测试 OK\r\n");
                    }
                    else {
                        flag_err = 1;
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器模块应答错误！\r\n");
                    }
                    break;
                default: break;
            }
        }
        private void EnDis_Timer1(bool endis)
        {
            if (endis == true)
            {
                if (timer1.Enabled != true)
                {
                    timer1.Enabled = true;
                }
                timer1.Interval = 300;
            }
            else
            {
                timer1.Enabled = false;
            }
        }
        private void port2_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收处理
        {
            int rx_cnt = 0;
            char[] InputBuf = new char[64];
            rx_cnt = serialPort2.BytesToRead;
            if (rx_cnt > 64) rx_cnt = 64;
            serialPort2.Read(InputBuf, 0, rx_cnt);

            string strdata = ""; ;
            for (int i = 0; i < rx_cnt; i++)
            {
                strdata += InputBuf[i];
            }
            this.BeginInvoke(new Action(() =>
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫码枪数据：");
                DP_DataRecord.AppendText(strdata + "\r\n");
                DP_ScanCode.Text = strdata;
                try
                {
                    ID_DEC = Convert.ToInt32(DP_ScanCode.Text.ToString());
                }
                catch
                {}
                if ((ID_DEC < 1) || (ID_DEC > 16777213))
                {
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    MessageBox.Show("出错，ID超出范围1～16777213！");
                }
                else if (ID_Selcet_comboBox.Text.ToString() == "")
                {
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    MessageBox.Show("出错，没有选择机种！");
                }
                else if (((ID_Selcet_comboBox.Text.ToString() == "STX0011") && ((ID_DEC < 11000000) || (ID_DEC > 11999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0011-SR") && ((ID_DEC < 11000000) || (ID_DEC > 11999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0011-SSR") && ((ID_DEC < 11000000) || (ID_DEC > 11999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0011-SSH") && ((ID_DEC < 11000000) || (ID_DEC > 11999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0031") && ((ID_DEC < 13000000) || (ID_DEC > 14999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0031-SR") && ((ID_DEC < 13000000) || (ID_DEC > 14999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0031-SSR") && ((ID_DEC < 13000000) || (ID_DEC > 14999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX0031-SSH") && ((ID_DEC < 13000000) || (ID_DEC > 14999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1231(A)") && ((ID_DEC < 15000000) || (ID_DEC > 15999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1531K") && ((ID_DEC < 2000000) || (ID_DEC > 2999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1531K-SR") && ((ID_DEC < 2000000) || (ID_DEC > 2999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1531K-SSR") && ((ID_DEC < 2000000) || (ID_DEC > 2999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1531K-SSH") && ((ID_DEC < 2000000) || (ID_DEC > 2999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "CTX1531TN") && ((ID_DEC < 3000000) || (ID_DEC > 3999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1631PB") && ((ID_DEC < 4000000) || (ID_DEC > 4999999))) ||
                         ((ID_Selcet_comboBox.Text.ToString() == "STX1731(A)") && ((ID_DEC < 15100000) || (ID_DEC > 15199999))) )
                {
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    MessageBox.Show("出错，扫描的二维码ID与选择机种ID不一致！");
                }
                else if (serialPort1.IsOpen && serialPort3.IsOpen && flag_err == 0)
                {
                    if (flag_auto_start == 0)
                    {
                        if (flag_one != 0)
                        {
                            DP_DataRecord.Text = "";
                            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫码枪数据：");
                            DP_DataRecord.AppendText(strdata + "\r\n");
                            DP_ScanCode.Text = strdata;
                        }
                        flag_one = 1;
                        DP_DataRecord.BackColor = Color.Black;
                        Display_Results.Text = "  ";
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + "  机型：" + ID_Selcet_comboBox.Text.ToString() + "\r\n");
                        flag_auto_start = 1;
                        AutoTest_Step = 1;
                        timer2.Enabled = true;
                        flag_err = 0;
                    }
                }
                else if (flag_err == 3 || flag_err == 4 || flag_err == 5)
                {
                    //DP_DataRecord.BackColor = Color.LimeGreen;
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    if (flag_err == 3) MessageBox.Show("出错，频谱仪RSA3xxx 未连接！");
                    if (flag_err == 4) MessageBox.Show("出错，信号源DSG3xxx 未连接！");
                    if (flag_err == 5) MessageBox.Show("出错，数字万用表DM3xxx 未连接！");
                    this.Close(); //直接关闭窗体
                }
                else
                {
                    //DP_DataRecord.BackColor = Color.LimeGreen;
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    flag_err = 0;
                    MessageBox.Show("出错，继电器串口 或 写ID串口 未打开！");
                }
            }));
        }

        private void port3_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收处理
        {
            int rx_cnt = 0;
            byte[] InputBuf = new byte[64];
            rx_cnt = serialPort3.BytesToRead;
            if (rx_cnt > 64) rx_cnt = 64;
            serialPort3.Read(InputBuf, 0, rx_cnt);

            string strdata = "";
            //for (int i = 0; i < rx_cnt; i++)
            //{
            //    strdata += InputBuf[i].ToString("X2") + " ";
            //}
            strdata = System.Text.Encoding.Default.GetString(InputBuf);
            this.BeginInvoke(new Action(() =>
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口接收数据："+ strdata );
                DP_DataRecord.AppendText("\r\n");
                UART3_WriteID_Received_textBox.AppendText(strdata);
            }));
        }

        private void DP_Uart1_comboBox1_Click(object sender, EventArgs e)
        {
            DP_Uart1_comboBox1.Items.Clear();
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close();
                }
                catch { }
            }
            //DP_Uart_OpenClose.BackColor = Color.LightSteelBlue;
            //DP_Uart_OpenClose.Text = "已关";
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口端口选择\r\n");
            DP_Uart1_comboBox1.Enabled = true;
            using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from Win32_PnPEntity"))
            {
                var hardInfos = searcher.Get();
                int index = 1;
                foreach (var hardInfo in hardInfos)
                {
                    if (hardInfo.Properties["Name"].Value != null && hardInfo.Properties["Name"].Value.ToString().Contains("(COM"))
                    {
                        String strComName = hardInfo.Properties["Name"].Value.ToString();
                        DP_Uart1_comboBox1.Items.Add(strComName); ;//给comboBox1添加选项,串口设备名称及串口号
                        index += 1;
                    }
                }
            }
        }

        private void DP_Uart2_comboBox2_Click(object sender, EventArgs e)
        {
            DP_Uart2_comboBox2.Items.Clear();
            if (serialPort2.IsOpen)
            {
                try
                {
                    serialPort2.Close();
                }
                catch { }
            }
            //DP_Uart_ScanCode.BackColor = Color.LightSteelBlue;
            //DP_Uart_ScanCode.Text = "已关";
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫描枪串口端口选择\r\n");
            DP_Uart2_comboBox2.Enabled = true;
            using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from Win32_PnPEntity"))
            {
                var hardInfos = searcher.Get();
                int index = 1;
                foreach (var hardInfo in hardInfos)
                {
                    if (hardInfo.Properties["Name"].Value != null && hardInfo.Properties["Name"].Value.ToString().Contains("(COM"))
                    {
                        String strComName = hardInfo.Properties["Name"].Value.ToString();
                        DP_Uart2_comboBox2.Items.Add(strComName); ;//给comboBox1添加选项,串口设备名称及串口号
                        index += 1;
                    }
                }
            }
        }

        private void DP_Uart3_comboBox3_Click(object sender, EventArgs e)
        {
            DP_Uart3_comboBox3.Items.Clear();
            if (serialPort3.IsOpen)
            {
                try
                {
                    serialPort3.Close();
                }
                catch { }
            }
            //DP_Uart_ScanCode.BackColor = Color.LightSteelBlue;
            //DP_Uart_ScanCode.Text = "已关";
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口端口选择\r\n");
            DP_Uart3_comboBox3.Enabled = true;
            using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from Win32_PnPEntity"))
            {
                var hardInfos = searcher.Get();
                int index = 1;
                foreach (var hardInfo in hardInfos)
                {
                    if (hardInfo.Properties["Name"].Value != null && hardInfo.Properties["Name"].Value.ToString().Contains("(COM"))
                    {
                        String strComName = hardInfo.Properties["Name"].Value.ToString();
                        DP_Uart3_comboBox3.Items.Add(strComName); ;//给comboBox1添加选项,串口设备名称及串口号
                        index += 1;
                    }
                }
            }
        }

        private void DP_Uart_OpenClose_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close();
                }
                catch { }
                DP_Uart_OpenClose.BackColor = Color.LightSteelBlue;
                DP_Uart_OpenClose.Text = "已关";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口 已关闭\r\n");
                EnDis_TestMode(false);
                EnDis_Button(false);
                DP_Uart1_comboBox1.Enabled = true;
            }
            else
            {
                try
                {
                    String strComName = DP_Uart1_comboBox1.Text;//更改端口名称
                    int p = strComName.IndexOf('(');
                    serialPort1.PortName = strComName.Substring(p + 1, strComName.Length - p - 2); //截取串口号 
                    serialPort1.Open();
                    DP_Uart_OpenClose.BackColor = Color.LightGreen;
                    DP_Uart_OpenClose.Text = "已开";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口 " + DP_Uart1_comboBox1.Text + " 已打开\r\n");
                    EnDis_TestMode(true);
                    DP_Uart1_comboBox1.Enabled = false;
                    //AutoTest_Step = 1;
                    //timer2.Enabled = true;
                }
                catch
                {
                    EnDis_TestMode(false);
                    DP_Uart1_comboBox1.Enabled = true;
                    DP_Uart_OpenClose.Text = "已关";
                    DP_Uart_OpenClose.BackColor = Color.LightSteelBlue;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口 " + DP_Uart1_comboBox1.Text + " 打开失败\r\n");
                    MessageBox.Show("出错，继电器串口 打开失败,请重新选择端口！");
                    DP_Uart1_comboBox1.Items.Clear();
                    DP_Uart1_comboBox1.Text = "";
                }
            }
        }

        private void DP_Uart_ScanCode_Click(object sender, EventArgs e)
        {
            if (serialPort2.IsOpen)
            {
                try
                {
                    serialPort2.Close();
                }
                catch { }
                DP_Uart_ScanCode.BackColor = Color.LightSteelBlue;
                DP_Uart_ScanCode.Text = "已关";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫描枪串口 已关闭\r\n");
                DP_Uart2_comboBox2.Enabled = true;
                //EnDis_TestMode(false);
                //EnDis_Button(false);
            }
            else
            {
                try
                {
                    String strComName = DP_Uart2_comboBox2.Text;//更改端口名称
                    int p = strComName.IndexOf('(');
                    serialPort2.PortName = strComName.Substring(p + 1, strComName.Length - p - 2); //截取串口号
                    serialPort2.Open();
                    DP_Uart_ScanCode.BackColor = Color.LightGreen;
                    DP_Uart_ScanCode.Text = "已开";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫描枪串口 " + DP_Uart2_comboBox2.Text + " 已打开\r\n");
                    DP_Uart2_comboBox2.Enabled = false;
                    //EnDis_TestMode(true);
                }
                catch
                {
                    //EnDis_TestMode(false);
                    DP_Uart2_comboBox2.Enabled = true;
                    DP_Uart_ScanCode.Text = "已关";
                    DP_Uart_ScanCode.BackColor = Color.LightSteelBlue;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 扫描枪串口 " + DP_Uart2_comboBox2.Text + " 打开失败\r\n");
                    MessageBox.Show("出错，扫描枪串口 打开失败,请重新选择端口！");
                    DP_Uart2_comboBox2.Items.Clear();
                    DP_Uart2_comboBox2.Text = "";
                }
            }
        }

        private void DP_Uart_WriteID_Click(object sender, EventArgs e)  //UART3
        {
            if (serialPort3.IsOpen)
            {
                try
                {
                    serialPort3.Close();
                }
                catch { }
                DP_Uart_WriteID.BackColor = Color.LightSteelBlue;
                DP_Uart_WriteID.Text = "已关";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口 已关闭\r\n");
                DP_Uart3_comboBox3.Enabled = true;
                //EnDis_TestMode(false);
                //EnDis_Button(false);
            }
            else
            {
                try
                {
                    String strComName = DP_Uart3_comboBox3.Text;//更改端口名称
                    int p = strComName.IndexOf('(');
                    serialPort3.PortName = strComName.Substring(p + 1, strComName.Length - p - 2); //截取串口号
                    serialPort3.Open();
                    DP_Uart_WriteID.BackColor = Color.LightGreen;
                    DP_Uart_WriteID.Text = "已开";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口 " + DP_Uart3_comboBox3.Text + " 已打开\r\n");
                    DP_Uart3_comboBox3.Enabled = false;
                    //EnDis_TestMode(true);
                }
                catch
                {
                    //EnDis_TestMode(false);
                    DP_Uart3_comboBox3.Enabled = true;
                    DP_Uart_WriteID.Text = "已关";
                    DP_Uart_WriteID.BackColor = Color.LightSteelBlue;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口 " + DP_Uart3_comboBox3.Text + " 打开失败\r\n");
                    MessageBox.Show("出错，写ID串口 打开失败,请重新选择端口！");
                    DP_Uart3_comboBox3.Items.Clear();
                    DP_Uart3_comboBox3.Text = "";
                }
            }
        }

        private void serialPort1_tx_data(byte[] data, int length)
        {
            if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
            {
                try
                {
                    serialPort1.Write(data, 0, length); //发送数据
                }
                catch
                {
                    flag_err = 1;
                    MessageBox.Show("继电器串口 数据发送出错，请检查.", "错误");//错误处理
                }
            }
            else
            {
                DP_Uart_OpenClose.Text = "已关";
                //DP_Uart_OpenClose.BackColor = BackClolor_OFF;
                EnDis_Button(false);
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 出错：继电器串口已断开\r\n");
                MessageBox.Show("出错：继电器串口已断开！");
                flag_err = 1;
            }
        }
        private void TEST_Mode_Click(object sender, EventArgs e)
        {
            EnDis_Button(true);
            EnDis_TestMode(false);
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 进入测试模式\r\n");
            //byte[] tx_data = { 0x01, 0x02, 0x00, 0xc4, 0x00, 0x16, 0xb8, 0x39 };
            //serialPort1_tx_data(tx_data, tx_data.Length);
        }
        private void EXIT_TEST_Click(object sender, EventArgs e)
        {
            EnDis_TestMode(true);
            EnDis_Button(false);
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 退出测试模式\r\n");
        }
        private void Tx_Carrier_Click(object sender, EventArgs e)
        {
            Tx_Carrier_Uart1();
        }
        private void Tx_Carrier_Uart1()
        {
            //发送载波,TP3->继电器1=0,TP4->继电器2=0.
            UInt16 crc = 0;                     //关闭继电器1、2 (地址从00开始，两个) 
            byte[] tx_data = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            crc = CRC16.GetCRC16_Value(tx_data, tx_data.Length - 2);
            tx_data[tx_data.Length - 2] = (byte)(crc >> 8 & 0xff);
            tx_data[tx_data.Length - 1] = (byte)(crc & 0xff);
            serialPort1_tx_data(tx_data, tx_data.Length); //应答：01 10 00 00 00 02 41 C8
            tx_cmd = 1;
            rx_ack_num = 8; //需要接收继电器模块应答8个字节
            //cvisa_opt.Opt_Set("RSA3", "ON");
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送载波\r\n");
            EnDis_Timer1(true);
        }
        private void Tx_Modula_Click(object sender, EventArgs e)
        {
            Tx_Modula_Uart1();
        }
        private void Tx_Modula_Uart1()
        {
            //发送载波和调制,TP3->继电器1=1,TP4->继电器2=0.
            UInt16 crc = 0;
            byte[] tx_data = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
            crc = CRC16.GetCRC16_Value(tx_data, tx_data.Length - 2);
            tx_data[tx_data.Length - 2] = (byte)(crc >> 8 & 0xff);
            tx_data[tx_data.Length - 1] = (byte)(crc & 0xff);
            serialPort1_tx_data(tx_data, tx_data.Length); //应答：01 10 00 00 00 02 41 C8
            tx_cmd = 2;
            rx_ack_num = 8;
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送调制\r\n");
            EnDis_Timer1(true);
        }
        private void Tx_Rece_Sensit_Click(object sender, EventArgs e)
        {
            Tx_Rece_Sensit_Uart1();
        }
        private void Tx_Rece_Sensit_Uart1()
        {
            //接收灵敏度,TP3->继电器1=1,TP4->继电器2=1.
            UInt16 crc = 0;
            byte[] tx_data = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00 };
            crc = CRC16.GetCRC16_Value(tx_data, tx_data.Length - 2);
            tx_data[tx_data.Length - 2] = (byte)(crc >> 8 & 0xff);
            tx_data[tx_data.Length - 1] = (byte)(crc & 0xff);
            serialPort1_tx_data(tx_data, tx_data.Length); //应答：01 10 00 00 00 02 41 C8
            tx_cmd = 3;
            rx_ack_num = 8;
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 接收灵敏度测试\r\n");
            EnDis_Timer1(true);
        }
        private void Tx_Read_Rece_Sensit() //读取继电器输入，灵敏度判断
        {
            Tx_Read_Rece_Uart1();
        }
        private void Tx_Read_Rece_Uart1()
        {
            UInt16 crc = 0;
            byte[] tx_data = { 0x01, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };
            crc = CRC16.GetCRC16_Value(tx_data, tx_data.Length - 2);
            tx_data[tx_data.Length - 2] = (byte)(crc >> 8 & 0xff);
            tx_data[tx_data.Length - 1] = (byte)(crc & 0xff);
            serialPort1_tx_data(tx_data, tx_data.Length);
            tx_cmd = 4;
            rx_ack_num = 7; //需要接收继电器模块应答7个字节
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读输入\r\n");
            EnDis_Timer1(true);
            //应答口1输入0：01 04 02 00 00 B9 30
            //应答口1输入1：01 04 02 00 01 78 F0
        }

        private void DP_Uart1_comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void DP_Uart2_comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void EnDis_TestMode(bool tf)
        {
            if (tf == true)
            {
                TEST_Mode.Enabled = true;
                TEST_Mode.BackColor = BackClolor_ON;
            }
            else {
                TEST_Mode.Enabled = false;
                TEST_Mode.BackColor = BackClolor_OFF;
            }
        }
        private void EnDis_Button(bool sw)
        {
            if (sw == true)
            {
                Tx_Carrier.Enabled = true;
                Tx_Carrier.BackColor = BackClolor_ON;
                Tx_Modula.Enabled = true;
                Tx_Modula.BackColor = BackClolor_ON;
                Tx_Rece_Sensit.Enabled = true;
                Tx_Rece_Sensit.BackColor = BackClolor_ON;
                EXIT_TEST.Enabled = true;
                EXIT_TEST.BackColor = BackClolor_ON;
                SignlSource_GroupBox.Enabled = true;
            }
            else {
                Tx_Carrier.Enabled = false;
                Tx_Carrier.BackColor = BackClolor_OFF;
                Tx_Modula.Enabled = false;
                Tx_Modula.BackColor = BackClolor_OFF;
                Tx_Rece_Sensit.Enabled = false;
                Tx_Rece_Sensit.BackColor = BackClolor_OFF;
                EXIT_TEST.Enabled = false;
                EXIT_TEST.BackColor = BackClolor_OFF;
                SignlSource_GroupBox.Enabled = false;
            }
        }
        private void DP_DataRecord_TextChanged(object sender, EventArgs e){ }

        private void timer3_Tick(object sender, EventArgs e)
        {
            SendKeys.Send("{Enter}"); //输出Enter(回车键),不用手动按键盘回车保存文件。
            timer3.Enabled = false;
        }
        private void OutPut_Data_Click(object sender, EventArgs e)
        {
            Save_Data("OK");
        }
        private void Save_Data(string OK_NG)
        {
            SaveFileDialog saveFile1 = new SaveFileDialog();
            saveFile1.Filter = "Excel files (*.csv)|*.csv";
            saveFile1.FilterIndex = 1;
            saveFile1.RestoreDirectory = true; //保存对话框是否记忆上次打开的目录
            //saveFile1.Title = "保存为csv文件";
            //DP_ScanCode.Text = "C2023007";
            saveFile1.FileName = "文化送信机无线测试 " + DP_ScanCode.Text + "  " + DateTime.Now.ToString("yyyy-MM-dd HH.mm.ss"); //年月日时分秒
            saveFile1.InitialDirectory = Application.StartupPath + "\\STX0031\\"+ OK_NG;//"D:\\CY2201_CY2202"; //保存至目录文件夹(D:\\MyWork)

            timer3.Enabled = true;
            if (saveFile1.ShowDialog() == System.Windows.Forms.DialogResult.OK && saveFile1.FileName.Length > 0)
            {
                System.IO.StreamWriter sWriter = new System.IO.StreamWriter(saveFile1.FileName, false, System.Text.Encoding.GetEncoding(-0));

                try{
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 记录已保存到 " + saveFile1.FileName + "\r\n");
                    sWriter.WriteLine(DP_DataRecord.Text); //要输出的内容
                    //MessageBox.Show("记录已保存到 " + saveFile1.FileName);
                }
                catch
                {
                    throw;
                }
                finally
                {
                    sWriter.Close();
                }
            }
        }

        /*
        private void OutPut_Data_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile1 = new SaveFileDialog();
            saveFile1.Filter = "文本文件(.txt)|*.txt";
            saveFile1.FilterIndex = 1;
            saveFile1.FileName = DateTime.Now.ToString("yyyy.MM.dd ") + DP_ScanCode.Text;
            if (saveFile1.ShowDialog() == System.Windows.Forms.DialogResult.OK && saveFile1.FileName.Length > 0)
            {
                System.IO.StreamWriter sw = new System.IO.StreamWriter(saveFile1.FileName, false);
                try
                {
                    sw.WriteLine(DP_DataRecord.Text); //要输出的内容
                }
                catch
                {
                    throw;
                }
                finally
                {
                    sw.Close();
                }
            }
        }*/

        private void Clear_Data_Click(object sender, EventArgs e)
        {
            DialogResult MsgBoxResult;//设置对话框的返回值
            if (DP_DataRecord.Text != "")   //不为空就提示
            {
                MsgBoxResult = System.Windows.Forms.MessageBox.Show("是否清除数据？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2);//定义对话框的按钮式样
                if (MsgBoxResult.ToString() == "Yes")//如果对话框的返回值是YES（按"Y"按钮）
                {
                    //选择了Yes，继续
                    DP_DataRecord.Text = "";    //清空文本
                }
                if (MsgBoxResult.ToString() == "No")//如果对话框的返回值是NO（按"N"按钮）
                {
                    //选择了No，继续
                }
            }
        }
        private void Tx_Read_Click(object sender, EventArgs e)
        {
            Tx_Read_Freq();
        }
        private void Tx_Read_Freq()
        {
            double heart=0,min = 0, max=0;

            freq_opt_stu = cvisa_opt.Opt_GetFreq("RSA3");
            //DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送功率：" + freq_opt_stu.get_dbm + "\r\n");
            //DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送频率：" + freq_opt_stu.get_hz + "\r\n");
            double freqnum = double.Parse(freq_opt_stu.get_hz,System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
            double powernum = double.Parse(freq_opt_stu.get_dbm, System.Globalization.NumberStyles.Float);
            freqnum = freqnum / 1000000; //MHz
            DP_Freq.Text = freqnum.ToString();
            DP_Power.Text = powernum.ToString();//("0.00"); //"0.00"保留两位小数
            
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取频率值：" + DP_Freq.Text.ToString() + "MHz\r\n");
            
            if(RY_count==1)
            {
                if ((ID_Selcet_comboBox.Text.ToString() == "STX0011-SSR") || (ID_Selcet_comboBox.Text.ToString() == "STX0031-SSR") || (ID_Selcet_comboBox.Text.ToString() == "STX1531K-SSR") ||
                  (ID_Selcet_comboBox.Text.ToString() == "STX0011-SSH") || (ID_Selcet_comboBox.Text.ToString() == "STX0031-SSH") || (ID_Selcet_comboBox.Text.ToString() == "STX1531K-SSH"))
                    heart = 426.075;
                else
                    heart = 426.0726;
                min = heart - Freq_MIN_DEF[RY_count];
                max = heart + Freq_MAX_DEF[RY_count];
                freqnum_bak = freqnum;
            }
            else if (RY_count == 2)
            {
                if (freqnum < freqnum_bak)
                {
                    min = freqnum_bak - Freq_MIN_DEF[RY_count]- Freq_MIN_DEF[RY_count-1];
                    max = freqnum_bak - Freq_MAX_DEF[RY_count]+ Freq_MAX_DEF[RY_count-1];
                }
                else
                {
                    min = freqnum_bak + Freq_MIN_DEF[RY_count] - Freq_MIN_DEF[RY_count - 1];
                    max = freqnum_bak + Freq_MAX_DEF[RY_count] + Freq_MAX_DEF[RY_count - 1];
                }
            }
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 频率要求最大值：" + max.ToString() + "MHz 最小值：" + min.ToString() + "MHz\r\n");
            if ( freqnum< min)
            {
                flag_err = 1;
                DP_FreqOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 频率检查: NG, 超出最小值\r\n");
            }
            else if(freqnum > max)
            {
                flag_err = 1;
                DP_FreqOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 频率检查: NG, 超出最大值\r\n");
            }
            else
            {
                DP_FreqOKNG.Text = "OK";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 频率检查: OK\r\n");
            }
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 功率要求最大值：" + PA_MAX_DEF[RY_count].ToString() + "dBm 最小值：" + PA_MIN_DEF[RY_count].ToString() + "dBm\r\n");
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取功率值：" + DP_Power.Text.ToString() + "dBm\r\n");
            if (powernum < PA_MIN_DEF[RY_count])
            {
                flag_err = 1;
                DP_PowerOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 功率检查: NG, 超出最小值\r\n");
            }
            else if(powernum> PA_MAX_DEF[RY_count])
            {
                flag_err = 1;
                DP_PowerOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 功率检查: NG, 超出最大值\r\n");
            }
            else
            {
                DP_PowerOKNG.Text = "OK";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "; 功率检查: OK\r\n");
            }
        }
        private void OPEN_radioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rab = sender as RadioButton;
            if (rab.Checked)
            {
                string textname = rab.Text;
                if (textname == "打开")
                {
                    cvisa_opt.Opt_Set("DSG3", "ON");
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 打开信号源\r\n");
                }
                else
                {
                    cvisa_opt.Opt_Set("DSG3", "OFF");
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 关闭信号源\r\n");
                }
            }
        }

        private void CLOSE_radioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rab = sender as RadioButton;
            if (rab.Checked)
            {
                string textname = rab.Text;
                if (textname == "打开")
                {
                    cvisa_opt.Opt_Set("DSG3", "ON");
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 打开信号源\r\n");
                }
                else
                {
                    cvisa_opt.Opt_Set("DSG3", "OFF");
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 关闭信号源\r\n");
                }
            }
        }

        private void SignlSource_GroupBox_Enter(object sender, EventArgs e){}

        private void timer1_Tick(object sender, EventArgs e)
        {
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器模块应答超时！\r\n");
            EnDis_Timer1(false);
            rx_offset = 0;
            flag_err = 1;
        }

        private void DP_FreqON_CheckedChanged(object sender, EventArgs e){}

        private void RY_Uart1(int count,int reset)
        {
            if (serialPort1.IsOpen)
            {
                int i = 0;
                //发送载波,TP3->继电器1=0,TP4->继电器2=0.
                UInt16 crc = 0;                     //关闭继电器1、2 (地址从00开始，两个) 
                tx_data[5] = RY_number_DEF;
                tx_data[6] = RY_number_DEF * 2;
                for (i = 0; i < RY_number_DEF; i++)
                {
                    if (reset == 1)
                    {
                        if (RY_reset1[i] != 0)
                            tx_data[8 + i * 2] = 0x01;
                        else
                            tx_data[8 + i * 2] = 0x00;
                    }
                    else if (reset == 2)
                    {
                        if (RY_reset2[i] != 0)
                            tx_data[8 + i * 2] = 0x01;
                        else
                            tx_data[8 + i * 2] = 0x00;
                    }
                    else
                    {
                        if ((ID_Selcet_comboBox.Text.ToString() == "STX1731(A)")&&(count>=1))
                        {
                            if (RY_data[1, i] != 0)
                                tx_data[8 + i * 2] = 0x01;
                            else
                                tx_data[8 + i * 2] = 0x00;
                        }
                        else
                        {
                            if (RY_data[count, i] != 0)
                                tx_data[8 + i * 2] = 0x01;
                            else
                                tx_data[8 + i * 2] = 0x00;
                        }
                    }
                }
                crc = CRC16.GetCRC16_Value(tx_data, tx_data.Length - 2);
                tx_data[tx_data.Length - 2] = (byte)(crc >> 8 & 0xff);
                tx_data[tx_data.Length - 1] = (byte)(crc & 0xff);
                serialPort1_tx_data(tx_data, tx_data.Length); //应答：01 10 00 00 00 02 41 C8
                tx_cmd = 1;
                rx_ack_num = 8; //需要接收继电器模块应答8个字节
                                //cvisa_opt.Opt_Set("RSA3", "ON");
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " Step" + (count+1).ToString() + "\r\n");
                //DP_DataRecord.AppendText(DateTime.Now.ToString() + "  继电器发送" + String.Join(", ", tx_data) + "\r\n");  //调试用
                string hexOutput = " ";
                for (i = 0; i < tx_data.Length; i++)
                {
                    hexOutput += tx_data[i].ToString("X2") + " ";

                }
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "  继电器发送:  " + hexOutput + "\r\n");
                EnDis_Timer1(true);
            }
            else
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器串口 未打开！\r\n");
            }
        }

        private void WriteID_Uart3(string string_str)
        {
            if (serialPort3.IsOpen)
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + "  写ID串口发送:  " + string_str + "\r\n");
                serialPort3.Write(string_str);
            }
            else
            {
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID串口 未打开！\r\n");
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            //Freq_AutoTest_Start();
            //Rx_AutoTest_Start();
            STX0031_Wireless();
        }
        private void STX0031_Wireless()
        {
            string str_res, str_res1="", str_res2;

            switch (AutoTest_Step)
            {
                case 1:
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 无线发射自动测试开始！\r\n");
                    timer2.Interval = 50;
                    cvisa_opt.Opt_CONFigureIVdc("DM3", "CONFigure:CURRent:DC 2mA");
                    RY_count = 0;
                    RY_repeat = 0;
                    AutoTest_Step = 2;
                    break;

                case 2:
                    RY_Uart1(RY_count,0);
                    timer2.Interval = 100;
                    AutoTest_Step = 3;
                    break;
                case 3:
                    if (flag_err == 0)
                    {
                        if (RY_count == 0)
                            AutoTest_Step = 6;
                        else
                        {
                            timer2.Interval = 100;
                            AutoTest_Step = 4;
                        }
                    }
                    else
                    {
                        timer2.Interval = 50;
                        AutoTest_Step = 220; //exit
                    }
                    break;
                case 4:
                    if (RY_count == RY_count_DEF - 1)  //写ID之前把Uart的数据通信线的继电器Y7,Y8 ON；为什么在Uart数据通信线加继电器，防止在测试待机漏电流时UART漏电过去。
                    {
                        RY_reset1[6] = 7;
                        RY_reset1[7] = 8;
                    }
                    RY_Uart1(RY_count, 1); //继电器reset1
                    timer2.Interval = 100;
                    AutoTest_Step = 5;
                    break;
                case 5:
                    if (flag_err == 0)
                    {
                        timer2.Interval = 300;
                        AutoTest_Step = 6;
                    }
                    else
                    {
                        timer2.Interval = 50;
                        AutoTest_Step = 220; //exit
                    }
                    break;
                case 6:
                    Tx_Read_IV("I");
                    if (RY_count==1) Tx_Read_Freq();
                    timer2.Interval = 100;
                    AutoTest_Step = 7;
                    break;
                case 7:
                    if (flag_err == 0)
                    {
                        timer2.Interval = 100;
                        RY_count++;
                        if(RY_count==1)
                            cvisa_opt.Opt_CONFigureIVdc("DM3", "CONFigure:CURRent:DC 20mA");
                        if (RY_count >= RY_count_DEF)
                            AutoTest_Step = 50;//写ID
                        else
                            AutoTest_Step = 2;
                    }
                    else
                    {
                        timer2.Interval = 50;
                        AutoTest_Step = 220; //exit
                    }
                    break;

                case 50:  // 写ID
                    UART3_WriteID_Received_textBox.Text = "";
                    ID_HEX = ID_DEC.ToString("X6");
                    WriteID_Uart3("(WG"+ ID_HEX + ")");
                    timer2.Interval = 200;
                    AutoTest_Step = 51;
                    break;
                case 51:
                    str_res = UART3_WriteID_Received_textBox.Text.ToString();
                    try
                    {
                        str_res1 = str_res.Substring(0, 4);
                    }
                    catch
                    { }
                    timer2.Interval = 30;
                    if ((str_res1 == "(WG)")|| (str_res1 == "(OK)"))
                        AutoTest_Step = 52;
                    else
                    {
                        AutoTest_Step = 220;
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID错误！\r\n");
                        flag_err = 1;
                    }
                    break;
                case 52:
                    UART3_WriteID_Received_textBox.Text = "";
                    WriteID_Uart3("(RG)");
                    timer2.Interval = 200;
                    AutoTest_Step = 53;
                    break;
                case 53:
                    str_res = UART3_WriteID_Received_textBox.Text.ToString();
                    str_res1 = str_res.Substring(0, 10);
                    str_res2 = "(RG)" + ID_HEX;
                    timer2.Interval = 30;
                    if (str_res1 == str_res2)
                        AutoTest_Step = 250;
                    else
                    {
                        AutoTest_Step = 220;
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 写ID错误！\r\n");
                        flag_err = 1;
                    }
                    break;

                case 220:
                    RY_Uart1(RY_count, 2);  //继电器reset2
                    timer2.Interval = 500;
                    RY_repeat++;
                    if (RY_repeat <= 1)
                    {
                        AutoTest_Step = 2;
                        RY_count = 0;
                        flag_err = 0;
                        cvisa_opt.Opt_CONFigureIVdc("DM3", "CONFigure:CURRent:DC 2mA");
                        DP_DataRecord.AppendText(DateTime.Now.ToString() + " 测试结果NG，重测一次！\r\n");
                    }
                    else
                        AutoTest_Step = 221;
                    break;
                case 221:
                    timer2.Enabled = false;
                    AutoTest_Step = 0;
                    flag_auto_start = 0;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 测试结果NG，自动测试结束！\r\n");
                    Display_Results.Text = "NG";
                    NG_count++;
                    NG_num.Text = NG_count.ToString();
                    if (flag_err == 0) DP_DataRecord.BackColor = Color.LimeGreen;
                    else DP_DataRecord.BackColor = Color.Red;
                    flag_err = 0;
                    Save_Data("NG");
                    break;
                case 250:
                    RY_Uart1(RY_count, 2);  //继电器reset2
                    timer2.Interval = 500;
                    AutoTest_Step = 251;
                    break;
                case 251:
                    timer2.Enabled = false;
                    AutoTest_Step = 0;
                    flag_auto_start = 0;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + "  测试结果OK，自动测试结束！\r\n");
                    Display_Results.Text = "OK";
                    OK_count++;
                    OK_num.Text = OK_count.ToString();
                    if (flag_err == 0) DP_DataRecord.BackColor = Color.LimeGreen;
                    else DP_DataRecord.BackColor = Color.Red;
                    flag_err = 0;
                    Save_Data("OK");
                    //MessageBox.Show("发射频率自动测试结束！");
                    break;
                default: break;
            }
        }
        private void Tx_Read_ReceSensit_Click(object sender, EventArgs e)
        {
            Tx_Read_Rece_Sensit();
        }
        //AutoTest_Step
        private void Freq_AutoTest_Start()
        {
            switch (AutoTest_Step)
            { 
                case 1:
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发射频率自动测试开始！\r\n");
                    Tx_Carrier_Uart1();
                    AutoTest_Step = 2;
                    break;

                case 2:
                    Tx_Read_IV("I");
                    AutoTest_Step = 3;
                    break;

                case 3:
                    Tx_Read_Freq();
                    timer2.Enabled = false;
                    AutoTest_Step = 0;
                    flag_auto_start = 0;
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发射频率自动测试结束！\r\n");
                    if (flag_err == 0) DP_DataRecord.BackColor = Color.LimeGreen;
                    else DP_DataRecord.BackColor = Color.Red;
                    flag_err = 0;
                    Save_Data("OK");
                    MessageBox.Show("发射频率自动测试结束！");
                    break;
                default: break;
            }
        }
        private void Rx_AutoTest_Start()
        {
            switch (AutoTest_Step)
            {
                case 1:
                    Tx_Rece_Sensit_Uart1();
                    AutoTest_Step = 2;
                    break;

                case 2:
                    Tx_Read_Rece_Sensit();
                    timer2.Enabled = false;
                    AutoTest_Step = 0;
                    flag_auto_start = 0;
                    break;
                default: break;
            }
        }
        private void Tx_ReadIV_Click(object sender, EventArgs e)
        {
            Tx_Read_IV("I");
        }
        private void Tx_Read_IV(string iv)
        {
            int RY_n = 0;

            if (iv == "V")
            {
                string read_v = "", read_v1 = "";
                read_v1 = cvisa_opt.Opt_GetIVdc("DM3", "V",""); //read_v = #9000000015-4.59713983e-04
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电压原始值：" + read_v1 + "\r\n");
                if (read_v1.IndexOf("#") != -1)
                    read_v = read_v1.Remove(read_v1.IndexOf("#"), 12); //从第0个开始，删除12个，留下后面的。//单位V
                else
                    read_v = read_v1;
                double ivnum = double.Parse(read_v, System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
                ivnum = ivnum * 1000; //转换为mV
                if (read_v1.IndexOf("-") != -1)
                    ivnum = -ivnum;
                //DP_DataRecord.AppendText(DateTime.Now.ToString() + " " + Voltage_TP[RY_count] + " 电压要求最大值：" + Voltage_MAX_DEF[RY_count].ToString() + "V 最小值：" + Voltage_MIN_DEF[RY_count].ToString() + "V\r\n");
                DP_I.Text = ivnum.ToString();
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电压值：" + DP_I.Text.ToString() + "mV\r\n");
                /*if (ivnum > Voltage_MAX_DEF[RY_count] * 1000)
                {
                    flag_err = 1;
                    DP_I_OKNG.Text = "NG";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " ; 电压检查: NG, 超出最大值\r\n");
                }
                else if (ivnum < Voltage_MIN_DEF[RY_count] * 1000)
                {
                    flag_err = 1;
                    DP_I_OKNG.Text = "NG";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " ; 电压检查: NG, 超出最小值\r\n");
                }
                else
                {
                    DP_I_OKNG.Text = "OK";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " ; 电压检查: OK\r\n");
                }*/
            }
            else if (iv == "I")
            {
                string read_i = "", read_i1 = "";

                RY_n = RY_count;
                if (ID_Selcet_comboBox.Text.ToString() == "STX1731(A)")
                {
                    if (RY_count == 2)
                        RY_n = 3;
                    else if (RY_count == 3)
                        RY_n = 2;
                } 
                if (RY_count == 0)
                    read_i1 = cvisa_opt.Opt_GetIVdc("DM3", "I", "MEASure:CURRent:DC? 2mA");
                else
                    read_i1 = cvisa_opt.Opt_GetIVdc("DM3", "I", "MEASure:CURRent:DC? 20mA"); //read_v = #9000000015-4.59713983e-04
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电流原始值：" + read_i1 + "\r\n");
                if (read_i1.IndexOf("#") != -1)
                    read_i = read_i1.Remove(read_i1.IndexOf("#"), 12); //从第0个开始，删除12个，留下后面的。//单位A
                else
                    read_i = read_i1;
                double ivnum = double.Parse(read_i, System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
                ivnum = ivnum * 1000; //转换为mA
                if (read_i.Substring(0,1)== "-")
                    ivnum = -ivnum;
                DP_DataRecord.AppendText(DateTime.Now.ToString() +  " 电流要求最大值：" + I_MAX_DEF[RY_n].ToString() + "mA 最小值：" + I_MIN_DEF[RY_n].ToString() + "mA\r\n");
                DP_I.Text = ivnum.ToString();
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电流值：" + DP_I.Text.ToString() + "mA\r\n");
                if (ivnum > I_MAX_DEF[RY_n])
                {
                    flag_err = 1;
                    DP_I_OKNG.Text = "NG";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + ";电流检查: NG, 超出最大值\r\n");
                }
                else if (ivnum < I_MIN_DEF[RY_n])
                {
                    flag_err = 1;
                    DP_I_OKNG.Text = "NG";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + ";电流检查: NG, 超出最小值\r\n");
                }
                else
                {
                    DP_I_OKNG.Text = "OK";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + ";电流检查: OK\r\n");
                }
            }
        }
        private void DP_DMMON_CheckedChanged(object sender, EventArgs e){ }

        private void DP_I_TextChanged(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void DP_Uart3_comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void ID_Selcet_comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            DP_DataRecord.AppendText(DateTime.Now.ToString() + "  " +ID_Selcet_comboBox.Text.ToString() + "\r\n");
        }

        private void ID_Selcet_comboBox_Click(object sender, EventArgs e)
        {
            
        }

        private void DP_I_OKNG_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
