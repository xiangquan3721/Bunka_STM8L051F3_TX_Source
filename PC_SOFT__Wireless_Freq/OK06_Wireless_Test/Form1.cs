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
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);//必须手动添加事件处理程序
            serialPort2.DataReceived += new SerialDataReceivedEventHandler(port2_DataReceived);

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
                case 3: //应答;01 10 00 00 00 02 41 C8
                    tx_cmd = 0;
                    if (buff[1] == 0x10 && buff[6] == 0x41 && buff[7] == 0xC8)
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
                if (serialPort1.IsOpen && flag_err == 0)
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
                        flag_auto_start = 1;
                        AutoTest_Step = 1;
                        timer2.Enabled = true;
                        flag_err = 0;
                    }
                }
                else if (flag_err == 3 || flag_err == 4 || flag_err == 5)
                {
                    //DP_DataRecord.BackColor = Color.White;
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
                    //DP_DataRecord.BackColor = Color.White;
                    flag_auto_start = 0;
                    AutoTest_Step = 0;
                    timer2.Enabled = false;
                    flag_err = 0;
                    MessageBox.Show("出错，继电器串口 未打开！");
                }
            }));
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
        private void DP_Uart2_comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

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
        private void OutPut_Data_Click(object sender, EventArgs e)
        {
            Save_Data();
        }
        private void Save_Data()
        {
            SaveFileDialog saveFile1 = new SaveFileDialog();
            saveFile1.Filter = "Excel files (*.csv)|*.csv";
            saveFile1.FilterIndex = 1;
            saveFile1.RestoreDirectory = true; //保存对话框是否记忆上次打开的目录
            //saveFile1.Title = "保存为csv文件";
            //DP_ScanCode.Text = "C2023007";
            saveFile1.FileName = DP_ScanCode.Text + " 发射测试 " + DateTime.Now.ToString("yyyy-MM-dd HH.mm.ss"); //年月日时分秒
            saveFile1.InitialDirectory = "D:"; //保存至目录文件夹(D:\\MyWork)

            SendKeys.Send("{Enter}"); //输出Enter(回车键),不用手动按键盘回车保存文件。
            SendKeys.Send("{Enter}");
            if (saveFile1.ShowDialog() == System.Windows.Forms.DialogResult.OK && saveFile1.FileName.Length > 0)
            {
                System.IO.StreamWriter sw = new System.IO.StreamWriter(saveFile1.FileName, false, System.Text.Encoding.GetEncoding(-0));

                try{
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 记录已保存到 " + saveFile1.FileName + "\r\n");
                    sw.WriteLine(DP_DataRecord.Text); //要输出的内容
                    MessageBox.Show("记录已保存到 " + saveFile1.FileName);
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
            freq_opt_stu = cvisa_opt.Opt_GetFreq("RSA3");
            //DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送功率：" + freq_opt_stu.get_dbm + "\r\n");
            //DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送频率：" + freq_opt_stu.get_hz + "\r\n");
            double freqnum = double.Parse(freq_opt_stu.get_hz,System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
            double powernum = double.Parse(freq_opt_stu.get_dbm, System.Globalization.NumberStyles.Float);
            freqnum = freqnum / 1000000; //MHz
            DP_Freq.Text = freqnum.ToString();
            DP_Power.Text = powernum.ToString("0.00"); //"0.00"保留两位小数
            if (429.174200 <= freqnum && freqnum <= 429.175800)
            {
                DP_FreqOKNG.Text = "OK";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送频率: " + freqnum.ToString() + " MHz; 检查: OK\r\n");
            }
            else
            {
                flag_err = 1;
                DP_FreqOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送频率: " + freqnum.ToString() + " MHz; 检查: NG\r\n");
            }
            if (5.0 <= powernum && powernum <= 13.0)
            {
                DP_PowerOKNG.Text = "OK";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送功率: " + powernum.ToString("0.00") + " dBm; 检查: OK\r\n");
            }
            else
            {
                flag_err = 1;
                DP_PowerOKNG.Text = "NG";
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 发送功率: " + powernum.ToString("0.00") + " dBm; 检查: NG\r\n");
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

        private void timer1_Tick(object sender, EventArgs e)
        {
            DP_DataRecord.AppendText(DateTime.Now.ToString() + " 继电器模块应答超时！\r\n");
            EnDis_Timer1(false);
            rx_offset = 0;
            flag_err = 1;
        }

        private void DP_FreqON_CheckedChanged(object sender, EventArgs e){}

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Interval = 1000;
            Freq_AutoTest_Start();
            //Rx_AutoTest_Start();
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
                    Save_Data();
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
            if (iv == "V")
            { 
                string read_v = cvisa_opt.Opt_GetIVdc("DM3", "V"); //read_v = #9000000015-4.59713983e-04
                read_v = read_v.Remove(0, 12); //从第0个开始，删除12个，留下后面的。//单位V
                double ivnum = double.Parse(read_v, System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
                DP_I.Text = ivnum.ToString("0.00");
                DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电压值：" + read_v + "\r\n");
            }
            else if (iv == "I")
            { 
                string read_i = cvisa_opt.Opt_GetIVdc("DM3", "I"); //read_v = #9000000015-4.59713983e-04
                read_i = read_i.Remove(0, 12); //从第0个开始，删除12个，留下后面的。//单位A
                double ivnum = double.Parse(read_i, System.Globalization.NumberStyles.Float); //将科学计数的字符串转换为浮点数
                ivnum = ivnum * 1000; //转换为mA
                DP_I.Text = ivnum.ToString("0.00");
                if (ivnum <= 60.0)
                {
                    DP_I_OKNG.Text = "OK";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电流值：" + ivnum.ToString() + "; 检查: OK\r\n");
                }
                else {
                    flag_err = 1;
                    DP_I_OKNG.Text = "NG";
                    DP_DataRecord.AppendText(DateTime.Now.ToString() + " 读取电流值：" + ivnum.ToString() + "; 检查: NG\r\n");
                }
            }
        }
        private void DP_DMMON_CheckedChanged(object sender, EventArgs e){ }

    }
}
