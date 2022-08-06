#include <Preferences.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PageBuilder.h>
#include <AutoConnect.h>
#include <Adafruit_NeoPixel.h>


/////// Preferences Settings ///////
Preferences preferences;
/////// Preferences Settings ///////


/////// AVR Power Control module /////////
#ifdef __AVR__
#include <avr/power.h>
#endif
/////// AVR Power Control module /////////


////// AutoConect Init ////////
WebServer Server;
AutoConnect portal(Server);
AutoConnectConfig Config("snowstake","snowstake");
////// AutoConect Init ////////


////// AutoConect Config API Page ////////
AutoConnectAux   aux("/snowstake_api", "SnowStake API");
ACText(header, "API settings");
ACText(caption, "Please go to Weather Unlocked and setup your API account and Ski Resort settings. URL: https://developer.weatherunlocked.com/skiresort");
////// AutoConect Config API Page ////////


////// Setting looping for checking API ///////
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
unsigned long period = 120000; // two minutes
////// Setting looping for checking API ///////


////// Declaring NeoPixel variables. ///////////
#define ONBOARD_LED_PIN 18
#define ONBOARD_LED_COUNT 1
Adafruit_NeoPixel onboard_pixel(ONBOARD_LED_COUNT, ONBOARD_LED_PIN, NEO_GRB + NEO_KHZ800);
#define LED_PIN 17
#define LED_COUNT 11
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
////// Declaring NeoPixel variables. ///////////


////// NeoPixel Colors ///////////
const uint32_t LED_RED    = pixels.Color( 255, 0, 0);
const uint32_t LED_GREEN  = pixels.Color( 0, 255, 0);
const uint32_t LED_BLUE   = pixels.Color( 0, 0, 255);
const uint32_t LED_PURPLE = pixels.Color( 153, 0, 153);
const uint32_t LED_WHITE  = pixels.Color( 255, 255, 255);
const uint32_t LED_BROWN  = pixels.Color( 139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color( 255, 255, 0);
const uint32_t LED_GRAY   = pixels.Color( 143, 188, 143);
const uint32_t LED_BLACK  = pixels.Color( 0, 0, 0);
////// NeoPixel Colors ///////////


////// NeoPixel Defaults ///////////
uint32_t LED_BRIGHTNESS = 50; // 1-100
uint32_t LED_BRIGHTNESS_OFF = 0; // 1-100
uint32_t LED_HEALTH_BRIGHTNESS = 50; // 1-100
uint32_t LED_HEALTH_COLOR = LED_BLUE;
uint32_t LED_GROUND_COLOR = LED_GREEN;
uint32_t LED_COLOR = LED_BLACK;
////// NeoPixel Defaults ///////////


////// Defining Snow, Visibility, and Rain  //////////
uint16_t inches_of_snow      = 0;
uint16_t inches_of_rain      = 0;
uint16_t miles_of_visibility = 0;
////// Defining Snow, Visibility, and Rain  //////////


////// Root webpage to enable people to change API data  //////////
static const char rootHtml[] PROGMEM = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF=8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <style type="text/css">
      input[type=text],
      select {
          width: 100%;
          padding: 12px 20px;
          margin: 8px 0;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
      }
      input[type=submit] {
          width: 100%;
          background-color: #4CAF50;
          color: white;
          padding: 14px 20px;
          margin: 8px 0;
          border: none;
          border-radius: 4px;
          cursor: pointer;
      }
      input[type=submit]:hover {
          background-color: #45a049;
      }
      input:required {
          border-color: #800000;
          border-width: 3px;
      }
      input:required:invalid {
          border-color: #c00000;
      }
      div {
          border-radius: 5px;
          background-color: #f2f2f2;
          padding: 20px;
      }
    </style>
    <body>
        <h2>Snowstake API Settings</h2>
        <p>
            Please make sure you have gone to Weather Unlocked and setup you API Settings. Please use the Developer URL here: <a href="https://developer.weatherunlocked.com/" target="_blank"> WeatherUnlocked.com</a>. Fill in the fields below and submit to
            enable Snowstake.
        </p>
        </br>
        <div>
            <form action="/">
                <label for="apid">Developer Application ID: Required</label>
                <input type="text" id="apid" name="applicationid" placeholder="ABC12345" value="{{APPID}}" required>
                <label for="apkey">Application Key: Required</label>
                <input type="text" id="apkey" name="applicationkey" placeholder="619b9d50..." value="{{APPKEY}}" required>
                <label for="rsid">Resort ID: Required</label>
                <input type="text" id="rsid" name="resortid" placeholder="206004" value="{{RESORTID}}" required>
                <input type="submit" class="button" value="Submit">
                {{WRITESETTINGS}}
        </div>
    </body>
    </html>
)" ;
////// Root webpage to enable people to change API data  //////////


