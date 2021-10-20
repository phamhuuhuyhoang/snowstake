// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include <HttpClient.h>
#include <ArduinoJson.h>
SYSTEM_MODE(AUTOMATIC);

/**
* Declaring the variables.
*/
#define PIXEL_PIN D6
#define PIXEL_COUNT 11
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
#define DELAY_VALUE 500
const pin_t LED_PIN=D7; // onboard LED
unsigned int nextTime = 0;    // Next time to contact the server

HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    { "Accept" , "application/json" },
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    Serial.begin(9600);
    // Init LED Strip of Pixels
    pixels.begin();
    pixels.clear();
}

void loop() {
    if (nextTime > millis()) {
        return;
    }
    // Request path and body can be set at runtime or at setup.
    request.hostname = "api.weatherunlocked.com";
    request.port = 80;
    request.path = "/api/resortforecast/206004?app_id=77183a51&app_key=";

    // Get request
    http.get(request, response, headers);
    // Particle.publish("Application>\tResponse status: ");
    // Particle.publish(String(response.status));

    // Particle.publish("Application>\tHTTP Response Body: ");
    Particle.publish(response.body);
    // Parse response
    // DynamicJsonDocument doc(2048);
    // String serializedJson
    // deserializeJson(doc, response.body);
    uint16_t inches=4; // response.body;
    // uint16_t inches=3;

    Particle.publish(String(inches));
    
    pixels.clear();
    for(uint16_t i=0; i < inches; i++) {
      pixels.setPixelColor(i, 128);
      pixels.setBrightness(100);
    }
    pixels.show();

    nextTime = millis() + 30000;
}