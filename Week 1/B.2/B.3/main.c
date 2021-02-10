/*
 * main.c
 *
 * Created: 2/3/2021 2:16:17 PM
 *  Author: beckh
 */ 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait(int ms){
	for (int i; i < ms; i++){
		_delay_ms(10);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	DDRC = 0x00;
	
    while(1)
    {
        int value = PINC0;
		
		if (value == 1){
			PORTD = 0x80;
			wait(250)
			PORTD = 0x00;
		}
		
		wait(250);
		
		
    }
	
	return 1;
}