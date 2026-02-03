#pragma once

class Time {
    public:
        static void init();
        static void update();

        static float deltaTime();

    private:
        static float s_deltaTime;
};