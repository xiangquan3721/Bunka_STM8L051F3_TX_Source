#ifndef __GPIO_DEFS_H
#define __GPIO_DEFS_H

#include "iostm8l151g4.h"

#ifndef u8
#define u8  unsigned char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef u32
#define u32 unsigned long
#endif

#ifndef U8
#define U8  unsigned char
#endif

#ifndef S8
#define S8  char
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U32
#define U32 unsigned long
#endif

typedef enum {FALSE = 0, TRUE = !FALSE} BOOL;


#define INFINITE 0xFFFFFFFF

#define Key_Login_Val   PA_IDR_IDR2 //登录按键
#define Key_Login_DDR   PA_DDR_DDR2
#define Key_Login_CR1   PA_CR1_C12
#define Key_Login_CR2   PA_CR2_C22

#define PIN_BEEP        PB_ODR_ODR1 //Output   蜂鸣器
#define PIN_BEEP_DDR    PB_DDR_DDR1
#define PIN_BEEP_CR1    PB_CR1_C11
#define PIN_BEEP_CR2    PB_CR2_C21

#define RX_LED          PB_ODR_ODR3 //受信指示
#define RX_LED_DDR      PB_DDR_DDR3
#define RX_LED_CR1      PB_CR1_C13
#define RX_LED_CR2      PB_CR2_C23

#define TX_LED          PB_ODR_ODR2 //送信指示
#define TX_LED_DDR      PB_DDR_DDR2
#define TX_LED_CR1      PB_CR1_C12
#define TX_LED_CR2      PB_CR2_C22

#define RX_LED_OUT      PA_ODR_ODR3 //动作指示
#define RX_LED_OUT_DDR  PA_DDR_DDR3
#define RX_LED_OUT_CR1  PA_CR1_C13
#define RX_LED_OUT_CR2  PA_CR2_C23

#define KEY_TX_OPEN     PD_IDR_IDR3 /* 工作模式下按键发送OPEN,低电平有效 */
#define KEY_TX_OPEN_DDR PD_DDR_DDR3
#define KEY_TX_OPEN_CR1 PD_CR1_C13
#define KEY_TX_OPEN_CR2 PD_CR2_C23
#define Key_Tx_Carrier  KEY_TX_OPEN /* 测试模式下按键发载波 */

#define KEY_TX_STOP     PD_IDR_IDR1 /* 工作模式下按键发送STOP,低电平有效 */
#define KEY_TX_STOP_DDR PD_DDR_DDR1
#define KEY_TX_STOP_CR1 PD_CR1_C11
#define KEY_TX_STOP_CR2 PD_CR2_C21
#define Key_Rx_Data     KEY_TX_STOP /* 测试模式下按键接收数据 */

#define KEY_TX_CLOSE     PD_IDR_IDR2 /* 工作模式下按键发送CLOSE,低电平有效 */
#define KEY_TX_CLOSE_DDR PD_DDR_DDR2
#define KEY_TX_CLOSE_CR1 PD_CR1_C12
#define KEY_TX_CLOSE_CR2 PD_CR2_C22
#define Key_Tx_Data      KEY_TX_CLOSE   /* 测试模式下按键发数据 */

#define TP7_TEST_MODE       PC_IDR_IDR0  /* 0:测试模式；1:工作模式 */
#define TP7_TEST_MODE_DDR   PC_DDR_DDR0
#define TP7_TEST_MODE_CR1   PC_CR1_C10
#define TP7_TEST_MODE_CR2   PC_CR2_C20

#define TP8_TXRX_MODE       PC_IDR_IDR1  /* 预留 */
#define TP8_TXRX_MODE_DDR   PC_DDR_DDR1
#define TP8_TXRX_MODE_CR1   PC_CR1_C11
#define TP8_TXRX_MODE_CR2   PC_CR2_C21

#define pin_sda_out         PC_ODR_ODR6    /* 测试模式下数据输出 */
#define pin_sda_in          PC_IDR_IDR6    /* 测试模式下数据输入 */
#define pin_clk_in          PC_IDR_IDR4    /* 测试模式下时钟输入 */

#define CMT2300A_ReadGpio1()    PD_IDR_IDR4 /* CMT2300A发送完成,高电平有效*/
#define CMT2300A_Gpio1_DDR      PD_DDR_DDR4
#define CMT2300A_Gpio1_CR1      PD_CR1_C14
#define CMT2300A_Gpio1_CR2      PD_CR2_C24

#define CMT2300A_ReadGpio2()    PC_IDR_IDR4 /* CMT2300A接收完成,高电平有效*/
#define CMT2300A_Gpio2_DDR      PC_DDR_DDR4
#define CMT2300A_Gpio2_CR1      PC_CR1_C14
#define CMT2300A_Gpio2_CR2      PC_CR2_C24

#define CMT2300A_ReadGpio3()    PC_IDR_IDR6
#define CMT2300A_Gpio3_DDR      PC_DDR_DDR6
#define CMT2300A_Gpio3_CR1      PC_CR1_C16
#define CMT2300A_Gpio3_CR2      PC_CR2_C26

/********************天线切换 CG2214M6控制引脚寄存器*****************************************/
#define CG2214M6_VC1        PA_ODR_ODR5
#define CG2214M6_VC1_DDR    PA_DDR_DDR5
#define CG2214M6_VC1_CR1    PA_CR1_C15
#define CG2214M6_VC1_CR2    PA_CR2_C25

#define CG2214M6_VC2        PB_ODR_ODR0
#define CG2214M6_VC2_DDR    PB_DDR_DDR0
#define CG2214M6_VC2_CR1    PB_CR1_C10
#define CG2214M6_VC2_CR2    PB_CR2_C20

#define CG2214M6_RF1_USE  \
    {                     \
        CG2214M6_VC1 = 0; \
        CG2214M6_VC2 = 1; \
    }
#define CG2214M6_RF2_USE  \
    {                     \
        CG2214M6_VC1 = 1; \
        CG2214M6_VC2 = 0; \
    }
#define CG2214M6_USE_T CG2214M6_RF1_USE
#define CG2214M6_USE_R CG2214M6_RF2_USE



#endif
