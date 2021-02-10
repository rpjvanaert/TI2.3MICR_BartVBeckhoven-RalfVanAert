/*
 * main.c
 *
 * Created: 2/3/2021 1:19:16 PM
 *  Author: beckh
 */ 

#define F_CPU 8000000UL

#define length1hz 500
#define length4hz 125

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait (int ms) {
	for (int i = 0; i<ms; i++){
		_delay_ms(1);
	}
}

void waitHz (int hz) {
	if (hz == 1){
		wait(length1hz);
		} else {
		wait(length4hz);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	DDRC = 0b00000000;

	int prevValPinC0 = 0;
	int currentHz = 1;
	
    while(1)
    {		
		int valPinC0 = PINC;
		
		if (valPinC0 == 1 && prevValPinC0 == 0)
		{
			
			
			if (currentHz == 1)
			{
				currentHz = 4;
			} else
			{
				currentHz = 1;
			}
		}
		prevValPinC0 = valPinC0;
		
		PORTD = 0x80;
		waitHz(currentHz);
		PORTD = 0x00;
		waitHz(currentHz);
    }	
	return 1;
}