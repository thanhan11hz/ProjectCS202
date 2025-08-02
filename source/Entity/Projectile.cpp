#include "Entity/Projectile.hpp"
#include "World/World.hpp"

// FireBall

FireBall::FireBall(bool isRight) {
    mBodyCollide.setLabel(Category::PROJECTILE);
    mBodyCollide.setFilter(Category::NONE);
    mPhysics.setDensity(2.0f);
    mBodyCollide.setStatic(false);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FIREBALL), 9, 9);

    if (!isRight) mSpeedX *= -1;
}

void FireBall::update(float dt) {
    if (isDie()) return;
    if (mPhysics.onGround()) {
        mPhysics.startJump(3);
    }
    MovingEntity::update(dt);
    mPhysics.accelerate({mSpeedX, 0});
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
        mWorld.addEffect(std::move(ExplosionEffect::spawnExplosionEffect(mPhysics.getPosition())));
    }

    if ((side == Side::LEFT || side == Side::RIGHT) && otherLabel == Category::BLOCK) {
        if (!mPhysics.onGround()) setDie(true);
        mWorld.addEffect(std::move(ExplosionEffect::spawnExplosionEffect(mPhysics.getPosition())));
    }

    if (side == Side::BOTTOM && otherLabel == Category::BLOCK) {

    }
}

Vector2 FireBall::getSize() {
    return {27, 27};
}

std::string FireBall::getTag() {
    return "FireBall";
}

std::unique_ptr<FireBall> FireBall::spawnFireBall(Vector2 position, bool isRight) {
    std::unique_ptr<FireBall> mFireBall = std::make_unique<FireBall>(isRight);
    mFireBall->mPhysics.setPosition(position);
    return std::move(mFireBall);
}

// BowserFire

BowserFire::BowserFire() {
    mBodyCollide.setLabel(Category::PROJECTILE);
    mBodyCollide.setFilter(static_cast<Category>(Category::BLOCK | Category::ITEM | Category::ENEMY));
    mBodyCollide.setStatic(false);
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