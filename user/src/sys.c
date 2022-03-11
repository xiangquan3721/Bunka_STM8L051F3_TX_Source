#include "sys.h"

void SysClock_Init(void)
{
    CLK_ICKCR_HSION = 1; //开启内部高速时钟
    while ((CLK_ICKCR & 0x02) == 0); //等待稳定
    CLK_SWR = 0x01;    //将系统时钟配置为内部高速时钟
    CLK_SWCR_SWEN = 1; // 执行切换
    CLK_CKDIVR = 0x00; //系统时钟1分频,16M

    CLK_ICKCR_LSION = 1; // 使能内部LSI OSC＿8KHz＿
    while (CLK_ICKCR_LSIRDY == 0);
}

void WDT_init(void)
{
    IWDG_KR = 0xCC;
    IWDG_KR = 0x55;
    IWDG_PR = 3;
    IWDG_KR = 0xAA;
}

void ClearWDT(void)
{
    IWDG_KR = 0xAA;
}



void GPIO_Pin_Init(void)
{
    /* 登录按键 */
    Key_Login_DDR = 0;      /* 输入 */
    Key_Login_CR1 = 0;      /* 浮空 */
    Key_Login_CR2 = 0;      /* 禁止外部中断 */

    /* 蜂鸣器 */
    PIN_BEEP_DDR = 1;       /* 输出 */
    PIN_BEEP_CR1 = 1;       /* 推挽 */
    PIN_BEEP_CR2 = 1;       /* Speed 10MHz */

    /* 接收LED */
    RX_LED_DDR = 1;         /* 输出 */
    RX_LED_CR1 = 1;         /* 推挽 */
    RX_LED_CR2 = 1;         /* Speed 10MHz */

    /* 发送LED */
    TX_LED_DDR = 1;         /* 输出 */
    TX_LED_CR1 = 1;         /* 推挽 */
    TX_LED_CR2 = 1;         /* Speed 10MHz */

    /* 输出指示LED */
    RX_LED_OUT_DDR = 1;     /* 输出 */
    RX_LED_OUT_CR1 = 1;     /* 推挽 */
    RX_LED_OUT_CR2 = 1;     /* Speed 10MHz */

    /* 按键发送指令输出OPEN */
    KEY_TX_OPEN_DDR = 0;    /* 输入 */
    KEY_TX_OPEN_CR1 = 1;    /* 上拉 */
    KEY_TX_OPEN_CR2 = 0;    /* 禁止外部中断 */

    /* 按键发送指令输出STOP */
    KEY_TX_STOP_DDR = 0;    /* 输入 */
    KEY_TX_STOP_CR1 = 1;    /* 上拉 */
    KEY_TX_STOP_CR2 = 0;    /* 禁止外部中断 */

    /* 按键发送指令输出CLOSE */
    KEY_TX_CLOSE_DDR = 0;   /* 输入 */
    KEY_TX_CLOSE_CR1 = 1;   /* 上拉 */
    KEY_TX_CLOSE_CR2 = 0;   /* 禁止外部中断 */

    /*天线切换 CG2214M6控制引脚*/
    CG2214M6_VC1_DDR = 1;
    CG2214M6_VC1_CR1 = 1;
    CG2214M6_VC1_CR2 = 1;

    CG2214M6_VC2_DDR = 1;
    CG2214M6_VC2_CR1 = 1;
    CG2214M6_VC2_CR2 = 1;

    /* 测试模式引脚 */
    TP7_TEST_MODE_DDR = 0;
    TP7_TEST_MODE_CR1 = 0;
    TP7_TEST_MODE_CR2 = 0;

    TP8_TXRX_MODE_DDR = 0;
    TP8_TXRX_MODE_CR1 = 0;
    TP8_TXRX_MODE_CR2 = 0;
}





