namespace WindowsFormsApplication2
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.receivingarea = new System.Windows.Forms.GroupBox();
            this.receivebuf = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.send = new System.Windows.Forms.Button();
            this.sendingarea = new System.Windows.Forms.GroupBox();
            this.sendbuf = new System.Windows.Forms.TextBox();
            this.SendDelaytxt1 = new System.Windows.Forms.Label();
            this.send16 = new System.Windows.Forms.CheckBox();
            this.SendDelaytxt = new System.Windows.Forms.Label();
            this.sendnewline = new System.Windows.Forms.CheckBox();
            this.timersend = new System.Windows.Forms.CheckBox();
            this.SendDelay = new System.Windows.Forms.TextBox();
            this.clearsend = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.comstats = new System.Windows.Forms.Label();
            this.clrcnt = new System.Windows.Forms.Button();
            this.lblSCount = new System.Windows.Forms.Label();
            this.lblRCount = new System.Windows.Forms.Label();
            this.stopsend = new System.Windows.Forms.Button();
            this.receiveB = new System.Windows.Forms.Label();
            this.sendpercentage = new System.Windows.Forms.Label();
            this.sendB = new System.Windows.Forms.Label();
            this.sendprogressBar = new System.Windows.Forms.ProgressBar();
            this.SendFile = new System.Windows.Forms.Button();
            this.OpenFile = new System.Windows.Forms.Button();
            this.setarea = new System.Windows.Forms.GroupBox();
            this.open_close_UART1 = new System.Windows.Forms.Button();
            this.savefile = new System.Windows.Forms.Button();
            this.clrreceive = new System.Windows.Forms.Button();
            this.check = new System.Windows.Forms.ComboBox();
            this.checktxt = new System.Windows.Forms.Label();
            this.databit = new System.Windows.Forms.ComboBox();
            this.databittxt = new System.Windows.Forms.Label();
            this.stopbit = new System.Windows.Forms.ComboBox();
            this.stopbittxt = new System.Windows.Forms.Label();
            this.baudrate = new System.Windows.Forms.ComboBox();
            this.display16 = new System.Windows.Forms.CheckBox();
            this.com = new System.Windows.Forms.ComboBox();
            this.receivedisplaycolor = new System.Windows.Forms.CheckBox();
            this.baudratetxt = new System.Windows.Forms.Label();
            this.comtxt = new System.Windows.Forms.Label();
            this.closecom = new System.Windows.Forms.Button();
            this.opencom = new System.Windows.Forms.Button();
            this.serialPort2 = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.open_close_UART2 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.check2 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.databit2 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.stopbit2 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.baudrate2 = new System.Windows.Forms.ComboBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.PCB_uart = new System.Windows.Forms.ComboBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.Label_select = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.InitprinterComboBox = new System.Windows.Forms.ComboBox();
            this.PrintLabNum = new System.Windows.Forms.TextBox();
            this.StartButton = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.KEYTextBox = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.SSIDTextBox = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.DEVICETextBox = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.LOTTextBox = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.PCBMACTextBox = new System.Windows.Forms.TextBox();
            this.datatime = new System.Windows.Forms.Label();
            this.UART1textBox = new System.Windows.Forms.TextBox();
            this.UART2textBox = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.ID_Box = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.Display_Results = new System.Windows.Forms.Label();
            this.receivingarea.SuspendLayout();
            this.sendingarea.SuspendLayout();
            this.panel2.SuspendLayout();
            this.setarea.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // receivingarea
            // 
            this.receivingarea.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.receivingarea.Controls.Add(this.receivebuf);
            this.receivingarea.Location = new System.Drawing.Point(13, 141);
            this.receivingarea.Name = "receivingarea";
            this.receivingarea.Size = new System.Drawing.Size(804, 432);
            this.receivingarea.TabIndex = 18;
            this.receivingarea.TabStop = false;
            this.receivingarea.Text = "Debug Log";
            // 
            // receivebuf
            // 
            this.receivebuf.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.receivebuf.BackColor = System.Drawing.Color.Black;
            this.receivebuf.ForeColor = System.Drawing.Color.LawnGreen;
            this.receivebuf.Location = new System.Drawing.Point(0, 21);
            this.receivebuf.Multiline = true;
            this.receivebuf.Name = "receivebuf";
            this.receivebuf.ReadOnly = true;
            this.receivebuf.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.receivebuf.Size = new System.Drawing.Size(798, 405);
            this.receivebuf.TabIndex = 13;
            this.receivebuf.TextChanged += new System.EventHandler(this.receivebuf_TextChanged);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // send
            // 
            this.send.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.send.Font = new System.Drawing.Font("宋体", 12F);
            this.send.Location = new System.Drawing.Point(814, 23);
            this.send.Name = "send";
            this.send.Size = new System.Drawing.Size(96, 27);
            this.send.TabIndex = 23;
            this.send.Text = "发送";
            this.send.UseVisualStyleBackColor = true;
            this.send.Click += new System.EventHandler(this.button3_Click);
            // 
            // sendingarea
            // 
            this.sendingarea.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.sendingarea.Controls.Add(this.sendbuf);
            this.sendingarea.Controls.Add(this.SendDelaytxt1);
            this.sendingarea.Controls.Add(this.send16);
            this.sendingarea.Controls.Add(this.SendDelaytxt);
            this.sendingarea.Controls.Add(this.sendnewline);
            this.sendingarea.Controls.Add(this.timersend);
            this.sendingarea.Controls.Add(this.SendDelay);
            this.sendingarea.Location = new System.Drawing.Point(3, 3);
            this.sendingarea.Name = "sendingarea";
            this.sendingarea.Size = new System.Drawing.Size(780, 160);
            this.sendingarea.TabIndex = 24;
            this.sendingarea.TabStop = false;
            this.sendingarea.Text = "发送区";
            // 
            // sendbuf
            // 
            this.sendbuf.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.sendbuf.Location = new System.Drawing.Point(-3, 21);
            this.sendbuf.Multiline = true;
            this.sendbuf.Name = "sendbuf";
            this.sendbuf.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.sendbuf.Size = new System.Drawing.Size(783, 133);
            this.sendbuf.TabIndex = 14;
            this.sendbuf.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox2_KeyPress);
            // 
            // SendDelaytxt1
            // 
            this.SendDelaytxt1.AutoSize = true;
            this.SendDelaytxt1.Font = new System.Drawing.Font("宋体", 10F);
            this.SendDelaytxt1.Location = new System.Drawing.Point(355, 2);
            this.SendDelaytxt1.Name = "SendDelaytxt1";
            this.SendDelaytxt1.Size = new System.Drawing.Size(21, 14);
            this.SendDelaytxt1.TabIndex = 33;
            this.SendDelaytxt1.Text = "ms";
            // 
            // send16
            // 
            this.send16.AutoSize = true;
            this.send16.Font = new System.Drawing.Font("宋体", 10F);
            this.send16.Location = new System.Drawing.Point(62, 2);
            this.send16.Name = "send16";
            this.send16.Size = new System.Drawing.Size(96, 18);
            this.send16.TabIndex = 29;
            this.send16.Text = "16进制发送";
            this.send16.UseVisualStyleBackColor = true;
            // 
            // SendDelaytxt
            // 
            this.SendDelaytxt.AutoSize = true;
            this.SendDelaytxt.Font = new System.Drawing.Font("宋体", 10F);
            this.SendDelaytxt.Location = new System.Drawing.Point(252, 4);
            this.SendDelaytxt.Name = "SendDelaytxt";
            this.SendDelaytxt.Size = new System.Drawing.Size(35, 14);
            this.SendDelaytxt.TabIndex = 32;
            this.SendDelaytxt.Text = "周期";
            // 
            // sendnewline
            // 
            this.sendnewline.AutoSize = true;
            this.sendnewline.Font = new System.Drawing.Font("宋体", 10F);
            this.sendnewline.Location = new System.Drawing.Point(164, 2);
            this.sendnewline.Name = "sendnewline";
            this.sendnewline.Size = new System.Drawing.Size(82, 18);
            this.sendnewline.TabIndex = 30;
            this.sendnewline.Text = "发送新行";
            this.sendnewline.UseVisualStyleBackColor = true;
            // 
            // timersend
            // 
            this.timersend.AutoSize = true;
            this.timersend.Font = new System.Drawing.Font("宋体", 10F);
            this.timersend.Location = new System.Drawing.Point(382, 2);
            this.timersend.Name = "timersend";
            this.timersend.Size = new System.Drawing.Size(82, 18);
            this.timersend.TabIndex = 28;
            this.timersend.Text = "定时发送";
            this.timersend.UseVisualStyleBackColor = true;
            this.timersend.CheckedChanged += new System.EventHandler(this.timersend_CheckedChanged);
            // 
            // SendDelay
            // 
            this.SendDelay.Location = new System.Drawing.Point(293, 0);
            this.SendDelay.MaxLength = 8;
            this.SendDelay.Name = "SendDelay";
            this.SendDelay.Size = new System.Drawing.Size(56, 21);
            this.SendDelay.TabIndex = 31;
            this.SendDelay.Text = "1000";
            this.SendDelay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtSendDelay_KeyPress);
            // 
            // clearsend
            // 
            this.clearsend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.clearsend.Font = new System.Drawing.Font("宋体", 12F);
            this.clearsend.Location = new System.Drawing.Point(814, 114);
            this.clearsend.Name = "clearsend";
            this.clearsend.Size = new System.Drawing.Size(96, 27);
            this.clearsend.TabIndex = 25;
            this.clearsend.Text = "清除发送";
            this.clearsend.UseVisualStyleBackColor = true;
            this.clearsend.Click += new System.EventHandler(this.button4_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.comstats);
            this.panel2.Controls.Add(this.clrcnt);
            this.panel2.Controls.Add(this.lblSCount);
            this.panel2.Controls.Add(this.lblRCount);
            this.panel2.Controls.Add(this.stopsend);
            this.panel2.Controls.Add(this.receiveB);
            this.panel2.Controls.Add(this.sendpercentage);
            this.panel2.Controls.Add(this.clearsend);
            this.panel2.Controls.Add(this.sendB);
            this.panel2.Controls.Add(this.sendprogressBar);
            this.panel2.Controls.Add(this.sendingarea);
            this.panel2.Controls.Add(this.send);
            this.panel2.Controls.Add(this.SendFile);
            this.panel2.Controls.Add(this.OpenFile);
            this.panel2.Location = new System.Drawing.Point(8, 598);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(911, 199);
            this.panel2.TabIndex = 1;
            // 
            // comstats
            // 
            this.comstats.AutoSize = true;
            this.comstats.Location = new System.Drawing.Point(3, 182);
            this.comstats.Name = "comstats";
            this.comstats.Size = new System.Drawing.Size(35, 12);
            this.comstats.TabIndex = 45;
            this.comstats.Text = "CLOSE";
            // 
            // clrcnt
            // 
            this.clrcnt.Location = new System.Drawing.Point(195, 170);
            this.clrcnt.Name = "clrcnt";
            this.clrcnt.Size = new System.Drawing.Size(75, 24);
            this.clrcnt.TabIndex = 35;
            this.clrcnt.Text = "计数清零";
            this.clrcnt.UseVisualStyleBackColor = true;
            this.clrcnt.Click += new System.EventHandler(this.clrcnt_Click);
            // 
            // lblSCount
            // 
            this.lblSCount.AutoSize = true;
            this.lblSCount.Location = new System.Drawing.Point(294, 177);
            this.lblSCount.Name = "lblSCount";
            this.lblSCount.Size = new System.Drawing.Size(11, 12);
            this.lblSCount.TabIndex = 37;
            this.lblSCount.Text = "0";
            // 
            // lblRCount
            // 
            this.lblRCount.AutoSize = true;
            this.lblRCount.Location = new System.Drawing.Point(364, 177);
            this.lblRCount.Name = "lblRCount";
            this.lblRCount.Size = new System.Drawing.Size(11, 12);
            this.lblRCount.TabIndex = 39;
            this.lblRCount.Text = "0";
            // 
            // stopsend
            // 
            this.stopsend.Location = new System.Drawing.Point(830, 167);
            this.stopsend.Name = "stopsend";
            this.stopsend.Size = new System.Drawing.Size(97, 27);
            this.stopsend.TabIndex = 42;
            this.stopsend.Text = "停止发送";
            this.stopsend.UseVisualStyleBackColor = true;
            this.stopsend.Click += new System.EventHandler(this.stopsend_Click);
            // 
            // receiveB
            // 
            this.receiveB.AutoSize = true;
            this.receiveB.Font = new System.Drawing.Font("宋体", 10F);
            this.receiveB.Location = new System.Drawing.Point(347, 175);
            this.receiveB.Name = "receiveB";
            this.receiveB.Size = new System.Drawing.Size(21, 14);
            this.receiveB.TabIndex = 38;
            this.receiveB.Text = "R:";
            // 
            // sendpercentage
            // 
            this.sendpercentage.AutoSize = true;
            this.sendpercentage.Font = new System.Drawing.Font("宋体", 10F);
            this.sendpercentage.Location = new System.Drawing.Point(790, 172);
            this.sendpercentage.Name = "sendpercentage";
            this.sendpercentage.Size = new System.Drawing.Size(21, 14);
            this.sendpercentage.TabIndex = 44;
            this.sendpercentage.Text = "0%";
            // 
            // sendB
            // 
            this.sendB.AutoSize = true;
            this.sendB.Font = new System.Drawing.Font("宋体", 10F);
            this.sendB.Location = new System.Drawing.Point(276, 175);
            this.sendB.Name = "sendB";
            this.sendB.Size = new System.Drawing.Size(21, 14);
            this.sendB.TabIndex = 36;
            this.sendB.Text = "S:";
            // 
            // sendprogressBar
            // 
            this.sendprogressBar.Location = new System.Drawing.Point(606, 171);
            this.sendprogressBar.Name = "sendprogressBar";
            this.sendprogressBar.Size = new System.Drawing.Size(178, 18);
            this.sendprogressBar.TabIndex = 43;
            // 
            // SendFile
            // 
            this.SendFile.Location = new System.Drawing.Point(525, 169);
            this.SendFile.Name = "SendFile";
            this.SendFile.Size = new System.Drawing.Size(75, 24);
            this.SendFile.TabIndex = 41;
            this.SendFile.Text = "发送文件";
            this.SendFile.UseVisualStyleBackColor = true;
            this.SendFile.Click += new System.EventHandler(this.SendFile_Click);
            // 
            // OpenFile
            // 
            this.OpenFile.Location = new System.Drawing.Point(434, 169);
            this.OpenFile.Name = "OpenFile";
            this.OpenFile.Size = new System.Drawing.Size(75, 24);
            this.OpenFile.TabIndex = 40;
            this.OpenFile.Text = "打开文件";
            this.OpenFile.UseVisualStyleBackColor = true;
            this.OpenFile.Click += new System.EventHandler(this.OpenFile_Click);
            // 
            // setarea
            // 
            this.setarea.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.setarea.Controls.Add(this.open_close_UART1);
            this.setarea.Controls.Add(this.savefile);
            this.setarea.Controls.Add(this.clrreceive);
            this.setarea.Controls.Add(this.check);
            this.setarea.Controls.Add(this.checktxt);
            this.setarea.Controls.Add(this.databit);
            this.setarea.Controls.Add(this.databittxt);
            this.setarea.Controls.Add(this.stopbit);
            this.setarea.Controls.Add(this.stopbittxt);
            this.setarea.Controls.Add(this.baudrate);
            this.setarea.Controls.Add(this.display16);
            this.setarea.Controls.Add(this.com);
            this.setarea.Controls.Add(this.receivedisplaycolor);
            this.setarea.Controls.Add(this.baudratetxt);
            this.setarea.Controls.Add(this.comtxt);
            this.setarea.Controls.Add(this.closecom);
            this.setarea.Controls.Add(this.opencom);
            this.setarea.Location = new System.Drawing.Point(11, 24);
            this.setarea.Name = "setarea";
            this.setarea.Size = new System.Drawing.Size(286, 51);
            this.setarea.TabIndex = 17;
            this.setarea.TabStop = false;
            this.setarea.Text = "扫码枪:Xenon 1900 (COMx)";
            // 
            // open_close_UART1
            // 
            this.open_close_UART1.Location = new System.Drawing.Point(205, 14);
            this.open_close_UART1.Name = "open_close_UART1";
            this.open_close_UART1.Size = new System.Drawing.Size(72, 29);
            this.open_close_UART1.TabIndex = 28;
            this.open_close_UART1.Text = "打开";
            this.open_close_UART1.UseVisualStyleBackColor = true;
            this.open_close_UART1.Click += new System.EventHandler(this.open_close_UART1_Click);
            // 
            // savefile
            // 
            this.savefile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.savefile.Font = new System.Drawing.Font("宋体", 10F);
            this.savefile.Location = new System.Drawing.Point(181, 257);
            this.savefile.Name = "savefile";
            this.savefile.Size = new System.Drawing.Size(87, 27);
            this.savefile.TabIndex = 27;
            this.savefile.Text = "保存窗口";
            this.savefile.UseVisualStyleBackColor = true;
            this.savefile.Click += new System.EventHandler(this.savefile_Click);
            // 
            // clrreceive
            // 
            this.clrreceive.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.clrreceive.Font = new System.Drawing.Font("宋体", 10F);
            this.clrreceive.Location = new System.Drawing.Point(45, 257);
            this.clrreceive.Name = "clrreceive";
            this.clrreceive.Size = new System.Drawing.Size(75, 27);
            this.clrreceive.TabIndex = 26;
            this.clrreceive.Text = "清除接收";
            this.clrreceive.UseVisualStyleBackColor = true;
            this.clrreceive.Click += new System.EventHandler(this.button5_Click);
            // 
            // check
            // 
            this.check.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.check.FormattingEnabled = true;
            this.check.Items.AddRange(new object[] {
            "无",
            "奇校验",
            "偶校验"});
            this.check.Location = new System.Drawing.Point(107, 160);
            this.check.Name = "check";
            this.check.Size = new System.Drawing.Size(161, 20);
            this.check.TabIndex = 25;
            // 
            // checktxt
            // 
            this.checktxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checktxt.AutoSize = true;
            this.checktxt.Location = new System.Drawing.Point(48, 163);
            this.checktxt.Name = "checktxt";
            this.checktxt.Size = new System.Drawing.Size(53, 12);
            this.checktxt.TabIndex = 24;
            this.checktxt.Text = "奇偶校验";
            // 
            // databit
            // 
            this.databit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.databit.FormattingEnabled = true;
            this.databit.Items.AddRange(new object[] {
            "8",
            "7",
            "6",
            "5"});
            this.databit.Location = new System.Drawing.Point(107, 123);
            this.databit.Name = "databit";
            this.databit.Size = new System.Drawing.Size(161, 20);
            this.databit.TabIndex = 23;
            // 
            // databittxt
            // 
            this.databittxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.databittxt.AutoSize = true;
            this.databittxt.Location = new System.Drawing.Point(48, 126);
            this.databittxt.Name = "databittxt";
            this.databittxt.Size = new System.Drawing.Size(41, 12);
            this.databittxt.TabIndex = 22;
            this.databittxt.Text = "数据位";
            // 
            // stopbit
            // 
            this.stopbit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.stopbit.FormattingEnabled = true;
            this.stopbit.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.stopbit.Location = new System.Drawing.Point(107, 87);
            this.stopbit.Name = "stopbit";
            this.stopbit.Size = new System.Drawing.Size(161, 20);
            this.stopbit.TabIndex = 21;
            // 
            // stopbittxt
            // 
            this.stopbittxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.stopbittxt.AutoSize = true;
            this.stopbittxt.Location = new System.Drawing.Point(48, 87);
            this.stopbittxt.Name = "stopbittxt";
            this.stopbittxt.Size = new System.Drawing.Size(41, 12);
            this.stopbittxt.TabIndex = 20;
            this.stopbittxt.Text = "停止位";
            // 
            // baudrate
            // 
            this.baudrate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.baudrate.FormattingEnabled = true;
            this.baudrate.Items.AddRange(new object[] {
            "自定义",
            "1382400",
            "961200",
            "460800",
            "256000",
            "230400",
            "128000",
            "115200",
            "76800",
            "57600",
            "43000",
            "38400",
            "19200",
            "14400",
            "9600",
            "4800",
            "2400",
            "1200"});
            this.baudrate.Location = new System.Drawing.Point(107, 54);
            this.baudrate.Name = "baudrate";
            this.baudrate.Size = new System.Drawing.Size(161, 20);
            this.baudrate.TabIndex = 11;
            this.baudrate.SelectedIndexChanged += new System.EventHandler(this.baudrate_SelectedIndexChanged);
            // 
            // display16
            // 
            this.display16.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.display16.AutoSize = true;
            this.display16.Font = new System.Drawing.Font("宋体", 10F);
            this.display16.Location = new System.Drawing.Point(181, 302);
            this.display16.Name = "display16";
            this.display16.Size = new System.Drawing.Size(96, 18);
            this.display16.TabIndex = 19;
            this.display16.Text = "16进制显示";
            this.display16.UseVisualStyleBackColor = true;
            this.display16.CheckedChanged += new System.EventHandler(this.display16_CheckedChanged);
            // 
            // com
            // 
            this.com.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.com.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.com.FormattingEnabled = true;
            this.com.Location = new System.Drawing.Point(38, 18);
            this.com.Name = "com";
            this.com.Size = new System.Drawing.Size(158, 20);
            this.com.TabIndex = 10;
            this.com.SelectedIndexChanged += new System.EventHandler(this.com_SelectedIndexChanged);
            this.com.Click += new System.EventHandler(this.com_Click);
            // 
            // receivedisplaycolor
            // 
            this.receivedisplaycolor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.receivedisplaycolor.AutoSize = true;
            this.receivedisplaycolor.Font = new System.Drawing.Font("宋体", 10F);
            this.receivedisplaycolor.Location = new System.Drawing.Point(45, 302);
            this.receivedisplaycolor.Name = "receivedisplaycolor";
            this.receivedisplaycolor.Size = new System.Drawing.Size(82, 18);
            this.receivedisplaycolor.TabIndex = 18;
            this.receivedisplaycolor.Text = "白底黑字";
            this.receivedisplaycolor.UseVisualStyleBackColor = true;
            this.receivedisplaycolor.CheckedChanged += new System.EventHandler(this.receivedisplaycolor_CheckedChanged);
            // 
            // baudratetxt
            // 
            this.baudratetxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.baudratetxt.AutoSize = true;
            this.baudratetxt.Location = new System.Drawing.Point(48, 57);
            this.baudratetxt.Name = "baudratetxt";
            this.baudratetxt.Size = new System.Drawing.Size(41, 12);
            this.baudratetxt.TabIndex = 7;
            this.baudratetxt.Text = "波特率";
            // 
            // comtxt
            // 
            this.comtxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.comtxt.AutoSize = true;
            this.comtxt.Location = new System.Drawing.Point(7, 21);
            this.comtxt.Name = "comtxt";
            this.comtxt.Size = new System.Drawing.Size(29, 12);
            this.comtxt.TabIndex = 6;
            this.comtxt.Text = "端口";
            // 
            // closecom
            // 
            this.closecom.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.closecom.Font = new System.Drawing.Font("宋体", 10F);
            this.closecom.Location = new System.Drawing.Point(181, 203);
            this.closecom.Name = "closecom";
            this.closecom.Size = new System.Drawing.Size(87, 33);
            this.closecom.TabIndex = 5;
            this.closecom.Text = "关闭串口";
            this.closecom.UseVisualStyleBackColor = true;
            this.closecom.Click += new System.EventHandler(this.button2_Click);
            // 
            // opencom
            // 
            this.opencom.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.opencom.Font = new System.Drawing.Font("宋体", 10F);
            this.opencom.Location = new System.Drawing.Point(45, 203);
            this.opencom.Name = "opencom";
            this.opencom.Size = new System.Drawing.Size(75, 33);
            this.opencom.TabIndex = 4;
            this.opencom.Text = "打开串口";
            this.opencom.UseVisualStyleBackColor = true;
            this.opencom.Click += new System.EventHandler(this.button1_Click);
            // 
            // serialPort2
            // 
            this.serialPort2.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort2_DataReceived);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.open_close_UART2);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.check2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.databit2);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.stopbit2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.baudrate2);
            this.groupBox1.Controls.Add(this.checkBox1);
            this.groupBox1.Controls.Add(this.PCB_uart);
            this.groupBox1.Controls.Add(this.checkBox2);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.button4);
            this.groupBox1.Controls.Add(this.button5);
            this.groupBox1.Location = new System.Drawing.Point(317, 25);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(298, 50);
            this.groupBox1.TabIndex = 35;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "PCB:  USB Serial Port (COMx)";
            // 
            // open_close_UART2
            // 
            this.open_close_UART2.Location = new System.Drawing.Point(217, 13);
            this.open_close_UART2.Name = "open_close_UART2";
            this.open_close_UART2.Size = new System.Drawing.Size(72, 29);
            this.open_close_UART2.TabIndex = 28;
            this.open_close_UART2.Text = "打开";
            this.open_close_UART2.UseVisualStyleBackColor = true;
            this.open_close_UART2.Click += new System.EventHandler(this.open_close_UART2_Click);
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.Font = new System.Drawing.Font("宋体", 10F);
            this.button2.Location = new System.Drawing.Point(193, 257);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(87, 27);
            this.button2.TabIndex = 27;
            this.button2.Text = "保存窗口";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button3.Font = new System.Drawing.Font("宋体", 10F);
            this.button3.Location = new System.Drawing.Point(57, 257);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 27);
            this.button3.TabIndex = 26;
            this.button3.Text = "清除接收";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // check2
            // 
            this.check2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.check2.FormattingEnabled = true;
            this.check2.Items.AddRange(new object[] {
            "无",
            "奇校验",
            "偶校验"});
            this.check2.Location = new System.Drawing.Point(119, 160);
            this.check2.Name = "check2";
            this.check2.Size = new System.Drawing.Size(161, 20);
            this.check2.TabIndex = 25;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(60, 163);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 24;
            this.label1.Text = "奇偶校验";
            // 
            // databit2
            // 
            this.databit2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.databit2.FormattingEnabled = true;
            this.databit2.Items.AddRange(new object[] {
            "8",
            "7",
            "6",
            "5"});
            this.databit2.Location = new System.Drawing.Point(119, 123);
            this.databit2.Name = "databit2";
            this.databit2.Size = new System.Drawing.Size(161, 20);
            this.databit2.TabIndex = 23;
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(60, 126);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 22;
            this.label2.Text = "数据位";
            // 
            // stopbit2
            // 
            this.stopbit2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.stopbit2.FormattingEnabled = true;
            this.stopbit2.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.stopbit2.Location = new System.Drawing.Point(119, 87);
            this.stopbit2.Name = "stopbit2";
            this.stopbit2.Size = new System.Drawing.Size(161, 20);
            this.stopbit2.TabIndex = 21;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(60, 87);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "停止位";
            // 
            // baudrate2
            // 
            this.baudrate2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.baudrate2.FormattingEnabled = true;
            this.baudrate2.Items.AddRange(new object[] {
            "自定义",
            "1382400",
            "961200",
            "460800",
            "256000",
            "230400",
            "128000",
            "115200",
            "76800",
            "57600",
            "43000",
            "38400",
            "19200",
            "14400",
            "9600",
            "4800",
            "2400",
            "1200"});
            this.baudrate2.Location = new System.Drawing.Point(119, 54);
            this.baudrate2.Name = "baudrate2";
            this.baudrate2.Size = new System.Drawing.Size(161, 20);
            this.baudrate2.TabIndex = 11;
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBox1.AutoSize = true;
            this.checkBox1.Font = new System.Drawing.Font("宋体", 10F);
            this.checkBox1.Location = new System.Drawing.Point(193, 302);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(96, 18);
            this.checkBox1.TabIndex = 19;
            this.checkBox1.Text = "16进制显示";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // PCB_uart
            // 
            this.PCB_uart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PCB_uart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.PCB_uart.FormattingEnabled = true;
            this.PCB_uart.Location = new System.Drawing.Point(44, 18);
            this.PCB_uart.Name = "PCB_uart";
            this.PCB_uart.Size = new System.Drawing.Size(164, 20);
            this.PCB_uart.TabIndex = 10;
            this.PCB_uart.SelectedIndexChanged += new System.EventHandler(this.PCB_uart_SelectedIndexChanged);
            this.PCB_uart.Click += new System.EventHandler(this.PCB_uart_Click);
            // 
            // checkBox2
            // 
            this.checkBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBox2.AutoSize = true;
            this.checkBox2.Font = new System.Drawing.Font("宋体", 10F);
            this.checkBox2.Location = new System.Drawing.Point(57, 302);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(82, 18);
            this.checkBox2.TabIndex = 18;
            this.checkBox2.Text = "白底黑字";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(60, 57);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "波特率";
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 21);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 6;
            this.label5.Text = "端口";
            // 
            // button4
            // 
            this.button4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button4.Font = new System.Drawing.Font("宋体", 10F);
            this.button4.Location = new System.Drawing.Point(193, 203);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(87, 33);
            this.button4.TabIndex = 5;
            this.button4.Text = "关闭串口";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button5.Font = new System.Drawing.Font("宋体", 10F);
            this.button5.Location = new System.Drawing.Point(57, 203);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 33);
            this.button5.TabIndex = 4;
            this.button5.Text = "打开串口";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.setarea);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.Label_select);
            this.groupBox2.Controls.Add(this.groupBox1);
            this.groupBox2.Location = new System.Drawing.Point(13, 4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(905, 80);
            this.groupBox2.TabIndex = 36;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "设置";
            // 
            // label11
            // 
            this.label11.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(636, 30);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(83, 12);
            this.label11.TabIndex = 45;
            this.label11.Text = "文化/新生精机";
            // 
            // Label_select
            // 
            this.Label_select.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Label_select.FormattingEnabled = true;
            this.Label_select.Items.AddRange(new object[] {
            "文化",
            "新生精机"});
            this.Label_select.Location = new System.Drawing.Point(638, 46);
            this.Label_select.Name = "Label_select";
            this.Label_select.Size = new System.Drawing.Size(130, 20);
            this.Label_select.TabIndex = 44;
            this.Label_select.Text = "文化";
            this.Label_select.SelectedIndexChanged += new System.EventHandler(this.Label_select_SelectedIndexChanged);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.InitprinterComboBox);
            this.groupBox3.Location = new System.Drawing.Point(994, 57);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(272, 49);
            this.groupBox3.TabIndex = 38;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "选择打印机";
            // 
            // InitprinterComboBox
            // 
            this.InitprinterComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.InitprinterComboBox.FormattingEnabled = true;
            this.InitprinterComboBox.Location = new System.Drawing.Point(6, 17);
            this.InitprinterComboBox.Name = "InitprinterComboBox";
            this.InitprinterComboBox.Size = new System.Drawing.Size(256, 20);
            this.InitprinterComboBox.TabIndex = 37;
            // 
            // PrintLabNum
            // 
            this.PrintLabNum.Location = new System.Drawing.Point(942, 25);
            this.PrintLabNum.Name = "PrintLabNum";
            this.PrintLabNum.Size = new System.Drawing.Size(37, 21);
            this.PrintLabNum.TabIndex = 37;
            this.PrintLabNum.Text = "1";
            // 
            // StartButton
            // 
            this.StartButton.Location = new System.Drawing.Point(942, 47);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(37, 27);
            this.StartButton.TabIndex = 38;
            this.StartButton.Text = "打印";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.KEYTextBox);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.SSIDTextBox);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.DEVICETextBox);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.LOTTextBox);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.PCBMACTextBox);
            this.groupBox4.Location = new System.Drawing.Point(942, 116);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(754, 62);
            this.groupBox4.TabIndex = 39;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "DATA";
            // 
            // KEYTextBox
            // 
            this.KEYTextBox.Enabled = false;
            this.KEYTextBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.KEYTextBox.Location = new System.Drawing.Point(628, 26);
            this.KEYTextBox.Name = "KEYTextBox";
            this.KEYTextBox.Size = new System.Drawing.Size(109, 29);
            this.KEYTextBox.TabIndex = 15;
            this.KEYTextBox.Text = "3dpHhg7F";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(626, 12);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 12);
            this.label10.TabIndex = 14;
            this.label10.Text = "KEY：";
            // 
            // SSIDTextBox
            // 
            this.SSIDTextBox.Enabled = false;
            this.SSIDTextBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SSIDTextBox.Location = new System.Drawing.Point(492, 27);
            this.SSIDTextBox.Name = "SSIDTextBox";
            this.SSIDTextBox.Size = new System.Drawing.Size(109, 29);
            this.SSIDTextBox.TabIndex = 13;
            this.SSIDTextBox.Text = "BX73C606";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(492, 11);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 12);
            this.label9.TabIndex = 12;
            this.label9.Text = "SSID：";
            // 
            // DEVICETextBox
            // 
            this.DEVICETextBox.Enabled = false;
            this.DEVICETextBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.DEVICETextBox.Location = new System.Drawing.Point(312, 27);
            this.DEVICETextBox.Name = "DEVICETextBox";
            this.DEVICETextBox.Size = new System.Drawing.Size(153, 29);
            this.DEVICETextBox.TabIndex = 11;
            this.DEVICETextBox.Text = "8McbTnx8QvVF";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(310, 12);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 10;
            this.label8.Text = "机器ID：";
            // 
            // LOTTextBox
            // 
            this.LOTTextBox.Enabled = false;
            this.LOTTextBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LOTTextBox.Location = new System.Drawing.Point(22, 27);
            this.LOTTextBox.Name = "LOTTextBox";
            this.LOTTextBox.Size = new System.Drawing.Size(77, 29);
            this.LOTTextBox.TabIndex = 9;
            this.LOTTextBox.Text = "22706";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 12);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 12);
            this.label7.TabIndex = 8;
            this.label7.Text = "LOT：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(127, 12);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 7;
            this.label6.Text = "管理番号：";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // PCBMACTextBox
            // 
            this.PCBMACTextBox.Enabled = false;
            this.PCBMACTextBox.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PCBMACTextBox.Location = new System.Drawing.Point(129, 27);
            this.PCBMACTextBox.Name = "PCBMACTextBox";
            this.PCBMACTextBox.Size = new System.Drawing.Size(156, 29);
            this.PCBMACTextBox.TabIndex = 6;
            this.PCBMACTextBox.Text = "8C1F640B01AF";
            // 
            // datatime
            // 
            this.datatime.AutoSize = true;
            this.datatime.Location = new System.Drawing.Point(9, 576);
            this.datatime.Name = "datatime";
            this.datatime.Size = new System.Drawing.Size(101, 12);
            this.datatime.TabIndex = 40;
            this.datatime.Text = "2019-09-12 17:40";
            // 
            // UART1textBox
            // 
            this.UART1textBox.Location = new System.Drawing.Point(994, 25);
            this.UART1textBox.Name = "UART1textBox";
            this.UART1textBox.Size = new System.Drawing.Size(43, 21);
            this.UART1textBox.TabIndex = 41;
            // 
            // UART2textBox
            // 
            this.UART2textBox.Location = new System.Drawing.Point(1043, 25);
            this.UART2textBox.Multiline = true;
            this.UART2textBox.Name = "UART2textBox";
            this.UART2textBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.UART2textBox.Size = new System.Drawing.Size(203, 21);
            this.UART2textBox.TabIndex = 42;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(1288, 46);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(88, 37);
            this.button1.TabIndex = 43;
            this.button1.Text = "读出并打印";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // timer3
            // 
            this.timer3.Interval = 50;
            this.timer3.Tick += new System.EventHandler(this.timer3_Tick);
            // 
            // ID_Box
            // 
            this.ID_Box.Enabled = false;
            this.ID_Box.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ID_Box.Location = new System.Drawing.Point(43, 98);
            this.ID_Box.Name = "ID_Box";
            this.ID_Box.Size = new System.Drawing.Size(177, 31);
            this.ID_Box.TabIndex = 44;
            this.ID_Box.TextChanged += new System.EventHandler(this.ID_Box_TextChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(22, 100);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 45;
            this.label12.Text = "ID";
            // 
            // Display_Results
            // 
            this.Display_Results.AutoSize = true;
            this.Display_Results.Font = new System.Drawing.Font("宋体", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Display_Results.ForeColor = System.Drawing.Color.Red;
            this.Display_Results.Location = new System.Drawing.Point(258, 92);
            this.Display_Results.Name = "Display_Results";
            this.Display_Results.Size = new System.Drawing.Size(70, 48);
            this.Display_Results.TabIndex = 46;
            this.Display_Results.Text = "OK";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(823, 596);
            this.Controls.Add(this.Display_Results);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.ID_Box);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.UART2textBox);
            this.Controls.Add(this.UART1textBox);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.datatime);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.PrintLabNum);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.receivingarea);
            this.Controls.Add(this.panel2);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ID Auto Check Ver1.00.0";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.receivingarea.ResumeLayout(false);
            this.receivingarea.PerformLayout();
            this.sendingarea.ResumeLayout(false);
            this.sendingarea.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.setarea.ResumeLayout(false);
            this.setarea.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.GroupBox receivingarea;
        private System.Windows.Forms.TextBox receivebuf;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Button send;
        private System.Windows.Forms.GroupBox sendingarea;
        private System.Windows.Forms.TextBox sendbuf;
        private System.Windows.Forms.TextBox SendDelay;
        private System.Windows.Forms.Button clearsend;
        private System.Windows.Forms.CheckBox timersend;
        private System.Windows.Forms.CheckBox sendnewline;
        private System.Windows.Forms.Label SendDelaytxt;
        private System.Windows.Forms.CheckBox send16;
        private System.Windows.Forms.Label SendDelaytxt1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button clrcnt;
        private System.Windows.Forms.Label sendB;
        private System.Windows.Forms.Label lblSCount;
        private System.Windows.Forms.Label receiveB;
        private System.Windows.Forms.Label lblRCount;
        private System.Windows.Forms.Button OpenFile;
        private System.Windows.Forms.Button SendFile;
        private System.Windows.Forms.Button stopsend;
        private System.Windows.Forms.ProgressBar sendprogressBar;
        private System.Windows.Forms.Label sendpercentage;
        private System.Windows.Forms.Label comstats;
        private System.Windows.Forms.GroupBox setarea;
        private System.Windows.Forms.Button savefile;
        private System.Windows.Forms.Button clrreceive;
        private System.Windows.Forms.ComboBox check;
        private System.Windows.Forms.Label checktxt;
        private System.Windows.Forms.ComboBox databit;
        private System.Windows.Forms.Label databittxt;
        private System.Windows.Forms.ComboBox stopbit;
        private System.Windows.Forms.Label stopbittxt;
        private System.Windows.Forms.ComboBox baudrate;
        private System.Windows.Forms.CheckBox display16;
        private System.Windows.Forms.ComboBox com;
        private System.Windows.Forms.CheckBox receivedisplaycolor;
        private System.Windows.Forms.Label baudratetxt;
        private System.Windows.Forms.Label comtxt;
        private System.Windows.Forms.Button closecom;
        private System.Windows.Forms.Button opencom;
        private System.Windows.Forms.Button open_close_UART1;
        private System.IO.Ports.SerialPort serialPort2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button open_close_UART2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.ComboBox check2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox databit2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox stopbit2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox baudrate2;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.ComboBox PCB_uart;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox InitprinterComboBox;
        private System.Windows.Forms.TextBox PrintLabNum;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox PCBMACTextBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox DEVICETextBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox LOTTextBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox KEYTextBox;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox SSIDTextBox;
        private System.Windows.Forms.Label datatime;
        private System.Windows.Forms.TextBox UART1textBox;
        private System.Windows.Forms.TextBox UART2textBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox Label_select;
        private System.Windows.Forms.TextBox ID_Box;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label Display_Results;
    }
}

