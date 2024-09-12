#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "../commondefs.h"
#include "process.h"
typedef struct
{
	Process *proc_queue[N_TASK];
	uint8_t index;
} Scheduler;

//prototipos de funcoes
Scheduler* Sch_Ctor(void);
//(private) void Sch_Init(Scheduler* me);
uint8_t Sch_Dctor(Scheduler* const me);
uint8_t Sch_AddProc(Scheduler *me, Process *proc_ptr);
void Sch_Run(Scheduler* me);

#endif