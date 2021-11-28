
// Slug to return when we get a failed call:
JsonObject blankForcast() {
  JsonObject blank_forcast = {};
  blank_forcast["vis_mi"] = 0;
  blank_forcast["snow_in"] = 0;
  blank_forcast["rain_in"] = 0;
  blank_forcast["base"]["freshsnow_in"] = 0;
  blank_forcast["base"]["temp_avg_f"] = 0;
  blank_forcast["mid"]["freshsnow_in"] = 0;
  blank_forcast["mid"]["temp_avg_f"] = 0;
  blank_forcast["upper"]["freshsnow_in"] = 0;
  blank_forcast["upper"]["temp_avg_f"] = 0;
  return blank_forcast;
}
