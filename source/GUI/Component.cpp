#include "GUI/Component.hpp"

bool Component::isActive() {
    return mIsActive;
}
    
bool Component::isSelected() {
    return mIsSelected;
}

void Component::select() { 
    mIsSelected = true;  
}

void Component::deselect() { 
    mIsSelected = false; 
}

void Component::activate() { 
    mIsActive = true;  
}

void Component::deactivate() { 
    mIsActive = false; 
}
