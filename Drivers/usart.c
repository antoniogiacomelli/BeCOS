/***************************************************
@file	usart.c
@brief	Driver para UART/USART
		Target: Atmega328p 
***************************************************/
#include "../commondefs.h"
#include "../Drivers/usart.h"
#include "../Components/uart_proxy.h"

//inicializa dispositivo a 38400bps
void uart_38400(void)
{
	#undef BAUD  
	#define BAUD 38400
	#include <util/setbaud.h>
	UBRR0H = 0x00;
	UBRR0L = 0x19; 
	#if USE_2X
	UCSR0A |= (1 << U2X0); 
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
}

//inicializa dispositivo a 9600bps
void uart_9600(void)
{
	#undef BAUD
	#define BAUD 9600
	#include <util/setbaud.h>
	UBRR0H = 0x00;
	UBRR0L = 0x33;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
}
uint8_t USART_init(Uart_Proxy* const me) 
{
	
	if (me->uart_server->baudrate == _9600_)
	{
		uart_9600();
	}
	else if (me->uart_server->baudrate == _38400_)
	{
   		uart_38400();
	}
	else
	{
		return FAIL; // configuração ainda nao suportada pela proxy
	}
	UCSR0A &= (0<<UDRE0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	if (me->uart_server->stopbits == ONE)
	{
		UCSR0C = (0<<USBS0)|(3<<UCSZ00);
		return SUCCESS;
	}
	else if (me->uart_server->stopbits == TWO)
	{
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);
		return SUCCESS;
	}
	else
	{
		return FAIL; // configuração ainda nao suportada pela proxy
	}
}

void usart_init_raw()
{
	uart_38400();
	UCSR0A &= (0<<UDRE0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART_send(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void USART_putstring(char * StringPtr) 
{
	while (*StringPtr != 0x00) 
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
}

uint8_t USART_get(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;	
}
/*
void USART_flush()
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) )
	{
		dummy = UDR0;
	}
}*/