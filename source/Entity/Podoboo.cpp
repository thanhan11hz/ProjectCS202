#include "Entity/Podoboo.hpp"

Podoboo::Podoboo() {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({14, 17});
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::PODOBOO), 14, 17);
    mAnim.setRepeating(true, false);
    mAnim.restart(); 
}

void Podoboo::update(float dt) {
    Enemy::update(dt);
    if (!isActive()) return;
    if (isDie()) return;
    MovingEntity::update(dt);
    if (mIsRest) {
        if (mRestTimer > mRestTime) {
            mIsRest = false;
            mRestTimer = 0.0f;
            mPhysics.startJump(8);
        } else mRestTimer += dt;
    } else {
        if (mPhysics.getPosition().y > mRestPoint.y) {
            mPhysics.setPosition({mPhysics.getPosition().x, mRestPoint.y});
            mPhysics.setOnGround(true);
            mIsRest = true;
        } 
    }
    mAnim.update(dt);
}
        
void Podoboo::handle() {

}
        
void Podoboo::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, false, !mPhysics.isRising());
}

void Podoboo::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (side == Side::TOP && otherLabel == Category::MARIO) {
        
    }
}
        
Vector2 Podoboo::getSize() {
    return {42, 51};
}

std::string Podoboo::getTag() {
    return "Podoboo";
}

void Podoboo::setRestPoint(Vector2 position) {
    mPhysics.setPosition(position);
    mRestPoint = position;
}

std::unique_ptr<Podoboo> Podoboo::spawnPodoboo(Vector2 position) {
    std::unique_ptr<Podoboo> mPodoboo = std::make_unique<Podoboo>();
    mPodoboo->setRestPoint(position);
    return std::move(mPodoboo);
}