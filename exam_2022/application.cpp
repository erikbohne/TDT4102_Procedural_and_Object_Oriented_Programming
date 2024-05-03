#include "application.h"
#include "forecast.h"
#include "util.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Widget.H>
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

vector<string> list_directory(string dir)
{
  vector<string> res;
  for (const auto &dir : filesystem::directory_iterator(dir)) {
    if (dir.is_regular_file() && dir.path().extension() == ".csv") {
      res.push_back(dir.path().stem().string());
    }
  }
  return res;
}

void Application::change_city(string city)
{
  forecast.load_city(city);
}

Application::Application()
    : window(50, 50, 900, 700, "Weather forecast"),
      in_cities(580, 220, 300, 200, "Select city to forecast"),
      btn_show(580, 440, 300, 30, "Show city"), forecast(window, 30, 30)
{
  string dirname = get_resource_path("forecasts", "");
  auto dirs = list_directory(dirname);
  if (dirs.size() == 0) {
    throw runtime_error(
        "forecasts directory does not contain any files ending with .csv");
  }

  for (auto d : dirs) {
    in_cities.add(d.c_str());
  }

  in_cities.align(FL_ALIGN_TOP_LEFT);

  window.add(in_cities);

  btn_show.callback(&Application::change_city_cb, this);
  window.add(btn_show);
}

