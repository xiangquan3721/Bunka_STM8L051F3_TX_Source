using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NationalInstruments.VisaNS;

struct Freq_stu
{
    public string get_dbm;
    public string get_hz;
    public string get_offset;
};

struct Source_stu
{
    public int err;
    public string source_name;
};

namespace OK06_Wireless_Test
{
    class CVisaOpt
    {
        private MessageBasedSession mbSession = null;     //会话

        private ResourceManager mRes = null;              //资源管理

        public static string[] ResourceArray = null;

        /// <summary>
        /// 默认构造函数
        /// </summary>
        /// <param name="strRes"></param>
        /// <returns></returns>
        ///
        // public CVisaOpt()
        //  {
        // }

        /// <summary>
        /// 静态函数，查找仪器资源
        /// </summary>
        /// <param name="strRes"></param>
        /// <returns></returns>
        public string[] FindResource(string strRes)
        {
            //string[] VisaRes = new string[1];
            try
            {
                mRes = null;
                mRes = ResourceManager.GetLocalManager();
                if (mRes == null)
                {
                    //throw new Exception("本机未安装Visa的.Net支持库！");
                }
                ResourceArray = mRes.FindResources(strRes);

                //mRes.Open();
            }
            catch (System.ArgumentException)
            {
                ResourceArray = new string[1];
                ResourceArray[0] = "未能找到可用资源!";
            }
            return ResourceArray;
        }

        /// <summary>
        /// 打开资源
        /// </summary>
        /// <param name="strResourceName"></param>
        public void OpenResource(string strResourceName)
        {
            //若资源名称为空，则直接返回
            if (strResourceName != null)
            {
                try
                {

                    mRes = ResourceManager.GetLocalManager();
                    mbSession = (MessageBasedSession)mRes.Open(strResourceName);
                    //此资源的超时属性
                    //setOutTime(5000);
                    mbSession.Timeout = 15000;
                }
                catch (NationalInstruments.VisaNS.VisaException )
                {
                    // Global.LogAdd(e.Message);
                }
                catch (Exception )
                {
                    //Global.LogAdd(exp.Message);
                    //throw new Exception("VisaCtrl-VisaOpen\n" + exp.Message);
                }
            }
        }


        /// <summary>
        /// 写命令函数
        /// </summary>
        /// <param name="strCommand"></param>
        public void Write(string strCommand)
        {
            try
            {
                if (mbSession != null)
                {
                    mbSession.Write(strCommand);
                }
            }
            catch (NationalInstruments.VisaNS.VisaException )
            {
                //Global.LogAdd(e.Message);
            }
            catch (Exception exp)
            {
                throw new Exception("VisaCtrl-VisaOpen\n" + exp.Message);
            }
        }


        /// <summary>
        /// 读取返回值函数
        /// </summary>
        /// <returns></returns>
        public string Read()
        {
            try
            {
                if (mbSession != null)
                {

                    return mbSession.ReadString();
                }
            }
            catch (NationalInstruments.VisaNS.VisaException)
            {
                return Convert.ToString(0);
            }
            return Convert.ToString(0);
        }


        /// <summary>
        /// 设置超时时间
        /// </summary>
        /// <param name="time">MS</param>
        public void SetOutTime(int time)
        {
            mbSession.Timeout = time;
        }

        /// <summary>
        /// 释放会话
        /// </summary>
        public void Release()
        {
            if (mbSession != null)
            {
                mbSession.Dispose();
            }
        }
    }

