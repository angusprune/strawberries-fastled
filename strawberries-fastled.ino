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

//wipes a single colour from a CRGB
void colorWipe(CRGB color, int wait){
	int i;
	for (i=0; i < NUM_LEDS; i++){
		fill_solid(leds, i+1, color);
		show();
		delay(wait);
	}
}

void simpleDripFill(CRGB color, int wait){
	int fill;
	for (fill=0; fill < NUM_LEDS; fill++){
		int drip;
		for (drip=0; drip < (NUM_LEDS - fill); drip++){
			leds[drip] = color;
			show();
			leds[drip] = CRGB::Black;
		}
		leds[NUM_LEDS - fill] = color;
	}
}

void longDripFill(CHSV color, uint16_t length, int wait){
	uint16_t drip;
	CHSV black;
	black.s = 0;
	black.v = 0;
	for (drip=0; drip < (NUM_LEDS + length); drip++){
		fill_gradient (leds, drip, black, drip + length, color);
		show();
		delay(wait);
		leds[drip] = CRGB::Black;
		
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
CHSV color;
color.h = 100;
color.s = 255;
color.v = 255;
longDripFill(color, 10, 100);
rainbowWipe(50,10,10);
colorWipe(CRGB::Green,10);
colorWipe(CRGB::Blue,10);

}