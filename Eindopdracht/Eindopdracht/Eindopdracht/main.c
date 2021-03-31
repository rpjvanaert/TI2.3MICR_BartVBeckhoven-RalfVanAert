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

#define SERVO_1 1
#define SERVO_2 2

#define SERVO_MAX_STATE 2000
#define SERVO_MIN_STATE 1000
int servo1_state;
int servo1_goal;
int servo2_state;
int servo2_goal;

// wait busy waiting for ms in milliseconds
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

// Initialize ADC for given pin (0b0000 or 0b0001
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




// Initialize Servo for
void servos_init( void )
{
	servo1_state = SERVO_MIN_STATE;
	servo2_state = SERVO_MIN_STATE;
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRE = 0xFF;
	ICR1 = 20000;
	ICR3 = 20000;
	
	OCR1A = servo1_state;
	OCR3A = servo1_state;
	
	TCCR1A = 0b10000010;
	TCCR1B = 0b00011010;
	
	TCCR3A = 0b10000010;
	TCCR3B = 0b00011010;
	
}

/*void servo_send(int servo_nr, int pwm)
{
	if (servo_nr == SERVO_1)
	{
		OCR1A = ICR1 - pwm;
	}
	if (servo_nr == SERVO_2)
	{
		OCR1B = ICR1 - pwm;
	}
	
}
*/

void servos_step(){
	if (servo1_state < servo1_goal){
		servo1_state += 1;
	} else if (servo1_state > servo1_goal){
		servo1_state -= 1;
	}
	
	if (servo2_state < servo2_goal){
		servo2_state += 1;
	} else if (servo2_state > servo2_goal){
		servo2_state -= 1;
	}
	
	OCR1A = servo1_state;
	OCR3A = servo2_state;
}




int main(void)
{
	servos_init();
	ADCSRA = 0b10000110; // ADC enabled, no interrupt, no free running, division by 64.
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	wait(1000);
	
	servo1_goal = 2000;
	servo2_goal = 2000;
	
	servo1_state = servo1_goal;
	servo2_state = servo2_goal;
	
	OCR1A = servo1_goal;
	OCR3A = servo2_goal;
	
	
    while(1)
    {		
		PORTA = adc_read_port(POT_METER_1);
		PORTB = adc_read_port(POT_METER_2);
		
		/*
		//servo_send(SERVO_1, 1);
		
		OCR1A = 2125;
		
		wait(2500);
		
		//servo_send(SERVO_1, 2);
		
		OCR3A = 1800;
		OCR1A = 1800;
		
		wait(2500);
		
		OCR3A = 1700;
		OCR1A = 1700;
		
		wait(2500);
		*/
		
		servos_step();
		
		wait(10000);
		
		if (servo1_state == SERVO_MAX_STATE){
			servo1_goal = SERVO_MIN_STATE;
		} else if (servo1_state == SERVO_MIN_STATE){
			servo1_goal = SERVO_MAX_STATE;
		}
		
		if (servo2_state == SERVO_MAX_STATE){
			servo2_goal = SERVO_MIN_STATE;
			} else if (servo2_state == SERVO_MIN_STATE){
			servo2_goal = SERVO_MAX_STATE;
		}
		
    }
}