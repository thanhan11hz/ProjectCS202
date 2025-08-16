#pragma once 

#include "State/State.hpp"
#include "World/World.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Container.hpp"
#include "Global.hpp"
class GameOverState: public State {
    public:
        GameOverState(StateStack& stack);
        
    private:
        Container mContainer;
        virtual void draw();
        virtual bool update(float dt);
        virtual bool handle();
};