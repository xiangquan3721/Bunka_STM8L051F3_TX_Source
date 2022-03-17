#ifndef __IAP_FLASH__
#define __IAP_FLASH__

#include "REG_MA82G5Bxx.H"
#include "Type.h"
#include "API_Macro_MA82G5Bxx.H"
#include "API_Uart_BRGRL_MA82G5Bxx.H"
#include <Intrins.h> 
#include <Absacc.h>
#include "ID_Decode.h"
#include "ram.h"
#include "uart.h"
#include "Type.h"

/* 

IAP Flash�ռ�: 1024Byte -> 0x7C00 ~ 0x7FFF.
255��ID: 255 * 3 = 765byte -> 0x7C00 ~ 0x7EFC; ��ͨID
Addr_rf_offset -> 0x7FFA; ��Ƶƫ����
ID_SCX1801_DATA -> 0x7FFB ~ 0x7FFD; ͨ��ID
ID_DATA_PCS -> 0x7FFE ~ 0X7FFF. ID����

*/

#define ISP_ADDRESS     0x7A00	 //ISP��ʼ��ַ 
#define IAP_ADDRESS     0x7C00	 //IAP��ʼ��ַ
#define ERR_CNT_MAX     3 		 // �������Լ������ֵ

#define addr_eeprom_sys IAP_ADDRESS
#define Addr_rf_offset  0x3FA
#define Addr_rom_KeyOpt 0x3F9

// ����ʹ��MOVC�ķ�ʽ��ȡIAP������
#define	IAP_ReadByteByMOVC(x)	CBYTE[x]


void Init_IAP_flash(void);
u8 IAP_ReadPPage(u8 PsfrAddr);
void IAP_WritePPage(u8 PsfrAddr,u8 PsfrData);
void IAP_ErasePage(u8 ByteAddr);
u8 IAP_WriteBuf_With_Protect_Verify(u16 ByteAddr,u8 *pBuf,u16 Cnt);
void ID_EEPROM_write(void);
void ID_learn(void);
void eeprom_sys_load(void);
void ID_Login_EXIT_Initial(void);
void ALL_ID_EEPROM_Erase(void);
void ID_SCX1801_EEPROM_write(u32 id);
void Delete_GeneralID_EEPROM(u32 id);
void IAP_Erase_All_ID(void);
void IAP_Write_Byte(u16 Addr, u8 wdata);

#endif
