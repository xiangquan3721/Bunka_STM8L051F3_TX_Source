#include "IAP_flash.h"

/* 

IAP Flash�ռ�: 1024Byte -> 0x7600 ~ 0x79FF.
255��ID: 255 * 3 = 765byte -> 0x7600 ~ 0x78FC; ��ͨID
Addr_rf_offset -> 0x79FA; ��Ƶƫ����
ID_SCX1801_DATA -> 0x79FB ~ 0x79FD; ͨ��ID
ID_DATA_PCS -> 0x79FE ~ 0X79FF. ID����

*/




void Init_IAP_flash(void)
{
    /* IAPʱ������ */
    CLK_SetIAPTimeBase(12);     //12MHz
    
    /* ����IAP��ʼ��ַ */
    IAP_WritePPage(IAPLB_P,IAP_ADDRESS/256);
}



/***********************************************************************************
��������:void IAP_WritePPage(u8 PsfrAddr,u8 PsfrData)
��������:дPҳ���⹦����
�������:   
		 u8 PsfrAddr: Pҳ��ַ,u8 PsfrData:  Pҳ����
���ز���:     
*************************************************************************************/
void IAP_WritePPage(u8 PsfrAddr,u8 PsfrData)
{
	bit bEA=EA;
	EA = 0; 					//���ж�
	IFADRH = 0; 				//IFADRH����Ϊ0
	IFADRL= PsfrAddr;			//��Pҳ��ַ;
	IFD= PsfrData;				//��Pҳ����
	IFMT = ISP_WRITE_P;
	ISPCR = 0x80;				//���õȴ�ʱ��, ����ISP/IAP����
	//CheckTrapFlag();
	SCMD = 0x46;
	//CheckTrapFlag();
	SCMD = 0xB9;
	nop();
	IFMT=0;
	ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
	EA = bEA;					//�ָ��ж�
}


/***********************************************************************************
��������:   u8 IAP_ReadPPage(u8 PsfrAddr)
��������:��ȡPҳ���⹦��������
�������:   
		 u8 PsfrAddr: Pҳ��ַ
���ز���:     
		 u8: Pҳ����
*************************************************************************************/
/*
u8 IAP_ReadPPage(u8 PsfrAddr)
{
	bit bEA=EA;
	EA = 0; 					//���ж�
	IFADRH = 0; 				//IFADRH����Ϊ0
	IFADRL= PsfrAddr;			//��Pҳ��ַ;
	IFMT = ISP_READ_P;
	ISPCR = 0x80;				//���õȴ�ʱ��, ����ISP/IAP����
	//CheckTrapFlag();
	SCMD = 0x46;
	//CheckTrapFlag();
	SCMD = 0xB9;
	nop();
	IFMT=0;
	ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
	EA = bEA;					//�ָ��ж�
	return IFD;
}*/




/***********************************************************************************
��������:void IAP_ErasePage(u8 ByteAddr)
��������:ҳ�����, ����ָ����ַ���ڵ�ҳ�档
		����һ��ҳ���Լ��Ҫ30ms
�������:   8
		 u8 ByteAddr: ָ����ҳ���ַ��8λ IAP_ErasePage((IAP_ADDRESS)/256);������ֵΪ0xFF
*************************************************************************************/
/*
void IAP_ErasePage(u8 ByteAddr)
{
		bit bEA=EA; 
		IFADRH = ByteAddr;		//�͵�ַ���ֽ�
		IFADRL= 0x00;			//�͵�ַ���ֽ�;
		EA = 0;					//���ж�
		IFMT = ISP_ERASE;
		ISPCR = 0x80; 			//����ISP/IAP����
		//CheckTrapFlag();
		SCMD = 0x46;
		//CheckTrapFlag();
		SCMD = 0xB9;
		nop();
		IFMT=0;
		ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
		EA = bEA; 					//�ָ��ж�
}*/




