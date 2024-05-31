#pragma once

#include "std_lib_facilities.h"

#include "AnimationWindow.h"
#include "image_renderer.h"

class Day
{

public:
  Day(AnimationWindow &window, int xpos, int ypos, string city, int day,
      double temp, double wind_dir, double wind_speed, string symbol,
      double percip_amount);

  void show_day();

private:
  AnimationWindow &window;
  [[maybe_unused]] int xpos;
  [[maybe_unused]] int ypos;

public:
  string city;
  int day;
  double temp;
  double wind_dir;
  double wind_speed;

private:
  ImageRenderer symbol;

public:
  double precip_amount;

private:
  void draw_text(Point pos, string text);
};

