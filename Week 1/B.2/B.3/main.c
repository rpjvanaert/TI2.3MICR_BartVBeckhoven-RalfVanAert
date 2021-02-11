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
	DDRD = 0b11111111; //make all D ports output
	
    while(1)
    {
	PORTD = 0x80; // put on only led 7
	wait(500);
	PORTD = 0x40; // put on only led 6
	wait(500);
    }
	
	return 1;
}
