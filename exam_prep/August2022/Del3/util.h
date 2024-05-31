#pragma once

#include "std_lib_facilities.h"
#include <filesystem>

enum Unit {
  UNIT_MS, // Meters per second, m/s
  UNIT_MM, // Millimeteres, mm
  UNIT_DC  // Degrees celcius, °C
};

string get_unit(Unit unit);
string format_value(double value, int decimals, Unit unit);
string format_weekday(int weekday_num);
string format_wind_dir(double heading);

string get_resource_path(string folder, string file);
vector<string> list_directory(string& dir);

