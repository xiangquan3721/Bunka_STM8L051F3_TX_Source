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
            this.DP_Uart1_comboBox1 = new System.Windows.Forms.ComboBox();
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
            this.DP_ScanCode = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.Freq_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_FreqOFF = new System.Windows.Forms.RadioButton();
            this.DP_FreqON = new System.Windows.Forms.RadioButton();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Signal_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_SignalOFF = new System.Windows.Forms.RadioButton();
            this.DP_SignalON = new System.Windows.Forms.RadioButton();
            this.V_groupBox1 = new System.Windows.Forms.GroupBox();
            this.DP_DMMOFF = new System.Windows.Forms.RadioButton();
            this.DP_DMMON = new System.Windows.Forms.RadioButton();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.Tx_Read_ReceSensit = new System.Windows.Forms.Button();
            this.Tx_ReadIV = new System.Windows.Forms.Button();
            this.DP_I = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.DP_I_OKNG = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.label16 = new System.Windows.Forms.Label();
            this.DP_Uart3_comboBox3 = new System.Windows.Forms.ComboBox();
            this.DP_Uart_WriteID = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.comtxt = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.Display_Results = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.NG_num = new System.Windows.Forms.Label();
            this.OK_num = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.serialPort3 = new System.IO.Ports.SerialPort(this.components);
            this.UART3_WriteID_Received_textBox = new System.Windows.Forms.TextBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.ID_Selcet_comboBox = new System.Windows.Forms.ComboBox();
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.SignlSource_GroupBox.SuspendLayout();
            this.Freq_groupBox1.SuspendLayout();
            this.Signal_groupBox1.SuspendLayout();
            this.V_groupBox1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // DP_Uart1_comboBox1
            // 
            this.DP_Uart1_comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DP_Uart1_comboBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart1_comboBox1.FormattingEnabled = true;
            this.DP_Uart1_comboBox1.Location = new System.Drawing.Point(30, 17);
            this.DP_Uart1_comboBox1.Name = "DP_Uart1_comboBox1";
            this.DP_Uart1_comboBox1.Size = new System.Drawing.Size(162, 20);
            this.DP_Uart1_comboBox1.TabIndex = 1;
            this.DP_Uart1_comboBox1.SelectedIndexChanged += new System.EventHandler(this.DP_Uart1_comboBox1_SelectedIndexChanged);
            this.DP_Uart1_comboBox1.Click += new System.EventHandler(this.DP_Uart1_comboBox1_Click);
            // 
            // TEST_Mode
            // 
            this.TEST_Mode.BackColor = System.Drawing.Color.Gainsboro;
            this.TEST_Mode.Enabled = false;
            this.TEST_Mode.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TEST_Mode.Location = new System.Drawing.Point(857, 40);
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
            this.EXIT_TEST.Location = new System.Drawing.Point(976, 41);
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
            this.Tx_Carrier.Location = new System.Drawing.Point(857, 73);
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
            this.Tx_Rece_Sensit.Location = new System.Drawing.Point(959, 103);
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
            this.Tx_Modula.Location = new System.Drawing.Point(1061, 103);
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
            this.DP_Uart_OpenClose.Location = new System.Drawing.Point(197, 13);
            this.DP_Uart_OpenClose.Name = "DP_Uart_OpenClose";
            this.DP_Uart_OpenClose.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.DP_Uart_OpenClose.Size = new System.Drawing.Size(50, 27);
            this.DP_Uart_OpenClose.TabIndex = 35;
            this.DP_Uart_OpenClose.Text = "已关";
            this.DP_Uart_OpenClose.UseVisualStyleBackColor = false;
            this.DP_Uart_OpenClose.Click += new System.EventHandler(this.DP_Uart_OpenClose_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 298);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 37;
            this.label2.Text = "Debug Log";
            // 
            // OutPut_Data
            // 
            this.OutPut_Data.BackColor = System.Drawing.Color.LightSteelBlue;
            this.OutPut_Data.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.OutPut_Data.Location = new System.Drawing.Point(857, 379);
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
            this.Clear_Data.Location = new System.Drawing.Point(938, 379);
            this.Clear_Data.Name = "Clear_Data";
            this.Clear_Data.Size = new System.Drawing.Size(75, 27);
            this.Clear_Data.TabIndex = 39;
            this.Clear_Data.Text = "清除记录";
            this.Clear_Data.UseVisualStyleBackColor = false;
            this.Clear_Data.Click += new System.EventHandler(this.Clear_Data_Click);
            // 
            // DP_DataRecord
            // 
            this.DP_DataRecord.BackColor = System.Drawing.Color.Black;
            this.DP_DataRecord.ForeColor = System.Drawing.Color.White;
            this.DP_DataRecord.Location = new System.Drawing.Point(21, 312);
            this.DP_DataRecord.Margin = new System.Windows.Forms.Padding(2);
            this.DP_DataRecord.Multiline = true;
            this.DP_DataRecord.Name = "DP_DataRecord";
            this.DP_DataRecord.ReadOnly = true;
            this.DP_DataRecord.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.DP_DataRecord.Size = new System.Drawing.Size(742, 360);
            this.DP_DataRecord.TabIndex = 40;
            // 
            // Tx_Read
            // 
            this.Tx_Read.BackColor = System.Drawing.Color.Gainsboro;
            this.Tx_Read.Enabled = false;
            this.Tx_Read.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tx_Read.Location = new System.Drawing.Point(938, 73);
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
            this.SignlSource_GroupBox.Location = new System.Drawing.Point(994, 265);
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
            this.label3.Location = new System.Drawing.Point(19, 240);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 45;
            this.label3.Text = "频率：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 266);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 46;
            this.label4.Text = "功率：";
            // 
            // DP_Freq
            // 
            this.DP_Freq.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_Freq.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Freq.Location = new System.Drawing.Point(55, 231);
            this.DP_Freq.Multiline = true;
            this.DP_Freq.Name = "DP_Freq";
            this.DP_Freq.ReadOnly = true;
            this.DP_Freq.Size = new System.Drawing.Size(102, 27);
            this.DP_Freq.TabIndex = 47;
            this.DP_Freq.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // DP_Power
            // 
            this.DP_Power.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_Power.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Power.Location = new System.Drawing.Point(55, 259);
            this.DP_Power.Multiline = true;
            this.DP_Power.Name = "DP_Power";
            this.DP_Power.ReadOnly = true;
            this.DP_Power.Size = new System.Drawing.Size(102, 27);
            this.DP_Power.TabIndex = 48;
            this.DP_Power.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(158, 238);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 12);
            this.label5.TabIndex = 49;
            this.label5.Text = "MHz";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(157, 266);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 12);
            this.label6.TabIndex = 50;
            this.label6.Text = "dBm";
            // 
            // DP_FreqOKNG
            // 
            this.DP_FreqOKNG.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_FreqOKNG.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_FreqOKNG.Location = new System.Drawing.Point(188, 233);
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
            this.DP_PowerOKNG.Location = new System.Drawing.Point(188, 261);
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
            this.label7.Location = new System.Drawing.Point(194, 188);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 12);
            this.label7.TabIndex = 53;
            this.label7.Text = "OK/NG";
            // 
            // DP_Uart2_comboBox2
            // 
            this.DP_Uart2_comboBox2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DP_Uart2_comboBox2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart2_comboBox2.FormattingEnabled = true;
            this.DP_Uart2_comboBox2.Location = new System.Drawing.Point(31, 18);
            this.DP_Uart2_comboBox2.Name = "DP_Uart2_comboBox2";
            this.DP_Uart2_comboBox2.Size = new System.Drawing.Size(162, 20);
            this.DP_Uart2_comboBox2.TabIndex = 54;
            this.DP_Uart2_comboBox2.SelectedIndexChanged += new System.EventHandler(this.DP_Uart2_comboBox2_SelectedIndexChanged);
            this.DP_Uart2_comboBox2.Click += new System.EventHandler(this.DP_Uart2_comboBox2_Click);
            // 
            // DP_Uart_ScanCode
            // 
            this.DP_Uart_ScanCode.BackColor = System.Drawing.Color.LightSteelBlue;
            this.DP_Uart_ScanCode.Cursor = System.Windows.Forms.Cursors.Default;
            this.DP_Uart_ScanCode.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart_ScanCode.Location = new System.Drawing.Point(198, 14);
            this.DP_Uart_ScanCode.Name = "DP_Uart_ScanCode";
            this.DP_Uart_ScanCode.Size = new System.Drawing.Size(47, 27);
            this.DP_Uart_ScanCode.TabIndex = 55;
            this.DP_Uart_ScanCode.Text = "已关";
            this.DP_Uart_ScanCode.UseVisualStyleBackColor = false;
            this.DP_Uart_ScanCode.Click += new System.EventHandler(this.DP_Uart_ScanCode_Click);
            // 
            // DP_ScanCode
            // 
            this.DP_ScanCode.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_ScanCode.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_ScanCode.Location = new System.Drawing.Point(48, 158);
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
            this.label10.Location = new System.Drawing.Point(19, 165);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(23, 12);
            this.label10.TabIndex = 59;
            this.label10.Text = "ID:";
            // 
            // Freq_groupBox1
            // 
            this.Freq_groupBox1.Controls.Add(this.DP_FreqOFF);
            this.Freq_groupBox1.Controls.Add(this.DP_FreqON);
            this.Freq_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Freq_groupBox1.Location = new System.Drawing.Point(185, 17);
            this.Freq_groupBox1.Name = "Freq_groupBox1";
            this.Freq_groupBox1.Size = new System.Drawing.Size(153, 43);
            this.Freq_groupBox1.TabIndex = 61;
            this.Freq_groupBox1.TabStop = false;
            this.Freq_groupBox1.Text = "频谱仪RSA3000";
            // 
            // DP_FreqOFF
            // 
            this.DP_FreqOFF.AutoSize = true;
            this.DP_FreqOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_FreqOFF.Checked = true;
            this.DP_FreqOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_FreqOFF.Location = new System.Drawing.Point(85, 20);
            this.DP_FreqOFF.Name = "DP_FreqOFF";
            this.DP_FreqOFF.Size = new System.Drawing.Size(59, 16);
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
            this.DP_FreqON.Location = new System.Drawing.Point(6, 20);
            this.DP_FreqON.Name = "DP_FreqON";
            this.DP_FreqON.Size = new System.Drawing.Size(59, 16);
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
            this.Signal_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Signal_groupBox1.Location = new System.Drawing.Point(357, 16);
            this.Signal_groupBox1.Name = "Signal_groupBox1";
            this.Signal_groupBox1.Size = new System.Drawing.Size(153, 44);
            this.Signal_groupBox1.TabIndex = 62;
            this.Signal_groupBox1.TabStop = false;
            this.Signal_groupBox1.Text = "信号源DSG3000";
            this.Signal_groupBox1.Visible = false;
            // 
            // DP_SignalOFF
            // 
            this.DP_SignalOFF.AutoSize = true;
            this.DP_SignalOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_SignalOFF.Checked = true;
            this.DP_SignalOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_SignalOFF.Location = new System.Drawing.Point(85, 18);
            this.DP_SignalOFF.Name = "DP_SignalOFF";
            this.DP_SignalOFF.Size = new System.Drawing.Size(59, 16);
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
            this.DP_SignalON.Location = new System.Drawing.Point(6, 18);
            this.DP_SignalON.Name = "DP_SignalON";
            this.DP_SignalON.Size = new System.Drawing.Size(59, 16);
            this.DP_SignalON.TabIndex = 61;
            this.DP_SignalON.Text = "已连接";
            this.DP_SignalON.UseVisualStyleBackColor = false;
            // 
            // V_groupBox1
            // 
            this.V_groupBox1.Controls.Add(this.DP_DMMOFF);
            this.V_groupBox1.Controls.Add(this.DP_DMMON);
            this.V_groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.V_groupBox1.Location = new System.Drawing.Point(10, 16);
            this.V_groupBox1.Name = "V_groupBox1";
            this.V_groupBox1.Size = new System.Drawing.Size(153, 44);
            this.V_groupBox1.TabIndex = 63;
            this.V_groupBox1.TabStop = false;
            this.V_groupBox1.Text = "数字万用表DM3000";
            // 
            // DP_DMMOFF
            // 
            this.DP_DMMOFF.AutoSize = true;
            this.DP_DMMOFF.BackColor = System.Drawing.SystemColors.Control;
            this.DP_DMMOFF.Checked = true;
            this.DP_DMMOFF.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DP_DMMOFF.Location = new System.Drawing.Point(85, 20);
            this.DP_DMMOFF.Name = "DP_DMMOFF";
            this.DP_DMMOFF.Size = new System.Drawing.Size(59, 16);
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
            this.DP_DMMON.Location = new System.Drawing.Point(6, 20);
            this.DP_DMMON.Name = "DP_DMMON";
            this.DP_DMMON.Size = new System.Drawing.Size(59, 16);
            this.DP_DMMON.TabIndex = 61;
            this.DP_DMMON.Text = "已连接";
            this.DP_DMMON.UseVisualStyleBackColor = false;
            this.DP_DMMON.CheckedChanged += new System.EventHandler(this.DP_DMMON_CheckedChanged);
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
            this.Tx_Read_ReceSensit.Location = new System.Drawing.Point(857, 103);
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
            this.Tx_ReadIV.Location = new System.Drawing.Point(1019, 74);
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
            this.DP_I.Location = new System.Drawing.Point(55, 203);
            this.DP_I.Multiline = true;
            this.DP_I.Name = "DP_I";
            this.DP_I.ReadOnly = true;
            this.DP_I.Size = new System.Drawing.Size(102, 27);
            this.DP_I.TabIndex = 66;
            this.DP_I.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.DP_I.TextChanged += new System.EventHandler(this.DP_I_TextChanged);
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
            this.label12.Location = new System.Drawing.Point(157, 209);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 68;
            this.label12.Text = "mA";
            this.label12.Click += new System.EventHandler(this.label12_Click);
            // 
            // DP_I_OKNG
            // 
            this.DP_I_OKNG.BackColor = System.Drawing.SystemColors.Menu;
            this.DP_I_OKNG.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_I_OKNG.Location = new System.Drawing.Point(188, 205);
            this.DP_I_OKNG.Multiline = true;
            this.DP_I_OKNG.Name = "DP_I_OKNG";
            this.DP_I_OKNG.ReadOnly = true;
            this.DP_I_OKNG.Size = new System.Drawing.Size(62, 27);
            this.DP_I_OKNG.TabIndex = 69;
            this.DP_I_OKNG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.DP_I_OKNG.TextChanged += new System.EventHandler(this.DP_I_OKNG_TextChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox6);
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Location = new System.Drawing.Point(21, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(779, 76);
            this.groupBox1.TabIndex = 70;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设置";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.label16);
            this.groupBox6.Controls.Add(this.DP_Uart3_comboBox3);
            this.groupBox6.Controls.Add(this.DP_Uart_WriteID);
            this.groupBox6.Location = new System.Drawing.Point(516, 17);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(252, 46);
            this.groupBox6.TabIndex = 2;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "写ID：USB Serial Port（COMx）";
            // 
            // label16
            // 
            this.label16.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(1, 21);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(29, 12);
            this.label16.TabIndex = 72;
            this.label16.Text = "端口";
            // 
            // DP_Uart3_comboBox3
            // 
            this.DP_Uart3_comboBox3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DP_Uart3_comboBox3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart3_comboBox3.FormattingEnabled = true;
            this.DP_Uart3_comboBox3.Location = new System.Drawing.Point(30, 17);
            this.DP_Uart3_comboBox3.Name = "DP_Uart3_comboBox3";
            this.DP_Uart3_comboBox3.Size = new System.Drawing.Size(162, 20);
            this.DP_Uart3_comboBox3.TabIndex = 1;
            this.DP_Uart3_comboBox3.SelectedIndexChanged += new System.EventHandler(this.DP_Uart3_comboBox3_SelectedIndexChanged);
            this.DP_Uart3_comboBox3.Click += new System.EventHandler(this.DP_Uart3_comboBox3_Click);
            // 
            // DP_Uart_WriteID
            // 
            this.DP_Uart_WriteID.BackColor = System.Drawing.Color.LightSteelBlue;
            this.DP_Uart_WriteID.Cursor = System.Windows.Forms.Cursors.Default;
            this.DP_Uart_WriteID.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DP_Uart_WriteID.Location = new System.Drawing.Point(197, 13);
            this.DP_Uart_WriteID.Name = "DP_Uart_WriteID";
            this.DP_Uart_WriteID.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.DP_Uart_WriteID.Size = new System.Drawing.Size(50, 27);
            this.DP_Uart_WriteID.TabIndex = 35;
            this.DP_Uart_WriteID.Text = "已关";
            this.DP_Uart_WriteID.UseVisualStyleBackColor = false;
            this.DP_Uart_WriteID.Click += new System.EventHandler(this.DP_Uart_WriteID_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.DP_Uart1_comboBox1);
            this.groupBox3.Controls.Add(this.DP_Uart_OpenClose);
            this.groupBox3.Location = new System.Drawing.Point(258, 17);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(252, 46);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "继电器：USB Serial Port（COMx）";
            // 
            // label8
            // 
            this.label8.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(1, 21);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 72;
            this.label8.Text = "端口";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.DP_Uart_ScanCode);
            this.groupBox2.Controls.Add(this.comtxt);
            this.groupBox2.Controls.Add(this.DP_Uart2_comboBox2);
            this.groupBox2.Location = new System.Drawing.Point(6, 17);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(246, 46);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "扫描枪：Xenon 1900（COMx）";
            // 
            // label13
            // 
            this.label13.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(2, 21);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(29, 12);
            this.label13.TabIndex = 71;
            this.label13.Text = "端口";
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(-29, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 71;
            this.label1.Text = "端口";
            // 
            // comtxt
            // 
            this.comtxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.comtxt.AutoSize = true;
            this.comtxt.Location = new System.Drawing.Point(-63, 21);
            this.comtxt.Name = "comtxt";
            this.comtxt.Size = new System.Drawing.Size(29, 12);
            this.comtxt.TabIndex = 71;
            this.comtxt.Text = "端口";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.Freq_groupBox1);
            this.groupBox4.Controls.Add(this.V_groupBox1);
            this.groupBox4.Controls.Add(this.Signal_groupBox1);
            this.groupBox4.Location = new System.Drawing.Point(238, 85);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(350, 66);
            this.groupBox4.TabIndex = 71;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "状态";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(19, 209);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 12);
            this.label9.TabIndex = 72;
            this.label9.Text = "电流：";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // Display_Results
            // 
            this.Display_Results.AutoSize = true;
            this.Display_Results.Font = new System.Drawing.Font("宋体", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Display_Results.ForeColor = System.Drawing.Color.Red;
            this.Display_Results.Location = new System.Drawing.Point(481, 238);
            this.Display_Results.Name = "Display_Results";
            this.Display_Results.Size = new System.Drawing.Size(70, 48);
            this.Display_Results.TabIndex = 73;
            this.Display_Results.Text = "OK";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.NG_num);
            this.groupBox5.Controls.Add(this.OK_num);
            this.groupBox5.Controls.Add(this.label15);
            this.groupBox5.Controls.Add(this.label14);
            this.groupBox5.Location = new System.Drawing.Point(609, 240);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(120, 57);
            this.groupBox5.TabIndex = 74;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "统计";
            // 
            // NG_num
            // 
            this.NG_num.AutoSize = true;
            this.NG_num.Location = new System.Drawing.Point(33, 39);
            this.NG_num.Name = "NG_num";
            this.NG_num.Size = new System.Drawing.Size(11, 12);
            this.NG_num.TabIndex = 3;
            this.NG_num.Text = "0";
            // 
            // OK_num
            // 
            this.OK_num.AutoSize = true;
            this.OK_num.Location = new System.Drawing.Point(33, 17);
            this.OK_num.Name = "OK_num";
            this.OK_num.Size = new System.Drawing.Size(11, 12);
            this.OK_num.TabIndex = 2;
            this.OK_num.Text = "0";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(6, 39);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(29, 12);
            this.label15.TabIndex = 1;
            this.label15.Text = "NG：";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 17);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(29, 12);
            this.label14.TabIndex = 0;
            this.label14.Text = "OK：";
            // 
            // serialPort3
            // 
            this.serialPort3.ReadTimeout = 50;
            // 
            // UART3_WriteID_Received_textBox
            // 
            this.UART3_WriteID_Received_textBox.Location = new System.Drawing.Point(857, 156);
            this.UART3_WriteID_Received_textBox.Name = "UART3_WriteID_Received_textBox";
            this.UART3_WriteID_Received_textBox.Size = new System.Drawing.Size(124, 21);
            this.UART3_WriteID_Received_textBox.TabIndex = 75;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.ID_Selcet_comboBox);
            this.groupBox7.Location = new System.Drawing.Point(21, 85);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(196, 66);
            this.groupBox7.TabIndex = 76;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "机种选择";
            // 
            // ID_Selcet_comboBox
            // 
            this.ID_Selcet_comboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ID_Selcet_comboBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ID_Selcet_comboBox.Items.AddRange(new object[] {
            "STX0011",
            "STX0031",
            "STX1231(A)",
            "STX1531K",
            "CTX1531TN",
            "STX1631PB",
            "STX1731(A)",
            "STX0011-SR",
            "STX0031-SR",
            "STX1531K-SR",
            "STX0011-SSR",
            "STX0031-SSR",
            "STX1531K-SSR",
            "STX0011-SSH",
            "STX0031-SSH",
            "STX0531K-SSH",
            "其它"});
            this.ID_Selcet_comboBox.Location = new System.Drawing.Point(9, 30);
            this.ID_Selcet_comboBox.Name = "ID_Selcet_comboBox";
            this.ID_Selcet_comboBox.Size = new System.Drawing.Size(174, 27);
            this.ID_Selcet_comboBox.TabIndex = 0;
            this.ID_Selcet_comboBox.SelectedIndexChanged += new System.EventHandler(this.ID_Selcet_comboBox_SelectedIndexChanged);
            this.ID_Selcet_comboBox.Click += new System.EventHandler(this.ID_Selcet_comboBox_Click);
            // 
            // timer3
            // 
            this.timer3.Tick += new System.EventHandler(this.timer3_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(809, 680);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.UART3_WriteID_Received_textBox);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.Display_Results);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.DP_I_OKNG);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.DP_I);
            this.Controls.Add(this.Tx_ReadIV);
            this.Controls.Add(this.Tx_Read_ReceSensit);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.DP_ScanCode);
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
            this.Controls.Add(this.Tx_Modula);
            this.Controls.Add(this.Tx_Rece_Sensit);
            this.Controls.Add(this.Tx_Carrier);
            this.Controls.Add(this.EXIT_TEST);
            this.Controls.Add(this.TEST_Mode);
            this.Controls.Add(this.label9);
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "文化送信机无线测试 Ver0.01";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.SignlSource_GroupBox.ResumeLayout(false);
            this.SignlSource_GroupBox.PerformLayout();
            this.Freq_groupBox1.ResumeLayout(false);
            this.Freq_groupBox1.PerformLayout();
            this.Signal_groupBox1.ResumeLayout(false);
            this.Signal_groupBox1.PerformLayout();
            this.V_groupBox1.ResumeLayout(false);
            this.V_groupBox1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox DP_Uart1_comboBox1;
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
        private System.Windows.Forms.TextBox DP_ScanCode;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox Freq_groupBox1;
        private System.Windows.Forms.RadioButton DP_FreqOFF;
        private System.Windows.Forms.RadioButton DP_FreqON;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox Signal_groupBox1;
        private System.Windows.Forms.RadioButton DP_SignalOFF;
        private System.Windows.Forms.RadioButton DP_SignalON;
        private System.Windows.Forms.GroupBox V_groupBox1;
        private System.Windows.Forms.RadioButton DP_DMMOFF;
        private System.Windows.Forms.RadioButton DP_DMMON;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Button Tx_Read_ReceSensit;
        private System.Windows.Forms.Button Tx_ReadIV;
        private System.Windows.Forms.TextBox DP_I;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox DP_I_OKNG;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label comtxt;
        private System.Windows.Forms.Label Display_Results;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label NG_num;
        private System.Windows.Forms.Label OK_num;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.IO.Ports.SerialPort serialPort3;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.ComboBox DP_Uart3_comboBox3;
        private System.Windows.Forms.Button DP_Uart_WriteID;
        private System.Windows.Forms.TextBox UART3_WriteID_Received_textBox;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.ComboBox ID_Selcet_comboBox;
        private System.Windows.Forms.Timer timer3;
    }
}

