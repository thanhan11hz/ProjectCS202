#pragma once

#include <queue>

#include "Command/Command.hpp"

class CommandQueue {
    public:
        void push(const Command& command);
        Command pop();
        bool isEmpty();
    private:
        void handle() {};
        std::queue<Command> mCommand;
};