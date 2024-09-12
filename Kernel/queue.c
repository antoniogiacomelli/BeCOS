#include "process.h"
#include "../commondefs.h"
/*
\brief   Construtor da fila de mensagens para IPC
\return  ponteiro para fila de processos
*/
static void Queue_Init(Queue* const me) //private
{
	unsigned char i=0;
	unsigned char j=0;
	for (i=0; i<MESSAGE_SIZE; i++)
	{
		me->message[i] = 0x00;
	}
}

Queue* Queue_Ctor(void)
{
	Queue* me = (Queue *) malloc(sizeof(Queue)*N_TASK);
	if (me != NULL)
	{
		Queue_Init(me);
		return me;
	}
	return me;
}

void Queue_Dctor(Queue* const me)
{
	if (me != NULL)
	{
		free((void *) me);
		return;
	}
	return;
}

/*
\brief  Adiciona uma mensagem na fila
\param	*process Ponteiro para o processo
\param	m_index Indice da mensagem.
\param *in_message Ponteiro para a mensagem;
\return 0 se bem sucedido; não-zero se mal sucedido
*/
unsigned char Queue_AddMsg(Process *process, unsigned char m_index, Message *in_message)
{
	unsigned char q_index;
    if ((q_index) < N_TASK) { // há espaço
	{
		if (m_index < MESSAGE_SIZE)
		{
			process->Msg_Queue[q_index].message[m_index] = *in_message;
			return SUCCESS;
		}
	}
	return FAIL;
}

/*
\brief  Lê uma mensagem da fila
\param  me ponteiro para a fila
\param  q_index  indice da mensagem
\param  temp_buffer ponteiro para objeto Message onde mensagem sera descarregada
\return 0 se bem sucedido; não-zero se mal sucedido
*/

unsigned char Queue_GetMsg(Process* process, unsigned char m_index, Message *temp_buffer)
{
	if (m_index <= MESSAGE_SIZE)
	{
		temp_buffer[m_index] = process->Msg_Queue[m_index];
		return SUCCESS;
	}
	return FAIL;
}