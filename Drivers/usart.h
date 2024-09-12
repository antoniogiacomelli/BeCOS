/***************************************************
@file	usart.h
@brief	Header para UART/USART
		Target: Atmega328p 
***************************************************/
#ifndef _USART_H_
#define _USART_H_
#include "../commondefs.h"
#include "../Components/uart_proxy.h"

uint8_t USART_init(Uart_Proxy* const me);
void USART_send(unsigned char data);
void USART_putstring( char * StringPtr) ;
void usart_init_raw();
uint8_t USART_get(void);
//void USART_flush(void);

#endif