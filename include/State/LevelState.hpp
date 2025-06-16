#pragma once

#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"

class LevelState : public State {
    public:
        LevelState(StateStack& stack, Context ctx);
    private:
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        Container mContainer;
};