/***********************************************************************/
/*  FILE        :key_and_Other.c                                       */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l051f3.h>
#include "Pin_define.h"		// 管脚定义
#include "initial.h"		// 初始化  预定义
#include "ram.h"		// RAM定义
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// 外部EXIT中断
#include "key_and_Other.h"		// 按键
#include "eeprom.h"		// eeprom

void key_check(void)
{
//    if (TB_100ms)--TB_100ms;
//    else{                            
//	  TB_100ms = BASE_100ms;
//	  FG_100ms = 1;	      // 100mS FLAG
//	}
  
  
   if(FG_1ms){
    FG_1ms=0; 
    if(m_KeyDupliSetTimeout)--m_KeyDupliSetTimeout;
    if(m_KeyDupli1stTimer)--m_KeyDupli1stTimer;
    else FG_d_StopKey=0;
    if	( FG_d_StopKey &&m_KeyDupli1stTimer){
      time_led++;
      if(time_led>=100){time_led=0;PIN_LED=!PIN_LED;}
    }
    if(m_TimerKey)--m_TimerKey;
    
    if(TIME_BEEP_on){
      --TIME_BEEP_on;
      if(FG_beep_on==0){FG_beep_on=1;FG_beep_off=0;BEEP_CSR2_BEEPEN=1;
                        if(FG_LED_on)PIN_LED=1;
                       }
    }
    else if(TIME_BEEP_off){
      --TIME_BEEP_off;
      if(FG_beep_off==0){FG_beep_off=1;FG_beep_on=0;BEEP_CSR2_BEEPEN=0;
                        if(FG_LED_on)PIN_LED=0;
                       }
    }
    else if(TIME_BEEP_freq){
      --TIME_BEEP_freq;
      TIME_BEEP_on=BASE_TIME_BEEP_on;
      TIME_BEEP_off=BASE_TIME_BEEP_off;
      if(FG_beep_on==0){FG_beep_on=1;FG_beep_off=0;BEEP_CSR2_BEEPEN=1;
                        if(FG_LED_on)PIN_LED=1;
                       }      
    }
    else  FG_LED_on=0;   
    
    _KeyInTx();
    _DupliFuncSetMode();
    
    
//    if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN==0))TIME_KEY_OPEN++;
//    if(PIN_KEY_OPEN==1){TIME_KEY_OPEN=0;FG_KEY_OPEN=0;}
//    if((TIME_KEY_OPEN>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_OPEN==0)&&(TB_5s>=20)){
//      FG_KEY_OPEN=1;
//      if(FG_PWRON==0){
//	FG_PWRON=1;
//	PIN_POWER_CONTROL=1;
//	TB_5s=50;
//      }
//      dd_set_ADF7021_Power_on();
//      dd_set_TX_mode();
//      Control_code=0x08;
//      BASE_TIME_BEEP_on=103;
//      BASE_TIME_BEEP_off=103;
//      TIME_BEEP_on=BASE_TIME_BEEP_on;
//      TIME_BEEP_off=BASE_TIME_BEEP_off;
//      TIME_BEEP_freq=0;
//      SendTxData();
//    }
//
//    
//    if((PIN_KEY_STOP==0)&&(FG_KEY_STOP==0))TIME_KEY_STOP++;
//    if(PIN_KEY_STOP==1){TIME_KEY_STOP=0;FG_KEY_STOP=0;}
//    if((TIME_KEY_STOP>=10)&&(TIME_KEY_LOGIN==0)&&(FLAG_APP_TX==0)&&(FG_KEY_STOP==0)&&(TB_5s>=20)){
//      FG_KEY_STOP=1;
//      if(FG_PWRON==0){
//	FG_PWRON=1;
//	PIN_POWER_CONTROL=1;
//	TB_5s=50;
//      }
//      dd_set_ADF7021_Power_on();
//      dd_set_TX_mode();
//      Control_code=0x04;
//      BASE_TIME_BEEP_on=103;
//      BASE_TIME_BEEP_off=103;
//      TIME_BEEP_on=BASE_TIME_BEEP_on;
//      TIME_BEEP_off=BASE_TIME_BEEP_off;
//      TIME_BEEP_freq=1;
//      SendTxData();
//    }
//
//    if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE==0))TIME_KEY_CLOSE++;
//    if(PIN_KEY_CLOSE==1){TIME_KEY_CLOSE=0;FG_KEY_CLOSE=0;}
//    if((TIME_KEY_CLOSE>=10)&&(FLAG_APP_TX==0)&&(FG_KEY_CLOSE==0)&&(TB_5s>=20)){
//      FG_KEY_CLOSE=1;
//      if(FG_PWRON==0){
//	FG_PWRON=1;
//	PIN_POWER_CONTROL=1;
//	TB_5s=50;
//      }
//      dd_set_ADF7021_Power_on();
//      dd_set_TX_mode();
//      Control_code=0x02;
//      BASE_TIME_BEEP_on=103;
//      BASE_TIME_BEEP_off=103;
//      TIME_BEEP_on=BASE_TIME_BEEP_on;
//      TIME_BEEP_off=BASE_TIME_BEEP_off;
//      TIME_BEEP_freq=2;
//      SendTxData();
//    } 
//
//    if((PIN_KEY_LOGIN==0)&&(FG_KEY_LOGIN==0))TIME_KEY_LOGIN++;
//    if(PIN_KEY_LOGIN==1){TIME_KEY_LOGIN=0;FG_KEY_LOGIN=0;}
//    if((TIME_KEY_LOGIN>=4000)&&(FG_KEY_LOGIN==0)&&(FLAG_APP_TX==0)&&
//       (TIME_KEY_STOP>=4000)&&(FG_KEY_STOP==0)&&(TB_5s>=20)){
//      FG_KEY_LOGIN=1;
//      if(FG_PWRON==0){
//	FG_PWRON=1;
//	PIN_POWER_CONTROL=1;
//	TB_5s=50;
//      }
//      dd_set_ADF7021_Power_on();
//      dd_set_TX_mode();
//      Control_code=0x14;
//      SendTxData();
//    } 
    
    
  }
}


