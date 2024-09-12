#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../commondefs.h"

typedef struct
{
	uint8_t CLA;
	uint8_t INS;
	uint8_t P1;
	uint8_t P2;
	uint8_t Nc;
	uint8_t Data[SHARED_BUFFER_SIZE];
	uint8_t Ne;
}Apdu;

typedef struct
{
	uint8_t Data[SHARED_BUFFER_SIZE];
	uint16_t Trailer;
}Response;

//typedef enum
//{
	//CLA, INS, P1, P2, Nc, Data, Ne
//}apdu_field;


#endif