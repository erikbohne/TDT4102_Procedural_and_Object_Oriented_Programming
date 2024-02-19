#pragma once
#include "AnimationWindow.h"

void bouncingBall();

struct BouncingBallConfig {
    int color_up;
    int color_down;
    int velocity;
};

istream& operator>>(istream& is, BouncingBallConfig& cfg);