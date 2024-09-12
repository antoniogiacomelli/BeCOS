/************************************************************************/
/* @file	transceiver.c												*/
/* @brief	Subclasse do VirtualTransceiver                             */
/************************************************************************/
#include "../commondefs.h"
#include "uart.h"
#include "transceiver.h"
#include "../Apps/application.h"
#include "../Drivers/usart.h"
#include <assert.h>

/************************************************************************/
/* Prototipos das funcoes virtuais			                            */
/************************************************************************/
static void Transceiver_Send_(VirtualTransceiver const * const me, uint8_t* response, size_t length);
static void Transceiver_Get_(VirtualTransceiver const * const me, size_t length);

/************************************************************************/
/* Transceiver: implementacao do metodos                                */
/************************************************************************/
/******
\brief	Construtor e inicializador 
\param	me ponteiro para endereço Transceiver 
\return ponteiro para tcv_uart	
***************************************************************/
Transceiver* Transceiver_Ctor(Transceiver* me)
{
	uint8_t i;
	me=(Transceiver*) malloc(sizeof(Transceiver));
	if (me != NULL)
	{
		static struct VirtualTransceiverVtbl vtbl =
		{
			&Transceiver_Get_,
			&Transceiver_Send_
		};
		//inicializa superclasse
		VirtualTransceiver_Ctor(&me->Super);
		me->Super.vptr=&vtbl; //sobreescreve vtbl de Super
		i=0;
		for (i=0;i<SHARED_BUFFER_SIZE;i++)
		{
			me->framebuffer[i] = 0x00;
		}
	}
	return me;
}

Transceiver_Send_(VirtualTransceiver const * const me, uint8_t* response, size_t length)
{
	Transceiver * me_ =(Transceiver*) me;
}

/************************************************************************/
/* API para aplicação                                                   */
/************************************************************************/
void Transceiver_SendFrame(Transceiver* const me, Program* program, size_t length)
{
	Transceiver * me_ = (Transceiver* )me; //downcast
	uint8_t i;
	i=0;
	for (i=0;i<length;i++)
	{
		me->framebuffer[i]=program->Response->Data[i];
	}
	me->framebuffer[length]   =  (program->Response->Trailer) >> 8;
	me->framebuffer[length+1] =  ((program->Response->Trailer) << 8) >> 8;
}
void Transceiver_GetFrame(Transceiver* const me, size_t length)
{
	 Transceiver  * me_ = (Transceiver* )me;
	 Transceiver_Get_(&me_->Super, length);
}