void time_control(void)
{
  if(FG_100ms){
    FG_100ms=0;    
    if(FG_PWRON==1){
    if ((TB_5s)&&(m_KeyOptSetMode==0))	--TB_5s;
    }    
  }
  
}


//
/*--------------------------------------*/
/*					*/
/*			Sw data input	*/
/*					*/
/*			  in  : sw	*/
/*			  out : none	*/
/*					*/
/*--------------------------------------*/
//
void	_SwIn( uchar sw )
{
	m_KeyNew<<= 1 ;
	if	( sw )
	{
		m_KeyNew |= d_On ;
	}
}
//
/****************************************/
/*										*/
/*			Check Key for Tx			*/
/*										*/
/*			  in  : none				*/
/*			  out : none				*/
/*										*/
/****************************************/
//
/*	Key data table	*/
//		||||||||
//		|||||||+ Auto Tx Stop
//		||||||++ Auto Tx Start
//		|||||+++ Reg.
//		||||++++ Vent.
//		|||+++++ Close
//		||++++++ Stop
//		|+++++++ Open
//		++++++++ 1
//
const	uchar	ct_KeyDataTable[]
={ 
	/*	Reg. (0)	*/
0xFB,//	0b11111011,
//	/*	Open (1)	*/
0xBF,//	0b10111111,
//	/*	Stop (2)	*/
0xDF,//	0b11011111,
//	/*	Close (3)	*/
0xEF,//	0b11101111,
//	/*	Vent. (4)	*/
0xF7,//	0b11110111,
//	/*	Open + Stop (5)	*/
0x9F,//	0b10011111,
//	/*	Open + Close (6)	*/
0xAF,//	0b10101111,
//	/*	Open + Vent. (7)	*/
0xB7,//	0b10110111,
//	/*	Open + Reg. (8)	*/
0xBB,//	0b10111011,
//	/*	Stop + Close (9)	*/
0xCF,//	0b11001111,
//	/*	Stop + Reg. (10)	*/
0xDB,//	0b11011011,
//	/*	Close + Reg. (11)	*/
0xEB,//	0b11101011,
//	/*	Close + Vent. (12)	*/
0xE7,//	0b11100111,
//	/*	Vent. + Reg. (13)	*/
0xF3,//	0b11110011,
//	/*	Auto Tx start (14)	*/
0xFD,//	0b11111101,
//	/*	Auto Tx stop (15)	*/
0xFE,//	0b11111110,
//	/*	No push (16)	*/
0xFF,//	0b11111111,
} ;

