#include <avr/io.h>
#include <util/delay.h>
#include "global.h"
#include "blink.h"

int main()
{	
	sbi(DDRD, PORTD6);
	
	cbi(PORTD, PORTD6);
	while(TRUE)
	{
		sbi(PORTD, PORTD6);
		_delay_us(500000/FREQ);
		cbi(PORTD, PORTD6);
		_delay_us(500000/FREQ);
	}
	return EXIT_SUCCESS;
}
