#include "gpio.h"


/***********************************************************************************
��������:   void InitPort(void)
��������:   IO����
�������:   
���ز���:     
*************************************************************************************/
void Init_Port(void)
{ 
    /* CLOSE/STOP/OPEN: P10/P11/P12; TP7: P13 TestMode */
    PORT_SetP1OpenDrain(BIT0|BIT1|BIT2|BIT3);           // ����P13 Ϊ��©���
    PORT_SetP1PushPull(BIT0|BIT1|BIT2);                 // ����P10,P11,P12 Ϊ�������
    P13 = 1;                                            // P13��Ϊ����ģʽ
    PORT_EnP10P11P12P13PullHigh();                      // ʹ�� P10,P11,P12,P13 ����
    
    /* SPI */
    PORT_SetP1PushPull(BIT4|BIT5|BIT7);					// ����P15(MOSI),P17(SPICLK)Ϊ׼˫���
	PORT_SetP1OpenDrain(BIT6);							// ����P16(MISO)Ϊ׼˫���
    P16 = 1;                                            // ����
	PORT_EnP14P15P16P17PullHigh();						// ʹ�� P14,P15,P16,P17 ����
    
    /*BEEP:P20; ��¼:P21; ���߿���:T->P22,R->P23; ����/����/����LED:P24/P25/P26; ML7345_RESETN:P27 */
	PORT_SetP2OpenDrain(BIT1);                          // ����P21 Ϊ��©���
    P21 = 1;                                            // P21��Ϊ����ģʽ
    
#if (NEW_PCB==0)   
    PORT_SetP2PushPull(BIT0|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7); // ����P20,P22,P23,P24,P25,P26,P27 Ϊ�������
#else
    PORT_SetP2PushPull(BIT0|BIT2|BIT3|BIT5|BIT7);       // ����P20,P22,P23,P25,P27 Ϊ�������
    PORT_SetP2OpenDrain(BIT4);
    P24 = 1;
#endif
    
    PORT_EnP20P21P22P23PullHigh();                      // ʹ�� P20,P21,P22,P23 ����
	PORT_EnP24P25P26P27PullHigh();			            // ʹ�� P24,P25,P26,P27 ����
    P20 = 0;
    
#if (NEW_PCB==0)  
    PORT_SetP3InputOnly(BIT5);
#else
    //PORT_SetP3PushPull(BIT4|BIT5);
    PORT_SetP3QuasiBi(0xFF);                            //����P3λ׼˫���ģʽ
#endif
 
    /* TP3/TP4: P40/P41 */
    PORT_SetP4OpenDrain(BIT0|BIT1);                     // ����P40,P41 Ϊ��©���
    P40 = 1; P41 = 1;                                   // P40/p41 ��Ϊ����ģʽ
    PORT_EnP40P41PullHigh();                            // ʹ�� P40,P41 ����
    
    //////////////////////test/////////////////////////
    //PORT_SetP6PushPull(BIT0);   //CLK OUT
    //AUXR0 &= ~(P60OC0|P60OC1);
    //AUXR0 |= (0x80|P60FD);
    //////////////////////test/////////////////////////
    
    FG_allow_out = 1;
	FG_NOT_allow_out = 0;
    Receiver_LED_TX = 0;  
    Receiver_LED_RX = 0;  
    Receiver_LED_OUT = 0; 
    Receiver_OUT_OPEN = 0;
    Receiver_OUT_STOP = 0;
    Receiver_OUT_CLOSE = 0;
    ML7345_RESETN = 0;
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
#if (NEW_PCB==1)
void Init_INT1(void)
{
	INT_SetINT1P33();						//����INT1����P33
	//INT_SetINT1_DetectRisingEdge();		
    INT_SetINT1_DetectFallingEdge();        //����INT1�ⲿ�жϼ�ⷽʽΪ�½��ؼ��
	INT_SetINT1Filter_Sysclk_x3();			//����INT1�˲�Ϊ��sysclk��*3
}
#endif

/***********************************************************************************
��������:   void INT_INT0(void)	
��������:INT0�жϷ������
�������:   
���ز���: 

����ML7345D���ͽ�������жϡ�

*************************************************************************************/
void INT_INT0(void)		interrupt INT_VECTOR_INT0
{
	if(Flag_test_mode == 0) ML7345_TRX_Del();
    else DataReceive();
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
	if(Flag_test_mode == 0) ML7345_TRX_Del();
    else DataReceive();
}


/***********************************************************************************
��������:   void InitInterrupt(void)
��������:   �жϳ�ʼ��
�������:    
���ز���:     
*************************************************************************************/
void Init_Interrupt(void)
{
#if (NEW_PCB==0)
    Init_INT0();
    INT_EnINT0();			//	ʹ��INT0�ж�
#else
    Init_INT1();
	INT_EnINT1();			//	ʹ��INT1�ж�
#endif
    INT_EnTIMER0();			//	ʹ��T0�ж�
	INT_EnUART0();			//	ʹ�ܴ����ж�
}


/*
u8 key_scan(void)
{
    if((Receiver_Login==0 | TP3==0 | TP4==0 | Receiver_test==0))
    {
        delay_ms(50);
        if((Receiver_Login==0 | TP3==0 | TP4==0 | Receiver_test==0) && key_flag == 0)
        {
            key_flag = 1;
            if(Receiver_Login==0) return 2;
            else if (Receiver_test==0) return 3;
            else return 1;
        }
        else return 0;
            
    }
    else if(Receiver_Login==1 && TP3==1 && TP4==1 && Receiver_test==1)
    {
        key_flag = 0;
        return 0;
    }
    return 0;    
}*/


