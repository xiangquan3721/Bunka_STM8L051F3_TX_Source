#ifndef UART_HANDLE_H
#define UART_HANDLE_H

void UART1_INIT_handle(void);
void UART1_RX_RXNE_handle(void);
void Uart_handle(void);

typedef enum COMM_HANDLE_STATUS
{
	COMM_IDLE,
	COMM_NACK,
        COMM_ACK,
        COMM_FAIL,
	
}COMM_HANDLE_TYPE;

#endif