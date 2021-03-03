/*
 * main.c
 *
 * Created: 3/3/2021 1:24:14 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "micr_lcd.c"


#define BIT(x)			(1 << (x))

void wait (int ms){
	for (int tms = 0; tms < ms; tms++){
		_delay_ms( 1 );
	}
}

int main(void)
{
	DDRD &= ~BIT(7);
	DDRB = 0xFF;
	TCCR2 = 0b00000111;
	
	init();
	
	wait(250);
	
	lcd_clear();
	
	
	
	
    while(1)
    {
        PORTB = TCNT2;
		
		/**
		int number = TCNT2;
		int n = log10(number) + 1;
		char *numberArray = calloc(n, sizeof(char));
		for (int i = n - 1; i >= 0; --i, number /= 10){
			numberArray[i] = (number % 10) + '0';
		}
		**/
		//const char number = TCNT2;
		
		lcd_clear();
		
		wait(1);
		
		char counterString[16];
		
		sprintf(counterString, "{%i}", TCNT2);
		
		display_text(counterString);
		
		wait(500);
    }
}