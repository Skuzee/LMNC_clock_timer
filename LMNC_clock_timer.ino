
// Ticks per minute
#define TICKS_PER_MINUTE_MIN 1  // once per minute
#define TICKS_PER_MINUTE_MAX 60 // once per second

// length of pulse in milliseconds
// might need adjusting
#define RELAY_PULSE_LENGTH 100
// time out period in seconds
#define TIMEOUT_PERIOD 60

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
	pulseTheRelay(TICKS_PER_MINUTE_MIN);
else
	pulseTheRelay(potValue);
}

void pulseTheRelay(unsigned int freq) {

	// calculate millisecond delay from freq
	unsigned int relayDelay = 60000 / freq;

	delay(relayDelay);
	digitalWrite(RELAY_PIN, HIGH);
	delay(RELAY_PULSE_LENGTH);
	digitalWrite(RELAY_PIN, LOW);
 }
