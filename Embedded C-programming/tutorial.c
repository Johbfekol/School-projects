#define F_CPU 8000000UL // define CPU speed for 8 MHz
#include <avr/io.h> // IO functions
#include <util/delay.h> // Delay functions
int main(void) {

	DDRB = 0xFF; // port B is output
	PORTB = 0xFE; // PORTB: 1111 1110 only the first led is 'on' 
	_delay_ms(200); // delay
	
	while(1) { // eternal loop. This loop turns all leds on one by one.
               // Shifts all bits by one first, so when its 0x00 (all leds 'on',) it turns all of and starts bit
			   // shifting again. This happens with 600 ms intervals.
		if(PORTB == 0) PORTB = 0xFF; // if all leds 'on', turn off all, PORTB = 1111 1111
		PORTB <<= 1; // leds go 'on' one by one
		_delay_ms(600); // delay
		
	}
	
	return 0;
}
