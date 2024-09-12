#include "comm.h"

// interface abstrata (declaracao adiantada)
static void Comm_Get_(Comm const * const me);
static void Comm_Send_(Comm const * const me);
static void Comm_Init_(Comm const * const me, uint8_t interface);


// construtor
Comm* Comm_Ctor(Comm * me, uint8_t interface)
{
	//tabela de funções virtuais do Comm
	static struct CommVtable const vtbl =
	{
		Comm_Get_,
		Comm_Send_,
		Comm_Init_
	};
	me = (Comm *) malloc(sizeof(Comm));
	if (me != NULL)
	{
		me->vptr = &vtbl; //atribui o ponteiro para funcoes virtuais ao endereco de vtbl
		me->interface = interface;
	}
	return me;
}

// funcoes abstratas (nunca devem ser chamadas)
static void Comm_Get_(Comm const * const me)
{
	return;
}
static void Comm_Send_(Comm const * const me)
{
	return;
}
static void Comm_Init_(Comm const * const me, uint8_t interface)
{
	return;
}
