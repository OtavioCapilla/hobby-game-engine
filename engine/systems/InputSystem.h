#pragma once

class InputSystem {
    public:
        static void update();
        static bool quitRequested();
        static bool isKeyDown(int key);

    private:
        static bool s_quit;
};