#pragma once
#include "AnimationWindow.h"

void bouncingBall();

struct BouncingBallConfig {
    int color_up;
    int color_down;
    int velocity;
};

std::map<int, Color> color_map = {
    {1, Color::red},
    {2, Color::green},
    {3, Color::blue},
    {4, Color::yellow}
};

istream& operator>>(istream& is, BouncingBallConfig& cfg);