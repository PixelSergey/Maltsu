#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN D6

CRGB leds[NUM_LEDS];

void setup(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::White;
        FastLED.show();
        delay(50);
        leds[i] = CRGB::Black;
        FastLED.show();
    }
}
