#ifndef _SPI_H_
#define _SPI_H_

#define DDR_SPI DDRB
#define DD_MOSI PORTB3
#define DD_SCK PORTB5
#define DD_MISO PORTB4
#include "../commondefs.h"
#include <util/delay.h>

void SPI_MasterInit(void);
void SPI_ss_high();
void SPI_ss_low();
unsigned char SPI_MasterTransmit(unsigned char cData);
void SPI_slave_init();
#endif