//
void	_KeyInTx( void )
{
	uchar	i ;
	
	m_KindOfKey = d_Idle ;
	
	m_KeyNew = 0xFF ;	
	/*	Registration sw		*/
	_SwIn( PIN_KEY_OPEN ) ;
	/*	Auto Tx Start sw		*/
	_SwIn( PIN_KEY_STOP ) ;
	/*	Auto Tx Stop sw		*/
	_SwIn( PIN_KEY_CLOSE ) ;
	/*	Auto Tx Vent. sw		*/
	_SwIn( 1 ) ;	
	/*	Auto Tx Reg. sw		*/
	_SwIn( PIN_KEY_LOGIN ) ;	
	/*	Auto Tx Auto Tx Start sw		*/
	_SwIn( 1 ) ;	
	/*	Auto TxAuto Tx Stop sw		*/
	_SwIn( 1 ) ;	
	
	if	( m_KeyNew != m_KeyOld )				// Key in
	{												// Different with the last state
		m_KeyOld = m_KeyNew ;
		_SetKeyChatterCount() ;						// Chatter counter set
		_ClearSpecialMultiKeyState() ;				// Clear key continue state
		return ;
	}
	
	if	( --m_ChatterCount )						// Chattering ok ?
	{
		return ;
	}
	m_ChatterCount = 1 ;
	
	/*		For generate Batt. Low tone		*/
	if	( m_KeyNew != d_KeyNoPush )			// Is key data no push ?
	{												// No, any key push
//		if	( m_BattState )							// Batt. Low ?
//		{											// Yes
//			_ReqBuzzer(d_BuzBattLow) ;				// Request
//		}
	}
	
	/*		Search of valid key		*/
	for	( i=0; i<17;i++)
	{
		if	( m_KeyNew == ct_KeyDataTable[i] )	// Match ?
		{
			m_KeyNo = i ;
			break ;									// Yes
		}
	}
	if	( i == 17)			// Found ?
	{												// No
		mb_NoPush = d_Clear ;						// No push clear(Push on)
		_ClearSpecialMultiKeyState() ;				// Special multi key status clear
		mb_NoPushWait = d_On ;						// Set no push wait
		_DupliFuncClear() ;							// Duplicate key function clear
		return ;
	}
	
	if	( mb_NoPushWait )							// Wait for no push ?
	{												// Yes
		if	( m_KeyNew != d_KeyNoPush )		// Is key data no push ?
		{
			return ;								// No
		}
	}
	
	switch	( i )    // Jumo to key function
	{
		case 0 :
		        _FuncReg();
			break ;		
		case 1 :
		case 2 :  
		case 3 : 
		case 4 :   
		        _FuncStop();
			break ;	
		case 5 :  
		case 6 :  
		case 7 :  
		case 9 :  
		case 12 :  
		        _FuncOpenStop();
			break ;		
		case 8 :  
		        _FuncOpenReg();
			break ;
		case 10 :  
		        _FuncStopReg();
			break ;
		case 11 :  
		        _FuncCloseReg();
			break ;
		case 13 :  
		        _FuncVentReg();
			break ;
		case 14 :  
		        _FuncAutoTxStart();
			break ;
		case 15 :  
		        _FuncAutoTxStop();
			break ;
		case 16 :  
		        _FuncNoPush();
			break ;
	}
}

