#include "FastLED.h"

//number of leds in strip
#define NUM_LEDS 20

//define data (yellow) and clock (green)
#define DATA_PIN 2
#define CLOCK_PIN 3

// Define the array of ledsCRGB leds[NUM_LEDS];
CRGB leds[NUM_LEDS];
CRGB display[NUM_LEDS];


void setup() {
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(display, NUM_LEDS);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
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

void longDrip(CHSV color, uint16_t length, int wait){
	CRGB gradient[length + 1];
	CHSV black;
	black.s = 0;
	black.v = 0;
	int i;
	
	fill_gradient (gradient, 0, black, length, color);
	for (i=0; i < NUM_LEDS + length + 1 ; i++){
		if(i <= length){
			memmove (&leds[1], &leds[0], (sizeof(CRGB) * i));
			memcpy(&leds[0], &gradient[length - i], sizeof(CRGB));
			show();
			delay(wait);
		} else if (i < NUM_LEDS + 1) {
			memmove (&leds[i-length], &leds[i-length-1], sizeof(gradient));
			show();
			delay(wait);
		} else{
			memmove (&leds[i-length], &leds[i-length-1], (sizeof(CRGB) * (NUM_LEDS + length - i)));
			show();
			delay(wait);
		}
	}
}



void longDripFillFade(CHSV color, uint16_t length, int fillRate, int wait){
	CRGB gradient[length + 1];
	CHSV black;
	black.s = 0;
	black.v = 0;
	int i;
	int i2;
	int fall = NUM_LEDS;
	int full = 0;
	
	while (fall > 0){
		fill_gradient (gradient, 0, black, length, color);
		for (i=0; i <= fall + length ; i++){
			if(i <= length){
				memmove (&leds[1], &leds[0], (sizeof(CRGB) * i));
				memcpy(&leds[0], &gradient[length - i], sizeof(CRGB));
				show();
				delay(wait);
			} else if (i <= (fall - fillRate)) {
				memmove (&leds[i-length], &leds[i-length-1], sizeof(gradient));
				show();
				delay(wait);
			} else if ( i <= (fall + fillRate)){
				memmove (&leds[i-length], &leds[i-length-1], (sizeof(CRGB) * (fall + length - i)));
				for (i2=0; i2 < fillRate; i2++){
					leds[NUM_LEDS - full - i2] = color;
				}
				show();
				delay(wait);
					if ( i = fall + fillRate){
						fadeToBlackBy(leds, full, 10);
					}
			} else {

			}
			
		}
		
		full = full + fillRate;
		fall = NUM_LEDS - full;
		
		for (i=0; i < full; i++){
			leds[NUM_LEDS-i] = color;
			
		
		}
		*/

		
	}
}


void longDripFill(CHSV color, uint16_t length, int fillRate, int wait){
	CRGB gradient[length + 1];
	CHSV black;
	black.s = 0;
	black.v = 0;
	int i;
	int i2;
	int fall = NUM_LEDS;
	int full = 0;
	
	while (fall > 0){
		fill_gradient (gradient, 0, black, length, color);
		for (i=0; i < fall + length + 1; i++){
			
if(i <= length){
				memmove (&leds[1], &leds[0], (sizeof(CRGB) * i));
				memcpy(&leds[0], &gradient[length - i], sizeof(CRGB));
				show();
				delay(wait);
			} else if (i < (fall - fillRate + 1)) {
				memmove (&leds[i-length], &leds[i-length-1], sizeof(gradient));
				show();
				delay(wait);
			} else if ( i < (fall + fillRate + 1)){
				memmove (&leds[i-length], &leds[i-length-1], (sizeof(CRGB) * (fall + length - i)));
				for (i2=0; i2 < fillRate; i2++){
					leds[NUM_LEDS - full - i2] = color;
				}
				show();
				delay(wait);
			} else {

			}
			
			
		}
		full = full + fillRate;
		fall = NUM_LEDS - full;
		for (i=0; i < full; i++){
			leds[NUM_LEDS-i] = color;
		}
		
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
color.h = 150;
color.s = 255;
color.v = 100;
longDripFill(color, 2, 2, 100);
//rainbowWipe(50,10,10);
colorWipe(CRGB::Green,10);
//colorWipe(CRGB::Blue,10);


}