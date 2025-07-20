#pragma once

#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"

class CharSelectState : public State {
    public:
        CharSelectState(StateStack& stack);
    private:
        int selectedCharacter;
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        Container mContainer;
};