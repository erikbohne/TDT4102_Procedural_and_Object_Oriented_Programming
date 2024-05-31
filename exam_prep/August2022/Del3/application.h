#pragma once

#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"
#include "forecast.h"
#include "image_renderer.h"
#include "util.h"

class Application
{
public:
  Application();
  void main_loop();

private:
  AnimationWindow window;

  string dir = get_resource_path("forecasts", "");
  vector<string> dirs = list_directory(dir);

  TDT4102::DropdownList in_cities;
  TDT4102::Button btn_show;
  Forecast forecast;
 
 
  
  unique_ptr<Forecast> cur_city;

  // void load_cities();
  void change_city(string city);

  void change_city_cb() {
    string city = in_cities.getValue();
    if (city.empty()) {
      window.show_error_dialog("Please select a city.");
    }
    else {
      change_city(city);      
    }
  }
};

