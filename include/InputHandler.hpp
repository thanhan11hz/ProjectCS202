#pragma once

#include <raylib.h>
#include <iostream>
#include <unordered_map>

#include "Command/Command.hpp"
#include "Command/CommandQueue.hpp"



class InputHandler {
    public:
        enum class Action {
            MOVE_LEFT,
            MOVE_RIGHT,
            MOVE_UP,
            MOVE_DOWN,
            FIRE,
            NONE
        };

        InputHandler();
        void handle();
        void assignedKey(Action action, int key);
        int getAssignedKey(Action action);

    private:
        std::unordered_map<int, Action> mKeyBinding;
        std::unordered_map<Action,Command> mActionBinding;
};