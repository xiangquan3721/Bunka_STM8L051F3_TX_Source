
#include "stm32l0xx_hal.h"
#include "Model_Test.h"
#include "main.h"

#ifdef MODEL_TEST

//extern UART_HandleTypeDef huart2;

//uint8_t rx_data[1]={0};
//uint32_t rx_data_32[1]={0};

//uint8_t uart_look = 0;
//uint8_t systick_look = 0;
//uint8_t ad_look=0;
//uint8_t exti_look=0;

//void MX_ADC_Init(void);

//#define addr_eeprom_sys 0x08080000

//void TEST_UART(void)
//{
//	uint8_t Tp_data[1]={0xa8};
//	
//	HAL_UART_Transmit(&huart2,Tp_data,1,3000);
//	
//	UART_Start_Receive_IT(&huart2,rx_data,1);
//	
//	
//}

////rx回调函数
////UART1_RX_RXNE
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	////UART1_RX_RXNE
//	uart_look++;
//	UART_Start_Receive_IT(huart,rx_data,1);
//}

////1ms的回调函数
////TIM4_UPD_OVF
////level 0
//void HAL_IncTick(void)
//{
//	systick_look++;
//	HAL_GPIO_TogglePin(POWER_GPIO_Port,POWER_Pin);
//}

//void TEST_EEPROM(void)
//{
//	uint8_t Tp_data[1]={0xa8};
//	
//	HAL_FLASHEx_DATAEEPROM_Unlock();
//	HAL_FLASHEx_DATAEEPROM_Erase(addr_eeprom_sys);
//	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,addr_eeprom_sys,0xa8);
//	rx_data[0] = *(uint8_t *)addr_eeprom_sys;
//	
//	HAL_FLASHEx_DATAEEPROM_Lock();
//}

////ADC2_EOC_INT
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	
//	ad_look++;
//	rx_data_32[0] = HAL_ADC_GetValue(hadc);
//	//HAL_ADC_Start_IT(hadc);
//}

////EXTI_PORTA1
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  exti_look++;
//}


	
#endif























