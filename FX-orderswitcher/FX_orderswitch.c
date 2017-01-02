/* This is a relay based switching scheme for 2 effects pedals.
 * With 1 simple momentary pushbutton, you can change the order of the pedals.
 * This is done by using 3 small relays acting as switches.
 *
 * Code consist of bits and bobs of arduino tutorial code */

const int buttonPin = 12;      // the number of the pushbutton pin
const int OUT_RELAY1 =  5;     // output to coil of relay 1
const int OUT_RELAY2 =  6;     // output to coil of relay 2
const int OUT_RELAY3 =  7;     // output to coil of relay 3

/*Changing variables*/
int OUTPUT_STATE = HIGH;
int buttonState;
int lastButtonState = LOW;

/*Debouncing variables*/
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

/*Sets up the used pins and writes the initial OUTPUT_STATE as HIGH*/
void setup() {

  pinMode(OUT_RELAY1, OUTPUT);
  pinMode(OUT_RELAY2, OUTPUT);
  pinMode(OUT_RELAY3, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(OUT_RELAY1, OUTPUT_STATE);
  digitalWrite(OUT_RELAY2, OUTPUT_STATE);
  digitalWrite(OUT_RELAY3, OUTPUT_STATE);

}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
	  lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

	  if (reading != buttonState) {
	  buttonState = reading;

	  	  if (buttonState == HIGH) {
		  OUTPUT_STATE = !OUTPUT_STATE;
	  	  }
	  }
  }

/* writes the OUTPUT_STATE to the relay coils*/
  digitalWrite(OUT_RELAY1, OUTPUT_STATE);
  digitalWrite(OUT_RELAY2, OUTPUT_STATE);
  digitalWrite(OUT_RELAY3, OUTPUT_STATE);

  lastButtonState = reading; //saves the state
}
