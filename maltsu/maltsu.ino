#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#define NUM_LEDS 30
#define LED_PIN D6

#define SSID "Maltsu"

CRGB leds[NUM_LEDS];

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleColour(){
    String colourString = server.arg("colour");
    int colour = colourString.toInt();
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = colour;
    }
    FastLED.show();
}

void setup(){
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

    Serial.begin(115200);
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
