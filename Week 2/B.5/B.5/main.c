/*
 * main.c
 *
 * Created: 2/10/2021 4:25:12 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include "micr_lcd.h"

int main(void)
{
	lcd_clear();
	_delay_ms(250);
	init();
	_delay_ms( 250 );
	lcd_write_command(0x02);
	_delay_ms( 250 );
	display_text("LCD I am");
	
	
    while(1)
    {
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );

    }
}