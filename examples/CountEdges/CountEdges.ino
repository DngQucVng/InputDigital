#include <InputDigital.h>

#define BUTTON_PIN 23

// Declare button with pin
InputDigital button(BUTTON_PIN);

unsigned long now, prePrint;

void setup() {
	Serial.begin(115200);

	// This method must always be called in setup()
	button.begin();

	// This method is OPTIONAL, if you don't call it then the default debounce duration will be 100 milli-seconds
	button.set_debounce_duration(200); // Unit = milli-seconds
}

void loop() {
	// This method must always be called in loop()
	button.check();

	// Get current time in milli-seconds
	now = millis();

	// Print the counters 2 times per second
	if (now - prePrint >= 500) {
		prePrint = now;
		Serial.print("FALLING edge counter: "); Serial.println(button.get_falling_counter());
		Serial.print("RISING edge counter: ");  Serial.println(button.get_rising_counter());
		Serial.print("CHANGE edge counter: ");  Serial.println(button.get_change_counter());
	}

	// Listen for Serial data to reset counters
	if (Serial.available()) {
		String data = Serial.readStringUntil('\n');

		if (data == "1")
			button.reset_falling_counter();
		else if (data == "2")
			button.reset_rising_counter();
		else if (data == "3")
			button.reset_change_counter();
		else if (data == "4")
			button.reset_all_counters();
	}
}
