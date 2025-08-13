#include "Entity/Entity.hpp"

Entity::Entity() : mBodyCollide(this), mFootCollide(this), mAnim(nullptr, 16, 16) {
    mBodyCollide.setFilter(Category::FOOT);
    mFootCollide.setLabel(Category::FOOT);
    mFootCollide.setFilter(Category::NONE);
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
    mFootCollide.setHitBox({
        postion.x + 4,
        postion.y + size.y,
        size.x - 8,
        1
    });
    mCheckStandingMovingBlock = false;
}

std::string Entity::getTag() {
    return "Entity";
}

void Entity::setDie(bool flag) {
    mIsDie = flag;
}
        
bool Entity::isDie() {
    return mIsDie;
}

void Entity::handleFootCollision(Collide other) {
    mPhysics.setOnGround(true);
    if (other.getLabel() == Category::BLOCK && other.getOwner()->getTag() == "VertMovingBlock" && !mCheckStandingMovingBlock) {
        mPhysics.setPosition({mPhysics.getPosition().x, other.getHitBox().y - getSize().y});
    }

    if (other.getLabel() == Category::BLOCK && other.getOwner()->getTag() == "HoriMovingBlock" && !mCheckStandingMovingBlock) {
        mPhysics.setPosition(mPhysics.getPosition() + other.getOwner()->mPhysics.getVelocity() * timePerFrame);
        mCheckStandingMovingBlock = true;
    }
}

void Entity::setAfterBlock(bool flag) {
    afterBlock = flag;
}
        
bool Entity::isAfterBlock() {
    return afterBlock;
}