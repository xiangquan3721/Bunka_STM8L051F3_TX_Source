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
    
    /* ����IAP��ʵ��ʼ��ַ */
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
}




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

//
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
}


void IAP_Erase_All_ID(void)
{
    xdata u8 read_rf = 0;
    xdata u8 scx1801_id[3] = {0};

    read_rf = IAP_ReadByteByMOVC(addr_eeprom_sys + Addr_rf_offset);
    scx1801_id[0] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FB);
    scx1801_id[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FC);
    scx1801_id[2] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FD);
    
	IAP_ErasePage(IAP_ADDRESS/256);   //����Ƭ��һ
    ClearWDT();

    IAP_ErasePage((IAP_ADDRESS + 512)/256);   //����Ƭ����
    ClearWDT();
     
    IAP_Write_Byte(addr_eeprom_sys + Addr_rf_offset,read_rf);
    IAP_Write_Byte(addr_eeprom_sys + 0x3FB,scx1801_id[0]);
    IAP_Write_Byte(addr_eeprom_sys + 0x3FC,scx1801_id[1]);
    IAP_Write_Byte(addr_eeprom_sys + 0x3FD,scx1801_id[2]);
}


void eeprom_sys_load(void)
{
    idata u8 offset = 0;
    idata u16 i, q, p;
    idata u8 xm[3] = {0};
    idata uni_rom_id xn;

	xm[0] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FB);
	xm[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FC);
	xm[2] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FD);
	xn.IDB[0] = 0;
	xn.IDB[1] = xm[0];
	xn.IDB[2] = xm[1];
	xn.IDB[3] = xm[2];
	if ((xn.IDC == 0) || (xn.IDC == 0xFFFFFF))ID_SCX1801_DATA=0;
	else ID_SCX1801_DATA= xn.IDC;

    xm[0] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FE);
    xm[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + 0x3FF);
    ID_DATA_PCS = xm[0] * 256 + xm[1];
    if (ID_DATA_PCS == 0xFFFF)
        ID_DATA_PCS = 0;
    else if (ID_DATA_PCS > ID_Max_PCS)
        ID_DATA_PCS = ID_Max_PCS;
    q = ID_DATA_PCS;
    p = 0;
    for (i = 0; i < q; i++)
    {
        xm[0] = IAP_ReadByteByMOVC(addr_eeprom_sys + i*3);
        xm[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + i*3+1);
        xm[2] = IAP_ReadByteByMOVC(addr_eeprom_sys + i*3+2);
        xn.IDB[0] = 0;
        xn.IDB[1] = xm[0];
        xn.IDB[2] = xm[1];
        xn.IDB[3] = xm[2];
        if ((xn.IDC == 0) || (xn.IDC == 0xFFFFFF))
            q++;
        else
#if RAM_LARGE == 1
            ID_Receiver_DATA[p*3] = xn.IDB[1];
            ID_Receiver_DATA[p*3+1] = xn.IDB[2];
            ID_Receiver_DATA[p*3+2] = xn.IDB[3];
            p++;
#else
            ID_Receiver_DATA[p++] = xn.IDC;
#endif
        if (q > 260)
            break;
        ClearWDT(); // Service the WDT
    }

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

void ID_EEPROM_write(void)
{
    idata u8 xm[3] = {0};
    idata u16 i, j, m1;
    idata uni_rom_id xn, xd;
    ID_DATA_PCS++;
    xm[0] = ID_DATA_PCS / 256;
    xm[1] = ID_DATA_PCS % 256;

    IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys + 0x3FE, &xm[0],2);

#if RAM_LARGE == 1
    ID_Receiver_DATA[(ID_DATA_PCS - 1)*3] = (u8)((ID_Receiver_Login>>16) & 0xff);
    ID_Receiver_DATA[(ID_DATA_PCS - 1)*3 + 1] = (u8)((ID_Receiver_Login>>8) & 0xff);
    ID_Receiver_DATA[(ID_DATA_PCS - 1)*3 + 2] = (u8)((ID_Receiver_Login) & 0xff);
#else
    ID_Receiver_DATA[ID_DATA_PCS - 1] = ID_Receiver_Login;
