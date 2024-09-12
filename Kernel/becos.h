#ifndef BECOS_H_
#define BECOS_H_

#include			 "../commondefs.h"
#include			 "../Drivers/usart.h"
#include			 "../Components/irq.h"
#include			 "../Components/uart_proxy.h"
#include			 "../Services/transceiver.h"
#include			 "../Services/uart.h"
#include			 "process.h"
#include			 "scheduler.h"

// 7816-4 trailers
#define INVALID_CLASS		0x6E00
#define INVALID_INS		0x6D00
#define ERROR_DEFAULT		0x6F00
#define OK_DEFAULT		0x9000
#define FILE_NOT_FOUND		0x6A82

// typedefs
typedef void (*Rx_IrqOn_fptr)(void);		 // Ponteiro pra funcao que atende interrupcao por Rx
typedef void (*Rx_IrqOff_fptr)(void);
typedef uint8_t (*app_fptr)(void);		 // Ponteiro para chamada de aplicação
typedef struct					 // estrutura lista de aplicativos
{
	uint8_t		App_Name[APP_NAME_SIZE];
	app_fptr	app_function;
}InstalledApps;

// Componentes do SO
Scheduler*			osScheduler;
Transceiver*			osTransceiver;
Uart_server*			osUartServer;
Uart_Proxy*			osUartProxy;
Program*			MainProgram;


#define APDU_CLA	(*MainProgram.Parser.Apdu.CLA)
#define APDU_INS	(*MainProgram.Parser.Apdu.INS)
#define APDU_P1		(*MainProgram.Parser.Apdu.P1)
#define APDU_P2		(*MainProgram.Parser.Apdu.P2)
#define APDU_Nc		(*MainProgram.Parser.Apdu.Nc)
#define APDU_Ne		(*MainProgram.Parser.Apdu.Ne)

/************************************************************************/
/* Metodo: Get Apdu Command                                            */
/************************************************************************/
void				osGet_Apdu();

/************************************************************************/
/* Metodo: Process Apdu Command                                        */
/************************************************************************/
void				osProcess_Apdu();

/************************************************************************/
/* Process Select App  (INS=0xA4)                                       */
/************************************************************************/
uint8_t					osSelect_App();
Process*				p_Select_App;
Queue*   				q_Select_App;
Task					t_Select_App;

/************************************************************************/
/* Autenticação  (INS=0x80)			                                    */
/************************************************************************/
uint8_t					App_Auth();
Process*				p_App_Auth;
Queue*   				q_App_Auth;
Task					t_App_Auth;
extern const uint8_t			App_Auth_Name[];


/************************************************************************/
/* Synthetic application (INS=0xFB)		                                */
/************************************************************************/
uint8_t					App_Inv();
Process*				p_App_Inv;
Queue*   				q_App_Inv;
Task					t_App_Inv;
extern const uint8_t			App_Inv_Name[];


void osAdd_App(const uint8_t* app_name, size_t app_name_size, app_fptr app_func_call, uint8_t app_index)
;
void osInit_App_List()
;
void osEnableRxIRQ(void)
;
void ossDisableRxIRQ(void)
;
void osInit()
;
void osRun()
;
#endif /* BECOS_H_ */