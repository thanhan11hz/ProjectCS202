#include "Entity/Entity.hpp"

Entity::Entity() : mBodyCollide(this) {
    mBodyCollide.setFilter(Category::FOOT);
}

void Entity::update(float dt) {
    mPhysics.update(dt);
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    mBodyCollide.setHitBox({
        postion.x,
        postion.y,
        size.x,
        size.y
    });
}

std::string Entity::getTag() {
    return "Entity";
}

void Entity::handleFootCollision(Collide other) {
    
}