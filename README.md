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

### A simple project
```cpp
#include <InputDigital.h>

#define BUTTON_PIN 23

InputDigital button(BUTTON_PIN);

void setup() {
	// This method must always be called in setup()
	button.begin();
}

void loop() {
	// This method must always be called in loop()
	button.check();

	if (button.is_high()) { // HIGH logic signal = 3.3V or 5V
		// do something
	}

	if (button.is_low()) {  // LOW logic signal = 0V
		// do something
	}
}

```

### Public methods
```cpp
//Initialize the input pin with interrupt, this method must always be called in setup()
void begin();

//Determine the real state of the input, this method must always be called in loop()
void check();

//Return true if the current state of the input is LOW after debouncing
bool is_low();

//Return true if the current state of the input is HIGH after debouncing
bool is_high();

//Set debounce duration in milli-seconds
void set_debounce_duration(uint32_t Millis);

//Return the number of times the input has changed after debouncing
uint32_t get_change_counter();

//Return the number of times the input has changed from HIGH to LOW after debouncing (FALLING edge)
uint32_t get_falling_counter();

//Return the number of times the input has changed from LOW to HIGH after debouncing (RISING edge)
uint32_t get_rising_counter();

//Reset the change counter to zero
void reset_change_counter();

//Reset the falling counter to zero
void reset_falling_counter();

//Reset the rising counter to zero
void reset_rising_counter();

//Reset change, falling and rising counters to zero
void reset_all_counters();

//Return true if the input has changed state after debouncing (FALLING and RISING edge)
bool has_changed();

//Return true if the input has changed from HIGH to LOW after debouncing (FALLING edge)
bool has_fallen();

//Return true if the input has changed from LOW to HIGH after debouncing (RISING edge)
bool has_risen();
```
