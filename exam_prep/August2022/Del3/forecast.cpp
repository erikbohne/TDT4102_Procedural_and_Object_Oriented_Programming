#include "forecast.h"
#include "csv.h"
#include "util.h"

#include <cctype>
#include <filesystem>
#include <limits>
#include <memory>
#include <stdexcept>

Forecast::Forecast(AnimationWindow &window, int xpos, int ypos)
    : window{window}, xpos{xpos}, ypos{ypos}
{
}

// Task F1: Forecast layout
//
// Write a function that returns the horizontal pixel offset for each
// day in the forecast. Each day is a 150 pixels wide. If the value of
// the  parameter is invalid, i.e. it is outside the range
int Forecast::get_day_placement(int day)
{
  // BEGIN: F1
  //
  // Write your answer to assignment F1 here, between the // BEGIN: F1
  // and // END: F1 comments. You should remove any code that is
  // already there and replace it with your own.
  if (day < 0 || day > 6) {
    throw std::runtime_error("Day is out of range: " + to_string(day));
  }

  return day * 150;
  // END: F1
}

// Task F2: Capitalize a string
//
// Write a function that capitalizes the first character of a string such that capitalize("trondheim") == "Trondheim". This function only needs to change the first character of the string. Remember that the function toupper can be used to change a char value to uppercase.
string Forecast::capitalize(string word)
{
  // BEGIN: F2

  word[0] = toupper(word[0]);

  return word;

  // END: F2
}

// Task F3: Precipitation statistics
//
// Write a function that calculates the total amount of precipitation
// expected across all the days covered in the forecast and save the
// result in the total_precip class variable. When this function is
// called, total_precip is 0.
//
// To do this, iterate over the days vector in the current
// Forecast class instance. Remember that the days vector is
// defined as vector&lt;unique_ptr&lt;Days&gt;&gt; days in forecast.h. To get
// the amount of precipitation expected for a day, use the public
// precip_amount variable of the Days class
// instance.
void Forecast::precip_statistics()
{
  // BEGIN: F3
  double total_precip = 0;

  for (const auto& day : days) {
    total_precip += day.get()->precip_amount;
  }

  this->total_precip = total_precip;

  // END: F3
}

// Task F4: Temperature statistics
//
// Write a function that calculates the maximum, minimum and average
// temperatures expected for the days included in the forecast and save
// the resulting values in the max_temp, min_temp and avg_temp
// class member variables respectively. When this function is called
// max_temp and min_temp are set to the minimum and maximum values
// supported by the C++ double type
// respectively.
//
// As in the previous tasks, iterate over the days vector
// and access the temp member variable of the Day class instance to
// retrieve the temperature expected for a day.
void Forecast::temp_statistics()
{
  // BEGIN: F4
  double total_temp = 0;
  for (const auto& day : days) {
    if (day.get()->temp > max_temp) {
      max_temp = day.get()->temp;
    }
    if (day.get()->temp < min_temp) {
      min_temp = day.get()->temp;
    }
    total_temp += day.get()->temp;
  }

  avg_temp = total_temp / days.size();

  // END: F4
}

// Task F5: Wind statistics
//
// Write a function that finds the windiest day of the week and save
// the result to the windiest_day class member variable. Keep in mind
// that we are interested in identifying the day number (i.e., an
// integer between 0-6) and not the actual wind
// speed.
//
// The wind speed for a day can be found in the public wind_speed
// member variable of the Day class instances.
void Forecast::wind_statistics()
{
  // BEGIN: F5
  int max_wind = 0;
  int index = 0;
  int day_idx = 0;
  for (const auto& day : days) {
    if (day.get()->wind_speed > max_wind) {
      max_wind = day.get()->wind_speed;
      day_idx = index;
    }
    index++;
  }

  windiest_day = day_idx;

  // END: F5
}

void Forecast::show_statistics()
{
  const int y_offset = 200;
  window.draw_text({xpos, ypos + y_offset}, "Weekly statistics");
  window.draw_text({xpos, ypos + y_offset + 20}, "Temperatures (min/max/avg)",
                   TDT4102::Color::black, 10);
  window.draw_text({xpos, ypos + y_offset + 35}, "Total precipitation",
                   TDT4102::Color::black, 10);
  window.draw_text({xpos, ypos + y_offset + 50}, "Windiest day",
                   TDT4102::Color::black, 10);

  const int values_pos = 170;
  window.draw_text({xpos + values_pos, ypos + y_offset + 20},
                   format_value(min_temp, 1, UNIT_DC) + " / " +
                       format_value(max_temp, 1, UNIT_DC) + " / " +
                       format_value(avg_temp, 1, UNIT_DC),
                   TDT4102::Color::black, 10);
  window.draw_text({xpos + values_pos, ypos + y_offset + 35},
                   format_value(total_precip, 1, UNIT_MM),
                   TDT4102::Color::black, 10);
  window.draw_text({xpos + values_pos, ypos + y_offset + 50},
                   format_weekday(windiest_day), TDT4102::Color::black, 10);
}

// |
// | END OF ASSIGNMENTS
// |

void Forecast::calc_statistics()
{
  temp_statistics();
  precip_statistics();
  wind_statistics();
}

// Reads a weather forecast CSV file corresponding to the city
void Forecast::load_city(string city)
{
  cur_city = city;

  string weather_data = get_resource_path("forecasts", city + ".csv");
  weather_data.erase(weather_data.begin()); // remove trailing dot in nthe beginning
  ifstream f(weather_data);
  csv::CsvParser parser(f);
  auto it = csv::init_csv(
      parser, weather_data,
      {"day", "temp", "wind_dir", "wind_speed", "symbol", "percip_amount"});

  days.clear();

  int day_seq = 0;
  while (it != parser.end()) {
    auto row = *it;
    // cout << "Reading line " << stoi(row[0]) << " " << stod(row[1]) << ","
    //      << stod(row[2]) << "," << stod(row[3]) << "," << row[4] << ","
    //      << stod(row[5]) << endl;
    days.push_back(make_unique<Day>(
        window, xpos + get_day_placement(day_seq), ypos, city, stoi(row[0]),
        stod(row[1]), stod(row[2]), stod(row[3]), row[4], stod(row[5])));
    it++;
    day_seq++;
  }

  max_temp = std::numeric_limits<double>::min();
  min_temp = std::numeric_limits<double>::max();
  avg_temp = 0;
  total_precip = 0;
  windiest_day = 0;

  calc_statistics();
}

// Assignment comment: Remember that you need to pass the unique
// pointer as a reference
void Forecast::show_forecast()
{
  if (cur_city != "") {
    window.draw_text({xpos, 30}, "5 day forecast for " + capitalize(cur_city));
    for (auto &d : days) {
      d->show_day();
    }
    show_statistics();
  }
}

