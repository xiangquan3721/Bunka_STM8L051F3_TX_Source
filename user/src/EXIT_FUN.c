/***********************************************************************/
/*  FILE        :EXIT_FUN.c                                            */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/ 
#include "EXIT_FUN.h"


void EXTI_PORTA1(void)
{
  if(FLAG_APP_TX==1){
    if(txphase%8==0)ID_INT_CODE=m_RFNormalBuf[txphase/8];
    if	(ID_INT_CODE & 0x80)CMT2300A_Gpio1=1;
    else CMT2300A_Gpio1=0;
    ID_INT_CODE<<=1;
    txphase++;
     //if(txphase>=224){
        if(txphase>=txphase_end){
        txphase=0;
        txphase_Repeat++;
        //if(txphase_Repeat>=3){FLAG_APP_TX=0;PIN_TX_LED=0;ADF7021_CE=0;ADF7021_POWER=1;}
				if(txphase_Repeat>=3){
					FLAG_APP_TX=0;
					if(FG_d_StopKey==0)PIN_TX_LED=0;
					CMT2300A_POWER=FG_NOT_allow_out;
					CMT2300A_Gpio1=0;
				}
    }    
  }
	else if(FG_test_mode==1)
		 CMT2300A_Gpio1=!CMT2300A_Gpio1;
}

void SendTxData(void)
{
  xdata u8 i;
       m_RFNormalBuf[0]=0xFF;
#if (BUNKA_STX == 1)	   
       for(i=1;i<=13;i++)m_RFNormalBuf[i]=0x55;
       m_RFNormalBuf[14]=0x15;
#else	
       for(i=1;i<=12;i++)m_RFNormalBuf[i]=0x55;
       m_RFNormalBuf[13]=0x54;
       m_RFNormalBuf[14]=0x56;
#endif 
       PIN_TX_LED=1;
       if(m_RegMode==0){
	 txphase_end=224;
	 SetTxData(15,ID_data,Control_code);
         m_RFNormalBuf[27]=0xFF;
       }
       else {
	 txphase_end=320;
	 SetTxData(15,ID_data,0x80);
	 if(m_RegMode==1)SetTxData(27,ID_data_add,0xFF);    //"1"?????
	 else SetTxData(27,ID_data_add,0);    //"2"??I??
         m_RFNormalBuf[39]=0xFF;
       }
       txphase=0;
       txphase_Repeat=0;
       ID_INT_CODE=0;
			 CMT2300A_GoTx();
       FLAG_APP_TX=1;
			 if(m_RegMode==0)Time_Tx_Out = 550;
			 else Time_Tx_Out = 800;
}

void SetTxData(u8 count_set ,uni_rom_id ID_data_set,u8 Control_code_set)
{
    xdata uni_i unii,unij,unik;
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
	xdata u16 Code;
	xdata u8 i;

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
