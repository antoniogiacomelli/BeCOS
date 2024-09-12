/*************************************************

@file spi.c
@brief Controladora do SPI 
@brief Target: AVR Atmega328p

**************************************************/
#include "spi.h"

void SPI_MasterInit(void)
{
	/* Configura direção dos pinos */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<PORTB2);
	/* Habilita SPI no modo master fck/16, modo 1 */
	SPCR |= (0<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPHA);
	PORTB |= (1<<PORTB2);
}

void SPI_SlaveInit(void)
{
	DDR_SPI |= (1<<DD_MISO);
	DDR_SPI &= ~(1<<PORTB2);
	//habilita
	SPCR |= (1<<SPE);
	PORTB &= ~(1<<PORTB2);
}
//slave select alto
void SPI_ss_high()
{
	PORTB |= (1<<PORTB2);
	_delay_us(1);
}
//slave select baixo
void SPI_ss_low()
{
	PORTB &= ~(1<<PORTB2);
	_delay_us(1);
}
// transmite e recebe
unsigned char SPI_MasterTransmit(unsigned char cData)
{
	//SPI_ss_low();
	_delay_us(1);
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));
	//SPI_ss_high();
	return SPDR;
}
unsigned char SPI_SlaveReceive(unsigned char cData)
{
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}
