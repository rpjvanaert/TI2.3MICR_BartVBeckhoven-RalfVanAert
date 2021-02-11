/*
 * main.c
 *
 * Created: 2/11/2021 2:00:24 PM
 *  Author: ralf
 */ 

#include <xc.h>

typedef enum { START, RUNNING, DONE } ENUM_STATES;
typedef enum { LONG_PRESS, SHORT_PRESS } ENUM_EVENTS;
	
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

ENUM_STATES state = START;

void handleEvent(ENUM_EVENTS event){
	state = navigation[state][event];
}

int main(void)
{
    while(1)
    {
        handleEvent(SHORT_PRESS);
		handleEvent(LONG_PRESS);
		handleEvent(SHORT_PRESS);
		handleEvent(SHORT_PRESS);
    }
}