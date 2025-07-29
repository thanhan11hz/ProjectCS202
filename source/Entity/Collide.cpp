#include "Entity/Collide.hpp"

Collide::Collide(Entity* owner) : mOwner(owner) {
    
}

void Collide::setStatic(bool flag) {
    mStatic = flag;
}

bool Collide::isStatic() const {
    return mStatic;
}

void Collide::setLabel(Category label) {
    mLabel = label;
}
        
void Collide::setFilter(Category filter) {
    mFilter = filter;
}

Category Collide::getLabel() const {
    return mLabel;
}

void Collide::setHitBox(Rectangle hitBox) {
    mHitBox = hitBox;
}

Rectangle Collide::getHitBox() const {
    return mHitBox;
}

Entity* Collide::getOwner() const {
    return mOwner;
}

// This function correctly checks for bitmask overlap
bool Collide::canOverlap(Collide other) {
    return (mLabel & other.mFilter) != 0 && (mFilter & other.mLabel) != 0;
}