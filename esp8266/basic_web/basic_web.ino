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
// Adding interval adds additional detail when 6 or 12 are chosen. 
// number of days greatly decreses the amount of data returned.
String addition_parameters = "?hourly_interval=12&num_of_days=1";
String app_id         = ("&app_id=" + String(SECRET_APP_ID));
String app_key        = ("&app_key=" + String(SECRET_APP_KEY));
String resort_id      = SECRET_RESORT_ID;
String connectionURL = String(server_address + addition_parameters + resort_id + app_id + app_key);

////// Declaring NeoPixel variables. ///////////
#define LED_PIN 12
#define LED_COUNT 11
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t LED_BRIGHTNESS = 50; // 1-100
const uint32_t LED_RED    = pixels.Color( 255, 0, 0);
const uint32_t LED_GREEN  = pixels.Color( 0, 255, 0);
const uint32_t LED_BLUE   = pixels.Color( 0, 0, 255);
const uint32_t LED_PURPLE = pixels.Color( 153, 0, 153);
const uint32_t LED_WHITE  = pixels.Color( 255, 255, 255);
const uint32_t LED_BROWN  = pixels.Color( 139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color( 255, 255, 0);
const uint32_t LED_GRAY   = pixels.Color( 143, 188, 143);
const uint32_t LED_BLACK  = pixels.Color( 0, 0, 0);
uint32_t LED_GROUND_COLOR = LED_GREEN;

// Defining Snow, Visibility, and Rain:
uint16_t inches_of_snow      = 0;
uint16_t inches_of_rain      = 0;
uint16_t miles_of_visibility = 0;

// MAIN SETUP:
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

// MAIN LOOP:
int counter = 0;
void loop() {
  currentMillis = millis();
  digitalWrite(LED_BUILTIN, HIGH);  
  Serial.println(++counter);

  // checks if its been two minutes before it queries the api again.
  if(currentMillis - previousMillis >= period){
    SetForecastValues();
    previousMillis = currentMillis;
  }
  ShowLEDPixels();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

uint16_t Incrementing_Pixels(){
  return abs(counter % LED_COUNT);
}

void SetForecastValues(){
  JsonObject forecast = GetForecast();
  Serial.println(forecast);
  if(forecast["vis_mi"] > 0){ miles_of_visibility = ((int)forecast["vis_mi"]) +1; }
  if(forecast["snow_in"] > 0){ inches_of_snow = (((int)forecast["snow_in"]) +1) /2; }
  if(forecast["rain_in"] > 0){ inches_of_rain = ((int)forecast["rain_in"]) +1; }
}

JsonObject GetForecast(){
  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;

  // setup client:
  http_client.begin(wifi_client, connectionURL.c_str());
  int response_code = http_client.GET();
  Serial.printf("[HTTP] GET... code: %d\n", response_code);
  if (response_code == HTTP_CODE_OK) {
    StaticJsonDocument<80> filter;
    JsonObject filter_forecast_0 = filter["forecast"].createNestedObject();
    filter_forecast_0["vis_mi"] = true;
    filter_forecast_0["snow_in"] = true;
    filter_forecast_0["rain_in"] = true;

    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, wifi_client, DeserializationOption::Filter(filter));
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
    }
    http_client.end();
    return doc["forecast"][0];
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http_client.errorToString(response_code).c_str());
  }
  
  JsonObject blank_forcast = {};
  blank_forcast["vis_mi"] = 0;
  blank_forcast["snow_in"] = 0;
  blank_forcast["rain_in"] = 0;
  return blank_forcast;
}

void ShowLEDPixels() {
  pixels.clear();
  pixels.setPixelColor(0, GROUND_COLOR());
  for(uint16_t LED=1; LED < LED_COUNT -1; LED++) {
    if (LED<=inches_of_snow) {
      pixels.setPixelColor(LED, LED_WHITE);
    } else {
      pixels.setPixelColor(LED, SKY_COLOR());
    }
  }
  // Setting the sun weather:
  pixels.setPixelColor(LED_COUNT-1, SUN_COLOR());
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

uint32_t SKY_COLOR(){
  if(inches_of_rain > 1){
    return LED_PURPLE;
  }
  return LED_BLUE;
}

uint32_t SUN_COLOR(){
  if (miles_of_visibility <= 2){
    return LED_PURPLE;
  } else if (miles_of_visibility <= 5){
    return LED_GRAY;
  }
  return LED_YELLOW;
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
