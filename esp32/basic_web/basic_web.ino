#include <Preferences.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PageBuilder.h>
#include <AutoConnect.h>
#include <Adafruit_NeoPixel.h>

// NOTE: Do not mix up import order
#include "globals.h"
#include "api.h"
#include "html.h"
#include "pixels.h"

// Preferences Settings
Preferences preferences;

// AVR Power Control module
#ifdef __AVR__
#include <avr/power.h>
#endif

// AutoConect Init
WebServer Server;
AutoConnect portal(Server);
AutoConnectConfig Config("snowstake", "snowstake");

// GET api Settings
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

// Split out calls because page builder expects to pass in page arguments
String getApplicationIDArgs(PageArgument& args) {
  return getApplicationID();
}
String getApplicationKeyArgs(PageArgument& args) {
  return getApplicationKey();
}
String getResortIdArgs(PageArgument& args) {
  return getResortId();
}

// Weather Unlocked Details
String getConnectionUrl() {
  String server_address = "http://api.weatherunlocked.com/api/resortforecast/";
  String day_qty_and_hourly_interval = "?hourly_interval=12&num_of_days=1";
  String connectionURL = String(server_address + getResortId() + day_qty_and_hourly_interval + "&app_id=" + getApplicationID() + "&app_key=" + getApplicationKey());
  Serial.printf("Using URL API: %s\n", connectionURL );
  return connectionURL;
}

// WRITE API Settings to preferences
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

// Building page and inserting data
PageElement ROOT_ELM(FPSTR(rootHtml), {
  {"APPID", getApplicationIDArgs },
  {"APPKEY", getApplicationKeyArgs },
  {"RESORTID", getResortIdArgs },
  {"WRITESETTINGS", writeApiSettings }
});
PageBuilder ROOT("/", {ROOT_ELM});

// Main call to API to get weather data
JsonObject GetForecast() {
  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;
  // setup client:
  http_client.begin(wifi_client, getConnectionUrl().c_str());
  int response_code = http_client.GET();
  Serial.printf("[HTTP] GET... code: %d\n", response_code);
  if (response_code == HTTP_CODE_OK) {
    StaticJsonDocument<224> filter;
    
    JsonObject filter_forecast_0 = filter["forecast"].createNestedObject();
    filter_forecast_0["vis_mi"] = true;
    filter_forecast_0["snow_in"] = true;
    filter_forecast_0["rain_in"] = true;
    
    JsonObject filter_forecast_0_base = filter_forecast_0.createNestedObject("base");
    filter_forecast_0_base["freshsnow_in"] = true;
    filter_forecast_0_base["temp_avg_f"] = true;
    
    JsonObject filter_forecast_0_mid = filter_forecast_0.createNestedObject("mid");
    filter_forecast_0_mid["freshsnow_in"] = true;
    filter_forecast_0_mid["temp_avg_f"] = true;
    
    JsonObject filter_forecast_0_upper = filter_forecast_0.createNestedObject("upper");
    filter_forecast_0_upper["freshsnow_in"] = true;
    filter_forecast_0_upper["temp_avg_f"] = true;
     
    DynamicJsonDocument doc(6144);
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
  return blankForcast();
}

// calls get forcast and sets the values
void SetForecastValues() {
  JsonObject forecast = GetForecast();
  char buffer[100];
  serializeJsonPretty(forecast, buffer);
  Serial.println(buffer);
  if (forecast["vis_mi"] > 0) {
    miles_of_visibility = ((int)forecast["vis_mi"]) + 1;
  }
  if (forecast["snow_in"] > 0) {
    inches_of_snow = (((int)forecast["snow_in"]) + 1) / 2;
  }
  if (forecast["rain_in"] > 0) {
    inches_of_rain = ((int)forecast["rain_in"]) + 1;
  }
  if (forecast["base"]["freshsnow_in"] > 0) {
    inches_of_fresh_snow = (((int)forecast["base"]["freshsnow_in"]) + 1);
  }
}

// MAIN LOOP
void loop() {
  portal.handleClient();

  currentMillis = millis();
  if (currentMillis - previousMillis >= period) {
    SetForecastValues();
    previousMillis = currentMillis;
  }
  ShowOnbaordPixel();
  ShowLEDPixels();
  delay(1000);
}

// MAIN SETUP
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