//
void	_FuncReg( void )
{
  
}
void	_FuncStop( void )
{
	if	( _GetNoPushState() )						// No push before ?
	{												// No
		if	( mb_OpenSw || mb_StopSw || mb_CloseSw )// Continue push ?
		{											// Yes
			if	( !m_TimerKey )						// 5sec passed ?
			{
//				if	( !--m_TimerKey )
//				{									// Yes
					if	( mb_OpenSw || mb_CloseSw )				// Close sw ?
					{
						m_KeyOptSetMode = 10 ;				// Yes
						//_ReqBuzzer( d_BuzOpt5 ) ;
						BASE_TIME_BEEP_on=103;
                                                BASE_TIME_BEEP_off=103;
                                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                                TIME_BEEP_freq=100;
						m_KindOfKey = d_Idle ;
						mb_NoPushWait = d_On ;			// Set no push wait
						return ;
					}
					m_KeyOptSetMode = 1 ;			// Opetion setting mode
					//_ReqBuzzer( d_BuzOpt1 ) ;
						BASE_TIME_BEEP_on=103;
                                                BASE_TIME_BEEP_off=103;
                                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                                TIME_BEEP_freq=1;	
						FG_LED_on=1;
						if(FG_PWRON==0){
	                                            FG_PWRON=1;
	                                            PIN_POWER_CONTROL=1;
	                                            TB_5s=51;  //5.1秒
                                                }
					m_KeyDupliSetTimeout = d_DupliTime4s ;
					m_KindOfKey = d_Idle ;
					mb_NoPush=d_Off;
					mb_NoPushWait = d_On ;			// Set no push wait
					m_KeyOptSetOpenStop = 1 ;
					if	( mb_OpenSw )				// Open ?
					{
						m_KeyOptSetOpenStop = 0 ;	// Yes
					}
//				}
//				return ;							// No
			}
			return ;
		}
		return ;
	}
	
	m_KindOfKey = m_KeyNo ;
	if	( m_KeyOptSetMode )							// Option setting mode ?
	{
		return ;									// Yes
	}
	
	switch	( m_KindOfKey )
	{
		case d_OpenKey :
			mb_OpenSw = d_On ;
			m_TimerKey = d_Time5s ;					// Set 5sec key timer
			break;
			
		case d_StopKey :
			mb_StopSw = d_On ;
			m_TimerKey = d_Time5s ;					// Set 5sec key timer
			break;
			
		case d_CloseKey :
			mb_CloseSw = d_On ;
			m_TimerKey = d_Time5s ;//d_Time9s ;					// Set 5sec key timer
			break;
	}
	if	( !rom_KeyOpt || m_KindOfKey == d_VentKey  )// Single push option or Vent. key ?
	{												// Yes
		_DupliFuncClear() ;							// Duplicate key function clear
		_ReqTxdEdit( m_KeyNo,m_KeyNo ) ;
		m_TimerKeyMonitor = d_Clear ;
		return ;
	}
	
	/*	Multi push option	*/
	if	( m_KeyOptSetMode || m_RegMode )
	{
		return ;
	}
	
	if	( m_KindOfKey == d_StopKey )
	{
		_DupliFuncClear() ;							// Duplicate key function clear
		_ReqTxdEdit( m_KeyNo,m_KeyNo ) ;
		m_TimerKeyMonitor = d_Clear ;
		FG_d_StopKey=1;
		m_KeyDupli1stTimer = d_D1stTime3s ;
		time_led=0;
		return ;
	}
	
	switch	( m_KindOfKey )
	{
//		case d_OpenKey :
//			m_KeyCloseCount = 2 ;
//			if	( !--m_KeyOpenCount )
//			{
//				_ReqTxdEdit( m_KeyNo,m_KeyNo ) ;
//				m_TimerKeyMonitor = d_Clear ;
//				_DupliFuncClear() ;					// Duplicate key function clear
//				return ;
//			}
//			m_KeyDupli1stTimer = d_D1stTime3s ;
//			break;
//			
//		case d_CloseKey :
//			m_KeyOpenCount = 2 ;
//			if	( !--m_KeyCloseCount )
//			{
//				_ReqTxdEdit( m_KeyNo,m_KeyNo ) ;
//				m_TimerKeyMonitor = d_Clear ;
//				_DupliFuncClear() ;					// Duplicate key function clear
//				return ;
//			}
//			m_KeyDupli1stTimer = d_D1stTime3s ;
//			break;
	  
		case d_OpenKey :
		case d_CloseKey :  
			if	( FG_d_StopKey && m_KeyDupli1stTimer)
			{
			        FG_d_StopKey=0;
				m_KeyDupli1stTimer=0;
				_ReqTxdEdit( m_KeyNo,m_KeyNo ) ;
				m_TimerKeyMonitor = d_Clear ;
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			break;
					
	}  
}
void	_FuncOpenStop( void )
{
  
}
void	_FuncOpenReg( void )
{
  
}
void	_FuncStopReg( void )
{
  
}
void	_FuncCloseReg( void )
{
  
}
void	_FuncVentReg( void )
{
  
}
void	_FuncAutoTxStart( void )
{
  
}
void	_FuncAutoTxStop( void )
{
  
}
void	_FuncNoPush( void )
{
	mb_OpenSw = d_Off ;							// For duplicate keyvfunction
	mb_StopSw = d_Off ;
	mb_CloseSw = d_Off ;
	
	_ClearSpecialMultiKeyState() ;				// Special multi key status clear
	mb_NoPush     = d_On ;						// No push on
	mb_NoPushWait = d_Off ;						// No push wait clear
	m_KindOfKey = d_KeyNoPush;//d_NoPushKey ;
//	if	( m_BuzzerMode == d_BuzBattLow )			// Batt.Low sound out ?
//	{
//		_BuzIdle() ;
//	}  
}
void	_SetKeyChatterCount( void )
{
	m_ChatterCount = d_Time50ms ;						// Chatter counter set
	m_TimerKey = 0 ;
}
/*==============================================*/
/*												*/
/*		Clear special multi key push status		*/
/*												*/
/*			 in  : none							*/
/*			 out : none							*/
/*												*/
/*==============================================*/
//
void	_ClearSpecialMultiKeyState( void )
{
	mb_RegSw      = d_Clear ;
	mb_RegStopSw  = d_Clear ;
	mb_RegOpenSw  = d_Clear ;
	mb_RegCloseSw = d_Clear ;
	mb_RegVentSw  = d_Clear ;
}
/****************************************/
/*										*/
/*		Key duplicate function clear	*/
/*										*/
/*			  in  : none				*/
/*			  out : none				*/
/*										*/
/****************************************/
//
void	_DupliFuncClear( void )
{
	m_KeyOptSetMode = d_Idle ;
	m_KeyOpenCount = 2 ;
	m_KeyCloseCount = 2 ;
	//mb_OpenSw = d_Off ;
	//mb_StopSw = d_Off ;
	if	( m_KeyDupli1stTimer )
	{
		m_KeyDupli1stTimer = d_Clear ;
		//_LedOnOff( d_LedOff ) ;				// Led off
	}
}
/*==============================================*/
/*												*/
/*			No Push(Last time) check			*/
/*												*/
/*			 in  : none							*/
/*			 out : 0: No push					*/
/*				   1: any push					*/
/*												*/
/*==============================================*/
//
uchar	_GetNoPushState( void )
{
	if	( !mb_NoPush )								// No push before ?
	{												// No
		return(d_NG) ;
	}
	
	mb_NoPush = d_Clear ;
//	/*		Set Auto Tx inhibit		*/
//	mb_AutoTxInhibit = d_On ;				// Inhibit
//	mb_AutoTxOnOff   = d_Off ;				// Off
//	
	m_TimerKey = d_Clear ;
	_ClearSpecialMultiKeyState() ;					// Special multi key status clear
	return(d_OK) ;
}
void	_ReqTxdEdit( uchar txreq , uchar buzreq )  // Tx data edit request
{
  if(TB_5s>=20){
        if(FG_PWRON==0){
	FG_PWRON=1;
	PIN_POWER_CONTROL=1;
	TB_5s=51;  //5.1秒
        }
  	switch	( txreq )    // Jumo to key function
	{
		case 1 :
		        Control_code=0x08;
			break ;
		case 2 :	
		        Control_code=0x04;
			break ;
		case 3 :	
		        Control_code=0x02;
			break ;
	}
  	switch	( buzreq )    // Jumo to key function
	{
		case 1 :
		        //mb_NoPushWait = d_On ;
			//mb_NoPush = d_Clear ;
			BASE_TIME_BEEP_on=103;
                        BASE_TIME_BEEP_off=103;
			TIME_BEEP_freq=0;
			break ;
		case 2 :
		       // mb_NoPushWait = d_Clear ;
			//mb_NoPush = d_On ;
			BASE_TIME_BEEP_on=103;
                        BASE_TIME_BEEP_off=103;
			TIME_BEEP_freq=1;
			break ;
		case 3 :	
		        //mb_NoPushWait = d_On ;
			//mb_NoPush = d_Clear ;
			BASE_TIME_BEEP_on=103;
                        BASE_TIME_BEEP_off=103;
			TIME_BEEP_freq=2;
			break ;
	}	
        dd_set_ADF7021_Power_on();
        dd_set_TX_mode();	
	TIME_BEEP_on=BASE_TIME_BEEP_on;
        TIME_BEEP_off=BASE_TIME_BEEP_off;
        SendTxData();
  }
  else PIN_LED=0;
}

//
/************************************************/
/*												*/
/*		Key duplicate function setting mode		*/
/*				Every 10ms						*/
/*												*/
/*			  in  : none						*/
/*			  out : none						*/
/*												*/
/************************************************/
//
void	_DupliFuncSetMode( void )
{
  UINT8 m_KeyOpt;
	switch	( m_KeyOptSetMode )
	{
		case 1 :
			if	( !mb_NoPushWait )					// No push ?
			{
				m_KeyDupliSetTimeout = d_DupliTime1s ;	// Yes
				++m_KeyOptSetMode ;
				return ;
			}
			if	( !m_KeyDupliSetTimeout )			// Pushing 9s over ?
			{
				m_KeyOptSetMode = 10 ;				// Yes
				//_ReqBuzzer( d_BuzOpt5 ) ;
				BASE_TIME_BEEP_on=103;
                                BASE_TIME_BEEP_off=103;
                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                TIME_BEEP_freq=100;
				
			}
			break ;
			
		case 2 :
			if	( !m_KeyDupliSetTimeout )			// Wait 1s ok ?
			{										// Yes
				++m_KeyOptSetMode;
				m_KeyDupliSetTimeout = d_DupliTime3s ;
				//_ReqBuzzer( d_BuzOpt2 ) ;
				BASE_TIME_BEEP_on=103;
                                BASE_TIME_BEEP_off=103;
                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                TIME_BEEP_freq=0;
				FG_LED_on=1;
			}
			
			if	( m_KindOfKey != d_Idle && m_KindOfKey != d_KeyNoPush )
			{
				_DupliFuncClear() ;					// Duplicate key function clear
			}
			break ;
			
		case 3 :									// Sw in wait
			if	( !m_KeyDupliSetTimeout )
			{
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			
			if	( m_KindOfKey == d_Idle || m_KindOfKey == d_KeyNoPush )
			{
				return ;
			}
			
			if	( m_KeyOptSetOpenStop )				// Setting by stop ?
			{										// Yes
				if	( m_KindOfKey == d_StopKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime1s ;
					++m_KeyOptSetMode ;
					//mb_NoPushWait = d_On ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			else
			{
				if	( m_KindOfKey == d_OpenKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime1s ;
					++m_KeyOptSetMode ;
					
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			break ;
			
		case 4 :
			if	( !m_KeyDupliSetTimeout )			// Wait 1s ok ?
			{										// Yes
				++m_KeyOptSetMode ;
				m_KeyDupliSetTimeout = d_DupliTime3s ;
				//_ReqBuzzer( d_BuzOpt2 ) ;
				BASE_TIME_BEEP_on=103;
                                BASE_TIME_BEEP_off=103;
                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                TIME_BEEP_freq=0;	
				FG_LED_on=1;
			}
//			
//			if	( m_KindOfKey != d_Idle && m_KindOfKey != d_KeyNoPush  )
//			{										// Error
//				_DupliFuncClear() ;					// Duplicate key function clear
//			}
			break ;
			
		case 5 :									// Sw in wait
			if	( !m_KeyDupliSetTimeout )
			{
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			
			if	( m_KindOfKey == d_Idle || m_KindOfKey == d_KeyNoPush )
			{
				return ;
			}
			
			if	( m_KeyOptSetOpenStop )				// Setting by stop ?
			{										// Yes
				if	( m_KindOfKey == d_StopKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime1s ;
					++m_KeyOptSetMode ;
					mb_NoPushWait = d_On ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			else
			{
				if	( m_KindOfKey == d_OpenKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime1s ;
					++m_KeyOptSetMode ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			break ;
			
		case 6 :
			if	( !m_KeyDupliSetTimeout )			// Wait 1s ok ?
			{										// Yes
				++m_KeyOptSetMode ;
				m_KeyDupliSetTimeout = d_DupliTime3s ;
				//_ReqBuzzer( d_BuzOpt3 ) ;
				BASE_TIME_BEEP_on=103;
                                BASE_TIME_BEEP_off=103;
                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                TIME_BEEP_freq=2;	
                                FG_LED_on=1;				
			}
			
//			if	( m_KindOfKey != d_Idle && m_KindOfKey != d_KeyNoPush )
//			{										// Error
//				_DupliFuncClear() ;					// Duplicate key function clear
//			}
			break ;
			
		case 7 :									// Sw in wait
			if	( !m_KeyDupliSetTimeout )
			{
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			
			if	( m_KindOfKey == d_Idle || m_KindOfKey == d_KeyNoPush )
			{
				return ;
			}
			
			if	( m_KeyOptSetOpenStop )				// Setting by stop ?
			{										// Yes
				if	( m_KindOfKey == d_StopKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime10s ;
					++m_KeyOptSetMode ;
					mb_NoPushWait = d_On ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			else
			{
				if	( m_KindOfKey == d_OpenKey )
				{
					m_KeyDupliSetTimeout = d_DupliTime10s ;
					++m_KeyOptSetMode ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			break ;
			
		case 8 :									// Sw in wait
		case 9 :									// Sw in wait
			if	( !m_KeyDupliSetTimeout )
			{
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			
			if	( m_KindOfKey == d_Idle || m_KindOfKey == d_KeyNoPush )
			{
				return ;
			}
			
			if	( m_KeyOptSetOpenStop )				// Setting by stop ?
			{										// Yes
				if	( m_KindOfKey == d_StopKey )
				{
					if	( m_KeyOptSetMode == 9 )
					{
						m_KeyOpt = rom_KeyOpt ;
						if	( m_KeyOpt )
						{
							m_KeyOpt = 0 ;
						}
						else
						{
							m_KeyOpt = 1 ;
						}
						rom_KeyOpt=m_KeyOpt;
						KeyOpt_EEPROM_write();
						//_FlashWriteID() ;				// Write data to flash rom
						
						//_ReqBuzzer( d_BuzOpt4 ) ;
						BASE_TIME_BEEP_on=103;
                                                BASE_TIME_BEEP_off=103;
                                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                                TIME_BEEP_freq=4;	
                                                FG_LED_on=1;	
						FG_d_StopKey=0;
						TB_5s=20;
						_DupliFuncClear() ;				// Duplicate key function clear
						return ;
					}
					++m_KeyOptSetMode ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			else
			{
				if	( m_KindOfKey == d_OpenKey )
				{
					if	( m_KeyOptSetMode == 9 )
					{
						m_KeyOpt = rom_KeyOpt ;
						if	( m_KeyOpt )
						{
							m_KeyOpt = 0 ;
						}
						else
						{
							m_KeyOpt = 1 ;
						}
						rom_KeyOpt=m_KeyOpt;
						KeyOpt_EEPROM_write();				// Write data to flash rom
						
						//_ReqBuzzer( d_BuzOpt4 ) ;
						BASE_TIME_BEEP_on=103;
                                                BASE_TIME_BEEP_off=103;
                                                TIME_BEEP_on=BASE_TIME_BEEP_on;
                                                TIME_BEEP_off=BASE_TIME_BEEP_off;
                                                TIME_BEEP_freq=4;	
                                                FG_LED_on=1;
						FG_d_StopKey=0;
						_DupliFuncClear() ;				// Duplicate key function clear
						
						return ;
					}
					++m_KeyOptSetMode ;
				}
				else
				{									// Error
					_DupliFuncClear() ;				// Duplicate key function clear
					return ;
				}
			}
			break ;
			
		case 10 :
			if	( !mb_NoPushWait )					// No push ?
			{
				//_BuzIdle() ;
				_DupliFuncClear() ;					// Duplicate key function clear
				return ;
			}
			break ;
			
	}
}





















void test_mode_control(void)
{
  if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN==0)){
    FG_KEY_OPEN=1;
    dd_set_ADF7021_Power_on();
    dd_set_TX_mode();
    FG_test_mode=0;
    ADF7021_DATA_tx=0;
  }
  if(PIN_KEY_OPEN==1)FG_KEY_OPEN=0;
  
   if((PIN_KEY_STOP==0)&&(FG_KEY_STOP==0)){
    FG_KEY_STOP=1;
    //ADF7021_CE = 0;
    ADF7021_POWER=1;
    FG_test_mode=0;
    ADF7021_DATA_tx=0;
  }
  if(PIN_KEY_STOP==1)FG_KEY_STOP=0; 
  
  if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE==0)){
    FG_KEY_CLOSE=1;
    dd_set_ADF7021_Power_on();
    dd_set_TX_mode();
    FG_test_mode=1;
  }
  if(PIN_KEY_CLOSE==1)FG_KEY_CLOSE=0;  
  
	
  if((ADF7021_DATA_CLK==1)&&(FG_test_mode==1)&&(FG_test1==0)){
     ADF7021_DATA_tx=!ADF7021_DATA_tx;
     FG_test1=1;
  }
  if(ADF7021_DATA_CLK==0)FG_test1=0;	  
  
}