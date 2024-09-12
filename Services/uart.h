#ifndef _UART_H_
#define _UART_H_
#include "../commondefs.h"

typedef enum
{
	_9600_,
	_38400_
} brate;

typedef enum
{
	ONE,
	TWO
} sbits;

typedef struct
{
	uint8_t		type;
	brate		baudrate;
	sbits		stopbits;
} Uart_server;
// API
Uart_server* Uart_server_Ctor(Uart_server* me)
;
void Uart_Send(uint8_t byte)
;
void Uart_receive(uint8_t* byte)
;
void Uart_receive_string(uint8_t* buffer, size_t length)
;
void Uart_send_string(uint8_t* buffer)
;
#endif