///// GET api Settings //////
String getApplicationID() {
  try {
    String appId = preferences.getString("applicationid", "");
    Serial.printf("getApplicationID: %s\n", appId );
    return appId;
  } catch (const std::exception& e) {
    Serial.printf("getApplicationID error: %s\n", e.what() );
    return "<p>";
  }
}
String getApplicationIDArgs(PageArgument& args) {return getApplicationID();}
String getApplicationKey() {
  try {
    String appKey = preferences.getString("applicationkey", "");
    Serial.printf("getApplicationKey: %s\n", appKey );
    return appKey;
  } catch (const std::exception& e) {
    Serial.printf("getApplicationKey error: %s\n", e.what() );
    return "<p>";
  }
}
String getApplicationKeyArgs(PageArgument& args) {return getApplicationKey();}
String getResortId() {
  try {
    String resortId = preferences.getString("resortid", "");
    Serial.printf("getResortId: %s\n", resortId );
    return resortId;
  } catch (const std::exception& e) {
    Serial.printf("getResortId error: %s\n", e.what() );
    return "<p>";
  }
}
String getResortIdArgs(PageArgument& args) {return getResortId();}
///// GET api Settings //////


/////// Weather Unlocked Details /////
String getConnectionUrl() {
  String server_address = "http://api.weatherunlocked.com/api/resortforecast/";
  String day_qty_and_hourly_interval = "?hourly_interval=12&num_of_days=1";
  String connectionURL = String(server_address + getResortId() + day_qty_and_hourly_interval + "&app_id=" + getApplicationID() + "&app_key=" + getApplicationKey());
  Serial.printf("Using URL API: %s\n", connectionURL );
  return connectionURL;
}
/////// Weather Unlocked Details /////


////// WRITE API Settings to SPIFFS ////////
String writeApiSettings(PageArgument& args) {
  if (args.hasArg("applicationid")) {
    preferences.putString("applicationid", args.arg("applicationid")); 
  }
  if (args.hasArg("applicationkey")) {
    preferences.putString("applicationkey", args.arg("applicationkey")); 
  }
  if (args.hasArg("resortid")) {
    preferences.putString("resortid", args.arg("resortid")); 
  }
  delay(10);
  return "<p>";
}
////// WRITE API Settings to SPIFFS ////////


////// Building page and inserting data //////
PageElement ROOT_ELM(FPSTR(rootHtml), {
    {"APPID", getApplicationIDArgs },
    {"APPKEY", getApplicationKeyArgs },
    {"RESORTID", getResortIdArgs },
    {"WRITESETTINGS", writeApiSettings }
});
PageBuilder ROOT("/", {ROOT_ELM});
////// Building page and inserting data //////


///// Main call to API to get weather data /////
JsonObject GetForecast(){
  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;

  // setup client:
  http_client.begin(wifi_client, getConnectionUrl().c_str());
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
///// Main call to API to get weather data /////


///// calls get forcast and sets the values  /////
void SetForecastValues(){
  JsonObject forecast = GetForecast();
  Serial.println(forecast);
  if(forecast["vis_mi"] > 0){ miles_of_visibility = ((int)forecast["vis_mi"]) +1; }
  if(forecast["snow_in"] > 0){ inches_of_snow = (((int)forecast["snow_in"]) +1) /2; }
  if(forecast["rain_in"] > 0){ inches_of_rain = ((int)forecast["rain_in"]) +1; }
}
///// calls get forcast and sets the values  /////


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

uint32_t GROUND_COLOR() {
  LED_GROUND_COLOR = (LED_GROUND_COLOR == LED_GREEN) ? LED_BLUE : LED_GREEN;
  return LED_GROUND_COLOR;
}

uint32_t HEALTH_COLOR() {
  LED_COLOR = (LED_COLOR == LED_HEALTH_COLOR) ? LED_BLACK : LED_HEALTH_COLOR;
  return LED_COLOR;
}

void ShowOnbaordPixel() {
  onboard_pixel.clear();
  onboard_pixel.setPixelColor(0, HEALTH_COLOR());
  onboard_pixel.setBrightness(LED_HEALTH_BRIGHTNESS);
  onboard_pixel.show();
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

//// MAIN LOOP: ////
int counter = 0;
void loop() {
  portal.handleClient();
  currentMillis = millis();

  if(currentMillis - previousMillis >= period){
    SetForecastValues();
    previousMillis = currentMillis;
  }

  ShowOnbaordPixel();
  ShowLEDPixels();
  delay(1000);
}
//// MAIN LOOP: ////


//// MAIN SETUP: ////
void setup() {
  delay(1000);  // for stable the module.
  Serial.begin(115200);
  Serial.println();
  preferences.begin("apiSettings", false);

  ROOT.insert(Server);
  Config.title = "SnowStake";
  portal.config(Config);
  if (portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }

  // Init ONBOARD_LED Strip of Pixels
  onboard_pixel.begin();
  onboard_pixel.show();
  // Init LED Strip of Pixels
  pixels.begin();
  pixels.show();
}
//// MAIN SETUP: ////
