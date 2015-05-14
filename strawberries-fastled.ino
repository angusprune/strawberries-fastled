#include "FastLED.h"

//number of leds in strip
#define NUM_LEDS 125

//define data (yellow) and clock (green)
#define DATA_PIN 2
#define CLOCK_PIN 3

// Define the array of ledsCRGB leds[NUM_LEDS];
CRGB leds[NUM_LEDS];

void setup() {
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop () {
	leds[10] = CRGB::Blue;
	FastLED.show();
}