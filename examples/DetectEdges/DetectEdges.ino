#include <InputDigital.h>

#define BUTTON_PIN 23

InputDigital button(BUTTON_PIN);

void setup() {
	Serial.begin(115200);

	// This must always be called in setup()
	button.begin();

	// This is OPTIONAL, if you don't call it then the default debounce duration will be 50 milli-seconds
	button.set_debounce_duration(100); // Unit = milli-seconds
}

void loop() {
	// This must always be called in loop()
	button.check();

	// This returns true when the pin changes state (RISING and FALLING edge)
	if (button.has_changed()) {
		// do something
	}

	// This returns true when the pin changes state from HIGH to LOW (FALLING edge)
	if (button.has_fallen()) {
		// do something
	}

	// This returns true when the pin changes state from LOW to HIGH (RISING edge)
	if (button.has_risen()) {
		// do some thing
	}
}
