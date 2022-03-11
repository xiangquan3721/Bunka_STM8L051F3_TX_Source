/***********************************************************************/
/*  FILE        :EXIT_FUN.c                                            */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

//#include "stm8s.h"
#include  <iostm8s003f3.h>
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����

void SetTxData(void);
UINT16 SetFixedLengthCode(UINT8 data );



void EXIT_init(void){
   EXTI_CR1=0X02;             //PORT A ���жϴ���λ
   ADF7021_DATA_CLK_CR2=1;     //ʹ�ܸ�I/O���ж�  PA1
//   EXTI_CR2=0X00;   
//   PIN_PD7_CR2=1;      
}

void EXTI_PORTA1(void){
 // if(PIN_KEY_LOGIN==0)ADF7021_DATA_tx=!ADF7021_DATA_tx;
  if(FLAG_APP_TX==1){
    if(txphase%8==0)ID_INT_CODE=m_RFNormalBuf[txphase/8];
    if	(ID_INT_CODE & 0x80)ADF7021_DATA_tx=1;
    else ADF7021_DATA_tx=0;
    ID_INT_CODE<<=1;
    txphase++;
    //if(txphase>=280){
     if(txphase>=224){
        txphase=0;
        txphase_Repeat++;
        if(txphase_Repeat>=3){FLAG_APP_TX=0;PIN_TX_LED=0;ADF7021_CE=0;}
    }    
  }
}


//void SendTxData(void)
//{
//   UINT8 i;
//       m_RFNormalBuf[0]=0xFF;
//       m_RFNormalBuf[1]=0xFF;
//       for(i=2;i<=21;i++)m_RFNormalBuf[i]=0x55;
//       PIN_TX_LED=1;
//       SetTxData();
//       txphase=0;
//       txphase_Repeat=0;
//       ID_INT_CODE=0;
//       FLAG_APP_TX=1;
//}
//
//
//void SetTxData(void)
//{
//    uni_i unii,unij,unik;
//  	/*	ID set	*/
//        m_RFNormalBuf[22]=0x15;
//	unii.ui = SetFixedLengthCode(ID_data.IDB[3]) ;
//	m_RFNormalBuf[23] = unii.uc[0] ;
//	m_RFNormalBuf[24] = unii.uc[1] ;
//	unii.ui = SetFixedLengthCode(ID_data.IDB[2]) ;
//	m_RFNormalBuf[25] = unii.uc[0] ;
//	m_RFNormalBuf[26] = unii.uc[1] ;
//	unii.ui = SetFixedLengthCode(ID_data.IDB[1]) ;
//	m_RFNormalBuf[27] = unii.uc[0] ;
//	m_RFNormalBuf[28] = unii.uc[1] ;
//	/*	Control code set	*/
//	unii.ui = SetFixedLengthCode(Control_code) ;
//	m_RFNormalBuf[29] = unii.uc[0] ;
//	m_RFNormalBuf[30] = unii.uc[1] ;
//	/*	SUM set	*/
//	unii.uc[1] = ID_data.IDB[1] ;
//	unii.uc[0] = Control_code;
//	unij.uc[1] = ID_data.IDB[3] ;
//	unij.uc[0] = ID_data.IDB[2] ;
//	unik.ui = unii.ui + unij.ui ;
//	unii.ui = SetFixedLengthCode(unik.uc[1]) ;
//	m_RFNormalBuf[31] = unii.uc[0] ;
//	m_RFNormalBuf[32] = unii.uc[1] ;
//	unii.ui = SetFixedLengthCode(unik.uc[0]) ;
//	m_RFNormalBuf[33] = unii.uc[0] ;
//	m_RFNormalBuf[34] = unii.uc[1] ;    
//}

void SendTxData(void)
{
   UINT8 i;
       m_RFNormalBuf[0]=0xFF;
       m_RFNormalBuf[1]=0xFF;
       for(i=2;i<=14;i++)m_RFNormalBuf[i]=0x55;
       PIN_TX_LED=1;
       SetTxData();
       txphase=0;
       txphase_Repeat=0;
       ID_INT_CODE=0;
       FLAG_APP_TX=1;
}


void SetTxData(void)
{
    uni_i unii,unij,unik;
  	/*	ID set	*/
        m_RFNormalBuf[15]=0x15;
	unii.ui = SetFixedLengthCode(ID_data.IDB[3]) ;
	m_RFNormalBuf[16] = unii.uc[0] ;
	m_RFNormalBuf[17] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(ID_data.IDB[2]) ;
	m_RFNormalBuf[18] = unii.uc[0] ;
	m_RFNormalBuf[19] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(ID_data.IDB[1]) ;
	m_RFNormalBuf[20] = unii.uc[0] ;
	m_RFNormalBuf[21] = unii.uc[1] ;
	/*	Control code set	*/
	unii.ui = SetFixedLengthCode(Control_code) ;
	m_RFNormalBuf[22] = unii.uc[0] ;
	m_RFNormalBuf[23] = unii.uc[1] ;
	/*	SUM set	*/
	unii.uc[1] = ID_data.IDB[1] ;
	unii.uc[0] = Control_code;
	unij.uc[1] = ID_data.IDB[3] ;
	unij.uc[0] = ID_data.IDB[2] ;
	unik.ui = unii.ui + unij.ui ;
	unii.ui = SetFixedLengthCode(unik.uc[1]) ;
	m_RFNormalBuf[24] = unii.uc[0] ;
	m_RFNormalBuf[25] = unii.uc[1] ;
	unii.ui = SetFixedLengthCode(unik.uc[0]) ;
	m_RFNormalBuf[26] = unii.uc[0] ;
	m_RFNormalBuf[27] = unii.uc[1] ;    
}

UINT16 SetFixedLengthCode(UINT8 data )
{
	UINT16	code ;
	UINT8	i ;

	for	(i=0; i<8; i++)
	{
		code <<=2 ;
		if	( data & 0x01)		// '1' ?
		{					// Yes
			code |= 0x0002 ;
		}
		else
		{
			code |= 0x0001 ;      // '0'

		}
		data >>= 1 ;
	}
	return(code) ;
}