/***********************************************************************/
/*  FILE        :EXIT_FUN.c                                            */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/ 
#include "EXIT_FUN.h"

/*
void EXTI_PORTA1(void)
{
    if(FLAG_APP_TX == 1)
    {
        if(txphase_Repeat == 0) 
        {
            ML7345_SetAndGet_State(Force_TRX_OFF);
            ML7345_AutoTx_Data(m_RFNormalBuf,txphase_end);
            txphase_Repeat++;
        }
        else if(txphase_Repeat < 3 && Flag_TxDone == 1)
        {
            Flag_TxDone = 0;
            ML7345_AutoTx_Data(m_RFNormalBuf,txphase_end);
            txphase_Repeat++;
        }
        else if(txphase_Repeat == 3 && Flag_TxDone == 1)
        {
            Flag_TxDone = 0;
            FLAG_APP_TX = 0;
            PIN_TX_LED = 0;
            ML7345D_POWER = FG_NOT_allow_out;
        }
    }
}*/

void SendTxData(void)
{
    PIN_TX_LED = 1;
    if(m_RegMode==0)
    {
        SetTxData(0,ID_data,Control_code);
        m_RFNormalBuf[12] = 0xFF;
        txphase_end = 13;
    }
    else 
    {
        SetTxData(0,ID_data,0x80);
        if(m_RegMode==1)    SetTxData(12,ID_data_add,0xFF);    //"1"是追加
        else SetTxData(12,ID_data_add,0);    //"2"是抹消
        m_RFNormalBuf[24] = 0xFF;
        txphase_end = 25;
    }
    FLAG_APP_TX = 1;
    ML7345_AutoTx_Data(m_RFNormalBuf,txphase_end);
    Time_Tx_Out = 550;
    txphase_Repeat = 1;
}

void SetTxData(u8 count_set ,uni_rom_id ID_data_set,u8 Control_code_set)
{
    idata uni_i unii,unij,unik;
  	/*	ID set	*/
	unii.ui = SetFixedLengthCode(ID_data_set.IDB[3]) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(ID_data_set.IDB[2]) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(ID_data_set.IDB[1]) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;
	/*	Control code set	*/
	unii.ui = SetFixedLengthCode(Control_code_set) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;
	/*	SUM set	*/
	unii.uc[1] = ID_data_set.IDB[1] ;
	unii.uc[0] = Control_code_set;
	unij.uc[1] = ID_data_set.IDB[3] ;
	unij.uc[0] = ID_data_set.IDB[2] ;
	unik.ui = unii.ui + unij.ui ;
	unii.ui = SetFixedLengthCode(unik.uc[1]) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(unik.uc[0]) ;
	m_RFNormalBuf[count_set++] = unii.uc[0] ;
	m_RFNormalBuf[count_set++] = unii.uc[1] ;    
}

u16 SetFixedLengthCode(u8 Data)
{
	idata u16 Code;
	idata u8 i;

	for	(i=0; i<8; i++)
	{
		Code <<=2 ;
		if	( Data & 0x01)		// '1' ?
		{					// Yes
			Code |= 0x0002 ;
		}
		else
		{
			Code |= 0x0001 ;      // '0'

		}
		Data >>= 1 ;
	}
	return(Code) ;
}
