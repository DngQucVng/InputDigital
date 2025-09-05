# Documentation

## A Library for Micro-controllers using Arduino IDE

This project is an attempt to implement C++ class with pin interrupt together with debounce algorithm. It can do the following:

* Apply debouncing to know if the signal is real (the debounce duration can be customized)
* Detect legitimate RISING and FALLING edges
* Record how many non-boucing edges have been detected
* Could be used for things such as buttons, limit switches, proximity sensors

## Installation

Here are the steps to install the library:

1. Download ZIP of the project
2. Open Arduino IDE
3. Navigate to Sketch -> Include Library -> Add .ZIP Library...
4. Browse for the downloaded .ZIP file

## Usage

### Simple Project
```cpp
#include <InputDigital.h>

#define BUTTON_PIN 23

InputDigital button(BUTTON_PIN);

void setup() {
	// This must always be called in setup()
	button.begin();
}

void loop() {
	// This must always be called in loop()
	button.check();

	if (button.is_high()) { // HIGH logic signal = 3.3V or 5V
		// do something while the pin is HIGH
	}

	if (button.is_low()) {  // LOW logic signal = 0V
		// do something while the pin is LOW
	}
}

```

### Detect Edges
```cpp
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
		// do something once
	}

	// This returns true when the pin changes state from HIGH to LOW (FALLING edge)
	if (button.has_fallen()) {
		// do something once
	}

	// This returns true when the pin changes state from LOW to HIGH (RISING edge)
	if (button.has_risen()) {
		// do some thing once
	}
}


```

### Count Edges
```cpp
#include <InputDigital.h>

#define BUTTON_PIN 23

InputDigital button(BUTTON_PIN);

unsigned long now, prePrint;

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

	// Get current time in milli-seconds
	now = millis();

	// Print the counters 5 times per second
	if (now - prePrint >= 200) {
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

```

### Activation
```cpp
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
```