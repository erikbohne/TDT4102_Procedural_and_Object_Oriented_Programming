#include "application.h"
#include "forecast.h"

#include <filesystem>
#include <stdexcept>

// The main loop of the program that redraws the grid and shows the
// next frame.
void Application::main_loop()
{
  while (!window.should_close()) {

    forecast.show_forecast();
    window.next_frame();
  }
}

void Application::change_city(string city)
{
  forecast.load_city(city);
}

Application::Application()
    : window(50, 50, 900, 700, "Weather forecast"),
      in_cities(TDT4102::Point{580, 220}, 300, 200, dirs),
      btn_show(TDT4102::Point{580, 440}, 300, 30, "Show city"), forecast(window, 30, 30)
{
 
  
  window.add(in_cities);

  btn_show.setCallback(std::bind(&Application::change_city_cb, this));
  window.add(btn_show);
}

