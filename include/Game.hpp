#pragma once

#include <raylib.h>
#include <iostream>
#include <cmath>

#include "Global.hpp"
#include "InputHandler.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "State/StateStack.hpp"
#include "State/Context.hpp"
#include "State/MenuState.hpp"
#include "State/LevelState.hpp"

class Game {
    public:
        Game();
        void run();
        void inputProcess();
        void update(float dt);
        void draw();

    private:
        InputHandler mInput;
        StateStack mStateStack;

};