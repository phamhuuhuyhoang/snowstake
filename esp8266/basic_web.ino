// This #include statement was automatically added by the Particle IDE.
#include <SPI.h>
#include <Arduino.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>
#include "arduino_secrets.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

/////// please enter your sensitive data in arduino_secrets.h ////////
/////// WiFi Settings ///////
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;

////// Setting looping for checking API ///////
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
unsigned long period = 120000; // two minutes

////// Setting nesting limit //////////
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20

/////// Weather Unlocked Details /////
String server_address = SECRET_SERVER_ADDRESS;
int    server_port    = String(SECRET_SERVER_PORT).toInt();
String app_id         = ("?app_id=" + String(SECRET_APP_ID));
String app_key        = ("&app_key=" + String(SECRET_APP_KEY));
String resort_id      = SECRET_RESORT_ID;

////// Declaring NeoPixel variables. ///////////
#define LED_PIN 12
#define LED_COUNT 11
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t LED_BRIGHTNESS = 50; // 1-100
const uint32_t LED_RED = pixels.Color( 255, 0, 0);
const uint32_t LED_GREEN = pixels.Color( 0, 255, 0);
const uint32_t LED_BLUE = pixels.Color( 0, 0, 255);
const uint32_t LED_WHITE = pixels.Color( 255, 255, 255);
const uint32_t LED_BROWN = pixels.Color( 139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color( 255, 255, 0);
const uint32_t LED_GRAY = pixels.Color( 143, 188, 143);
uint32_t LED_GROUND_COLOR = LED_GREEN;

int counter = 0;
uint16_t inches_of_snow; 

void setup() {
  // Activity LED PIN
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Serial port out: USED with <particle serial monitor>
  Serial.begin(115200);

  // connecting to Wifi:
  ConnectWifi();

  // Init LED Strip of Pixels
  pixels.begin();
  pixels.show();
}

void loop() {
  currentMillis = millis();
  digitalWrite(LED_BUILTIN, HIGH);  
  Serial.println(++counter);

  // checks if its been two minutes before it queries the api again.
  if(currentMillis - previousMillis >= period || !inches_of_snow){
    inches_of_snow = GetInchesOfSnow();
    if(!inches_of_snow){delay(10000); }
    previousMillis = currentMillis;
  }
  ShowLEDPixels(inches_of_snow);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

uint16_t Incrementing_Pixels(){
  return abs(counter % LED_COUNT);
}

uint16_t GetInchesOfSnow(){
  String connectionURL = String(server_address + resort_id + app_id + app_key);
  uint16_t forecast_0_vis_mi = 0;

  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;

  // setup client:
  http_client.begin(wifi_client, connectionURL.c_str());
  int response_code = http_client.GET();
  Serial.printf("[HTTP] GET... code: %d\n", response_code);
  if (response_code == HTTP_CODE_OK) {

    // set size and buffer:
    int len = http_client.getSize();
    uint8_t buff[128] = { 0 };

    // Get stream from Wifi Client:
    // WiFiClient * stream = &wifi_client;

    StaticJsonDocument<48> filter;
    filter["forecast"][0]["vis_mi"] = true;

    // ReadLoggingStream loggingStream(wifi_client, Serial);
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, wifi_client, DeserializationOption::Filter(filter));
    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
    }

    // Serialize for troubleshooting:
    // Serial.println( serializeJson(doc, Serial) );
    
    JsonArray forecast = doc["forecast"];
    Serial.print("Visual Miles: ");
    // Grabs the first visable miles for now.
    forecast_0_vis_mi = forecast[0]["vis_mi"];
    Serial.println(forecast_0_vis_mi);
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http_client.errorToString(response_code).c_str());
  }
  http_client.end();
  if(forecast_0_vis_mi > 0){ inches_of_snow = forecast_0_vis_mi; }
  return inches_of_snow;
}

void ShowLEDPixels(uint16_t inches) {
  pixels.clear();
  pixels.setPixelColor(0, GROUND_COLOR());
  for(uint16_t LED=1; LED < LED_COUNT -1; LED++) {
    if (LED<=inches) {
      pixels.setPixelColor(LED, LED_WHITE);
    } else {
      pixels.setPixelColor(LED, LED_BLUE);
    }
  }
  // Setting the sun weather:
  pixels.setPixelColor(LED_COUNT-1, LED_YELLOW);
  pixels.setBrightness(LED_BRIGHTNESS);
  pixels.show();
}

uint32_t GROUND_COLOR(){
  if(LED_GROUND_COLOR == LED_GREEN) {
    LED_GROUND_COLOR = LED_BROWN;
  } else { 
    LED_GROUND_COLOR = LED_GREEN;
  }
  return LED_GROUND_COLOR;
}

void ConnectWifi(){
  // Connect to Wifi
  WiFi.begin(ssid, pass);
  Serial.printf("Connecting to: %d\n", ssid);
  int i = 0;
  Serial.println("Waiting 15 seconds...");
  delay(15000);
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 
}
