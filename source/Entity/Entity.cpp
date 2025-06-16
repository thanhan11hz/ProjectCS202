#include "Entity/Entity.hpp"

Entity::Entity(int hitPoint = 1) : mHitPoint(hitPoint), mVelocity() {}
        
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

void Entity::updateCurrent(float dt) {

}