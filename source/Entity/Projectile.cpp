#include "Entity/Projectile.hpp"

// FireBall

FireBall::FireBall() {
    mBodyCollide.setLabel(Category::PROJECTILE);
    mBodyCollide.setFilter(Category::NONE);
    mPhysics.setDensity(0.0f);
}

void FireBall::update(float dt) {
    if (isDie()) return;
    MovingEntity::update(dt);
    mPhysics.accelerate({100, isDown ? 100.0f : -100.0f});
}

void FireBall::handle() {

}

void FireBall::draw() {
    if (isDie()) return;
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
}

void FireBall::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (otherLabel == Category::ENEMY) {
        setDie(true);
        return;
    }

    if ((side == Side::LEFT || side == Side::RIGHT) && otherLabel == Category::BLOCK) {
        setDie(true);
    }

    if ((side == Side::TOP || side == Side::BOTTOM) && otherLabel == Category::BLOCK) {
        isDown = (side == Side::TOP);
        mLives--;
        if (mLives <= 0) setDie(true);
    }
}

Vector2 FireBall::getSize() {
    return {27, 27};
}

std::string FireBall::getTag() {
    return "FireBall";
}

std::unique_ptr<FireBall> FireBall::spawnFireBall(Vector2 position) {
    std::unique_ptr<FireBall> mFireBall = std::make_unique<FireBall>();
    mFireBall->mPhysics.setPosition(position);
    return std::move(mFireBall);
}

// BowserFire

BowserFire::BowserFire() {
    mBodyCollide.setLabel(Category::PROJECTILE);
    mBodyCollide.setFilter(static_cast<Category>(Category::BLOCK | Category::ITEM | Category::ENEMY));
    mPhysics.setDensity(0.0f);
}

void BowserFire::update(float dt) {
    if (isDie()) return;
    MovingEntity::update(dt);
    mPhysics.accelerate({mSpeed, 0});
}

void BowserFire::handle() {

}
        
void BowserFire::draw() {
    if (isDie()) return;
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
}

void BowserFire::handleCollision(Side side, Collide other) {
    
}

Vector2 BowserFire::getSize() {
    return {72, 24};
}

std::string BowserFire::getTag() {
    return "BowserFire";
}

void BowserFire::setSpeed(float speed) {
    mSpeed = speed;
}

std::unique_ptr<BowserFire> BowserFire::spawnBowserFire(Vector2 position, float speed) {
    std::unique_ptr<BowserFire> mBowserFire = std::make_unique<BowserFire>();
    mBowserFire->mPhysics.setPosition(position);
    mBowserFire->setSpeed(speed);
    return std::move(mBowserFire);
}