#pragma once

#include "AnimationWindow.h"
#include "day.h"
#include "std_lib_facilities.h"

class Forecast
{

public:
  Forecast(AnimationWindow &window, int xpos, int ypos);

  void show_forecast();
  void load_city(string city);

private:
  AnimationWindow &window;
  int xpos;
  int ypos;

  string cur_city;

  vector<unique_ptr<Day>> days;

  int get_day_placement(int day);
  string format_number(float num);
  string fomrat_number(int num);
  string capitalize(string word);

  // Statistics
  double max_temp;
  double min_temp;
  double avg_temp;
  double total_precip;
  int windiest_day;

  void show_statistics();
  void calc_statistics();
  void temp_statistics();
  void precip_statistics();
  void wind_statistics();
};

