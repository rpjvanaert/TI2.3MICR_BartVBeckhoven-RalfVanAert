/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/******************************************************************
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/*****************************************************************
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT2_vect ) {
    if (PORTC >= 0x80)
    {
	    PORTC = 0x01;
    } else
    {
	    PORTC <<= 1;
    }
}

/******************************************************************
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT1_vect ) {
    if (PORTC >= 0x80)
    {
	    PORTC = 0x01;
    } else
    {
	    PORTC <<= 1;
    }		
}

/******************************************************************
short:			main() loop, entry point of executable
inputs:
outputs:s
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
int main( void ) {
	// Init I/O
	DDRC = 0xFF;			// PORTC(7:0) output

	// Init Interrupt hardware
	EICRA |= 0x3C;			// INT1 rising edge, INT2 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();	
	
	PORTC = 0b1;			

	while (1) {							
	}

	return 1;
}