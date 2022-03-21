#include "IAP_flash.h"

/* 

IAP Flash空间: 1024Byte -> 0x7600 ~ 0x79FF.
255个ID: 255 * 3 = 765byte -> 0x7600 ~ 0x78FC; 普通ID
Addr_rf_offset -> 0x79FA; 射频偏移量
ID_SCX1801_DATA -> 0x79FB ~ 0x79FD; 通信ID
ID_DATA_PCS -> 0x79FE ~ 0X79FF. ID数量

*/




void Init_IAP_flash(void)
{
    /* IAP时基设置 */
    CLK_SetIAPTimeBase(12);     //12MHz
    
    /* 设置IAP起始地址 */
    IAP_WritePPage(IAPLB_P,IAP_ADDRESS/256);
}



/***********************************************************************************
函数名称:void IAP_WritePPage(u8 PsfrAddr,u8 PsfrData)
功能描述:写P页特殊功能器
输入参数:   
		 u8 PsfrAddr: P页地址,u8 PsfrData:  P页内容
返回参数:     
*************************************************************************************/
void IAP_WritePPage(u8 PsfrAddr,u8 PsfrData)
{
	bit bEA=EA;
	EA = 0; 					//关中断
	IFADRH = 0; 				//IFADRH必须为0
	IFADRL= PsfrAddr;			//送P页地址;
	IFD= PsfrData;				//送P页内容
	IFMT = ISP_WRITE_P;
	ISPCR = 0x80;				//设置等待时间, 允许ISP/IAP操作
	//CheckTrapFlag();
	SCMD = 0x46;
	//CheckTrapFlag();
	SCMD = 0xB9;
	nop();
	IFMT=0;
	ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
	EA = bEA;					//恢复中断
}


/***********************************************************************************
函数名称:   u8 IAP_ReadPPage(u8 PsfrAddr)
功能描述:读取P页特殊功能器内容
输入参数:   
		 u8 PsfrAddr: P页地址
返回参数:     
		 u8: P页内容
*************************************************************************************/
/*
u8 IAP_ReadPPage(u8 PsfrAddr)
{
	bit bEA=EA;
	EA = 0; 					//关中断
	IFADRH = 0; 				//IFADRH必须为0
	IFADRL= PsfrAddr;			//送P页地址;
	IFMT = ISP_READ_P;
	ISPCR = 0x80;				//设置等待时间, 允许ISP/IAP操作
	//CheckTrapFlag();
	SCMD = 0x46;
	//CheckTrapFlag();
	SCMD = 0xB9;
	nop();
	IFMT=0;
	ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
	EA = bEA;					//恢复中断
	return IFD;
}*/




/***********************************************************************************
函数名称:void IAP_ErasePage(u8 ByteAddr)
功能描述:页面擦除, 擦除指定地址所在的页面。
		擦除一个页面大约需要30ms
输入参数:   8
		 u8 ByteAddr: 指定的页面地址高8位 IAP_ErasePage((IAP_ADDRESS)/256);擦除后值为0xFF
*************************************************************************************/
/*
void IAP_ErasePage(u8 ByteAddr)
{
		bit bEA=EA; 
		IFADRH = ByteAddr;		//送地址高字节
		IFADRL= 0x00;			//送地址低字节;
		EA = 0;					//关中断
		IFMT = ISP_ERASE;
		ISPCR = 0x80; 			//允许ISP/IAP操作
		//CheckTrapFlag();
		SCMD = 0x46;
		//CheckTrapFlag();
		SCMD = 0xB9;
		nop();
		IFMT=0;
		ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
		EA = bEA; 					//恢复中断
}*/




