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

	if (button.is_high()) { // HIGH logic signal = 3.3V or 5V
		// do something
	}

	if (button.is_low()) {  // LOW logic signal = 0V
		// do something
	}
}
