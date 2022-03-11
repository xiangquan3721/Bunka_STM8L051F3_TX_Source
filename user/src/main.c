#include "timer.h"
#include "sys.h"
#include "spi.h"
#include "radio.h"
#include "cmt2300a_app.h"


static u8 g_txBuffer1[RF_PACKET_SIZE] = {0x95,0x55,0x55,0x55,0x55,0x55,0x56,0x55,0x95,0x55,0x56,0x55};//open
static u8 g_txBuffer2[RF_PACKET_SIZE] = {0x95,0x55,0x55,0x55,0x55,0x55,0x59,0x55,0x95,0x55,0x59,0x55};//stop   /* RF Tx buffer */
static u8 g_txBuffer3[RF_PACKET_SIZE] = {0x95,0x55,0x55,0x55,0x55,0x55,0x65,0x55,0x95,0x55,0x65,0x55}; //close


u8 sum = 1;

int main(void)
{
    u8 sw_s = 0;
    u8 cnt = 0;
    u8 rate = 1;
    _DI();
    //WDT_init();
    SysClock_Init();
    ClearWDT();
    GPIO_Pin_Init();
    TIM4_Init();
    SPI_Config_Init();
    _EI();

    RF_Test_Mode();
    RF_Init();
    //CG2214M6_USE_R;

    ClearWDT();
    //CMT2300A_RX_ENABLE();

    while(1)
    {
        if(Key_Login_Val == 0 && sw_s == 0)
        {
            sw_s = 1;
            if(cnt == 0)
            {
                cnt = 1;
                CMT2300A_Set_Freq(1);
            }
            else
            {
                cnt = 0;
                CMT2300A_Set_Freq(0);
            }
        }
        if(Key_Login_Val == 1 && KEY_TX_OPEN == 1 && KEY_TX_CLOSE == 1 && KEY_TX_STOP == 1 && TP8_TXRX_MODE == 1)
        {
            sw_s = 0;
        }
        if(CMT2300A_ReadGpio1())
        {
            TX_LED = 0;
            CMT2300A_ClearInterruptFlags();
            CMT2300A_GoSleep();
            CMT2300A_RX_ENABLE();
        }
        if(KEY_TX_OPEN == 0 && sw_s == 0)
        {
            sw_s = 1;
            CMT2300A_TX_PACKET(g_txBuffer1,12);
            TX_LED = 1;
        }
        if(KEY_TX_STOP == 0 && sw_s == 0)
        {
            sw_s = 1;
            CMT2300A_TX_PACKET(g_txBuffer2,12);
            TX_LED = 1;
        }
        if(KEY_TX_CLOSE == 0 && sw_s == 0)
        {
           sw_s = 1;
           CMT2300A_TX_PACKET(g_txBuffer3,12);
           TX_LED = 1;
        }
        if(CMT2300A_ReadGpio2())
        {
            RX_LED = 1;
            time_rx_led = 200;
            CMT2300A_GoStby();
            CMT2300A_ReadFifo(g_rxBuffer, RF_PACKET_SIZE);
            CMT2300A_GoSleep();
            //Signal_DATA_Decode(0,g_rxBuffer);
            CMT2300A_RX_ENABLE();
        }
        if(TP8_TXRX_MODE == 0 && sw_s == 0)
        {
            rate++;
            sw_s = 1;
            CMT2300A_Set_DataRate(rate);
            if(rate == 3)   rate = 0;
        }
       if(time_rx_led == 0) RX_LED = 0;
       system_delay_ms(10);
    }
}

