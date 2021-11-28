// Setting looping for checking API
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long period = 120000; // two minutes

// Defining Snow, Visibility, and Rain
uint16_t inches_of_snow      = 0;
uint16_t inches_of_fresh_snow = 0;
uint16_t inches_of_rain      = 0;
uint16_t miles_of_visibility = 0;