#endif
    xn.IDC = ID_Receiver_Login;

    for (i = 0; i < 256; i++)
    {
        j = 3 * i;
        xm[0] = IAP_ReadByteByMOVC(addr_eeprom_sys + j);
        j++;
        xm[1] = IAP_ReadByteByMOVC(addr_eeprom_sys + j);
        j++;
        xm[2] = IAP_ReadByteByMOVC(addr_eeprom_sys + j);
        xd.IDB[0] = 0;
        xd.IDB[1] = xm[0];
        xd.IDB[2] = xm[1];
        xd.IDB[3] = xm[2];
        if ((xd.IDC == 0) || (xd.IDC == 0xFFFFFF))
            break;
        ClearWDT(); // Service the WDT
    }

    xm[0] = xn.IDB[1];
    xm[1] = xn.IDB[2];
    xm[2] = xn.IDB[3];
    m1 = j - 2;
    
    IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys + m1, &xm[0],3);

    if (ID_DATA_PCS >= ID_Max_PCS)
    {
        ID_Login_EXIT_Initial();
        DATA_Packet_Control = 0;
        time_Login_exit_256 = 110;
    }
}

void ID_Login_EXIT_Initial(void)
{
    // #if defined(__Product_PIC32MX2_Receiver__)
	if(FLAG_ID_Erase_Login == 1)
    {
        BEEP_Module(300,900);
        BEEP_Module(300,900);
        BEEP_Module(1800,1);
    }
	else if(FLAG_ID_Login==1)
    {
        BEEP_Module(300,900);
        BEEP_Module(1800,1);
    }
	Beep_Off(); //BEEP_CSR2_BEEPEN = 0;
    FLAG_ID_Login_EXIT = 1;
    FLAG_ID_Login_OK = 0;
    FLAG_ID_Login_OK_bank = 0;
    FLAG_ID_Login = 0;
    FLAG_ID_Erase_Login = 0;
	FLAG_ID_SCX1801_Login=0;
    Receiver_LED_OUT = 0;
    COUNT_Receiver_Login = 0;
    //#endif
    //#if defined(__Product_PIC32MX2_WIFI__)
    //     FLAG_ID_Login_EXIT=1;
    //     FLAG_ID_Login_OK=0;
    //     FLAG_ID_Login_OK_bank=0;
    //     FLAG_ID_Login=0;
    //     FLAG_ID_Erase_Login=0;
    //     WIFI_LED_RX=0;
    //#endif
}

void ID_SCX1801_EEPROM_write(u32 id)
{
    idata u8 xm[3] = {0};
    idata uni_rom_id xn;

    xn.IDC = id;//ID_Receiver_Login;
	ID_SCX1801_DATA= id;//ID_Receiver_Login;
	xm[0] = xn.IDB[1];
    xm[1] = xn.IDB[2];
    xm[2] = xn.IDB[3];
    IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys + 0x3FB, &xm[0],3);
}

void Delete_GeneralID_EEPROM(u32 id)
{
    idata u16 i, j, m2, original_pcs = 0;
    idata u8 xm[3] = {0};
    idata uni_rom_id xn;

    original_pcs = ID_DATA_PCS;
    for (i = 0; i < ID_DATA_PCS; i++)
    {
#if RAM_LARGE == 1
		if ((Return_ID_DATA(i) == id)&&(id!=0xFFFFFE)&&(id!=0))
		{
            for (j = i; j < ID_DATA_PCS; j++)
            {
                ID_Receiver_DATA[j*3] = ID_Receiver_DATA[j*3+3];
                ID_Receiver_DATA[j*3+1] = ID_Receiver_DATA[j*3+4];
                ID_Receiver_DATA[j*3+2] = ID_Receiver_DATA[j*3+5];
                ClearWDT(); // Service the WDT
            }
            ID_DATA_PCS--;
            if (ID_DATA_PCS==0)
            {
                ALL_ID_EEPROM_Erase();
                return;
            }
        }
#else
        if ((ID_Receiver_DATA[i] == id)&&(id!=0xFFFFFE)&&(id!=0))
		{
            for (j = i; j < ID_DATA_PCS; j++)
            {
                ID_Receiver_DATA[j] = ID_Receiver_DATA[j+1];
                ClearWDT(); // Service the WDT
            }
            ID_DATA_PCS--;
            if (ID_DATA_PCS==0)
            {
                ALL_ID_EEPROM_Erase();
                return;
            }
        }
#endif
        ClearWDT(); // Service the WDT
    }

    xm[0] = ID_DATA_PCS / 256;
    xm[1] = ID_DATA_PCS % 256;
    IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys + 0x3FE, &xm[0],2);

    for (i = 0; i < original_pcs; i++)
    {
#if RAM_LARGE == 1
        xn.IDC = Return_ID_DATA(i);
#else
        xn.IDC = ID_Receiver_DATA[i];
#endif
        xm[0] = xn.IDB[1];
        xm[1] = xn.IDB[2];
        xm[2] = xn.IDB[3];
        m2 = 3 * i;
        IAP_WriteBuf_With_Protect_Verify(addr_eeprom_sys + m2, &xm[0],3);
        ClearWDT(); // Service the WDT
    }
}

