#pragma once

#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"

class InstructionState : public State {
    public:
        InstructionState(StateStack& stack);
    private:
        int mCurrentPage;
        int mMaxPage;
        void setupPage(int page);
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        Container mContainer;
        Button* muteButton;
        Label* tracker;
        Label* description;
};