/***********************************************************************************
��������:		u8 IAP_WriteBuf_With_Protect_Verify(u16 ByteAddr,u8 *pBuf,u16 Cnt)
��������:		дһ�����ݵ�IAPָ����ַ
		 	��ʹ�õ�512�ֽ�XDATA��������ԭ������
		 	д��һ���ֽ����ݴ�Լ��Ҫ80us
�������:   
		 	u16 ByteAddr: ָ����IAP��ַ, u8 *pBuf: ��д������Buf��ַ��u16 Cnt: ��д�����
���ز���:     
		 	u8 0���ɹ�,	other:ʧ��
*************************************************************************************/
u8 IAP_WriteBuf_With_Protect_Verify(u16 ByteAddr,u8 *pBuf,u16 Cnt)
{
		xdata u8 TempBuf[512]; 
		xdata u16 i;
		xdata u8 ErrCnt;
		xdata WordTypeDef SectorAddr;
		bit bEA = EA;
		// ��ȡ����¼����ԭ�����ݵ���ʱ����
		EA = 0;
		ErrCnt = 0;
		
		SectorAddr.W=ByteAddr&0xFE00;
		for(i = 0;i < 512; i++)
		{
			IFADRH = SectorAddr.B.BHigh;//�͵�ַ���ֽ�
			IFADRL= SectorAddr.B.BLow;	//�͵�ַ���ֽ�;
			IFMT = ISP_READ;
			ISPCR = 0x80;				//����ISP/IAP����
			SCMD = 0x46;
			SCMD = 0xB9;
			IFMT = 0;
			ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
			SectorAddr.W++;
			TempBuf[i] = IFD;
            ClearWDT();
		}
		// ������д�������
		i = ByteAddr & 0x01FF;
		while(Cnt != 0)
		{
			TempBuf[i] = *pBuf;
			pBuf++;
			i++;
			Cnt--;
		}
	Err_Loop:
		// ��������
		SectorAddr.W = ByteAddr&0xFE00;
		IFADRH = SectorAddr.B.BHigh;	//�͵�ַ���ֽ�
		IFADRL= 0x00;					//�͵�ַ���ֽ�;
		IFMT = ISP_ERASE;
		ISPCR = 0x80; 					//����ISP/IAP����
		//CheckTrapFlag();
		SCMD = 0x46;
		//CheckTrapFlag();
		SCMD = 0xB9;
		nop();
		IFMT = 0;
		ISPCR = 0;						//��ISP/IAP����Ĵ�������ֹ�����
		// �����ĺ������д��IAP
		for(i = 0;i < 512; i++)
		{
			IFD = TempBuf[i];			//����Ҫд������	
			IFADRH = SectorAddr.B.BHigh;	//�͵�ַ���ֽ�
			IFADRL= SectorAddr.B.BLow;	//�͵�ַ���ֽ�;
			IFMT = ISP_WRITE;
			ISPCR = 0x80;               //����ISP/IAP����
			//CheckTrapFlag();
			SCMD = 0x46;
			//CheckTrapFlag();
			SCMD = 0xB9;
			nop();
			IFMT = 0;
			ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
			SectorAddr.W++;
            ClearWDT();
		}
		// У�������Ƿ���ȷ
		SectorAddr.W=ByteAddr&0xFE00;
		for(i = 0;i < 512; i++)
		{
			IFADRH = SectorAddr.B.BHigh;//�͵�ַ���ֽ�
			IFADRL= SectorAddr.B.BLow;	//�͵�ַ���ֽ�;
			IFMT = ISP_READ;
			ISPCR = 0x80;				//����ISP/IAP����
			//CheckTrapFlag();
			SCMD = 0x46;
			//CheckTrapFlag();
			SCMD = 0xB9;
			IFMT = 0;
			ISPCR = 0;					//��ISP/IAP����Ĵ�������ֹ�����
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
		EA = bEA;					//�ָ��ж�
		return ErrCnt;		
}

/*
void IAP_Write_Byte(u16 Addr, u8 wdata)
{
    bit bEA = EA;
    EA = 0;
    IFD = wdata;			    //����Ҫд������	
    IFADRH = (Addr >> 8) & 0xff;	//�͵�ַ���ֽ�
    IFADRL = Addr & 0xff;	    //�͵�ַ���ֽ�;
    IFMT = ISP_WRITE;
    ISPCR = 0x80;               //����ISP/IAP����
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
