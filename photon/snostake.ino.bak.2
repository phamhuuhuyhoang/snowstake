// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include <HttpClient.h>
#include <ArduinoJson.h>
SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 11
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
#define DELAY_VALUE 500
const pin_t LED_PIN=D7; // onboard LED

// Prototypes for local build, ok to leave in for Build IDE
//void rainbow(uint8_t wait);
//uint32_t Wheel(byte WheelPos);



void setup() {
    // Define which pin is output:
    // pinMode(LED_PIN, OUTPUT);

    // Init LED Strip of Pixels
    pixels.begin();
    pixels.clear();

    // pixels.setBrightness(128);
    // pixels.show(); // Initialize all pixels to 'off'
}

void loop() {
    // digitalWrite(LED_PIN, HIGH);
    for(i=0;i<12;i+=1){
        pixels.setPixelColor(i,128);
        pixels.setBrightness(10);
        pixels.show();
        delay(DELAY_VALUE);
        pixels.clear();
    }
    // digitalWrite(LED_PIN,LOW);
}


uint32_t InchesOfSnow() {
    // Weatherunlocked ID, Key, and Resort Code:
    const String app_id="77183a51";
    const String app_key="";
    const String resort_id="206004"; // Stevens Pass
    
    unsigned int nextTime = 0;    // Next time to contact the server
    HttpClient http;
    http.useHTTP10(true);
    http.begin("http://api.weatherunlocked.com/api/resortforecast/206004?app_id=77183a51&app_key=");
    http.GET();
    
    // Parse response
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getStream());
    
    // End connection and return parsed results
    http.end();
    // Return values
    // Snow inches:
    // return doc["forecast"][0]["snow_in"].as<long>();
    return doc["forecast"][0]["vis_mi"].as<long>();
}