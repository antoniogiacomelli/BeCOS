/************************************************************************/
/* @file becos.c                                                        */
/* @brief Implementação do sistema operacional 'BeCOS'                  */
/************************************************************************/

#include	 "../commondefs.h"
#include	 "../Drivers/usart.h"
#include	 "../Components/irq.h"
#include	 "../Components/uart_proxy.h"
#include	 "../Services/transceiver.h"
#include	 "../Services/uart.h"
#include     "../Apps/application.h"
#include	 "process.h"
#include	 "scheduler.h"
#include	 "becos.h"

#define APDU_DATA(x) (Message*)&MainProgram->Parser->Apdu.Data[x]

#define __DEBUG__
/************************************************************************/
/* Inicialização								                        */
/************************************************************************/

/* Ponteiro para função de interrupção por Rx							*/
/************************************************************************/
Rx_IrqOn_fptr  RxIrqOn;
Rx_IrqOn_fptr  RxIrqOff;

/************************************************************************/
/* Applets disponiveis                                                  */
/************************************************************************/
InstalledApps COSApps[N_APPS];
uint8_t SelectedApp_index;
const uint8_t App_Inv_Name[]  = {0xB0, 0x50, 0xF3, 0xD3};  // nome
#define	 APP_INV_INDEX  0 								   // indice
const uint8_t App_Auth_Name[] = {0xB0, 0x50, 0xFE, 0xDE};  // nome
#define  APP_AUTH_INDEX 1								   // indice na lista de applets

/**
 * \brief				Adiciona aplicativo a lista COSApps
 * 
 * \param app_name		Código do aplicativo. Máximo de APP_NAME_SIZE bytes
 * \param app_name_size Número de bytes do código do aplicativo.
 * \param app_func_call Função de chamada do aplicativo.
 * \param app_index		Índice do aplicativo na lista de apps instalados.
 * 
 * \return void
 */
void osAdd_App(const uint8_t* app_name, size_t app_name_size, app_fptr app_func_call, uint8_t app_index)
{
	uint8_t i;
	for (i=0; i<app_name_size; i++)
	{
		COSApps[app_index].App_Name[i] = app_name[i];
	}
	
	COSApps[app_index].app_function = app_func_call;
}

/**
 * \brief Inicializa a lista de aplicativos e cria um 
 *		  processo para o mesmo.
 * 
 * \return void
 */
void osInit_App_List()
{
	osAdd_App(App_Inv_Name,  4,  App_Inv,  APP_INV_INDEX);
	osAdd_App(App_Auth_Name, 4, App_Auth, APP_AUTH_INDEX);
	t_App_Auth   = App_Auth;
	p_App_Auth   = Proc_Ctor(t_App_Auth);
	t_App_Inv	 = App_Inv;
	p_App_Inv    = Proc_Ctor(t_App_Inv);
}

/**
 * \brief Constrói e inicializa todos os objetos e inicializa variáveis de dado e controle.
 *
 * \return void
 */
void osInit()
{
	norb			=   0;
	TxMode			=   false;
	osScheduler		=	Sch_Ctor();
	osUartServer	=	Uart_server_Ctor(osUartServer,_38400_, ONE);
	osUartProxy		=	Uart_Proxy_Ctor(osUartProxy, osUartServer);
	osTransceiver	=	(Uart_server*)Transceiver_Ctor(osTransceiver);
	MainProgram		=	Program_Ctor(MainProgram, (unsigned char*)"MainProgram");	
	RxIrqOn			=   &RXUart_IRQ_on;
	RxIrqOff	    =   &RXUart_IRQ_off;
	// Construção dos processos
	t_Select_App	=	osSelect_App;
	p_Select_App	=	Proc_Ctor(t_Select_App);
	osInit_App_List();
	RXUart_IRQ_on();
}

/**
 * \brief  Habilita interrupção após recebepção de 1 byte;
 *		   Utiliza ponteiro para função definido conforme
 *		   a interface (UART, SPI, etc.)
 * \return void
 */
