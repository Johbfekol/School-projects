/*
 * GccApplication1.c
 *
 * Created: 23.1.2017 16:27:24
 * Author : u97479
 */ 

#define F_CPU 8000000UL // CPU speed @ 8 MHz
#include <avr/io.h>
#include <util/delay.h>


/* function prototype */
static inline uint8_t debounce(volatile uint8_t *, const uint8_t);

int main(void) {
	uint8_t counter = 0; // defines counter variable
	DDRB = 0xFF;  // Port b every bit is output
	DDRD = 0xF8;  // Port b first 3 bits are input (1111 1000)
	PORTB = 0xFF; // Port b value 1111 1111 (no leds on)
	//PORTD = 0xFF; // Port d value 1111 1111 (no buttons pressed)
	
    /* Checks the first 3 buttons and does  */
    while (1) {
		if (debounce(&PIND, PD0)) counter++; // increases with 1st button pressed
		if (debounce(&PIND, PD1)) counter--; // decreases with 2nd button pressed
		if (debounce(&PIND, PD2)) counter = 0; // resets counter with 3rd button pressed
		if (counter > 5) PORTB = 0x00;	// if counter is larger than 5 then turns all leds on			   
		else PORTB = 0xFF;
	}
	
	return 0;
}

static inline uint8_t debounce(volatile uint8_t *pinReg, const uint8_t pin) {
	if(!(*pinReg & (1 << pin))) {
		//pin grounded wait 100ms
		_delay_ms(100);
		
		if(*pinReg & (1 << pin)) {
			// give the user time to release the button
			_delay_ms(100);
			return 1;
		}
	}
	return 0;
}
