#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#include "html.h"

#define NUM_LEDS 30
#define LED_PIN D6

#define SSID "Maltsu"

CRGB leds[NUM_LEDS];
int colour;
int spacing;
int animationType;

enum AnimationType {
    STATIC,
    SPIN,
};

ESP8266WebServer server(80);

void animateStatic(){
    for(int i=0; i<NUM_LEDS; i++){
        leds[i] = colour;
    }

    FastLED.show();
}

void animateSpin(){
    static unsigned long transitionTime = 0;
    static unsigned int state = 0;
    unsigned long currentTime = millis();

    if(currentTime >= transitionTime){
        ++state %= spacing;
        transitionTime = currentTime + 100;
    }

    for(int i=0; i<NUM_LEDS; i++){
        if(i % spacing == state) leds[i] = colour;
        else leds[i] = 0;
    }

    FastLED.show();
}

void animate(){
    switch(animationType){
        default:
        case STATIC:
            animateStatic();
            break;
        case SPIN:
            animateSpin();
            break;
    }
}

void setAnimation(AnimationType newAnimation){
    animationType = newAnimation;
}

void setColour(int newColour){
    colour = newColour;
}

void setSpacing(int newSpacing){
    spacing = newSpacing;
}

void handleRoot(){
    server.send(200, "text/html", html_index);
}

void handleColour(){
    String colourString = server.arg("colour");
    int colour = colourString.toInt();
    setColour(colour);

    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
}

void setup(){
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    setColour(0xff4400);
    setSpacing(4);
    setAnimation(SPIN);

    Serial.println("Configuring access point...");

    WiFi.softAP(SSID);

    IPAddress IP(192, 168, 1, 1);
    IPAddress Mask(255, 255, 255, 0);
    WiFi.softAPConfig(IP, IP, Mask);

    server.on("/", handleRoot);
    server.on("/colour", handleColour);
    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    server.handleClient();
    animate();
}
