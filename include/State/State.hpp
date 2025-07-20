#pragma once

#include "State/StateIdentifier.hpp"
#include "Global.hpp"

class StateStack;

class State {
    public:
        State(StateStack& stack);
        virtual ~State() = default;
        virtual void draw() = 0;
        virtual bool update(float dt) = 0;
        virtual bool handle() = 0;

    protected:
        void requestStackPush(StateIdentifier id);
        void requestStackPop();
        void requestStackClear();

    private:
        StateStack* mStack;

};