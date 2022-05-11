/***********************************************************************/
/*  FILE        :adf7012.c                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/


#include "main.h"
//#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����

void dd_write_7021_reg(unsigned char* reg_bytes)
{
    UINT8 i, j;
    UINT8 byte;

    HAL_GPIO_WritePin(ADF7021_LE_GPIO_Port,ADF7021_LE_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ADF7021_CLK_GPIO_Port,ADF7021_CLK_Pin,GPIO_PIN_RESET);


    /* Clock data out MSbit first */
//#ifdef _BIG_ENDIAN_
//    for (i=0; i<=3; i++)
//#else
//    for (i=3; i>=0; i--)
//#endif
    for (i=0; i<=3; i++)
    {
        byte = reg_bytes[i];

        for (j=8; j>0; j--)
        {
             HAL_GPIO_WritePin(ADF7021_CLK_GPIO_Port,ADF7021_CLK_Pin,GPIO_PIN_RESET);
            if (byte & (1<<(j-1)))  HAL_GPIO_WritePin(ADF7021_DATA_GPIO_Port,ADF7021_DATA_Pin,GPIO_PIN_SET);
            else HAL_GPIO_WritePin(ADF7021_DATA_GPIO_Port,ADF7021_DATA_Pin,GPIO_PIN_RESET);
             HAL_GPIO_WritePin(ADF7021_CLK_GPIO_Port,ADF7021_CLK_Pin,GPIO_PIN_SET);
            //byte += byte; // left shift 1
        }
        HAL_GPIO_WritePin(ADF7021_CLK_GPIO_Port,ADF7021_CLK_Pin,GPIO_PIN_RESET);
    }


    /* Strobe the latch */

    HAL_GPIO_WritePin(ADF7021_LE_GPIO_Port,ADF7021_LE_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(ADF7021_LE_GPIO_Port,ADF7021_LE_Pin,GPIO_PIN_SET); // Slight pulse extend
    HAL_GPIO_WritePin(ADF7021_DATA_GPIO_Port,ADF7021_DATA_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ADF7021_LE_GPIO_Port,ADF7021_LE_Pin,GPIO_PIN_RESET);;

    /* All port lines left low */

}

void dd_set_ADF7021_Power_on_Init(void)
{
  ADF70XX_REG_T register_value;
	if (HAL_GPIO_ReadPin(ADF7021_CE_GPIO_Port,ADF7021_CE_Pin) == FG_NOT_allow_out)
	{
		HAL_GPIO_WritePin(ADF7021_CE_GPIO_Port,ADF7021_CE_Pin,GPIO_PIN_SET); 
		//ADF7021_CE=1;
		//Delayus(65);             //delay 100us
                Delayus(130);             //delay 200us
	//	Delayus(130);             //delay 200us
	//	Delayus(130);             //delay 200us
	//	Delayus(130);             //delay 200us
	//	Delayus(130);             //delay 200us
	//write R3
            //register_value.whole_reg = 0x0021d043;    //BATTERY MEASURE IS < 2.35V
	    register_value.whole_reg = ROM_adf7012_value[3].whole_reg & 0xF3FFFFFF; 
            dd_write_7021_reg(&register_value.byte[0]);
            Delayus(25);  //delay 40us		
	}
}


void dd_set_ADF7021_Power_on(void)
{
//	if (ADF7021_CE == 0)
//	{
//		ADF7021_CE = 1;
	if (HAL_GPIO_ReadPin(ADF7021_CE_GPIO_Port,ADF7021_CE_Pin) == FG_NOT_allow_out)
	{
		HAL_GPIO_WritePin(ADF7021_CE_GPIO_Port,ADF7021_CE_Pin,GPIO_PIN_SET); 
		//ADF7021_CE=1;
		//Delayus(65);             //delay 100us
                Delayus(130);             //delay 200us
		//Delayus(130);             //delay 200us
		//Delayus(130);             //delay 200us
		//Delayus(130);             //delay 200us
		//Delayus(130);             //delay 200us  
	}
}


void dd_set_TX_mode(void)
{
//	ADF70XX_REG_T register_value;       FSK mode
//        //write R0
//	register_value.whole_reg = 0x01082000;
//	dd_write_7021_reg(&register_value.byte[0]);
//	Delayus(79);		//delay 40us
//        
//	//write R1
//	register_value.whole_reg = 0x000aa6e1;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(79);		//delay 40us
//
//	//write R2
//	register_value.whole_reg = 0x00001aa2;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(79);		//delay 40us	
//	
//	//write R3
//	register_value.whole_reg = 0x0022a0cf;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(79);		//delay 40us	


  
//	ADF70XX_REG_T register_value;      GFSK mode
//        //write R0
//	register_value.whole_reg = 0x01084000;
//	dd_write_7021_reg(&register_value.byte[0]);
//	Delayus(25);		//delay 40us
//        
//	//write R1
//	register_value.whole_reg = 0x00154dc1;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(25);		//delay 40us
//
//	//write R2
//	register_value.whole_reg = 0x01120aa6;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(25);		//delay 40us	
//	
//	//write R3
//	register_value.whole_reg = 0x0022a0cf;
//	dd_write_7021_reg(&register_value.byte[0]);
//        Delayus(25);		//delay 40us	



////modify  2014 6 5
//      ADF70XX_REG_T register_value;
//
//      //write R0
//      register_value.whole_reg = 0x0884000;
//      dd_write_7021_reg(&register_value.byte[0]);
//      Delayus(25);  //delay 40us
//        
//      //write R1
//      register_value.whole_reg = 0x00154dc1;
//      dd_write_7021_reg(&register_value.byte[0]);
//      Delayus(25);  //delay 40us
// 
//      //write R2
//      register_value.whole_reg = 0x011209a6;
//      dd_write_7021_reg(&register_value.byte[0]);
//      Delayus(25);  //delay 40us 
// 
//      //write R3
//      //register_value.whole_reg = 0x0021a04f;    //DIGITAL LOCK DETECT
//      register_value.whole_reg = 0x0021d04f;    //BATTERY MEASURE IS < 2.35V
//      dd_write_7021_reg(&register_value.byte[0]);
//      Delayus(25);  //delay 40us   
  
  
  
//modify  2014 7 10
      ADF70XX_REG_T register_value;

      //write R0
      register_value.whole_reg = ROM_adf7012_value[0].whole_reg;
      dd_write_7021_reg(&register_value.byte[0]);
      Delayus(25);  //delay 40us
        
      //write R1
      register_value.whole_reg = ROM_adf7012_value[1].whole_reg;
      dd_write_7021_reg(&register_value.byte[0]);
      Delayus(25);  //delay 40us
 
      //write R2
      register_value.whole_reg = ROM_adf7012_value[2].whole_reg;
      dd_write_7021_reg(&register_value.byte[0]);
      Delayus(25);  //delay 40us 
 
      //write R3
      //register_value.whole_reg = 0x0021a04f;    //DIGITAL LOCK DETECT
      register_value.whole_reg = ROM_adf7012_value[3].whole_reg;    //BATTERY MEASURE IS < 2.35V
      dd_write_7021_reg(&register_value.byte[0]);
      Delayus(25);  //delay 40us    
}