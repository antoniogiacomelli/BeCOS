/************************************************************************/
/* @file app_auth.c														*/
/* @brief Executa instrução 0x80. Criptografa dados recebidos           */
/*        com mecanismo DES e retorna ao leitor.						*/
/************************************************************************/
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
#include	 "des.h" // biblioteca criptográfica de terceiros

const uint8_t key[8] = {0xB0, 0x50, 0x15, 0xD3, 0x4D, 0x0E, 0xF3, 0xD3};
/* em um sistema comercial esta chave seria derivada a partir de uma chave
   armazenada em local protegido da memória
  */

uint8_t App_Auth()
{
	const uint8_t challenge_size = MainProgram->Parser->Apdu.Nc;
	uint8_t challenge[challenge_size];
	uint8_t cypher[challenge_size];
	uint8_t msg_index = 0;
	//consome mensagem a ser criptografada
	for (msg_index=0; msg_index<(MainProgram->Parser->Apdu.Nc); msg_index++)
	{
		challenge[msg_index]=Queue_GetMsg(p_App_Auth, msg_index);	
	}
	des_enc(cypher, challenge, key); // criptografa
	// coloca resposta no buffer do programa principal
	Program_Set_Response(MainProgram, cypher, 8, 0x9000); 
	// executa transmissao
	Transceiver_SendFrame(osTransceiver, MainProgram, 8);
	return 0;
}


