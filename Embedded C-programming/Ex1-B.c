/*
 * GccApplication1.c
 * 
 * Created: 24.1.2017 16:08:31
 * Author : Samu Haapoja
 */ 

#define F_CPU 8000000UL // CPU speed @ 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/*Function prototypes*/
static inline uint8_t debounce(volatile uint8_t *, const uint8_t);
void blink();

/*Main function*/
int main(void) {	
	DDRB = 0xFF;  // PORTB as input
	PORTB = 0xFF; // PORTB default values off
	DDRD = 0x00;  // PORTD as inputs
	uint8_t number = 0;
	uint8_t counter = 0;
	while (PIND&0x80) counter++;   // Loops until SW7 is pressed
		
	srand(counter);   // generates a random seed based on the counter valule
	number = rand() % 3; // a random number from 0 to 2
	number++;            // now it's from 1 to 3

	while (1) {
		if(debounce(&PIND, PD0) && number == 1 ) {
			blink();
			PORTB =~ number;
		}
		
		if(debounce(&PIND, PD1)&& number == 2 ) {
			blink();
			PORTB =~ number;
		}
		
		if(debounce(&PIND, PD2)&& number == 3 ) {
			blink();
			PORTB =~ number;
		}
   	}
	
	return 0;
}

void blink() {
	for (int i = 0; i < 5; i++) {
		PORTB = 0x00;
		_delay_ms(500);
		PORTB =~ PORTB;
		_delay_ms(500);
	}
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
