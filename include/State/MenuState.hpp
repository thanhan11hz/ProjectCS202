#pragma once

#include <raylib.h>
#include "Global.hpp"
#include "World/World.hpp"
#include "State/State.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Container.hpp"

class MenuState : public State {
    public:
        MenuState(StateStack& stack);
    private:
        virtual void draw();
        virtual bool update(float dt);
        virtual bool handle();
        Container mContainer;
        Container mContainer_gamemode;
        Button* muteButton;
        Button* loadButton;
        bool gamemode;
};