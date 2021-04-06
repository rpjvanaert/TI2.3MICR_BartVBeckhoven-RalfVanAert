/*
 * main.c
 *
 * Created: 2/10/2021 2:21:47 PM
 *  Author: ralf
 */ 

#include <xc.h>

const char Numbers [] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b11111001, // E.
};

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x00;
	
	int index = 0;
	
	int prevPinC = 0b0;
	
    while(1)
    {
		
		if (PINC == 0b01 && prevPinC == 0b0){
			if (index == 16){
				index = 16;
				} else {
				++index;
			}
		}
		
		if (PINC == 0b10 && prevPinC == 0b0){
			if (index == 0){
				index = 0;
				} else {
				--index;
			}
		}
		
		prevPinC = PINC;
		
		PORTD = Numbers[index];
		
    }
}