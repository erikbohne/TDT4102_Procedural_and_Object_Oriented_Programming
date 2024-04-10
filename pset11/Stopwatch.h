#pragma once
#include <iostream>
#include <chrono>

// This class abstracts some (somewhat) nasty code that is
// definitely outside the scope of this course.
// Its main purpose is to return the amount of time 
// taken by the program in main.cpp

// Calling start() starts the stopwatch
// Calling stop() stops it and returns the amount of time
// that has elapsed since start() was called in seconds

class Stopwatch {
    std::chrono::time_point<std::chrono::steady_clock> startTime;

public:
    void start();
    double stop();
};