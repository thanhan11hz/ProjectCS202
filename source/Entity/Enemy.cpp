#include "Entity/Enemy.hpp"
#include "World/World.hpp"

Enemy::Enemy() {
    mBodyCollide.setStatic(false);
}

void Enemy::setActive(bool flag) {
    mIsActive = flag;
}
        
bool Enemy::isActive() {
    return mIsActive;
}

void Enemy::update(float dt) {
    Vector2 screenPos = GetWorldToScreen2D(mPhysics.getPosition(), mWorld.getCamera());
    if (screenPos.x <= targetWidth + 50) {
        mIsActive = true;}
}

std::string Enemy::getTag() {
    return "Enemy";
}