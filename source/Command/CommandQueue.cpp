#include "Command/CommandQueue.hpp"

void CommandQueue::push(const Command& command) {
    mCommand.push(command);
}

Command CommandQueue::pop() {
    Command command = mCommand.front();
    mCommand.pop();
    return command;
}

bool CommandQueue::isEmpty() {
    return mCommand.empty();
}

