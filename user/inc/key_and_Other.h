/***********************************************************************/
/*  FILE        :key_and_Other.h                                       */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003f3     Crystal: 4M HSI                        */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include "gpio.h"		// �ܽŶ���
#include "Type.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����

#include "IAP_flash.h"		// eeprom
#include "uart.h"		// uart
#include "adc.h"		// ad
#include "Timer.h"		// ��ʱ��
#include "gpio.h"
#include "EXIT_FUN.h"
#include "ML7345.h"

void key_check(void);
void time_control(void);
void test_mode_control(void);


void	_SwIn( uchar sw );
void	_FuncReg( void );
void	_FuncStop( void );
void	_FuncOpenStop( void );
void	_FuncOpenReg( void );
void	_FuncStopReg( void );
void	_FuncCloseReg( void );
void	_FuncVentReg( void );
void	_FuncAutoTxStart( void );
void	_FuncAutoTxStop( void );
void	_FuncNoPush( void );
void	_SetKeyChatterCount( void );
void	_KeyInTx( void );
void	_ClearSpecialMultiKeyState( void );
void	_DupliFuncClear( void );
uchar	_GetNoPushState( void );
void	_ReqTxdEdit( uchar txreq , uchar buzreq );  // Tx data edit request
void	_DupliFuncSetMode( void );
void	_SetRegistrationMode( uchar mode );
uchar	_GetRegMode( void );
void	_IdClear( void );
void	_RegistrationMode( void );
u32 atol(unsigned char* m_RegID_x);
void	_FuncStopReg( void );
void	_Pass3secKey( uchar req );

//void START_AD_SAMPLER(void);
//void ADC_read(void);
void _ReqBuzzer(u16 BEEP_on_SET,u8 BEEP_off_SET,u8 BEEP_freq_SET);

