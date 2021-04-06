/*
 * main.c
 *
 * Created: 3/10/2021 12:52:47 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}


// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100001;
	ADCSRA = 0b10000110;
}


// Main program: Counting on T1
int main( void )
{
	DDRF = 0x00;
	DDRA = 0xFF;
	adcInit();

	while (1)
	{
		ADCSRA |= BIT(6);
		while ( ADCSRA & BIT(6) );
		PORTA = ADCH;
		wait(500);
	}
}
