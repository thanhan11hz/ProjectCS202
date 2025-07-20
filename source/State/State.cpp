#include "State/State.hpp"
#include "State/StateStack.hpp"

State::State(StateStack& stack) : mStack(&stack) {}

void State::requestStackPush(StateIdentifier id) {
    mStack->pushState(id);
}
        
void State::requestStackPop() {
    mStack->popState();
}
        
void State::requestStackClear() {
    mStack->clearState();
}
