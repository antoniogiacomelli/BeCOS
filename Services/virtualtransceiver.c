/************************************************************************/
/* @file	virtualtransceiver.c                                        */
/* @brief	Implementação dos metodos da classe VirtualTransceiver      */
/************************************************************************/
#include "../commondefs.h"
#include "../Apps/application.h"
#include "virtualtransceiver.h"
#include <assert.h>

// funcoes dummy privadas
static void VirtualTransceiver_GetFrame_(VirtualTransceiver const * const me, size_t length)
{
	assert(0); //erro se chamada
}
static void VirtualTransceiver_SendFrame_(VirtualTransceiver const * const me, uint8_t* response, size_t length)
{
	assert(0); //erro se chamada
}

static const uint8_t type_ = 0xFF;

/******
\brief	Construtor e inicializador 
\param	me ponteiro VirtualTransceiver
\return ponteiro para virtual transceiver se ok, NULL se falhar
***************************************************************/
VirtualTransceiver* VirtualTransceiver_Ctor(VirtualTransceiver* me)
	uint8_t i=0;
	me = (VirtualTransceiver*) malloc(sizeof(VirtualTransceiver));
	if (me != NULL)
	{
		//inicializa (static limit o escopo, const garante somente leitura)
		static struct VirtualTransceiverVtbl const vtbl =
		{
			&VirtualTransceiver_GetFrame_,
			&VirtualTransceiver_SendFrame_	
		};
		me->vptr=&vtbl; // inicializei com a vtble de funções dummy
	}
	return me; //retorna ponteiro para virtualtransceiver
}
/******
\brief	Desconstrutor
\param	me ponteiro VirtualTransceiver
\return não retorna valor
***************************************************************/
void Tcv_Dctor(VirtualTransceiver const* me)
{
	if (me!= NULL)
	{
		free((void*) me);
	}
}