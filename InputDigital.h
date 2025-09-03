#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <stdint.h>

class InputDigital {
	public:
		// Constructor
		InputDigital(uint8_t Pin) : PIN(Pin) {
			pinMode(PIN, INPUT);
			realSignal = rawSignal = digitalRead(PIN);
		}

		// Destructor
		~InputDigital() { detachInterrupt(PIN); }

		// Initialize the input pin with interrupt, this method must always be called in setup()
		void begin() { attachInterrupt(digitalPinToInterrupt(PIN), std::bind(&InputDigital::isr, this), CHANGE); }

		// Return true if the current state of the input is LOW after debouncing
		bool is_low() const { return !realSignal; }

		// Return true if the current state of the input is HIGH after debouncing
		bool is_high() const { return realSignal; }

		// Set debounce duration in milli-seconds
		void set_debounce_duration(uint32_t Millis) { debounceDuration = Millis; }

		// Return the number of times the input has changed after debouncing (FALLING and RISING edge)
		uint32_t get_change_counter() const { return counterChange; }

		// Return the number of times the input has changed from HIGH to LOW after debouncing (FALLING edge)
		uint32_t get_falling_counter() const { return counterFalling; }

		// Return the number of times the input has changed from LOW to HIGH after debouncing (RISING edge)
		uint32_t get_rising_counter() const { return counterRising; }

		// Reset the change counter to zero
		void reset_change_counter() { counterChange = 0; }

		// Reset the falling counter to zero
		void reset_falling_counter() { counterFalling = 0; }

		// Reset the rising counter to zero
		void reset_rising_counter() { counterRising = 0; }

		// Reset change, falling and rising counters to zero
		void reset_all_counters() { counterChange = counterFalling = counterRising = 0; }

		// Determine the real state of the input, this method must always be called in loop()
		void check();

		// Return true if the input has changed state after debouncing (FALLING and RISING edge)
		bool has_changed();

		// Return true if the input has changed from HIGH to LOW after debouncing (FALLING edge)
		bool has_fallen();

		// Return true if the input has changed from LOW to HIGH after debouncing (RISING edge)
		bool has_risen();

	private:
		const uint8_t PIN;

		volatile uint32_t lastTimeRawSignalChanged = 0; // Milli-seconds
		volatile bool rawSignal;

		uint32_t counterChange = 0, counterFalling = 0, counterRising = 0, debounceDuration = 100;
		bool realSignal, justChanged = false, justChangedToLow = false, justChangedToHigh = false;

		void ARDUINO_ISR_ATTR isr();
};