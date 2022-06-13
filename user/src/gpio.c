#include "gpio.h"


/***********************************************************************************
��������:   void InitPort(void)
��������:   IO����
�������:   
���ز���:     
*************************************************************************************/
void Init_Port(void)
{ 
    /* KEY OPEN/STOP: P12/P11; PIN_test_mode: P13*/
    PORT_SetP1OpenDrain(BIT1|BIT2|BIT3);                // ���� P11/P12/P13Ϊ��©���
    P11 = 1;P12 = 1;P13 = 1;                            // P11/P12/P13��Ϊ����ģʽ
    PORT_EnP10P11P12P13PullHigh();                      // ʹ�� P10,P11,P12,P13 ����
    
    /* SPI */
    //PORT_SetP1PushPull(BIT4|BIT5|BIT7);					// ����P15(MOSI),P17(SPICLK)Ϊ׼˫���
	//PORT_SetP1OpenDrain(BIT6);							// ����P16(MISO)Ϊ׼˫���
    //P16 = 1;                                            // ����
	//PORT_EnP14P15P16P17PullHigh();						// ʹ�� P14,P15,P16,P17 ����
    
    /*KEY CLOSE:P25; BEEP:P20; ��¼:P21; ML7345D_GPIO3:P24; ����LED:P27 */
	PORT_SetP2OpenDrain(BIT1|BIT3);                          // ����P21 Ϊ��©���
    P21 = 1; P23 = 1;                                           // P21��Ϊ����ģʽ
    
    PORT_SetP2PushPull(BIT0|BIT7);                      // ����P20/P27 Ϊ�������
    
    PORT_SetP2OpenDrain(BIT5);
    P25 = 1;                                            // ����P25Ϊ����
    
    PORT_EnP20P21P22P23PullHigh();                      // ʹ�� P20,P21,P22,P23 ����
	PORT_EnP24P25P26P27PullHigh();			            // ʹ�� P24,P25,P26,P27 ����
    P20 = 0;

    /* ML7345_RESETN:P34; ML7345D_POWER:P35; */
    PORT_SetP3PushPull(BIT4|BIT5);                      // ����P34/P35 Ϊ�������
    
    /* PIN_POWER_CONTROL:P40 */
    PORT_SetP4PushPull(BIT0);                           // ����P40Ϊ�������
    
    //////////////////////test/////////////////////////
    //PORT_SetP6PushPull(BIT0);   //CLK OUT
    //AUXR0 &= ~(P60OC0|P60OC1);
    //AUXR0 |= (0x80|P60FD);      //MCK/2 output 
    //////////////////////test/////////////////////////
   
    ML7345_RESETN = 0;
    PIN_TX_LED = 0;
    PIN_POWER_CONTROL = 0;
    ML7345D_POWER = FG_NOT_allow_out;
    
    PORT_SetP2OpenDrain(BIT2|BIT3|BIT4|BIT6);           //δ��IO��ȫ����Ϊ����
    P22=1;P23=1;P24=1;P26=1;
    PORT_SetP3InputOnly(BIT2);
    PORT_SetP4OpenDrain(BIT1);
    P41=1;
}

void SpiGpio_Init(void)
{
    PORT_SetP1PushPull(BIT4|BIT5|BIT7);					// ����P15(MOSI),P17(SPICLK)Ϊ׼˫���
	PORT_SetP1OpenDrain(BIT6);							// ����P16(MISO)Ϊ׼˫���
    P16 = 1;                                            // ����
	PORT_EnP14P15P16P17PullHigh();
}

void SpiGpio_UnInit(void)
{
    PORT_SetP1OpenDrain(BIT4|BIT5|BIT6|BIT7);
    P16 = 1;                                            // ����
    P14 = 1;P15 = 1;P17 = 1;
	//PORT_EnP14P15P16P17PullHigh();
}


/***********************************************************************************
��������:   void InitINT0(void)
��������:   INT0��ʼ��
�������:   
���ز���:  
����ML7345D ���ͽ�������жϡ�
*************************************************************************************/

void Init_INT0(void)
{
	INT_SetINT0P32();						//����INT0����P32
	INT_SetINT0_DetectFallingEdge();		//����INT0�ⲿ�жϼ�ⷽʽΪ�½��ؼ��
	//INT_SetINT0_DetectRisingEdge();
    INT_SetINT0Filter_Sysclk_x3();			//����INT0�˲�Ϊ��sysclk��*3
}


/***********************************************************************************
��������:   void InitINT1(void)
��������:   INT1��ʼ��
�������:   
���ز���:   
ML7345D BER���ԡ�
*************************************************************************************/
void Init_INT1(void)
{
	INT_SetINT1P33();						//����INT1����P33
	//INT_SetINT1_DetectRisingEdge();		
    INT_SetINT1_DetectFallingEdge();        //����INT1�ⲿ�жϼ�ⷽʽΪ�½��ؼ��
	INT_SetINT1Filter_Sysclk_x3();			//����INT1�˲�Ϊ��sysclk��*3
}


/***********************************************************************************
��������:   void INT_INT0(void)	
��������:INT0�жϷ������
�������:   
���ز���: 

����ML7345D���ͽ�������жϡ�

*************************************************************************************/
void INT_INT0(void)		interrupt INT_VECTOR_INT0
{
    //ML7345_TRX_Del();
		EXTI_PORTA1();
}


/***********************************************************************************
��������:   void INT_INT1(void)	
��������:INT1�жϷ������
�������:   
���ز���:    

ML7345D BER���ԡ�

*************************************************************************************/
void INT_INT1(void)		interrupt INT_VECTOR_INT1
{
    //ML7345_TRX_Del();
}


/***********************************************************************************
��������:   void InitInterrupt(void)
��������:   �жϳ�ʼ��
�������:    
���ز���:     
*************************************************************************************/
void Init_Interrupt(void)
{
    Init_INT0();
	INT_EnINT0();			//	ʹ��INT1�ж�
}


/*
u8 key_scan(void)
{
    if((PIN_KEY_OPEN==0 | PIN_KEY_STOP==0 | PIN_KEY_CLOSE==0 | PIN_KEY_LOGIN==0))
    {
        delay_ms(50);
        if((PIN_KEY_OPEN==0 | PIN_KEY_STOP==0 | PIN_KEY_CLOSE==0 | PIN_KEY_LOGIN==0) && key_flag == 0)
        {
            key_flag = 1;
            if(PIN_KEY_OPEN==0)         return 2;
            else if (PIN_KEY_STOP==0)   return 3;
            else if (PIN_KEY_CLOSE==0)  return 4;
            else if (PIN_KEY_LOGIN==0)  return 5;
            else return 1;
        }
        else return 0;
            
    }
    else if(PIN_KEY_OPEN==1 && PIN_KEY_STOP==1 && PIN_KEY_CLOSE==1 && PIN_KEY_LOGIN==1)
    {
        key_flag = 0;
        return 0;
    }
    return 0;    
}*/


