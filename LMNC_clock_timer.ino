/*
	consider this code open source. I give express permission for anyone
	to use, edit, or distribute this code for any reason. This code is
	untested, so use at your own risk??? It's probably fine. Please link
	to my github if you distribute or quote this code anywhere. Thanks!
	https://github.com/Skuzee
*/

/* Hiya~~~~
	This should produce a pulse between once per second (TICKS_PER_MINUTE_MAX)
	and once per minute (TICKS_PER_MINUTE_MIN).
	You may need to change the input/output pin numbers. (RELAY_PIN) (POT_PIN)
	The length of the relay pulse is set via (RELAY_PULSE_LENGTH)
	The timeout period is set for 60 seconds (TIMEOUT_PERIOD)

	I hope this helps! (I hope this works!)
	It compiles fine for an arduino nano, but I haven't tested it.

	<3 J3
*/


// Ticks per minute
#define TICKS_PER_MINUTE_MIN 1  // once per minute
#define TICKS_PER_MINUTE_MAX 60 // 60 times per minute

// length of pulse in milliseconds
// might need adjusting
#define RELAY_PULSE_LENGTH 100
// time out period in milliseconds
#define TIMEOUT_PERIOD 60000

// input pins
#define RELAY_PIN 1
#define POT_PIN A1

unsigned long startTime;
unsigned int potValue;
unsigned int prevPotValue;


void setup() {

// init relay as output, and low
digitalWrite(RELAY_PIN, LOW);
pinMode(RELAY_PIN, OUTPUT);
}

void loop() {

// save prev potentiometer value
prevPotValue = potValue;

// read potentiometer value and
// map pot range (0 - 1023) to tick freq range.
// swap 0 and 1023 if you want the pot to be reversed.
potValue = map(analogRead(POT_PIN), 0, 1023, TICKS_PER_MINUTE_MIN, TICKS_PER_MINUTE_MAX);

// if the pot is being moved, update our timer.
if (potValue != prevPotValue)
	startTime = millis();

// if a certain time has elapsed, only tick once per minute
// this should never be true while the pot is being moved
if (millis() - startTime >= TIMEOUT_PERIOD)
	updateTheRelay(TICKS_PER_MINUTE_MIN);
else
	updateTheRelay(potValue);
}

void updateTheRelay(unsigned int freq) {

static long relayStartTime;
static bool relayIsOn;

// calculate millisecond delay from freq
unsigned int relayDelay = (60000 / freq) - RELAY_PULSE_LENGTH;

	// if the relay is off and the timer has counted to relayDelay:
	// turn on relay and reset timer
	if (!relayIsOn && (millis() - relayStartTime >= relayDelay)){
		digitalWrite(RELAY_PIN, HIGH);
		relayIsOn = true;
		relayStartTime = millis();
	}
	// if the relay is on and the timer has counted to RELAY_PULSE_LENGTH:
	// turn off the relay and reset timer
	else if (relayIsOn && (millis() - relayStartTime >= RELAY_PULSE_LENGTH)) {
			digitalWrite(RELAY_PIN, LOW);
			relayIsOn = false;
			relayStartTime = millis();
	}
}
