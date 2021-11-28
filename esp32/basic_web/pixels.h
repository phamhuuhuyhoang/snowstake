#include <Adafruit_NeoPixel.h>

#define ONBOARD_LED_PIN 18
#define ONBOARD_LED_COUNT 1
#define LED_PIN 17
#define LED_COUNT 11

// Declaring NeoPixel variables.
Adafruit_NeoPixel onboard_pixel(ONBOARD_LED_COUNT, ONBOARD_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// NeoPixel Colors
const uint32_t LED_RED    = pixels.Color( 255, 0, 0);
const uint32_t LED_GREEN  = pixels.Color( 0, 255, 0);
const uint32_t LED_BLUE   = pixels.Color( 0, 0, 255);
const uint32_t LED_PURPLE = pixels.Color( 153, 0, 153);
const uint32_t LED_WHITE  = pixels.Color( 255, 255, 255);
const uint32_t LED_BROWN  = pixels.Color( 139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color( 255, 255, 0);
const uint32_t LED_GRAY   = pixels.Color( 143, 188, 143);
const uint32_t LED_BLACK  = pixels.Color( 0, 0, 0);

// NeoPixel Defaults
uint32_t LED_BRIGHTNESS = 50; // 1-100
uint32_t LED_BRIGHTNESS_OFF = 0; // 1-100
uint32_t LED_HEALTH_BRIGHTNESS = 50; // 1-100
uint32_t LED_HEALTH_COLOR = LED_BLUE;
uint32_t LED_GROUND_COLOR = LED_GREEN;
uint32_t LED_COLOR = LED_BLACK;


uint32_t SKY_COLOR() {
  if (inches_of_rain > 1) {
    return LED_PURPLE;
  }
  return LED_BLUE;
}

uint32_t SUN_COLOR() {
  if (miles_of_visibility <= 2) {
    return LED_PURPLE;
  } else if (miles_of_visibility <= 5) {
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
  for (uint16_t LED = 1; LED < LED_COUNT - 1; LED++) {
    if (LED <= inches_of_snow) {
      pixels.setPixelColor(LED, LED_WHITE);
    } else {
      pixels.setPixelColor(LED, SKY_COLOR());
    }
  }
  // Setting the sun weather:
  pixels.setPixelColor(LED_COUNT - 1, SUN_COLOR());
  pixels.setBrightness(LED_BRIGHTNESS);
  pixels.show();
}
