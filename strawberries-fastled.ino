#include "FastLED.h"

//number of leds in strip
#define NUM_LEDS 150

//define data (yellow) and clock (green)
#define DATA_PIN 2
#define CLOCK_PIN 3

// Define the array of ledsCRGB leds[NUM_LEDS];
CRGB leds[NUM_LEDS];
CRGB display[NUM_LEDS];


void setup() {
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(display, NUM_LEDS);
}


void correction(){
    int start = 75; // starting index
    int count = 25;
    int left, right;
	memcpy(display, leds, sizeof(display));
	for (left=start, right=start+count-1 ; left < right ; left++, right--){
        display[right] = leds[left];
		display[left] = leds[right];
	}
}


//abstract the FastLED away
void show(){
	correction();
	FastLED.show();
}

//wipes the whole spectrum from a strating HSV
void rainbowWipe(int hue, int shift, int wait){
	int i;
	for (i=0; i < NUM_LEDS; i++){
		fill_rainbow(leds, i+1, hue, shift);
		show();
		delay(wait);
	}
}


void loop () {

int i;
/*for (i=0; i < NUM_LEDS; i++){
	leds[i] = CRGB::Red;

	show();
		delay(1000);
	leds[i] = CRGB::Black;

}*/
fill_solid(leds, NUM_LEDS, CRGB::Black);
rainbowWipe(50, 10, 50);
//fill_rainbow(leds, NUM_LEDS, 50, 5);
//show();
delay(100);
//fill_solid(leds, NUM_LEDS, CRGB::Black);
}