#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#include "html.h"

#define NUM_LEDS 30
#define LED_PIN D6

#define SSID "Maltsu"

CRGB leds[NUM_LEDS];

ESP8266WebServer server(80);

void setColours(int colour){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = colour;
    }
    FastLED.show();
}

void handleRoot(){
    server.send(200, "text/html", html_index);
}

void handleColour(){
    String colourString = server.arg("colour");
    int colour = colourString.toInt();
    setColours(colour);

    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
}

void setup(){
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    // For some reason, this doesn't work first try
    setColours(13172907);
    setColours(13172907);
    setColours(13172907);
    setColours(13172907);

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
}
