#include "Entity/Entity.hpp"

void Entity::update(float dt) {
    mPhysics.update(dt);
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    mCollide.setHitBox({
        postion.x - size.x / 2.0f,
        postion.y - size.y / 2.0f,
        size.x,
        size.y
    });
}