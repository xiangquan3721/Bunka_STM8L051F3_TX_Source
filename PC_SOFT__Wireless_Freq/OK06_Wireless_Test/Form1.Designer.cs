namespace OK06_Wireless_Test
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.Check_Com = new System.Windows.Forms.Button();
            this.DP_Uart1_comboBox1 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.TEST_Mode = new System.Windows.Forms.Button();
            this.EXIT_TEST = new System.Windows.Forms.Button();
            this.Tx_Carrier = new System.Windows.Forms.Button();
            this.Tx_Rece_Sensit = new System.Windows.Forms.Button();
            this.Tx_Modula = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.DP_Uart_OpenClose = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.OutPut_Data = new System.Windows.Forms.Button();
            this.Clear_Data = new System.Windows.Forms.Button();
            this.DP_DataRecord = new System.Windows.Forms.TextBox();
            this.Tx_Read = new System.Windows.Forms.Button();
            this.OPEN_radioButton = new System.Windows.Forms.RadioButton();
            this.SignlSource_GroupBox = new System.Windows.Forms.GroupBox();
            this.CLOSE_radioButton = new System.Windows.Forms.RadioButton();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.DP_Freq = new System.Windows.Forms.TextBox();
            this.DP_Power = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.DP_FreqOKNG = new System.Windows.Forms.TextBox();
            this.DP_PowerOKNG = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.DP_Uart2_comboBox2 = new System.Windows.Forms.ComboBox();
            this.DP_Uart_ScanCode = new System.Windows.Forms.Button();
            this.serialPort2 = new System.IO.Ports.SerialPort(this.components);
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.DP_ScanCode = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.Freq_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_FreqOFF = new System.Windows.Forms.RadioButton();
            this.DP_FreqON = new System.Windows.Forms.RadioButton();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Signal_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_SignalOFF = new System.Windows.Forms.RadioButton();
            this.DP_SignalON = new System.Windows.Forms.RadioButton();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.V_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_DMMOFF = new System.Windows.Forms.RadioButton();
            this.DP_DMMON = new System.Windows.Forms.RadioButton();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.Tx_Read_ReceSensit = new System.Windows.Forms.Button();
            this.Tx_ReadIV = new System.Windows.Forms.Button();
            this.DP_I = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.DP_I_OKNG = new System.Windows.Forms.TextBox();
            this.SignlSource_GroupBox.SuspendLayout();
            this.Freq_groupBox1.SuspendLayout();
            this.Signal_groupBox1.SuspendLayout();
            this.V_groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Check_Com
            // 
            this.Check_Com.BackColor = System.Drawing.Color.LightSteelBlue;
            this.Check_Com.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Check_Com.Location = new System.Drawing.Point(29, 47);
            this.Check_Com.Name = "Check_Com";
            this.Check_Com.Size = new System.Drawing.Size(75, 27);
            this.Check_Com.TabIndex = 0;
            this.Check_Com.Text = "检查端口";
            this.Check_Com.UseVisualStyleBackColor = false;
            this.Check_Com.Click += new System.EventHandler(this.Check_Com_Click);
            // 
            // DP_Uart1_comboBox1
            // 
            this.DP_Uart1_comboBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart1_comboBox1.FormattingEnabled = true;
            this.DP_Uart1_comboBox1.Location = new System.Drawing.Point(147, 29);
            this.DP_Uart1_comboBox1.Name = "DP_Uart1_comboBox1";
            this.DP_Uart1_comboBox1.Size = new System.Drawing.Size(85, 20);
            this.DP_Uart1_comboBox1.TabIndex = 1;
            this.DP_Uart1_comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(252, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "打开/关闭";
            // 
            // TEST_Mode
            // 
            this.TEST_Mode.BackColor = System.Drawing.Color.Gainsboro;
            this.TEST_Mode.Enabled = false;
            this.TEST_Mode.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TEST_Mode.Location = new System.Drawing.Point(667, 47);
            this.TEST_Mode.Name = "TEST_Mode";
            this.TEST_Mode.Size = new System.Drawing.Size(96, 27);
            this.TEST_Mode.TabIndex = 4;
            this.TEST_Mode.Text = "进入测试模式";
            this.TEST_Mode.UseVisualStyleBackColor = false;
            this.TEST_Mode.Visible = false;
            this.TEST_Mode.Click += new System.EventHandler(this.TEST_Mode_Click);
            // 
            // EXIT_TEST
            // 
            this.EXIT_TEST.BackColor = System.Drawing.Color.Gainsboro;
            this.EXIT_TEST.Enabled = false;
            this.EXIT_TEST.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.EXIT_TEST.Location = new System.Drawing.Point(809, 47);
            this.EXIT_TEST.Name = "EXIT_TEST";
            this.EXIT_TEST.Size = new System.Drawing.Size(96, 27);
            this.EXIT_TEST.TabIndex = 22;
            this.EXIT_TEST.Text = "退出测试模式";
            this.EXIT_TEST.UseVisualStyleBackColor = false;
            this.EXIT_TEST.Visible = false;
            this.EXIT_TEST.Click += new System.EventHandler(this.EXIT_TEST_Click);
            // 
            // Tx_Carrier
            // 
            this.Tx_Carrier.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Carrier.Enabled = false;
            this.Tx_Carrier.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Carrier.Location = new System.Drawing.Point(29, 194);
            this.Tx_Carrier.Name = "Tx_Carrier";
            this.Tx_Carrier.Size = new System.Drawing.Size(75, 27);
            this.Tx_Carrier.TabIndex = 23;
            this.Tx_Carrier.Text = "发送载波";
            this.Tx_Carrier.UseVisualStyleBackColor = false;
            this.Tx_Carrier.Click += new System.EventHandler(this.Tx_Carrier_Click);
            // 
            // Tx_Rece_Sensit
            // 
            this.Tx_Rece_Sensit.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Rece_Sensit.Enabled = false;
            this.Tx_Rece_Sensit.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Rece_Sensit.Location = new System.Drawing.Point(515, 340);
            this.Tx_Rece_Sensit.Name = "Tx_Rece_Sensit";
            this.Tx_Rece_Sensit.Size = new System.Drawing.Size(96, 27);
            this.Tx_Rece_Sensit.TabIndex = 25;
            this.Tx_Rece_Sensit.Text = "接收灵敏度";
            this.Tx_Rece_Sensit.UseVisualStyleBackColor = false;
            this.Tx_Rece_Sensit.Visible = false;
            this.Tx_Rece_Sensit.Click += new System.EventHandler(this.Tx_Rece_Sensit_Click);
            // 
            // Tx_Modula
            // 
            this.Tx_Modula.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Modula.Enabled = false;
            this.Tx_Modula.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Modula.Location = new System.Drawing.Point(426, 524);
            this.Tx_Modula.Name = "Tx_Modula";
            this.Tx_Modula.Size = new System.Drawing.Size(75, 27);
            this.Tx_Modula.TabIndex = 26;
            this.Tx_Modula.Text = "发送调制";
            this.Tx_Modula.UseVisualStyleBackColor = false;
            this.Tx_Modula.Visible = false;
            this.Tx_Modula.Click += new System.EventHandler(this.Tx_Modula_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 38400;
            // 
            // DP_Uart_OpenClose
            // 
            this.DP_Uart_OpenClose.BackColor = System.Drawing.Color.LightSteelBlue;
            this.DP_Uart_OpenClose.Cursor = System.Windows.Forms.Cursors.Default;
            this.DP_Uart_OpenClose.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart_OpenClose.Location = new System.Drawing.Point(238, 25);
            this.DP_Uart_OpenClose.Name = "DP_Uart_OpenClose";
            this.DP_Uart_OpenClose.Size = new System.Drawing.Size(93, 27);
            this.DP_Uart_OpenClose.TabIndex = 35;
            this.DP_Uart_OpenClose.Text = "串口1已关闭";
            this.DP_Uart_OpenClose.UseVisualStyleBackColor = false;
            this.DP_Uart_OpenClose.Click += new System.EventHandler(this.DP_Uart_OpenClose_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(636, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 37;
            this.label2.Text = "数据记录";
            // 
            // OutPut_Data
            // 
            this.OutPut_Data.BackColor = System.Drawing.Color.LightSteelBlue;
            this.OutPut_Data.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.OutPut_Data.Location = new System.Drawing.Point(638, 531);
            this.OutPut_Data.Name = "OutPut_Data";
            this.OutPut_Data.Size = new System.Drawing.Size(75, 27);
            this.OutPut_Data.TabIndex = 38;
            this.OutPut_Data.Text = "保存记录";
            this.OutPut_Data.UseVisualStyleBackColor = false;
            this.OutPut_Data.Click += new System.EventHandler(this.OutPut_Data_Click);
            // 
            // Clear_Data
            // 
            this.Clear_Data.BackColor = System.Drawing.Color.LightSteelBlue;
            this.Clear_Data.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Clear_Data.Location = new System.Drawing.Point(904, 531);
            this.Clear_Data.Name = "Clear_Data";
            this.Clear_Data.Size = new System.Drawing.Size(75, 27);
            this.Clear_Data.TabIndex = 39;
            this.Clear_Data.Text = "清除记录";
            this.Clear_Data.UseVisualStyleBackColor = false;
            this.Clear_Data.Click += new System.EventHandler(this.Clear_Data_Click);
            // 
            // DP_DataRecord
            // 
            this.DP_DataRecord.BackColor = System.Drawing.Color.White;
            this.DP_DataRecord.Location = new System.Drawing.Point(638, 123);
            this.DP_DataRecord.Margin = new System.Windows.Forms.Padding(2);
            this.DP_DataRecord.Multiline = true;
            this.DP_DataRecord.Name = "DP_DataRecord";
            this.DP_DataRecord.ReadOnly = true;
            this.DP_DataRecord.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.DP_DataRecord.Size = new System.Drawing.Size(341, 403);
            this.DP_DataRecord.TabIndex = 40;
            // 
            // Tx_Read
            // 
            this.Tx_Read.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Read.Enabled = false;
            this.Tx_Read.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Read.Location = new System.Drawing.Point(29, 269);
            this.Tx_Read.Name = "Tx_Read";
            this.Tx_Read.Size = new System.Drawing.Size(75, 27);
            this.Tx_Read.TabIndex = 42;
            this.Tx_Read.Text = "读频谱仪";
            this.Tx_Read.UseVisualStyleBackColor = false;
            this.Tx_Read.Click += new System.EventHandler(this.Tx_Read_Click);
            // 
            // OPEN_radioButton
            // 
            this.OPEN_radioButton.AutoSize = true;
            this.OPEN_radioButton.BackColor = System.Drawing.SystemColors.Control;
            this.OPEN_radioButton.Location = new System.Drawing.Point(6, 32);
            this.OPEN_radioButton.Name = "OPEN_radioButton";
            this.OPEN_radioButton.Size = new System.Drawing.Size(49, 16);
            this.OPEN_radioButton.TabIndex = 43;
            this.OPEN_radioButton.Text = "打开";
            this.OPEN_radioButton.UseVisualStyleBackColor = false;
            this.OPEN_radioButton.CheckedChanged += new System.EventHandler(this.OPEN_radioButton_CheckedChanged);
            // 
            // SignlSource_GroupBox
            // 
            this.SignlSource_GroupBox.Controls.Add(this.CLOSE_radioButton);
            this.SignlSource_GroupBox.Controls.Add(this.OPEN_radioButton);
            this.SignlSource_GroupBox.Enabled = false;
            this.SignlSource_GroupBox.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SignlSource_GroupBox.Location = new System.Drawing.Point(175, 487);
            this.SignlSource_GroupBox.Name = "SignlSource_GroupBox";
            this.SignlSource_GroupBox.Size = new System.Drawing.Size(136, 71);
            this.SignlSource_GroupBox.TabIndex = 44;
            this.SignlSource_GroupBox.TabStop = false;
            this.SignlSource_GroupBox.Text = "信号源";
            this.SignlSource_GroupBox.Visible = false;
            this.SignlSource_GroupBox.Enter += new System.EventHandler(this.SignlSource_GroupBox_Enter);
            // 
            // CLOSE_radioButton
            // 
            this.CLOSE_radioButton.AutoSize = true;
            this.CLOSE_radioButton.BackColor = System.Drawing.SystemColors.Control;
            this.CLOSE_radioButton.Location = new System.Drawing.Point(76, 32);
            this.CLOSE_radioButton.Name = "CLOSE_radioButton";
            this.CLOSE_radioButton.Size = new System.Drawing.Size(49, 16);
            this.CLOSE_radioButton.TabIndex = 44;
            this.CLOSE_radioButton.Text = "关闭";
            this.CLOSE_radioButton.UseVisualStyleBackColor = false;
            this.CLOSE_radioButton.CheckedChanged += new System.EventHandler(this.CLOSE_radioButton_CheckedChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(134, 253);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 45;
            this.label3.Text = "频率：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(134, 302);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 46;
            this.label4.Text = "功率：";
            // 
            // DP_Freq
            // 
            this.DP_Freq.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_Freq.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Freq.Location = new System.Drawing.Point(171, 246);
            this.DP_Freq.Multiline = true;
            this.DP_Freq.Name = "DP_Freq";
            this.DP_Freq.ReadOnly = true;
            this.DP_Freq.Size = new System.Drawing.Size(96, 27);
            this.DP_Freq.TabIndex = 47;
            this.DP_Freq.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // DP_Power
            // 
            this.DP_Power.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_Power.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Power.Location = new System.Drawing.Point(171, 295);
            this.DP_Power.Multiline = true;
            this.DP_Power.Name = "DP_Power";
            this.DP_Power.ReadOnly = true;
            this.DP_Power.Size = new System.Drawing.Size(96, 27);
            this.DP_Power.TabIndex = 48;
            this.DP_Power.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(271, 261);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 12);
            this.label5.TabIndex = 49;
            this.label5.Text = "MHz";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(271, 310);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 12);
            this.label6.TabIndex = 50;
            this.label6.Text = "dBm";
            // 
            // DP_FreqOKNG
            // 
            this.DP_FreqOKNG.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_FreqOKNG.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_FreqOKNG.Location = new System.Drawing.Point(312, 246);
            this.DP_FreqOKNG.Multiline = true;
            this.DP_FreqOKNG.Name = "DP_FreqOKNG";
            this.DP_FreqOKNG.ReadOnly = true;
            this.DP_FreqOKNG.Size = new System.Drawing.Size(62, 27);
            this.DP_FreqOKNG.TabIndex = 51;
            this.DP_FreqOKNG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // DP_PowerOKNG
            // 
            this.DP_PowerOKNG.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_PowerOKNG.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_PowerOKNG.Location = new System.Drawing.Point(312, 295);
            this.DP_PowerOKNG.Multiline = true;
            this.DP_PowerOKNG.Name = "DP_PowerOKNG";
            this.DP_PowerOKNG.ReadOnly = true;
            this.DP_PowerOKNG.Size = new System.Drawing.Size(62, 27);
            this.DP_PowerOKNG.TabIndex = 52;
            this.DP_PowerOKNG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(328, 231);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 12);
            this.label7.TabIndex = 53;
            this.label7.Text = "OK/NG";
            // 
            // DP_Uart2_comboBox2
            // 
            this.DP_Uart2_comboBox2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart2_comboBox2.FormattingEnabled = true;
            this.DP_Uart2_comboBox2.Location = new System.Drawing.Point(147, 78);
            this.DP_Uart2_comboBox2.Name = "DP_Uart2_comboBox2";
            this.DP_Uart2_comboBox2.Size = new System.Drawing.Size(85, 20);
            this.DP_Uart2_comboBox2.TabIndex = 54;
            // 
            // DP_Uart_ScanCode
            // 
            this.DP_Uart_ScanCode.BackColor = System.Drawing.Color.LightSteelBlue;
            this.DP_Uart_ScanCode.Cursor = System.Windows.Forms.Cursors.Default;
            this.DP_Uart_ScanCode.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart_ScanCode.Location = new System.Drawing.Point(238, 74);
            this.DP_Uart_ScanCode.Name = "DP_Uart_ScanCode";
            this.DP_Uart_ScanCode.Size = new System.Drawing.Size(93, 27);
            this.DP_Uart_ScanCode.TabIndex = 55;
            this.DP_Uart_ScanCode.Text = "串口2已关闭";
            this.DP_Uart_ScanCode.UseVisualStyleBackColor = false;
            this.DP_Uart_ScanCode.Click += new System.EventHandler(this.DP_Uart_ScanCode_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(100, 32);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 56;
            this.label8.Text = "控制器:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(100, 81);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 57;
            this.label9.Text = "扫码枪:";
            // 
            // DP_ScanCode
            // 
            this.DP_ScanCode.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_ScanCode.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_ScanCode.Location = new System.Drawing.Point(72, 123);
            this.DP_ScanCode.Multiline = true;
            this.DP_ScanCode.Name = "DP_ScanCode";
            this.DP_ScanCode.ReadOnly = true;
            this.DP_ScanCode.Size = new System.Drawing.Size(198, 27);
            this.DP_ScanCode.TabIndex = 58;
            this.DP_ScanCode.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(31, 131);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 12);
            this.label10.TabIndex = 59;
            this.label10.Text = "扫码:";
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.SystemColors.Menu;
            this.textBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox1.Location = new System.Drawing.Point(41, 20);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(75, 20);
            this.textBox1.TabIndex = 60;
            this.textBox1.Text = "RSA3015E";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Freq_groupBox1
            // 
            this.Freq_groupBox1.Controls.Add(this.DP_FreqOFF);
            this.Freq_groupBox1.Controls.Add(this.DP_FreqON);
            this.Freq_groupBox1.Controls.Add(this.textBox1);
            this.Freq_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Freq_groupBox1.Location = new System.Drawing.Point(385, 12);
            this.Freq_groupBox1.Name = "Freq_groupBox1";
            this.Freq_groupBox1.Size = new System.Drawing.Size(153, 100);
            this.Freq_groupBox1.TabIndex = 61;
            this.Freq_groupBox1.TabStop = false;
            this.Freq_groupBox1.Text = "频谱仪";
            // 
            // DP_FreqOFF
            // 
            this.DP_FreqOFF.AutoSize = true;
            this.DP_FreqOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_FreqOFF.Checked = true;
            this.DP_FreqOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_FreqOFF.Location = new System.Drawing.Point(86, 56);
            this.DP_FreqOFF.Name = "DP_FreqOFF";
            this.DP_FreqOFF.Size = new System.Drawing.Size(62, 16);
            this.DP_FreqOFF.TabIndex = 62;
            this.DP_FreqOFF.TabStop = true;
            this.DP_FreqOFF.Text = "未连接";
            this.DP_FreqOFF.UseVisualStyleBackColor = false;
            // 
            // DP_FreqON
            // 
            this.DP_FreqON.AutoSize = true;
            this.DP_FreqON.BackColor = System.Drawing.SystemColors.Control;
            this.DP_FreqON.Enabled = false;
            this.DP_FreqON.Location = new System.Drawing.Point(7, 56);
            this.DP_FreqON.Name = "DP_FreqON";
            this.DP_FreqON.Size = new System.Drawing.Size(62, 16);
            this.DP_FreqON.TabIndex = 61;
            this.DP_FreqON.Text = "已连接";
            this.DP_FreqON.UseVisualStyleBackColor = false;
            this.DP_FreqON.CheckedChanged += new System.EventHandler(this.DP_FreqON_CheckedChanged);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Signal_groupBox1
            // 
            this.Signal_groupBox1.Controls.Add(this.DP_SignalOFF);
            this.Signal_groupBox1.Controls.Add(this.DP_SignalON);
            this.Signal_groupBox1.Controls.Add(this.textBox2);
            this.Signal_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Signal_groupBox1.Location = new System.Drawing.Point(385, 391);
            this.Signal_groupBox1.Name = "Signal_groupBox1";
            this.Signal_groupBox1.Size = new System.Drawing.Size(153, 100);
            this.Signal_groupBox1.TabIndex = 62;
            this.Signal_groupBox1.TabStop = false;
            this.Signal_groupBox1.Text = "信号源";
            this.Signal_groupBox1.Visible = false;
            // 
            // DP_SignalOFF
            // 
            this.DP_SignalOFF.AutoSize = true;
            this.DP_SignalOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_SignalOFF.Checked = true;
            this.DP_SignalOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_SignalOFF.Location = new System.Drawing.Point(86, 56);
            this.DP_SignalOFF.Name = "DP_SignalOFF";
            this.DP_SignalOFF.Size = new System.Drawing.Size(62, 16);
            this.DP_SignalOFF.TabIndex = 62;
            this.DP_SignalOFF.TabStop = true;
            this.DP_SignalOFF.Text = "未连接";
            this.DP_SignalOFF.UseVisualStyleBackColor = false;
            // 
            // DP_SignalON
            // 
            this.DP_SignalON.AutoSize = true;
            this.DP_SignalON.BackColor = System.Drawing.SystemColors.Control;
            this.DP_SignalON.Enabled = false;
            this.DP_SignalON.Location = new System.Drawing.Point(7, 56);
            this.DP_SignalON.Name = "DP_SignalON";
            this.DP_SignalON.Size = new System.Drawing.Size(62, 16);
            this.DP_SignalON.TabIndex = 61;
            this.DP_SignalON.Text = "已连接";
            this.DP_SignalON.UseVisualStyleBackColor = false;
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.SystemColors.Menu;
            this.textBox2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox2.Location = new System.Drawing.Point(41, 20);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(75, 20);
            this.textBox2.TabIndex = 60;
            this.textBox2.Text = "DSG3065B";
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // V_groupBox1
            // 
            this.V_groupBox1.Controls.Add(this.DP_DMMOFF);
            this.V_groupBox1.Controls.Add(this.DP_DMMON);
            this.V_groupBox1.Controls.Add(this.textBox3);
            this.V_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.V_groupBox1.Location = new System.Drawing.Point(385, 132);
            this.V_groupBox1.Name = "V_groupBox1";
            this.V_groupBox1.Size = new System.Drawing.Size(153, 100);
            this.V_groupBox1.TabIndex = 63;
            this.V_groupBox1.TabStop = false;
            this.V_groupBox1.Text = "数字万用表";
            // 
            // DP_DMMOFF
            // 
            this.DP_DMMOFF.AutoSize = true;
            this.DP_DMMOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_DMMOFF.Checked = true;
            this.DP_DMMOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_DMMOFF.Location = new System.Drawing.Point(86, 56);
            this.DP_DMMOFF.Name = "DP_DMMOFF";
            this.DP_DMMOFF.Size = new System.Drawing.Size(62, 16);
            this.DP_DMMOFF.TabIndex = 62;
            this.DP_DMMOFF.TabStop = true;
            this.DP_DMMOFF.Text = "未连接";
            this.DP_DMMOFF.UseVisualStyleBackColor = false;
            // 
            // DP_DMMON
            // 
            this.DP_DMMON.AutoSize = true;
            this.DP_DMMON.BackColor = System.Drawing.SystemColors.Control;
            this.DP_DMMON.Enabled = false;
            this.DP_DMMON.Location = new System.Drawing.Point(7, 56);
            this.DP_DMMON.Name = "DP_DMMON";
            this.DP_DMMON.Size = new System.Drawing.Size(62, 16);
            this.DP_DMMON.TabIndex = 61;
            this.DP_DMMON.Text = "已连接";
            this.DP_DMMON.UseVisualStyleBackColor = false;
            this.DP_DMMON.CheckedChanged += new System.EventHandler(this.DP_DMMON_CheckedChanged);
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.Menu;
            this.textBox3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox3.Location = new System.Drawing.Point(41, 20);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.Size = new System.Drawing.Size(75, 20);
            this.textBox3.TabIndex = 60;
            this.textBox3.Text = "DM3058E";
            this.textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // timer2
            // 
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // Tx_Read_ReceSensit
            // 
            this.Tx_Read_ReceSensit.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Read_ReceSensit.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Read_ReceSensit.Location = new System.Drawing.Point(515, 287);
            this.Tx_Read_ReceSensit.Name = "Tx_Read_ReceSensit";
            this.Tx_Read_ReceSensit.Size = new System.Drawing.Size(96, 27);
            this.Tx_Read_ReceSensit.TabIndex = 64;
            this.Tx_Read_ReceSensit.Text = "读取IO";
            this.Tx_Read_ReceSensit.UseVisualStyleBackColor = false;
            this.Tx_Read_ReceSensit.Visible = false;
            this.Tx_Read_ReceSensit.Click += new System.EventHandler(this.Tx_Read_ReceSensit_Click);
            // 
            // Tx_ReadIV
            // 
            this.Tx_ReadIV.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_ReadIV.Enabled = false;
            this.Tx_ReadIV.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_ReadIV.Location = new System.Drawing.Point(29, 359);
            this.Tx_ReadIV.Name = "Tx_ReadIV";
            this.Tx_ReadIV.Size = new System.Drawing.Size(96, 27);
            this.Tx_ReadIV.TabIndex = 65;
            this.Tx_ReadIV.Text = "读取电流";
            this.Tx_ReadIV.UseVisualStyleBackColor = false;
            this.Tx_ReadIV.Click += new System.EventHandler(this.Tx_ReadIV_Click);
            // 
            // DP_I
            // 
            this.DP_I.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_I.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_I.Location = new System.Drawing.Point(171, 359);
            this.DP_I.Multiline = true;
            this.DP_I.Name = "DP_I";
            this.DP_I.ReadOnly = true;
            this.DP_I.Size = new System.Drawing.Size(96, 27);
            this.DP_I.TabIndex = 66;
            this.DP_I.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(273, 374);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(0, 12);
            this.label11.TabIndex = 67;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(271, 374);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 68;
            this.label12.Text = "mA";
            // 
            // DP_I_OKNG
            // 
            this.DP_I_OKNG.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_I_OKNG.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_I_OKNG.Location = new System.Drawing.Point(312, 359);
            this.DP_I_OKNG.Multiline = true;
            this.DP_I_OKNG.Name = "DP_I_OKNG";
            this.DP_I_OKNG.ReadOnly = true;
            this.DP_I_OKNG.Size = new System.Drawing.Size(62, 27);
            this.DP_I_OKNG.TabIndex = 69;
            this.DP_I_OKNG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(987, 563);
            this.Controls.Add(this.DP_I_OKNG);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.DP_I);
            this.Controls.Add(this.Tx_ReadIV);
            this.Controls.Add(this.Tx_Read_ReceSensit);
            this.Controls.Add(this.V_groupBox1);
            this.Controls.Add(this.Signal_groupBox1);
            this.Controls.Add(this.Freq_groupBox1);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.DP_ScanCode);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.DP_Uart_ScanCode);
            this.Controls.Add(this.DP_Uart2_comboBox2);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.DP_PowerOKNG);
            this.Controls.Add(this.DP_FreqOKNG);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.DP_Power);
            this.Controls.Add(this.DP_Freq);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.SignlSource_GroupBox);
            this.Controls.Add(this.Tx_Read);
            this.Controls.Add(this.DP_DataRecord);
            this.Controls.Add(this.Clear_Data);
            this.Controls.Add(this.OutPut_Data);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.DP_Uart_OpenClose);
            this.Controls.Add(this.Tx_Modula);
            this.Controls.Add(this.Tx_Rece_Sensit);
            this.Controls.Add(this.Tx_Carrier);
            this.Controls.Add(this.EXIT_TEST);
            this.Controls.Add(this.TEST_Mode);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DP_Uart1_comboBox1);
            this.Controls.Add(this.Check_Com);
            this.KeyPreview = true;
            this.Name = "Form1";
            this.Text = "无线发射测试_TX";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.SignlSource_GroupBox.ResumeLayout(false);
            this.SignlSource_GroupBox.PerformLayout();
            this.Freq_groupBox1.ResumeLayout(false);
            this.Freq_groupBox1.PerformLayout();
            this.Signal_groupBox1.ResumeLayout(false);
            this.Signal_groupBox1.PerformLayout();
            this.V_groupBox1.ResumeLayout(false);
            this.V_groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Check_Com;
        private System.Windows.Forms.ComboBox DP_Uart1_comboBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button TEST_Mode;
        private System.Windows.Forms.Button EXIT_TEST;
        private System.Windows.Forms.Button Tx_Carrier;
        private System.Windows.Forms.Button Tx_Rece_Sensit;
        private System.Windows.Forms.Button Tx_Modula;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button DP_Uart_OpenClose;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button OutPut_Data;
        private System.Windows.Forms.Button Clear_Data;
        private System.Windows.Forms.TextBox DP_DataRecord;
        private System.Windows.Forms.Button Tx_Read;
        private System.Windows.Forms.RadioButton OPEN_radioButton;
        private System.Windows.Forms.GroupBox SignlSource_GroupBox;
        private System.Windows.Forms.RadioButton CLOSE_radioButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox DP_Freq;
        private System.Windows.Forms.TextBox DP_Power;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox DP_FreqOKNG;
        private System.Windows.Forms.TextBox DP_PowerOKNG;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox DP_Uart2_comboBox2;
        private System.Windows.Forms.Button DP_Uart_ScanCode;
        private System.IO.Ports.SerialPort serialPort2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox DP_ScanCode;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.GroupBox Freq_groupBox1;
        private System.Windows.Forms.RadioButton DP_FreqOFF;
        private System.Windows.Forms.RadioButton DP_FreqON;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox Signal_groupBox1;
        private System.Windows.Forms.RadioButton DP_SignalOFF;
        private System.Windows.Forms.RadioButton DP_SignalON;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.GroupBox V_groupBox1;
        private System.Windows.Forms.RadioButton DP_DMMOFF;
        private System.Windows.Forms.RadioButton DP_DMMON;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Button Tx_Read_ReceSensit;
        private System.Windows.Forms.Button Tx_ReadIV;
        private System.Windows.Forms.TextBox DP_I;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox DP_I_OKNG;
    }
}

