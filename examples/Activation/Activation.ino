#include <InputDigital.h>

#define BUTTON_PIN 23

InputDigital button(BUTTON_PIN);

void setup() {
	Serial.begin(115200);

	// This must always be called in setup()
	button.begin();

	// This is OPTIONAL, if you don't call it then the default debounce duration will be 50 milli-seconds
	button.set_debounce_duration(100); // Unit = milli-seconds

	// Default is pulled down mode, if your circuit is pulled up then use INPUT_DIGITAL_MODE_PULL_UP
	button.set_mode(INPUT_DIGITAL_MODE_PULL_DOWN);
}

void loop() {
	// This must always be called in loop()
	button.check();

	// Get current time in milli-seconds
	now = millis();

	if (button.is_active()) {
		// do something while button is held down
	}

	if (button.has_activated()) {   // when button is pressed
		// do something once
	}

	if (button.has_deactivated()) { // when button is released
		// do something once
	}

	// Print the counters 5 times per second
	if (now - prePrint >= 200) {
		prePrint = now;
		Serial.print("Number of clicks: ");
		Serial.println(button.get_activation_counter()); // There is also a deactivation counter
	}

	// Listen for Serial data to reset counter
	if (Serial.available()) {
		String data = Serial.readStringUntil('\n');

		if (data == "1")
			button.reset_activation_counter();
	}
}