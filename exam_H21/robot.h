#pragma once

#include "std_lib_facilities.h"
#include "AnimationWindow.h"

struct Robot {
  Robot(string name, Point pos, Color color);

  string name;
  Point pos;
  Color color;
};

