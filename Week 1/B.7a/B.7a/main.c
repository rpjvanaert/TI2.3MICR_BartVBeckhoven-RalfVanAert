/*
 * main.c
 *
 * Created: 2/11/2021 2:00:24 PM
 *  Author: ralf
 */ 

#include <xc.h>

/* 3 states; start, running and done */
typedef enum { START, RUNNING, DONE } ENUM_STATES;
	
/* 2 events; long press and a short press */
typedef enum { LONG_PRESS, SHORT_PRESS } ENUM_EVENTS;
	
/* The navigation array is returns the state the machine should go to depending on the input (ENUM_STATES, ENUM_EVENTS) */
ENUM_STATES navigation[3][2] = {
	{
		{
			START, RUNNING
		},
		{
			START, DONE
		},
		{
			START, START
		}
	}
};

// Start with state START
ENUM_STATES state = START;

/* Sets state depending on event with navigation array */
void handleEvent(ENUM_EVENTS event){
	// Potentially do something here...
	state = navigation[state][event];
}

int main(void)
{
    while(1)
    {
		// Example
        handleEvent(SHORT_PRESS);
		handleEvent(LONG_PRESS);
		handleEvent(SHORT_PRESS);
		handleEvent(SHORT_PRESS);
    }
}