    class CVisaOpt_Option
    {
        CVisaOpt m_VisaOpt = new CVisaOpt();
        CVisaOpt m_VisaOpt_RSA3 = new CVisaOpt();
        CVisaOpt m_VisaOpt_DSG3 = new CVisaOpt();
        CVisaOpt m_VisaOpt_DM3 = new CVisaOpt();
        public Source_stu SourceOpt_Init(string name) 
        {
            Source_stu source_stu;
            source_stu.err = 0; source_stu.source_name = "";
            string m_strResourceName = null; //仪器资源名

            string[] InstrResourceArray = m_VisaOpt.FindResource("?*INSTR"); //查找资源

            if (InstrResourceArray[0] == "未能找到可用资源!")
            {
                source_stu.err = 1;
                return source_stu;
            }
            else
            {
                for (int i = 0; i < InstrResourceArray.Length; i++)
                {
                    if (InstrResourceArray[i].Contains(name)) //仪器型号,RSA3频谱仪、DSG3信号源、DM3电压表
                    {
                        m_strResourceName = InstrResourceArray[i];
                    }
                }
            }
            //如果没有找到指定仪器直接退出
            if (m_strResourceName == null)
            {
                source_stu.err = 2;
                return source_stu;
            }
            string strback = "";
            //打开指定资源
            if (name == "RSA3")
            {
                m_VisaOpt_RSA3.OpenResource(m_strResourceName);
                //发送命令
                m_VisaOpt_RSA3.Write("*IDN?");
                //读取命令
                strback = m_VisaOpt_RSA3.Read(); 
            }
            else if (name == "DSG3")
            {
                m_VisaOpt_DSG3.OpenResource(m_strResourceName);
                //发送命令
                m_VisaOpt_DSG3.Write("*IDN?");
                //读取命令
                strback = m_VisaOpt_DSG3.Read();
            }
            else if (name == "DM3")
            {
                m_VisaOpt_DM3.OpenResource(m_strResourceName);
                //发送命令
                m_VisaOpt_DM3.Write("*IDN?");
                //读取命令
                strback = m_VisaOpt_DM3.Read();
            }
            //显示读取内容
            source_stu.source_name = strback;
            source_stu.err = 3;

            return source_stu;
        }
        public void Opt_Set(string name,string onoff) 
        {
            if (name == "RSA3") //频谱仪
            {
                m_VisaOpt_RSA3.Write(":SENSe:FREQuency:CENTer 426.075MHz"); //设置中心频率
                m_VisaOpt_RSA3.Write(":SENSe:FREQuency:SPAN 10KHz"); //设置扫宽SPAN
                m_VisaOpt_RSA3.Write(":CALCulate:MARKer1:CPSearch:STATe ON"); //打开或关闭连续峰值搜索功能
                //m_VisaOpt_RSA3.Write(":CALCulate:MARKer:AOFF"); //关闭所以打开的光标
                m_VisaOpt_RSA3.Write(":DISPlay:WINDow:TRACe:Y:SCALe:RLEVel 10"); //设置参考电平dBm
            }
            else if(name == "DSG3") //信号源
            {
                if (onoff == "ON")
                {
                    m_VisaOpt_DSG3.Write(":SOURce:FREQuency 426.750MHz");  //载波频率
                    m_VisaOpt_DSG3.Write(":SOURce:LEVel 0dBm");  //载波幅度
                    m_VisaOpt_DSG3.Write(":SOURce:FMPM:TYPE FM");  //调制类型 FM
                    m_VisaOpt_DSG3.Write(":SOURce:FM:STATe ON");   //调制开关 ON
                    m_VisaOpt_DSG3.Write(":SOURce:FM:SOURce INTernal"); //调制源类型
                    m_VisaOpt_DSG3.Write(":SOURce:FM:WAVEform SQUA"); //调制方波
                    m_VisaOpt_DSG3.Write(":SOURce:FM:DEViation 2.2KHz"); //调制频偏
                    m_VisaOpt_DSG3.Write(":SOURce:FM:FREQuency 600Hz"); //调制速率
                    m_VisaOpt_DSG3.Write(":SOURce:MODulation:STATe ON"); //打开所有调制输出开关MOD ON,//OFF关闭调制

                    m_VisaOpt_DSG3.Write(":OUTPut:STATe ON");  //RF输出开关 ON
                }
                else
                {
                    m_VisaOpt_DSG3.Write(":OUTPut:STATe OFF");  //RF输出开关 OFF
                }
            }
            else if (name == "DM3") //电压表
            {
                if (onoff == "I")
                {
                    m_VisaOpt_DM3.Write(":MEASure:CURRent:DC 3"); //电流最大测量200mA
                    //m_VisaOpt_DM3.Write(":MEASure:CURRent:DC?");
                    //string strback_RIGOL_DM305_Vdc = m_VisaOpt_DSG3.Read();
                }
                else if (onoff == "V")
                {
                    m_VisaOpt_DM3.Write(":MEASure:VOLTage:DC 2"); //电压最大测量20V
                }
            }
        }
        public Freq_stu Opt_GetFreq(string name)
        {
            Freq_stu freq_stu = new Freq_stu();
            if(name == "RSA3")
            {
                m_VisaOpt_RSA3.Write(":CALCulate:MARKer1:Y?"); //查询指定光标处的Y轴值，单位默认为dBm。
                freq_stu.get_dbm = m_VisaOpt_RSA3.Read();
                m_VisaOpt_RSA3.Write(":CALCulate:MARKer1:X?"); //P53 查询指定光标的横坐标值，单位默认为Hz。
                freq_stu.get_hz = m_VisaOpt_RSA3.Read();
                //m_VisaOpt_RSA3.Write(":INSTrument:SELect VSA"); //VSA 模式，需要等待机器反应，此时要延时。常规是GPSA模式
                //延时8秒
                //m_VisaOpt_RSA3.Write(":TRACe4:DATA?"); //查询频偏。
                //freq_stu.get_offset = m_VisaOpt_RSA3.Read();
            }
            return freq_stu;
        }
        public string Opt_GetIVdc(string name,string iv)
        {
            if (name == "DM3")
            {
                if (iv == "I")
                {
                    m_VisaOpt_DM3.Write(":MEASure:CURRent:DC?");
                    string strback_Idc = m_VisaOpt_DM3.Read();
                    return strback_Idc;
                }
                else if (iv == "V")
                {
                    m_VisaOpt_DM3.Write(":MEASure:VOLTage:DC?");
                    string strback_Vdc = m_VisaOpt_DM3.Read();
                    return strback_Vdc;
                }
            }
            return "0";
        }
    }
}
