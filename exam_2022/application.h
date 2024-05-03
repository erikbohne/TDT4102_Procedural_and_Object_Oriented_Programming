#pragma once

#include "AnimationWindow.h"
#include "forecast.h"
#include "image_renderer.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/fl_ask.H>

class Application
{
public:
  Application();
  void main_loop();

private:
  AnimationWindow window;

  Fl_Hold_Browser in_cities;
  Fl_Button btn_show;
  Forecast forecast;

  unique_ptr<Forecast> cur_city;

  void load_cities();
  void change_city(string city);

  static void change_city_cb(Fl_Widget *, void *ref2)
  {
    auto ref = static_cast<Application *>(ref2);
    int selected_item = ref->in_cities.value();
    if (selected_item > 0) {
      string city = ref->in_cities.text(ref->in_cities.value());
      ref->change_city(city);
    } else {
      fl_alert("Please select a city.");
    }
  }
};

