/************************************************
@file	servers/uart.c
@brief	Servidor UART para camada de aplicação
************************************************/
#include "../commondefs.h"
#include "../Components/uart_proxy.h"

/*funções privadas do servidor*/
static inline void  Uart_server_init(Uart_server* const me, brate baudrate, sbits stopbits);
static inline void	Uart_server_Send(uint8_t data);
static inline void	Uart_server_Receive(uint8_t *data);
static inline void	Uart_server_SendString(uint8_t* data);
static inline void  Uart_server_ReceiveString(uint8_t* receive_buffer, size_t length);

Uart_server* Uart_server_Ctor(Uart_server* me, brate baudrate, sbits stopbits)
{
	me = (Uart_server*) malloc(sizeof(Uart_server));
	if (me != NULL)
	{	
			Uart_server_init(me, baudrate, stopbits);
			return me;
	}
	return me;
}

// funções privadas //
static inline void  Uart_server_init(Uart_server* const me, brate baudrate, sbits stopbits)
{
	me->baudrate=baudrate;
	me->stopbits=stopbits;
	
}
static inline void	Uart_server_Send(uint8_t data)
{
	Uart_Proxy_SendByte(data);
}

static inline void Uart_server_Receive(uint8_t* data)
{
	*data = Uart_Proxy_ReceiveByte();
}

static void Uart_server_SendString(uint8_t* data)
{
	Uart_Proxy_PutString(data);
}
static inline void Uart_server_ReceiveString(uint8_t* receive_buffer, size_t length)
{
	uint8_t i = 0;
	receive_buffer = (uint8_t*) malloc(sizeof(uint8_t)*length);
	for (i=0; i<length; i++)
	{
		while (receive_buffer[i] != '\0')
		{
			receive_buffer[i] = Uart_Proxy_ReceiveByte();	
		}
	}
}
// API para a aplicação
void Uart_Send(uint8_t byte)
{
	Uart_server_Send(byte);
}

void Uart_receive(uint8_t *byte)
{
	Uart_server_Receive(byte);
}

void Uart_receive_string(uint8_t* buffer, size_t length)
{
	Uart_server_ReceiveString(buffer, length);
}

void Uart_send_string(uint8_t* buffer)
{
	Uart_server_SendString(buffer);
}