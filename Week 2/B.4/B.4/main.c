/*
 * main.c
 *
 * Created: 2/10/2021 3:47:24 PM
 *  Author: ralf
 */ 

#define F_CPU 8000000UL

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

const char show [] = {
		0b01000000,
		0b00100000,
		0b00000001,
		0b00000010,
		0b01000000,
		0b00010000,
		0b00001000,
		0b00000100,
};

void wait(int ms){
	for (int i = 0; i < ms; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;
	
	int index = 0;
	
    while(1)
    {
         PORTD = show[index];
		 
		 if (index == 7){
			index = 0;
		 } else {
			 ++index;
		 }
		 wait(200);
    }
}