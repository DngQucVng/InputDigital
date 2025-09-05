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

		justActivated = mode != rawSignal;
		if (justActivated) counterActivation++;

		justDeactivated = mode == rawSignal;
		if (justDeactivated) counterDeactivation++;

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

// Return true if the input has changed from default pulled state to the other after debouncing (RISING or FALLING edge)
bool InputDigital::has_activated() {
	if (justActivated) {
		justActivated = false;
		return true;
	}

	return false;
}

// Return true if the input has changed from non-default pulled state to the default after debouncing (RISING or FALLING edge)
bool InputDigital::has_deactivated() {
	if (justDeactivated) {
		justDeactivated = false;
		return true;
	}

	return false;
}