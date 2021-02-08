/*
 * main.c
 *
 * Created: 2/3/2021 3:29:29 PM
 *  Author: ralf
 */ 

#define F_CPU 8000000UL

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait (int ms) {
	for (int i = 0; i<ms; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0b11111111;

	int byte = 0x01;
	
	
	while(1)
	{
		
		
		PORTD = byte;

		wait(50);
		
		byte = byte << 1;
		
		if (byte == 0x00)
		{
			byte = 0x01;
		}
		
	}
	
	return 1;
}