/***********************************************************************************
函数名称:		u8 IAP_WriteBuf_With_Protect_Verify(u16 ByteAddr,u8 *pBuf,u16 Cnt)
功能描述:		写一串数据到IAP指定地址
		 	会使用到512字节XDATA保存扇区原有数据
		 	写入一个字节数据大约需要80us
输入参数:   
		 	u16 ByteAddr: 指定的IAP地址, u8 *pBuf: 待写入数据Buf地址，u16 Cnt: 待写入个数
返回参数:     
		 	u8 0：成功,	other:失败
*************************************************************************************/
u8 IAP_WriteBuf_With_Protect_Verify(u16 ByteAddr,u8 *pBuf,u16 Cnt)
{
		xdata u8 TempBuf[512]; 
		xdata u16 i;
		xdata u8 ErrCnt;
		xdata WordTypeDef SectorAddr;
		bit bEA = EA;
		// 读取待烧录扇区原有数据到临时缓冲
		EA = 0;
		ErrCnt = 0;
		
		SectorAddr.W=ByteAddr&0xFE00;
		for(i = 0;i < 512; i++)
		{
			IFADRH = SectorAddr.B.BHigh;//送地址高字节
			IFADRL= SectorAddr.B.BLow;	//送地址低字节;
			IFMT = ISP_READ;
			ISPCR = 0x80;				//允许ISP/IAP操作
			SCMD = 0x46;
			SCMD = 0xB9;
			IFMT = 0;
			ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
			SectorAddr.W++;
			TempBuf[i] = IFD;
            ClearWDT();
		}
		// 更改需写入的数据
		i = ByteAddr & 0x01FF;
		while(Cnt != 0)
		{
			TempBuf[i] = *pBuf;
			pBuf++;
			i++;
			Cnt--;
		}
	Err_Loop:
		// 擦除扇区
		SectorAddr.W = ByteAddr&0xFE00;
		IFADRH = SectorAddr.B.BHigh;	//送地址高字节
		IFADRL= 0x00;					//送地址低字节;
		IFMT = ISP_ERASE;
		ISPCR = 0x80; 					//允许ISP/IAP操作
		//CheckTrapFlag();
		SCMD = 0x46;
		//CheckTrapFlag();
		SCMD = 0xB9;
		nop();
		IFMT = 0;
		ISPCR = 0;						//清ISP/IAP特殊寄存器，防止误操作
		// 将更改后的数据写入IAP
		for(i = 0;i < 512; i++)
		{
			IFD = TempBuf[i];			//送所要写的数据	
			IFADRH = SectorAddr.B.BHigh;	//送地址高字节
			IFADRL= SectorAddr.B.BLow;	//送地址低字节;
			IFMT = ISP_WRITE;
			ISPCR = 0x80;               //允许ISP/IAP操作
			//CheckTrapFlag();
			SCMD = 0x46;
			//CheckTrapFlag();
			SCMD = 0xB9;
			nop();
			IFMT = 0;
			ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
			SectorAddr.W++;
            ClearWDT();
		}
		// 校验数据是否正确
		SectorAddr.W=ByteAddr&0xFE00;
		for(i = 0;i < 512; i++)
		{
			IFADRH = SectorAddr.B.BHigh;//送地址高字节
			IFADRL= SectorAddr.B.BLow;	//送地址低字节;
			IFMT = ISP_READ;
			ISPCR = 0x80;				//允许ISP/IAP操作
			//CheckTrapFlag();
			SCMD = 0x46;
			//CheckTrapFlag();
			SCMD = 0xB9;
			IFMT = 0;
			ISPCR = 0;					//清ISP/IAP特殊寄存器，防止误操作
			SectorAddr.W++;
            ClearWDT();
			if(TempBuf[i] != IFD)
			{
				ErrCnt++;
				if(ErrCnt<ERR_CNT_MAX)
				{
					goto Err_Loop;
				}
				else
				{
					goto Err_Return;
				}
			}
		}
		ErrCnt = 0;
	Err_Return:
		EA = bEA;					//恢复中断
		return ErrCnt;		
}

/*
void IAP_Write_Byte(u16 Addr, u8 wdata)
{
    bit bEA = EA;
    EA = 0;
    IFD = wdata;			    //送所要写的数据	
    IFADRH = (Addr >> 8) & 0xff;	//送地址高字节
    IFADRL = Addr & 0xff;	    //送地址低字节;
    IFMT = ISP_WRITE;
    ISPCR = 0x80;               //允许ISP/IAP操作
    SCMD = 0x46;
    SCMD = 0xB9;
    nop();
    IFMT = 0;
    ISPCR = 0;	
    EA = bEA;    
}*/


void eeprom_sys_load(void)
{
    xdata uni_rom_id Init_ID_data;
    idata u8 offset = 0;
    
    rom_KeyOpt = IAP_ReadByteByMOVC(addr_eeprom_sys + Addr_rom_KeyOpt);
    if(rom_KeyOpt > 1)  rom_KeyOpt = 0;
    
	Init_ID_data.IDB[0] = 0;
	Init_ID_data.IDB[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FB);
	Init_ID_data.IDB[2] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FC);
	Init_ID_data.IDB[3] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FD);
	if ((Init_ID_data.IDC == 0) || (Init_ID_data.IDC == 0xFFFFFF))  Init_ID_data.IDC = 0;
	ID_data.IDC = Init_ID_data.IDC;
    
    offset = IAP_ReadByteByMOVC(addr_eeprom_sys + Addr_rf_offset);
    if(0 < offset && offset <= 10)
    {
        rf_offset = offset;
        PROFILE_CH_FREQ_32bit_200002EC = 426075000 + 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_426_075);

        PROFILE_CH_FREQ_32bit_200002EC = 426750000 + 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_426_750);

        PROFILE_CH_FREQ_32bit_200002EC = 429175000 + 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_175);

        PROFILE_CH_FREQ_32bit_200002EC = 429350000 + 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_350);

        PROFILE_CH_FREQ_32bit_200002EC = 429550000 + 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_550);
    }
    else if(10 < offset && offset <= 20)
    {
        rf_offset = offset;
        offset = offset - 10;
        PROFILE_CH_FREQ_32bit_200002EC = 426075000 - 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_426_075);

        PROFILE_CH_FREQ_32bit_200002EC = 426750000 - 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_426_750);

        PROFILE_CH_FREQ_32bit_200002EC = 429175000 - 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_175);

        PROFILE_CH_FREQ_32bit_200002EC = 429350000 - 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_350);

        PROFILE_CH_FREQ_32bit_200002EC = 429550000 - 150 * offset;
        ML7345_Frequency_Calcul(PROFILE_CH_FREQ_32bit_200002EC,Fre_429_550);
    }
    else {}
    
}
