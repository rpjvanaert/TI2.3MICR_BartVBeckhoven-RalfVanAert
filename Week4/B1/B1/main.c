/*
 * main.c
 *
 * Created: 3/10/2021 12:42:57 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );	
	}
}

void adcInit( void )
{
	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcInit();

	while (1)
	{
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}