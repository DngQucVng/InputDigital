#include <InputDigital.h>

#define BUTTON_PIN 23

// Declare button with pin
InputDigital button(BUTTON_PIN);

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

	// This method returns true when the pin changes state (RISING and FALLING edge)
	if (button.has_changed())
		Serial.println("Button has changed.");

	// This method returns true when the pin changes state from high to low (FALLING edge)
	if (button.has_fallen())
		Serial.println("Falling edge detected.");

	// This method returns true when the pin changes state from low to high (RISING edge)
	if (button.has_risen())
		Serial.println("Rising edge detected.");
}
