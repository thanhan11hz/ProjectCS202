#pragma once

#include "State/State.hpp"
#include "World/World.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Container.hpp"

class CompleteState: public State {
    public:
        CompleteState(StateStack& stack);
        
    private:
        Container mContainer_level;
        Container mContainer_game;

        virtual void draw();
        virtual bool update(float dt);
        virtual bool handle();
};