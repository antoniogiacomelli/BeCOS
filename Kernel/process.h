/***************************************************
@file	process.h
@brief	Header dos Processos e IPC
		Superclass Queue
		Subclass   Process 
***************************************************/
#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "../commondefs.h"
typedef uint8_t (*Task)();
typedef uint8_t Message;

typedef struct {
	Message message[MESSAGE_SIZE];
} Queue;

typedef struct
{
    Queue *Msg_Queue; // Superclass
	Task function;
}Process;

/*superclass' prototypes*/
//(private) static void Queue_Init(Queue* const me); 
Queue*	     Queue_Ctor(Queue*  me);
void		 Queue_Dctor(Queue* const me);
uint8_t		 Queue_AddMsg(Process *process, uint8_t m_index, Message *in_message);
uint8_t		 Queue_GetMsg(Process* process, uint8_t m_index);

/*subclass' prototypes*/
Process* Proc_Ctor(Task p_task);
void Proc_Dctor(Process* const me);

#endif //_PROCESS_H_