#pragma once

#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"

class PauseState : public State {
    public:
        PauseState(StateStack& stack);
    private:
        bool confirmMode;
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        Container mContainer;
        Container mConfirmContainer;
};