void osEnableRxIRQ(void)
{
	(RxIrqOn)();
}

/**
 * \brief  Desabilita interrupção de Rx.
 *
 * \return void
 */
void osDisableRxIRQ(void)
{
	(RxIrqOff)();
}
/**
 * \brief	Recebe comando e armazena no buffer do programa principal
 * 
 * \return void
 */
void osGet_Apdu()
{
	Transceiver_GetFrame(osTransceiver, SHARED_BUFFER_SIZE);
	Program_Get_Apdu(osTransceiver, MainProgram);
    osProcess_Apdu();
};

/**
 * \brief  Processa o comando e armazena resposta no buffer do
 *		   programa principal.
 * 
 * \return void
 */
void osProcess_Apdu()       /* processamento de comando simplificado
							para atender à validação de conceito	 
							parâmetros como P1 e P2 não sao avaliados, por ex.
							uma extensao para atender à norma ISO7816-4
							de forma mais completa manteria o mesmo
							padrão de design.*/
{
	uint8_t msg_index=0;
	switch(APDU_CLA) // Classe	
	{
		case 0x00:
			break;		 // ok, classe interindustrial suportada, segue adiante
		default:		 // nenhuma outra classe suportada
			Program_Set_Response(MainProgram, NULL, 0, INVALID_CLASS);
			Transceiver_SendFrame(osTransceiver, MainProgram, 0);
			break;
	}
	switch(APDU_INS) // Instrução
	{
		// instrucoes suportadas
		case 0xA4: // select app
			msg_index=0;
			for (msg_index=0; msg_index<APDU_Nc; msg_index++)	
			{
				Queue_AddMsg(p_Select_App, msg_index, APDU_DATA(msg_index));
			}
			osSelect_App();
			break;
		case 0x80: 	
			msg_index=0;
			for(msg_index=0; msg_index<APDU_Nc; msg_index++)
			{
				Queue_AddMsg(p_App_Auth, 0, APDU_DATA(msg_index));
			}
			Sch_AddProc(osScheduler, p_App_Auth);
		    break;
		case 0xFB:
			msg_index=0;
			for(msg_index=0; msg_index<APDU_Nc; msg_index++)
			{
				Queue_AddMsg(p_App_Inv, 0,  APDU_DATA(msg_index));
			}
			Sch_AddProc(osScheduler, p_App_Inv);
			break;
		default:
			Program_Set_Response(MainProgram, NULL, 0, INVALID_INS);
			Transceiver_SendFrame(osTransceiver, MainProgram, 0);
			break;
	}
}

/**
 * \brief Executa instrução '0xA4' da norma ISO7816-4.
 *		  Como não há sistema de arquivos neste protótipo	
 *		  a única interpretação possível é a de seleção de
 *		  aplicativo.
 *
 * \return SUCCESS ou FAIL
 */
uint8_t osSelect_App() 
{
	uint8_t i;
	uint8_t this_exit_code;
	Message thisMessage[MESSAGE_SIZE];
	for (i=0; i<(MainProgram->Parser->Apdu.Nc); i++)
	{
		thisMessage[i]=Queue_GetMsg(p_Select_App, i);
	}

	//varre lista de aplicativos instalados
	for (i=0; i<N_APPS; i++)
	{
		if (memcmp(thisMessage, &COSApps[i].App_Name, MainProgram->Parser->Apdu.Nc) == 0)
		{
			SelectedApp_index = i;
			this_exit_code = SUCCESS; // encontrou aplicativo selecionado
			break;
		}
	} 
	if (this_exit_code == SUCCESS)
	{
		Program_Set_Response(MainProgram, NULL, 0, OK_DEFAULT);
	}
	else
	{
		Program_Set_Response(MainProgram, NULL, 0, FILE_NOT_FOUND); // nao encontrou aplicativo selecionado	
	}
	Transceiver_SendFrame(osTransceiver, MainProgram, 0); // para A4 responde somente o trailer
	return this_exit_code;
}
