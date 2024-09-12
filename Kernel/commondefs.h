
#ifndef _COMMONDEFS_H_
#define _COMMONDEFS_H_
/* parametros do escalonador */
#define _N_TASK 4  /* numero de tarefas a serem escalonadas */
#define _MESSAGE_SIZE 4 /* tamanho da mensagem (em bytes) */
#define _QUEUE_SIZE 4

/* códigos de retorno */

#define _SUCCESS 0
#define _FAIL 1

/* Application defines
*************************/
#define FAIL	     _FAIL
#define SUCCESS	     _SUCCESS
#define MESSAGE_SIZE _MESSAGE_SIZE
#define N_TASK		 _N_TASK+1
#define QUEUE_SIZE   N_TASK

#endif