void ALL_ID_EEPROM_Erase(void)
{
    idata u16 i;
    
    ID_DATA_PCS = 0;

#if RAM_LARGE == 1
    for (i = 0; i < 768; i++)
#else
    for (i = 0; i < 100; i++)
#endif
    {
        ID_Receiver_DATA[i] = 0;
        ClearWDT(); // Service the WDT
    }
    IAP_Erase_All_ID();
}

void ID_learn(void) 
{
    //    UINT16 i;
    // #if defined(__Product_PIC32MX2_Receiver__)
    if (FG_10ms)
    { //90==1��
        FG_10ms = 0;
		if(TIME_TestNo91)
			--TIME_TestNo91;
		else FLAG_testNo91=0;
		if(TIME_ERROR_Read_once_again)
			--TIME_ERROR_Read_once_again;
		if(Time_error_read_timeout)
			--Time_error_read_timeout;
		if(Time_error_read_gap)
			--Time_error_read_gap;
		if(TIME_APP_TX_fromOUT)
			--TIME_APP_TX_fromOUT;
        if (TIME_auto_out)
            --TIME_auto_out;
        if (TIME_auto_close)
            --TIME_auto_close;
        if (TIME_OUT_OPEN_CLOSE)
            --TIME_OUT_OPEN_CLOSE;
        if (TIME_Receiver_LED_OUT)
            --TIME_Receiver_LED_OUT;
        if (TIME_Login_EXIT_Button)
            --TIME_Login_EXIT_Button;
        if (Manual_override_TIMER)
            --Manual_override_TIMER;
        if (time_Login_exit_256)
            --time_Login_exit_256;
        if (TIME_Receiver_Login_restrict)
            --TIME_Receiver_Login_restrict;
        else if ((FLAG_ID_Erase_Login == 1) || (FLAG_ID_Login == 1) ||(FLAG_ID_SCX1801_Login == 1))
            ;
        else
        {
            TIME_Receiver_Login = 0;
            COUNT_Receiver_Login = 0;
        }

        if (Receiver_Login == 0)
        {
            if(FLAG_ID_SCX1801_Login!=1)TIME_Receiver_Login++;
            TIME_Receiver_Login_restrict = 350;
            if ((COUNT_Receiver_Login >= 2) && (FLAG_ID_Erase_Login == 0) && (FLAG_ID_Login == 0) && (ID_DATA_PCS < ID_Max_PCS))
            {
                FLAG_ID_Login = 1;
				BEEP_Module(1800,900);
				BEEP_Module(300,1);
				COUNT_Receiver_Login++; //??????????????BEEP_Module?��beep????��?????��????TIME_Receiver_Login
                TIME_Login_EXIT_rest = 5380;
                TIME_Login_EXIT_Button = 500;
            } //6000
            else if (((FLAG_ID_Erase_Login == 1) && (COUNT_Receiver_Login >= 1)) ||
				(FLAG_ID_SCX1801_Login == 1)||
                ((FLAG_ID_Login == 1) && (COUNT_Receiver_Login >= 3)))
            {
                if (TIME_Login_EXIT_Button == 0)
                    ID_Login_EXIT_Initial();
            }
        }
        if (Receiver_Login == 1)
        {
	            if (TIME_Receiver_Login > 3)
	            {
	                if (COUNT_Receiver_Login < 10)
	                    COUNT_Receiver_Login++;
	            }
	            if (FLAG_ID_Login_EXIT == 1)
	            {
	                FLAG_ID_Login_EXIT = 0;
	                COUNT_Receiver_Login = 0;
	            }
	            TIME_Receiver_Login = 0;
        }
        if(TIME_Receiver_Login >= 450)  //590
        {
            FLAG_ID_SCX1801_Login=1;
            FLAG_ID_Erase_Login = 0;
            TIME_Receiver_Login = 0;
            Beep_Off(); //BEEP_CSR2_BEEPEN = 0;
            FG_ID_SCX1801_Login_BEEP=0;
            TIME_ID_SCX1801_Login=130;
            TIME_Login_EXIT_rest = 5380;
            COUNT_Receiver_Login=0;
            TIME_Login_EXIT_Button = 500;
        }
	    else if ((TIME_Receiver_Login >= 250)&&(FLAG_ID_Erase_Login==0)&&(FLAG_ID_SCX1801_Login==0))
	      {
	            //TIME_Receiver_Login = 0;
	            FLAG_ID_Erase_Login = 1;
	            FLAG_ID_Erase_Login_PCS = 1; //׷�Ӷ��WID��¼
	            BEEP_Module(1800,900);
				BEEP_Module(300,900);
				BEEP_Module(300,1);
				COUNT_Receiver_Login++; //??????????????BEEP_Module?��beep????��?????��????TIME_Receiver_Login
	            TIME_Login_EXIT_rest = 5380;
	            TIME_Login_EXIT_Button = 500;
	       }
		if((FLAG_ID_SCX1801_Login==1)&&(TIME_ID_SCX1801_Login==0))
		{
			if(FG_ID_SCX1801_Login_BEEP==0)
			{
			    FG_ID_SCX1801_Login_BEEP=1;
				TIME_ID_SCX1801_Login=390;
				Beep_Off(); //BEEP_CSR2_BEEPEN = 0;
			}
			else if(FG_ID_SCX1801_Login_BEEP==1)
			{
			    FG_ID_SCX1801_Login_BEEP=0;
				TIME_ID_SCX1801_Login=130;
				Beep_On();  //BEEP_CSR2_BEEPEN = 1;
			}
		}
        if ((FLAG_ID_Erase_Login == 1) || (FLAG_ID_Login == 1) ||(FLAG_ID_SCX1801_Login==1))
        {
            TIME_Receiver_Login_led++;
            if (TIME_Receiver_Login_led >= 46)
            {
                TIME_Receiver_Login_led = 0;
                if (TIME_Receiver_LED_OUT > 0)
                    Receiver_LED_OUT = 1;
                else
                    Receiver_LED_OUT = !Receiver_LED_OUT;
            }
            if ((FLAG_ID_Login_OK == 1) && (FLAG_ID_Login_OK_bank == 0))
            {
                if ((ID_Receiver_Login == 0xFFFFFE)&&(FLAG_ID_Erase_Login==1))FLAG_ID_Login_OK_bank=1;             //׷�Ӷ��WID��¼
                FLAG_ID_Login_OK = 0; //׷�Ӷ��WID��¼
                if(FLAG_ID_SCX1801_Login==1)
                {
                    FLAG_ID_SCX1801_Login=0;
					FG_ID_SCX1801_Login_BEEP=0;
					FLAG_ID_Login=0;
					FLAG_ID_Erase_Login=0;
                	BEEP_and_LED();
					ID_SCX1801_EEPROM_write(ID_Receiver_Login);
					if(FLAG_IDCheck_OK==1)
                    {
                        FLAG_IDCheck_OK = 0;
                        Delete_GeneralID_EEPROM(ID_SCX1801_DATA);
                    }
					ID_Login_EXIT_Initial();
                }
				else
				{
		                if (FLAG_IDCheck_OK == 1)
		                    FLAG_IDCheck_OK = 0;
		                else
		                {
		                    BEEP_and_LED();
		                    TIME_Login_EXIT_rest = 5380; //׷�Ӷ��WID��¼
		                    if ((FLAG_ID_Login == 1) && (ID_Receiver_Login != 0xFFFFFE))
                            {
                                if (ID_SCX1801_DATA == 0)
                                    ID_SCX1801_EEPROM_write(ID_Receiver_Login);
                                else ID_EEPROM_write();
                            }
		                    else if (FLAG_ID_Erase_Login == 1)
		                    {
		                        if (FLAG_ID_Erase_Login_PCS == 1)
		                        {
		                            FLAG_ID_Erase_Login_PCS = 0;
		                            ID_DATA_PCS = 0;
		                            ALL_ID_EEPROM_Erase();
                                    ID_SCX1801_DATA = 0;
                                    ID_SCX1801_EEPROM_write(0x00);
                                    if (ID_Receiver_Login != 0xFFFFFE)
                                        ID_SCX1801_EEPROM_write(ID_Receiver_Login);
		                        } //׷�Ӷ��WID��¼
		                        else if (ID_Receiver_Login != 0xFFFFFE)
		                            ID_EEPROM_write();
		                    }
		                } //end else
				}
            }
            if (TIME_Login_EXIT_rest)
                --TIME_Login_EXIT_rest;
            else
                ID_Login_EXIT_Initial();
        }
    }
    //#endif
}
