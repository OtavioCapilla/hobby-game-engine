#include "Time.h"

#include <chrono>

using HighResClock = std::chrono::high_resolution_clock;

static HighResClock::time_point s_lastTime;

float Time::s_deltaTime = 0.0f;

void Time::init(){
    s_lastTime = HighResClock::now();
}

void Time::update(){
    auto now = HighResClock::now();
    std::chrono::duration<float> delta = now - s_lastTime;
    s_lastTime = now;

    s_deltaTime = delta.count();
}

float Time::deltaTime(){
    return s_deltaTime;
}