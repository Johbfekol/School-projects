/*
 * GccApplication1.c
 *
 * Created: 23.1.2017 16:27:24
 * Author : u97479
 */ 

#define F_CPU 8000000UL // CPU speed @ 8 MHz
#include <avr/io.h>
#include <util/delay.h>



int main(void) {
	uint8_t inverse = 0xFF;
	DDRB = 0xFF;  // Port b every bit is output
	PORTB = 0xFE; // 1111 1110 - First led is on
	_delay_ms(1000);
	
    /* Changes output value of PORTB1 */
    while (1) {
        for (int i = 0; i < 7; i++) {
			inverse =~ PORTB;
			inverse <<= 1;
			PORTB =~ inverse;
			_delay_ms(1000);
		}
	 PORTB = 0xFE;
	 _delay_ms(1000);
    }
	
	return 0;
}
