/*
 * GccApplication1.c
 *
 * Created: 23.1.2017 16:27:24
 * Author : u97479
 */ 

#define F_CPU 8000000UL // CPU speed @ 8 MHz
#include <avr/io.h>
#include <avr/interrupt.h>

/*Interrupt vectors, just FYI						*/
/*#define INT0_vect 		_VECTOR(1) // PD2 (SW2) */
/*#define SIG_INTERRUPT0 	_VECTOR(1)				*/
/*													*/
/*#define	INT1_vect 		_VECTOR(2) // PD3 (SW3) */
/*#define SIG_INTERRUPT1	_VECTOR(2)				*/

/* Interrupt service routines for turning on and off LED5 */

ISR(INT0_vect) {
	PORTB = 0xEF; // 1110 1111, PD2 sets LED5 on
}

ISR(INT1_vect) {
	PORTB = 0xFF; // 1111 1111, PD3 turns off all LEDS
}

int main(void) {
	DDRB = 0xFF;  // PORTB as input
	PORTB = 0xFF; // PORTB default values off
	DDRD = 0x00;  // PORTD as inputs
	GICR |= ((1<<INT0)|(1<<INT1)); // 1100 0000 INT0 and INT1 enabled as interrupts
	MCUCR = 0x0F; //0000 1111 values for MCUCR means Rising edge for both INT0 and INT1
	sei(); // Enables global interrupts
	while (1) {
		// endless loop	
	}
	
	return 0;
}
