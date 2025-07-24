#include "Entity/Entity.hpp"

Entity::Entity() : mCollide(this) {

}

void Entity::update(float dt) {
    mPhysics.update(dt);
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    mCollide.setHitBox({
        postion.x,
        postion.y,
        size.x,
        size.y
    });
}