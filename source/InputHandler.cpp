#include "InputHandler.hpp"

InputHandler::InputHandler() {
    mKeyBinding[KEY_LEFT] = Action::MOVE_LEFT;
    mKeyBinding[KEY_RIGHT] = Action::MOVE_RIGHT;
    mKeyBinding[KEY_UP] = Action::MOVE_UP;
    mKeyBinding[KEY_DOWN] = Action::MOVE_DOWN;
    mKeyBinding[KEY_D] = Action::MOVE_LEFT;
    mKeyBinding[KEY_A] = Action::MOVE_RIGHT;
    mKeyBinding[KEY_W] = Action::MOVE_UP;
    mKeyBinding[KEY_S] = Action::MOVE_DOWN;
    mKeyBinding[KEY_LEFT_CONTROL] = Action::FIRE;
    mKeyBinding[KEY_RIGHT_CONTROL] = Action::FIRE;
    mKeyBinding[KEY_LEFT_SHIFT] = Action::FIRE;
    mKeyBinding[KEY_RIGHT_SHIFT] = Action::FIRE;
}
        
void InputHandler::handle() {
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ++itr) {
        if (IsKeyPressed(itr->first)) ;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

    }
}
        
void InputHandler::assignedKey(Action action, int key) {
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ) {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else 
            ++itr; 
    }
}
        
int InputHandler::getAssignedKey(Action action) {
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ++itr) {
        if (itr->second == action) return itr->first;
    }
    return KEY_NULL;
}
