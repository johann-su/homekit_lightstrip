#include <Arduino.h>
#include <FastLED.h>
#include <HomeSpan.h>
#include "identify.h"
#include "led.h"

#define LED_PIN 13
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define NUM_LEDS 55

#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

void setup()
{
    Serial.begin(115200);

    homeSpan.enableOTA(); // OTA updates with default password "homespan-ota"
    homeSpan.begin(Category::Lighting, "Homekit Lightstrip");
    homeSpan.setQRID("MOIN");
    homeSpan.enableAutoStartAP();

    delay(3000); // sanity delay
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    new SpanAccessory();
    new Custom_Identify("RGB Led Strip", "Navabase", "187", "CoolLightStripV1", "0.9", 0);
    new Service::HAPProtocolInformation();
    new Characteristic::Version("1.1.0");
    new Custom_RgbLED();
}

void loop()
{
    homeSpan.poll();
}