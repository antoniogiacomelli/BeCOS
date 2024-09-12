#include	 "../commondefs.h"
#include	 "../Drivers/usart.h"
#include	 "../Components/irq.h"
#include	 "../Components/uart_proxy.h"
#include	 "../Services/transceiver.h"
#include	 "../Services/uart.h"
#include	 "../Kernel/process.h"
#include	 "../Kernel/scheduler.h"
#include     "../Kernel/becos.h"
#include	 "application.h"

uint8_t App_Inv()
{
	uint8_t message_index;
	uint8_t this_message[MESSAGE_SIZE];
	message_index=0;
	for (message_index=0; message_index<(MainProgram->Parser->Apdu.Nc); message_index++)
	{
		this_message[message_index] = Queue_GetMsg(p_App_Inv, message_index);
	}
	for (message_index=0; message_index<(MainProgram->Parser->Apdu.Nc); message_index++)
	{
		this_message[message_index] = ~(this_message[message_index]);
	}
	Program_Set_Response(MainProgram, this_message, (size_t) MainProgram->Parser->Apdu.Nc, OK_DEFAULT);
	Transceiver_SendFrame(osTransceiver, MainProgram, (size_t) MainProgram->Parser->Apdu.Ne);
	return 0;
}