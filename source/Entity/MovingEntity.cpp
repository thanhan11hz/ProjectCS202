#include "Entity/MovingEntity.hpp"

MovingEntity::MovingEntity() : mFootCollide(this), mAnim(nullptr, 48, 48) {
    mFootCollide.setLabel(Category::FOOT);
    mFootCollide.setFilter(Category::NONE);
}

void MovingEntity::update(float dt) {
    Entity::update(dt);
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    mFootCollide.setHitBox({
        postion.x + 4,
        postion.y + size.y,
        size.x - 8,
        1
    });
}

void MovingEntity::setDie(bool flag) {
    mIsDie = flag;
}
        
bool MovingEntity::isDie() {
    return mIsDie;
}

void MovingEntity::handleFootCollision() {
    mPhysics.setOnGround(true);
}