/***************************************************
@file	uart_proxy.c
@brief	Componente do BSP que conecta o serviço ao
		driver da Uart.
***************************************************/
#include "../Drivers/usart.h"
#include "uart_proxy.h"
#include "../Apps/printascii.h"
/**********************************************
Metodos Uart_Proxy 
***********************************************/
/******
\brief	Construtor e inicializador 
\param	me ponteiro para endereço da Proxy
\param	server ponteiro para serviço Uart
		(0=Transceiver contato, 1=Transceiver sem contato)		
\return ponteiro para proxy se ok, NULL se falhar
***************************************************************/
Uart_Proxy* Uart_Proxy_Ctor(Uart_Proxy* me, Uart_server* server)
{
	me = (Uart_Proxy*) malloc(sizeof(Uart_Proxy));
	if (me != NULL)
	{
		me->uart_server=server;
		Uart_Proxy_Init(me);
	}	
	return me;
}

/******
\brief	Desconstrutor 
\param	me ponteiro para endereço da proxy
\return	nao retorna valor
***************************************************************/
void Uart_Proxy_Dctor(Uart_Proxy* me)
{
	if (me != NULL)
	{
		free((void *) me);
	}
}

/******
\brief	Inicializa o hardware
\param	me ponteiro para endereço da Proxy
\return	SUCCESS ou FAIL
************************************************************ ***/
uint8_t Uart_Proxy_Init(Uart_Proxy* const me)
{
	uint8_t r;	
	r = USART_init(me); // HALL API
	return r;
}

/******
\brief	Envia byte pela Uart
\param	me ponteiro para endereço da Proxy
\return	Não retorna parâmetro
***************************************************************/
void Uart_Proxy_SendByte(uint8_t byte)
{
	USART_send(byte); // HALL API
}

/******
\brief	Recebe byte pela Uart
\return	byte recebido
***************************************************************/
uint8_t Uart_Proxy_ReceiveByte()
{
	unsigned char r;
	r = USART_get(); // HALL API
	return r;
}

void Uart_Proxy_PutString(uint8_t* StringPtr)
{
	 USART_putstring((char *)StringPtr);
}