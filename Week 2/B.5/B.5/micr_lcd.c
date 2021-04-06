#include "micr_lcd.h"

#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			//
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			//
}

void lcd_write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void init(){
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void display_text(const char *str){
	for(;*str; str++){
		lcd_write_data(*str);
	}	
}

void set_cursor(int position){
	
}

void lcd_clear() {
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x01;
	lcd_strobe_lcd_e();
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x02;
	lcd_strobe_lcd_e();
}