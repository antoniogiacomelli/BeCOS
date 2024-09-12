// Interface fortemente hardware-dependente
#include "../commondefs.h"
#include "irq.h"
#include <stdio.h>

//desliga Watchdog timer
void WDT_off(void)
{
	cli();
	wdt_reset();
	MCUSR &= ~(1<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	WDTCSR = 0x00;
	sei();
}
// habilita IRQ quando byte é recebido
void RXUart_IRQ_on(void)
{
	cli();
	UCSR0B |= (1<<RXCIE0); // interrupcao ao receber byte
	//led laranja
	DDRB |= (1<<DDB5);
	sei();
}
void RXUart_IRQ_off(void)
{
	cli();
	UCSR0B &= ~(1<<RXCIE0); // interrupcao ao receber byte
	sei();
}
// habilita IRQ no pino 2, borda de subida
void INT0_IRQ_on(void)
{
	cli();
	DDRD &= (0<<DDD2);
	EICRA &= (1 << ISC00) | (1 << ISC01); // re interrupt
	EIMSK |= (1 << INT0);
	MCUCR &= (0 << PUD);
	PORTD |= (1<<PORTD2);
	sei();
}
void INT0_IRQ_off(void)
{
	cli();
	EIMSK &= ~(1 << INT0);
	sei();
}
// habilita interrupcao SPI
void SPI_IRQ_on()
{
	SPCR |= (1<<SPIE);
}