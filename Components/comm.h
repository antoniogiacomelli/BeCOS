#ifndef _TRANSCEIVER_H_
#define _TRANSCEIVER_H_
#include "../commondefs.h"

struct CommVtable;  // tabela de funcoes virtuais 

typedef struct  
{
	struct CommVtable const *vptr; //ponteiro para tabela de funções virtuais
	uint8_t interface;  // 0=contact, nao-zero=contactless
}Comm;

//tabela de ponteiros para funções
struct CommVtable
{
	void (*get)(Comm const * const me); //assinatura é um ponteiro constante com valor constante
	void (*send)(Comm const * const me);
	void (*init)(Comm const * const me, uint8_t interface);
};

// métodos nao virtuais
Comm* Comm_Ctor(Comm* const me, uint8_t interface);
void Comm_Dctor(Comm* const me);

// interface para polimorfismo
static inline void Comm_Get(Comm const * const me)
{
	return (*me->vptr->get)(me);
} 
static inline void Comm_Send(Comm const * const me)
{
	return (*me->vptr->send)(me);
}
static inline void Comm_Init(Comm const * const me, uint8_t interface)
{
	return (*me->vptr->init)(me, interface);
}

#endif /* _TRANSCEIVER_H_ */