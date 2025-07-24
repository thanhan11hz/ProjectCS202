#include "Entity/Physics.hpp"

Physics::Physics() : mVelocity({0,0}), mPosition({0,0}), mIsGround(false), mIsRight(true) {}

void Physics::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 Physics::getPosition() const {
    return mPosition;
}
        
void Physics::setVelocity(Vector2 velocity) {
    mVelocity = velocity;
}
        
void Physics::setVelocity(float vx, float vy) {
    mVelocity = {vx, vy};
}
        
Vector2 Physics::getVelocity() const {
    return mVelocity;
}
        
void Physics::accelerate(Vector2 dv) {
    mVelocity += dv;
}
        
void Physics::accelerate(float vx, float vy) {
    mVelocity += {vx, vy};
}
        
void Physics::applyGravity(float dt) {
    if (!mIsGround) {
        accelerate(0, Gravity * dt);
    }
}

void Physics::applyDrag(float dt) {
    float lambda = mIsGround ? Friction : AirDrag;
    float delta = mVelocity.x * lambda * dt;
    if (std::fabs(mVelocity.x) <= delta) {
        mVelocity.x = 0.f;
    } else mVelocity.x -= std::copysign(delta, mVelocity.x);
}

void Physics::update(float dt) {
    applyGravity(dt);
    applyDrag(dt);
    mPosition += mVelocity * dt;
    if (mIsGround) {
        if (mVelocity.x >= Eps) mIsRight = true;
        else if (mVelocity.x <= -Eps) mIsRight = false;
    }
}

void Physics::startJump(int high) {
    if (mIsGround) {
        mIsGround = false;
        mVelocity.y = - std::sqrt(2.0f * Gravity * high * 48.0f);
    }
}

void Physics::endJump() {
    if (mVelocity.y < 0.f) mVelocity.y *= 0.5f;
}

bool Physics::isRest() {
    return std::fabs(getVelocity().x) < Eps && std::fabs(getVelocity().y) < Eps; 
}

bool Physics::isRunning() {
    return std::fabs(getVelocity().x) >= Eps;
}

bool Physics::isRising() {
    return getVelocity().y < -Eps;
}

bool Physics::isRight() {
    return mIsRight;
}

bool Physics::onGround() {
    return mIsGround;
}

void Physics::setOnGround(bool flag) {
    mIsGround = flag;
}