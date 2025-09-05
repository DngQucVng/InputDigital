#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <stdint.h>

#define INPUT_DIGITAL_MODE_PULL_DOWN 0
#define INPUT_DIGITAL_MODE_PULL_UP   1

class InputDigital {
	public:
		// Constructor
		InputDigital(uint8_t Pin) : PIN(Pin) {
			pinMode(PIN, INPUT);
			realSignal = rawSignal = digitalRead(PIN);
		}

		// Destructor
		~InputDigital() { detachInterrupt(digitalPinToInterrupt(PIN)); }

		// Initialize the input pin with interrupt, this method must always be called in setup()
		void begin() { attachInterrupt(digitalPinToInterrupt(PIN), std::bind(&InputDigital::isr, this), CHANGE); }

		// Return true if the current state of the input is LOW after debouncing
		bool is_low() const { return !realSignal; }

		// Return true if the current state of the input is HIGH after debouncing
		bool is_high() const { return realSignal; }

		// Return true if the current state of the input is not its default state
		bool is_active() const { return realSignal != mode; }

		// The default mode is INPUT_DIGITAL_MODE_PULL_DOWN, if your circuit is pulled up then use INPUT_DIGITAL_MODE_PULL_UP
		void set_mode(bool Mode) { mode = Mode; }

		// Set debounce duration in milli-seconds
		void set_debounce_duration(uint32_t Millis) { debounceDuration = Millis; }

		// Return the number of times the input has changed after debouncing (FALLING and RISING edge)
		uint32_t get_change_counter() const { return counterChange; }

		// Return the number of times the input has changed from HIGH to LOW after debouncing (FALLING edge)
		uint32_t get_falling_counter() const { return counterFalling; }

		// Return the number of times the input has changed from LOW to HIGH after debouncing (RISING edge)
		uint32_t get_rising_counter() const { return counterRising; }

		// Return the number of times the input has changed from default state to the other after debouncing (RISING or FALLING edge)
		uint32_t get_activation_counter() const { return counterActivation; }

		// Return the number of times the input has changed from non-default state to default after debouncing (RISING or FALLING edge)
		uint32_t get_deactivation_counter() const { return counterDeactivation; }

		// Reset the change counter to zero
		void reset_change_counter() { counterChange = 0; }

		// Reset the falling counter to zero
		void reset_falling_counter() { counterFalling = 0; }

		// Reset the rising counter to zero
		void reset_rising_counter() { counterRising = 0; }

		// Reset the activation counter to zero
		void reset_activation_counter() { counterActivation = 0; }

		// Reset the deactivation counter to zero
		void reset_deactivation_counter() { counterDeactivation = 0; }

		// Reset change, falling and rising counters to zero
		void reset_all_counters() { counterChange = counterFalling = counterRising = counterActivation = counterDeactivation = 0; }

		// Determine the real state of the input, this method must always be called in loop()
		void check();

		// Return true if the input has changed state after debouncing (FALLING and RISING edge)
		bool has_changed();

		// Return true if the input has changed from HIGH to LOW after debouncing (FALLING edge)
		bool has_fallen();

		// Return true if the input has changed from LOW to HIGH after debouncing (RISING edge)
		bool has_risen();

		// Return true if the input has changed from default pulled state to the other after debouncing (RISING or FALLING edge)
		bool has_activated();

		// Return true if the input has changed from non-default pulled state to the default after debouncing (RISING or FALLING edge)
		bool has_deactivated();

	private:
		const uint8_t PIN;

		volatile uint32_t lastTimeRawSignalChanged = 0; // Milli-seconds
		volatile bool rawSignal;

		uint32_t counterChange = 0, counterFalling = 0, counterRising = 0, counterActivation = 0, counterDeactivation = 0, debounceDuration = 50;
		bool mode = false, realSignal, justChanged = false, justChangedToLow = false, justChangedToHigh = false, justActivated = false, justDeactivated = false;

		void ARDUINO_ISR_ATTR isr();
};