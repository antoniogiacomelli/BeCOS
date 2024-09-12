/***************************************************
@file	process.c
@brief	Implementação dos Processos e IPC
		Superclass Queue
		Subclass   Process 
***************************************************/

#include "process.h"

/**********************************************
Queue Methods
***********************************************/

/******
\brief   Inicializador da fila de mensagens para IPC
\param	 me ponteiro para endereço constante que armazena 
		 algum valor Queue
\return  nao retorna valor
***************************************************************/
static void Queue_Init(Queue* const me) //private
{
	uint8_t i=0;
	for (i=0; i<MESSAGE_SIZE; i++)
	{
		me->message[i] = 0x00;
	}
}
/******
\brief   Construtor da fila de mensagens
\brief	 Ponteiro para Queue a ser alocada na memória
\return  Ponteiro para o Queue se sucesso ou ponteiro
         para NULL se falhar
****************************************************/
Queue* Queue_Ctor(Queue* me)
{
	me = (Queue *) malloc(sizeof(Queue));
	if (me != NULL)
	{
		Queue_Init(me);
		return me;
	}
	return me;
}

/******
\brief   Construtor da fila de mensagens
\brief	 Ponteiro para Queue a ser desalocada na memória
\return  não retorna valor
****************************************************/
void Queue_Dctor(Queue* const me)
{
	if (me != NULL)
	{
		free((void *) me);
		return;
	}
	return;
}

/******
\brief	Adiciona uma mensagem na fila
\param	*process Ponteiro para o processo
\param	m_index Indice da mensagem.
\param	*in_message Ponteiro para a mensagem;
\return	0 se bem sucedido; não-zero se mal sucedido
****************************************************/
uint8_t Queue_AddMsg(Process *process, uint8_t m_index, Message *in_message)
{
	if (m_index < MESSAGE_SIZE)
	{
		process->Msg_Queue->message[m_index] = *in_message;
		return SUCCESS;
	}
		return FAIL;
}
/******
\brief  Lê uma mensagem da fila
\param  me ponteiro para a fila
\param  q_index  indice da mensagem
\return 0 se bem sucedido; não-zero se mal sucedido
****************************************************/
uint8_t Queue_GetMsg(Process* process, uint8_t m_index)
{
	if (m_index <= MESSAGE_SIZE)
	{
		return process->Msg_Queue->message[m_index];
	}
	else
	{
		return FAIL;
	}
}
/*****************************************
Subclass Process methods
******************************************/
/******
/brief  Construtor de um processo
/param  Endereço da função a ser processada
/return Ponteiro para o processo
*********************************************/
Process* Proc_Ctor(Task p_task)
{
	Process*  me = (Process *) malloc(sizeof(Process));
	if (me != NULL) 
	{
		//controi e inicializa superclass
		Queue*    msg_queue = Queue_Ctor((Queue *) &me->Msg_Queue); //upclass 
		// inicializa subclass
		me->function=p_task;
		me->Msg_Queue=msg_queue;
	}
	return me;
}
/******
/brief  Desconstrutor de um processo
/param  Endereço da função a ser processada
/return Não retorna valor
*********************************************/
void Proc_Dctor(Process* const me)
{
	if (me != NULL)
	{
		free(me);
	}
}