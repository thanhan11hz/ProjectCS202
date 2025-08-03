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

BowserFire::BowserFire(bool isRight) {
    mBodyCollide.setLabel(Category::PROJECTILE);
    mBodyCollide.setFilter(static_cast<Category>(Category::BLOCK | Category::ITEM | Category::ENEMY));
    mBodyCollide.setStatic(false);
    mPhysics.setDensity(0.0f);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::BOWSER_FIRE), 24, 8);
    this->isRight = isRight;
    if (!isRight) mSpeed *= -1;
}

void BowserFire::update(float dt) {
    if (isDie()) return;
    mPhysics.accelerate({mSpeed, 0});
    MovingEntity::update(dt);
    Vector2 screenPos = GetWorldToScreen2D(mPhysics.getPosition(), mWorld.getCamera());
    if (screenPos.x < -100.0f || screenPos.x > 100 + targetWidth) setDie(true);
}

void BowserFire::handle() {

}
        
void BowserFire::draw() {
    mAnim.draw(mPhysics.getPosition(), 6.0f, 0.0f, !isRight);
}

void BowserFire::handleCollision(Side side, Collide other) {
    
}

Vector2 BowserFire::getSize() {
    return {144, 48};
}

std::string BowserFire::getTag() {
    return "BowserFire";
}

std::unique_ptr<BowserFire> BowserFire::spawnBowserFire(Vector2 position, bool isRight) {
    std::unique_ptr<BowserFire> mBowserFire = std::make_unique<BowserFire>(isRight);
    mBowserFire->mPhysics.setPosition(position);
    return std::move(mBowserFire);
}