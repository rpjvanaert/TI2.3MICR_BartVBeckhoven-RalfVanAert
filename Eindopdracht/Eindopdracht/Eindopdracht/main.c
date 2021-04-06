/*
 * main.c
 *
 * Created: 3/24/2021 1:07:41 PM
 *  Author: ralf
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

#define POT_METER_1 0b0000
#define POT_METER_2 0b0001

int pot_1_val;
int pot_2_val;

#define SERVO_FREQ 50

#define SERVO_MAX_STATE 2500
#define SERVO_MIN_STATE 500
#define ADC_TO_SERVO_FACTOR 8

// wait busy waiting for ms in milliseconds
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

// Initialize ADC for given pin (0b0000 or 0b0001)
void adc_set_port( int bit )
{
	ADMUX = (0b01100000 | bit); // AREF = VCC, result left adjusted, channel1 at PF1.
}

// Method that sets adc port, reads adc on that port and then returns value of the port
int adc_read_port ( int bit )
{
	adc_set_port(bit);			// Set port to bit ( PF0 to PF5)
	ADCSRA |= BIT(6);			// Start ADC
	while (ADCSRA & BIT(6));	// Wait for completion
	return ADCH;				// Return MSB (bit 9:2) of ADC
}


// Initialize PWM for servos
void servos_init( void )
{	
	// Set ports to output
	DDRB = 0xFF;
	DDRE = 0xFF;
	
	
	ICR1 = F_CPU / SERVO_FREQ;
	ICR3 = F_CPU / SERVO_FREQ;
	
	// Set PWM's to min value of servos
	OCR1A = SERVO_MIN_STATE;
	OCR3A = SERVO_MIN_STATE;
	
	// Init Timer1
	TCCR1A = 1<<COM1A1 | 1<<WGM11;
	TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS11;
	
	// Init Timer3
	TCCR3A = 1<<COM3A1 | 1<<WGM31;
	TCCR3B = 1<<WGM33 | 1<<WGM32 | 1<<CS31;
	
}

// Calculates the adc measurement to servo value
int servoSpeed(int adc_pot_val){
	return SERVO_MIN_STATE + adc_pot_val * ADC_TO_SERVO_FACTOR;
}


int main(void)
{
	servos_init();
	ADCSRA = 0b10000110; // ADC enabled, no interrupt, no free running, division by 64.
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRC = 0xFF;	
	
    while(1)
    {
		//Measure potentiometers
		pot_1_val = adc_read_port(POT_METER_1);
		pot_2_val = adc_read_port(POT_METER_2);
		
		//Show potentiometers value on board with LED's
		PORTA = pot_1_val;
		PORTC = pot_2_val;
		
		//Adjust servo motor 1 according to potentiometer 1
		OCR1A = servoSpeed(pot_1_val);
	
		//Adjust servo motor 2 according to potentiometer 2
		OCR3A = servoSpeed(pot_2_val);
		
		//Wait a bit to rest for servo
		wait(100);
		
		
    }
}