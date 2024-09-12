#ifndef IRQ_H_
#define IRQ_H_
// Interface fortemente hardware-dependent
//desliga Watchdog timer
void WDT_off(void)
;
// habilita IRQ quando byte é recebido
void RXUart_IRQ_on(void)
;
void RXUart_IRQ_off(void)
;
// habilita IRQ no pino 2, borda de subida
void INT0_IRQ_on(void)
;
void INT0_IRQ_off(void)
;
// habilita interrupcao SPI 
void SPI_IRQ_on()
;

#endif /* IRQ_H_ */