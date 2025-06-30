#include "Entity/Entity.hpp"

Entity::Entity(int hitPoint) : mHitPoint(hitPoint), mVelocity({0,0}), mPosition({0,0}), mIsJump(false), mIsGround(true) {}

void Entity::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 Entity::getPosition() const {
    return mPosition;
}
        
void Entity::setVelocity(Vector2 velocity) {
    mVelocity = velocity;
}
        
void Entity::setVelocity(float vx, float vy) {
    mVelocity = {vx, vy};
}
        
Vector2 Entity::getVelocity() const {
    return mVelocity;
}
        
void Entity::accelerate(Vector2 dv) {
    mVelocity += dv;
}
        
void Entity::accelerate(float vx, float vy) {
    mVelocity += {vx, vy};
}
        
void Entity::repair(int points) {
    mHitPoint += points;
}
        
void Entity::damage(int points) {
    mHitPoint = std::max(0, mHitPoint - points);
}
        
void Entity::destroy() {
    mHitPoint = 0;
}
        
int Entity::getHitPoints() {
    return mHitPoint;
}
        
bool Entity::isDestroy() {
    return mHitPoint <= 0;
}

void Entity::applyGravity(float dt) {
    if (!mIsGround) {
        accelerate(0, Gravity * dt);
    }
}

void Entity::applyDrag(float dt) {
    float lambda = mIsGround ? Friction : AirDrag;
    if (std::fabs(mVelocity.x) > Eps) {
        float delta = mVelocity.x * lambda * dt;
        if (std::fabs(mVelocity.x) <= delta)
            mVelocity.x = 0.f;
        else
            mVelocity.x -= std::copysign(delta, mVelocity.x);
    }
}

void Entity::updateCurrent(float dt) {
    applyGravity(dt);
    applyDrag(dt);
    mPosition += mVelocity * dt;
}

void Entity::startJump() {
    if (mIsGround && !mIsJump) {
        mIsGround = false;
        mIsJump = true;
        mVelocity.y = - std::sqrt(2.0f * Gravity * 128.f);
    }
}

void Entity::endJump() {
    if (mVelocity.y < 0.f) mVelocity.y *= 0.5f;
}

bool Entity::isRest() {
    return std::fabs(getVelocity().x) < Eps && std::fabs(getVelocity().y) < Eps; 
}

bool Entity::isRunning() {
    return std::fabs(getVelocity().x) >= Eps;
}

bool Entity::isRising() {
    return getVelocity().y < -Eps;
}