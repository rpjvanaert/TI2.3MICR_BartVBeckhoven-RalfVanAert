/*
 * main.c
 *
 * Created: 2/3/2021 1:19:16 PM
 *  Author: beckh
 */ 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait (int ms) {
	for (int i = 0; i<ms; i++){
		_delay_ms(10);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	
    while(1)
    {
        PORTD = 0x80; 
		wait(500);
		PORTD = 0x40;
		wait(500);
    }
	
	return 1;
}