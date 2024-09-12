/************************************************************************/
/* @file  uart_proxy.h */
/* @brief Header da proxy para serviço UART */
/************************************************************************/

#ifndef UART_PROXY_H_
#define UART_PROXY_H_
#include "../Services/uart.h"
typedef struct  
{
	Uart_server* uart_server; // para cada proxy existe um server
}Uart_Proxy;

// Metodos
Uart_Proxy*		 Uart_Proxy_Ctor(Uart_Proxy* me, Uart_server* server);
uint8_t			 Uart_Proxy_Init(Uart_Proxy* const me);
void			 Uart_Proxy_Dctor(Uart_Proxy* const me);
void			 Uart_Proxy_SendByte(uint8_t byte);
uint8_t			 Uart_Proxy_ReceiveByte(void);
void			 Uart_Proxy_PutString(uint8_t* buffer);

#endif /* UART_PROXY_H_ */