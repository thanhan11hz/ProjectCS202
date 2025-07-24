#include "World/Collision.hpp"

Collision::Collision() : mCharacter(nullptr) {

}

void Collision::addItem() {
    
}
        
void Collision::addBlock() {

}
        
void Collision::addCharacter(Character* character) {
    mCharacter = character;
}

void Collision::handleCollision() {
    // if (mCharacter)
    // for (int i = 0; i < mMain.size(); ++i) {
    //     for (int j = 0; j < mMain[i].size(); ++j) {
    //         checkCollision(mCharacter->mCollide, mMain[i][j]->mCollide);
    //     }
    // }
}
        
void Collision::checkCollision(Collide A, Collide B) {
    if (!checkBroadPhase(A, B)) return;
    std::pair<Side,Side> side = checkNarrowPhase(A, B);
    if (!A.canOverlap(B)) separate(A, B, side.first, side.second);
    A.getOwner()->handleCollision(side.first, B.getLabel());
    B.getOwner()->handleCollision(side.second, A.getLabel());
}

bool Collision::checkBroadPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    return CheckCollisionRecs(hitBoxA, hitBoxB);
}
        
std::pair<Side,Side> Collision::checkNarrowPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    Rectangle intersection = {
        fmax(hitBoxA.x, hitBoxB.x),
        fmax(hitBoxA.y, hitBoxB.y),
        fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x),
        fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y),
    };
    return {getCollisionSide(hitBoxA, intersection), getCollisionSide(hitBoxB, intersection)};
}
        
void Collision::separate(Collide A, Collide B, Side sideA, Side sideB) {

    if (A.isStatic()) std::swap(A, B);
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    Vector2 position = A.getOwner()->mPhysics.getPosition();

    switch (sideA) {
    case Side::TOP:
        position.y += fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y);
        A.getOwner()->mPhysics.setPosition(position);
        break;
    case Side::BOTTOM:
        position.y -= fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y);
        A.getOwner()->mPhysics.setPosition(position);
        break;
    case Side::LEFT:
        position.x += fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x);
        A.getOwner()->mPhysics.setPosition(position);
        break;
    case Side::RIGHT:
        position.x -= fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x);
        A.getOwner()->mPhysics.setPosition(position);
        break;
    }
}

Side Collision::getCollisionSide(Rectangle hitBox, Rectangle intersection) {
    float top = fabs(hitBox.y - intersection.y);
    float bottom = fabs((hitBox.y + hitBox.height) - (intersection.y + intersection.height));
    float left = fabs(hitBox.x - intersection.x);
    float right = fabs((hitBox.x + hitBox.width) - (intersection.y + intersection.width));
    float overlapX = (left > right) ? left : -right;
    float overlapY = (top > bottom) ? top : -bottom;
    if (fabs(overlapX) < fabs(overlapY) || (fabs(overlapX) == fabs(overlapY) && intersection.width < intersection.height)) {
        return (overlapX > 0) ? Side::LEFT : Side::RIGHT;
    } else {
        return (overlapY > 0) ? Side::TOP : Side::BOTTOM;
    }
}