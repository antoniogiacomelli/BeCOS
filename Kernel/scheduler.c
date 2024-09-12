#include "../commondefs.h"
#include "scheduler.h"
#include "process.h"
static inline void Sch_Init(Scheduler* const me)
{
	me->index=0;
}
/*
\brief   Construtor da fila de processos
\return  ponteiro para a fila de processos
*/
Scheduler* Sch_Ctor(void)
{
	Scheduler* const me = malloc(sizeof(Scheduler));
	if (me != NULL)
	{
		Sch_Init(me);
	}
	return me;
}
/*
\brief   Desconstrutor da fila de processos
\return  Esta função nao retorna
*/
uint8_t Sch_Dctor(Scheduler* const me)
{
	if (me != NULL)
	{
		free(me);
		return SUCCESS;
	}
	return FAIL;
}
/*
\brief  Esta função adiciona um processo na fila
\param  proc_ptr ponteiro para um processo
\param  me  ponteiro para a fila de processos
\return zero se ok, não-zero se falhar
*/
uint8_t Sch_AddProc(Scheduler *me, Process *proc_ptr)
{
	uint8_t index;
	if (proc_ptr != NULL)
	{
		index = me->index;
		if (index < N_TASK)  // não está cheio 
		{
			me->proc_queue[index] = proc_ptr;
			me->index++;
			return SUCCESS;
		}
		else if (index == N_TASK) // sobrescreve
		{
			me->index=0;
			me->proc_queue[index] = proc_ptr;
			me->index++;
			return SUCCESS;
		}
	}
	return FAIL;
}
/*
\brief  Laço de execução.
\return Nao retorna parametro
*/
void Sch_Run(Scheduler* me)
{
	uint8_t i;
	i=0;
	for (i=0; i<(me->index); i++)
	{
		me->proc_queue[i]->function(); //executa
	}
}
