#include "State/State.hpp"
#include "State/StateStack.hpp"

State::State(StateStack& stack, Context ctx) : mStack(&stack), mContext(ctx) {}

void State::requestStackPush(StateIdentifier id) {
    mStack->pushState(id);
}
        
void State::requestStackPop() {
    mStack->popState();
}
        
void State::requestStackClear() {
    mStack->clearState();
}
