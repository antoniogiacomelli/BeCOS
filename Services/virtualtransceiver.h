/************************************************************************/
/* @file	virtualtransceiver.h                                        */
/* @brief	Classe Abstrata que oferece interface de funçoes virtuais   */
/************************************************************************/

#ifndef _VIRTUALTRANSCEIVER_H_
#define _VIRTUALTRANSCEIVER_H_
#include "../commondefs.h"

struct VirtualTransceiverVtbl; //declaração adiantada

// Classe Abstrata
typedef struct 
{
	struct VirtualTransceiverVtbl const *vptr; // ponteiro para tabela de funcoes virtuais
	uint8_t type;
}VirtualTransceiver;

// Tabela virtual de funções //
struct VirtualTransceiverVtbl
{
	void (*getframe)(VirtualTransceiver const * const me, size_t length);
	void (*sendframe)(VirtualTransceiver const * const me,  uint8_t *response, size_t length);
};

// Interface do transceiver //
VirtualTransceiver* VirtualTransceiver_Ctor(VirtualTransceiver* me);
VirtualTransceiver* VirtualTransceiver_Dctor(VirtualTransceiver* const me);

// Funções com chamada virtual (late binding) //
static inline void VirtualTransceiver_GetFrame(VirtualTransceiver const * const me, size_t length)
{
	(*me->vptr->getframe)(me, length);
}

static inline void VirtualTransceiver_SendFrame(VirtualTransceiver const * const me,  uint8_t *response, size_t length)
{
	(*me->vptr->sendframe)(me, response, length);
}

#endif //_VIRTUALTRANSCEIVER_H_