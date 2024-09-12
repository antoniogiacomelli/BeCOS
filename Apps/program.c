#include "../commondefs.h"
#include "../Services/transceiver.h"

Program* Program_Ctor(Program* me, const uint8_t* App_Name)
{
	uint8_t i = 0;
	me = (Program *) malloc(sizeof(Program));
	if (me != NULL)
	{
		me->Parser = (Parser *) malloc(sizeof(Parser));
		if (me->Parser != NULL)
		{
			me->Parser->Apdu.CLA=0x00;
			me->Parser->Apdu.INS=0x00;
			me->Parser->Apdu.P1=0x00;
			me->Parser->Apdu.P2=0x00;
			me->Parser->Apdu.Nc=0x00;
			for (i=0;i<SHARED_BUFFER_SIZE;i++)
			{
				me->Parser->Apdu.Data[i]=0x00;
			}
			me->Parser->Apdu.Ne=0x00;
		}
		me->Response = (Response *) malloc(sizeof(Response));
		if (me->Response != NULL)
		{
			i=0;
			for (i=0;i<SHARED_BUFFER_SIZE;i++)
			{
				me->Response->Data[i] = 0x00;
			}
			me->Response->Trailer=0x0000;
		}
		i=0;
		for (i=0;i<APP_NAME_SIZE;i++)
		{
			me->App_Name[i]=App_Name[i];
		}
	}
	return me;
}

void Program_Get_Apdu(Transceiver* const transceiver, Program* const me)
{
	uint8_t i = 0;
	uint8_t Nc;
	me->Parser->Apdu.CLA = transceiver->framebuffer[0];
	me->Parser->Apdu.INS = transceiver->framebuffer[1];
	me->Parser->Apdu.P1  = transceiver->framebuffer[2];
	me->Parser->Apdu.P2  = transceiver->framebuffer[3];
	me->Parser->Apdu.Nc  = transceiver->framebuffer[4];
	Nc =transceiver->framebuffer[4];
	for (i=0; i<Nc; i++)
	{
		me->Parser->Apdu.Data[i] = transceiver->framebuffer[i+5];
	}
	me->Parser->Apdu.Ne  = transceiver->framebuffer[Nc+5];
}

void Program_Set_Response(Program* const me, uint8_t* response, size_t length, uint16_t trailer)
{
	uint8_t i;
	i=0;
	for (i=0;i<length;i++)
	{
		me->Response->Data[i]=response[i];
	}
		me->Response->Trailer=trailer;

}