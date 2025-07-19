#include "State/StateStack.hpp"

void StateStack::pushState(StateIdentifier id) {
    mPendingList.emplace_back(Action::PUSH, id);
}

void StateStack::popState() {
    mPendingList.emplace_back(Action::POP);
}
        
void StateStack::clearState() {
    mPendingList.emplace_back(Action::CLEAR);
}
        
void StateStack::update(float dt) {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->update(dt)) break;
    }
    applyPendingChanges();
}
        
void StateStack::draw() {
    for (const auto& itr: mStack) {
        itr->draw();
    }
}
        
void StateStack::handle() {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->handle()) break;
    }
    applyPendingChanges();
}
        
bool StateStack::isEmpty() {
    return mStack.empty();
}
        
std::unique_ptr<State> StateStack::creatState(StateIdentifier id) {
    auto found = mFactories.find(id);
    assert(found != mFactories.end() && "Don't find State ID");
    return found->second();
}
        
void StateStack::applyPendingChanges() {
    for (auto changes: mPendingList) {
        switch (changes.action)
        {
        case Action::PUSH:
            mStack.push_back(creatState(changes.id));
            break;
        case Action::POP:
            if (!mStack.empty()) mStack.pop_back();
            break;
        case Action::CLEAR:
            mStack.clear();
            break;
        default:
            break;
        }
    }
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, StateIdentifier id) : action(action), id(id) {}