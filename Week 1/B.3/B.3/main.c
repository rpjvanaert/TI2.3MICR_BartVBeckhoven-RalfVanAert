/*
 * main.c
 *
 * Created: 2/3/2021 2:32:28 PM
 *  Author: beckh
 */ 

#define F_CPU 8000000UL

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait(int ms){
	for (int i = 0; i < ms; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	DDRC = 0x00;
	
	while(1)
	{
		int value = PINC;
		
		if (value == 0x01){
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
		} else {
			PORTD = 0x00;
		}
		wait(250);
	}
	return 1;
}