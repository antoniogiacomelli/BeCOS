/************************************************************************/
/* @file  transceiver.h													*/
/* @brief Subclasse da classe abstrata VirtualTransceiver               */
/************************************************************************/
#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_
#include "../commondefs.h"
#include "../Apps/application.h"
#include "virtualtransceiver.h"
/* VirtualTransceiver SubClass */
typedef struct
{
	VirtualTransceiver Super; // Superclasse
	uint8_t type;
	uint8_t framebuffer[SHARED_BUFFER_SIZE];   // framebuffer

}Transceiver;

typedef struct
{
	Apdu Apdu;
}Parser;

typedef struct
{
	Parser*   Parser;
	Response* Response;
	uint8_t   App_Name[APP_NAME_SIZE];
}Program;

/* Interface */
Transceiver* Transceiver_Ctor(Transceiver* me, uint8_t type);
Transceiver* Transceiver_Dctor(Transceiver* const me);
void		 Transceiver_SendFrame(Transceiver* const me, Program* program, size_t length);
void		 Transceiver_GetFrame(Transceiver* const me, size_t length);

Program*	 Program_Ctor(Program* me, const uint8_t* App_Name);
void		 Program_Get_Apdu(Transceiver* const transceiver, Program* const me);
void		 Program_Set_Response(Program* const me, uint8_t* response, size_t length, uint16_t trailer);
void		 Program_Exit();

#endif /* TRANSCEIVER_UART_H_ */