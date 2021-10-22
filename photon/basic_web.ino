// This #include statement was automatically added by the Particle IDE.
#include <ArduinoJson.h>
#include <Particle.h>
#include <neopixel.h>
#include <HttpClient.h>
#include "arduino_secrets.h"
SYSTEM_MODE(AUTOMATIC);


////// Setting nesting limit //////////
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20

/////// Weather Unlocked Details /////
String server_address = SECRET_SERVER_ADDRESS;
int    server_port    = String(SECRET_SERVER_PORT).toInt();
String app_id         = ("?app_id=" + String(SECRET_APP_ID));
String app_key        = ("&app_key=" + String(SECRET_APP_KEY));
String resort_id      = SECRET_RESORT_ID;
String connectionURL = String(resort_id + app_id + app_key);

/**
* Declaring NeoPixel variables.
*/
#define PIXEL_PIN D6
#define PIXEL_COUNT 11
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
const pin_t HEALTH_LED=D7; // Photon Health LED
const uint32_t LED_BRIGHTNESS = 50; // 1-100
const uint32_t LED_RED = pixels.Color( 255, 0, 0);
const uint32_t LED_GREEN = pixels.Color( 0, 255, 0);
const uint32_t LED_BLUE = pixels.Color( 0, 0, 255);
const uint32_t LED_WHITE = pixels.Color( 255, 255, 255);
const uint32_t LED_BROWN = pixels.Color( 139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color( 255, 255, 0);
const uint32_t LED_GRAY = pixels.Color( 143, 188, 143);

/**
* Declaring HttpClient variables.
*/
HttpClient http;
// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    { "Content-Type", "application/json" },
    { "Accept" , "application/json" },
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};
http_request_t request;
http_response_t response;



int counter = 0;

void setup() {
    // Activity LED PIN
    pinMode(HEALTH_LED,OUTPUT);
    
    // Serial port out: USED with <particle serial monitor>
    Serial.begin(9600);
    
    // Init LED Strip of Pixels
    pixels.begin();
    pixels.show();
}

void loop() {
    Serial.printlnf("testing %d", ++counter);
    digitalWrite(HEALTH_LED,HIGH);
    ShowLEDPixels(GetInchesOfSnow());
    digitalWrite(HEALTH_LED,LOW);
    delay(60s);
}

uint16_t GetInchesOfSnow(){
    // Request path and body can be set at runtime or at setup.
    request.hostname = server_address;
    request.port = server_port;
    request.path = connectionURL;

    // Get request
    http.get(request, response, headers);
    
    // Setting up filter to limit the data coming in to parse
    StaticJsonDocument<24> filter;
    filter["forecast"][0]["vis_mi"] = true;
    
    //const char* filterforecast = filter["forecast"];
    // Serial.println( filterforecast );
    DynamicJsonDocument doc(1024);
    
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, response.body.c_str(), DeserializationOption::Filter(filter));
    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return 0;
    }
    
    const char* forecast = doc["forecast"];
    Serial.println( forecast );
    // Particle.publish( String(["forecast"][0]["vis_mi"].as<char*>()) );
    uint16_t inches=1;
    return inches;
}

void ShowLEDPixels(uint16_t inches) {
    pixels.clear();
    // Set ground color
    pixels.setPixelColor(0, LED_GREEN);
    for(uint16_t i=1; i < PIXEL_COUNT -1; i++) {
        if (i<=inches) {
            pixels.setPixelColor(i, LED_WHITE);
        } else {
            pixels.setPixelColor(i, LED_BLUE);
        }
    }
    // Setting the sun weather:
    pixels.setPixelColor(PIXEL_COUNT-1, LED_YELLOW);
    
    //
    pixels.setBrightness(LED_BRIGHTNESS);
    pixels.show();
}
