/*
 * main.c
 *
 * Created: 3/10/2021 12:52:47 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "micr_lcd.c"

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
	
	init();
	
	wait(250);

	while (1)
	{
		lcd_clear();
		ADCSRA |= BIT(6);
		while ( ADCSRA & BIT(6) );
		PORTA = ADCH;
		char tempString[8];
		sprintf(tempString, "measure {%i}", ADCH * 2);
		
		wait(500);
		
		display_text(tempString);
		
		wait(500);
	}
}
