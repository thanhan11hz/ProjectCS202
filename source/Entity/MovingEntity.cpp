#include "Entity/MovingEntity.hpp"

MovingEntity::MovingEntity() : mFootCollide(this), mAnim(nullptr, 16, 16) {
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
    mCheckStandingMovingBlock = false;
}

void MovingEntity::setDie(bool flag) {
    mIsDie = flag;
}
        
bool MovingEntity::isDie() {
    return mIsDie;
}

void MovingEntity::handleFootCollision(Collide other) {
    mPhysics.setOnGround(true);
    if (other.getLabel() == Category::BLOCK && other.getOwner()->getTag() == "VertMovingBlock" && !mCheckStandingMovingBlock) {
        mPhysics.setPosition({mPhysics.getPosition().x, other.getHitBox().y - getSize().y});
    }

    if (other.getLabel() == Category::BLOCK && other.getOwner()->getTag() == "HoriMovingBlock" && !mCheckStandingMovingBlock) {
        mPhysics.setPosition(mPhysics.getPosition() + other.getOwner()->mPhysics.getVelocity() * timePerFrame);
        mCheckStandingMovingBlock = true;
    }
}

void MovingEntity::setAfterBlock(bool flag) {
    afterBlock = flag;
}
        
bool MovingEntity::isAfterBlock() {
    return afterBlock;
}