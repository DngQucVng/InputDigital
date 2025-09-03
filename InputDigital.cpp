#include "InputDigital.h"

// Interrupt Service Routine for when the Pin change state
void ARDUINO_ISR_ATTR InputDigital::isr() {
	rawSignal = digitalRead(PIN);
	lastTimeRawSignalChanged = millis();
}

// Check for debouncing to determine the real state of the input, this function must be called in loop()
void InputDigital::check() {
	if (realSignal != rawSignal && millis() - lastTimeRawSignalChanged >= debounceDuration) {
		if (rawSignal) {
			counterRising++;
			justChangedToHigh = true;
			justChangedToLow = false;
		}
		else {
			counterFalling++;
			justChangedToHigh = false;
			justChangedToLow = true;
		}

		counterChange++;
		justChanged = true;
		realSignal = rawSignal;
	}
}

// Return true if the input has changed state
bool InputDigital::has_changed() {
	if (justChanged) {
		justChanged = false;
		return true;
	}

	return false;
}

// Return true if the input has changed from HIGH to LOW (FALLING edge)
bool InputDigital::has_fallen() {
	if (justChangedToLow) {
		justChangedToLow = false;
		return true;
	}

	return false;
}

// Return true if the input has changed from LOW to HIGH (RISING edge)
bool InputDigital::has_risen() {
	if (justChangedToHigh) {
		justChangedToHigh = false;
		return true;
	}

	return false;
}
