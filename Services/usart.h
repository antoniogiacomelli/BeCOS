/*******************************
Uart Services
*******************************/
#include "../commondefs.h"
#include "../Components/uart_proxy.h"

typedef struct  
{
	brate_enum baudrate;
	sbits_enum sbits;
	
}Uart_server;


// Construtor
Uart_server* Uart_server_Ctor(Uart_server* me, brate_enum baudrate, sbits_enum sbits)
{
	me = (Uart_server*) malloc(sizeof(Uart_server));
	if (me != NULL)
	{ // inicializa
		me->baudrate=baudrate;
		me->sbits=sbits;
	}
	return me;
}

// Transmite 
void Uart_server_send(Uart_Proxy* const proxy, uint8_t bytedata)
{
	Uart_Proxy_SendByte(proxy, bytedata);	
}

// Recebe
uint8_t Uart_server_receive(Uart_Proxy* const proxy)
{
	uint8_t r;
	r=Uart_Proxy_ReceiveByte(proxy);
	return r;
}