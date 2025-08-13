#include "Entity/FlyingKoopa.hpp"
#include "World/World.hpp"

FlyingKoopa::FlyingKoopa() {
    mBodyCollide.setLabel(Category::ENEMY);
    mBodyCollide.setFilter(Category::NONE);
    mPhysics.setDensity(0.0f);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FLYING_KOOPA), 16, 24);
}
        
FlyingKoopa::FlyingKoopa(const nlohmann::json& j) {
    mBodyCollide.setLabel(Category::ENEMY);
    mBodyCollide.setFilter(Category::NONE);
    mPhysics.setDensity(0.0f);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FLYING_KOOPA), 16, 24);
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mFixedPoint = j["fixedPoint"].get<Vector2>();
    mSpeed = j["speed"].get<float>();
}
        
void FlyingKoopa::update(float dt) {
    Enemy::update(dt);
    if (!isActive()) return;
    if (isDie()) return;
    Entity::update(dt);
    if (mPhysics.getPosition().y > mFixedPoint.y + 48.0f * 3) {
        mPhysics.setPosition({mFixedPoint.x, mFixedPoint.y + 48.0f * 3});
        mSpeed = -50.0f;
    } else if (mPhysics.getPosition().y < mFixedPoint.y - 48.0f * 3) {
        mPhysics.setPosition({mFixedPoint.x, mFixedPoint.y - 48.0f * 3});
        mSpeed = 50.0f;
    }
    mPhysics.accelerate({0, mSpeed});
    mAnim.update(dt);
    mPhysics.setOnGround(false);
}
        
void FlyingKoopa::handle() {

}
        
void FlyingKoopa::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, false);
}

void FlyingKoopa::handleCollision(Side side, Collide other) {
    if (other.getLabel() == Category::PROJECTILE && other.getOwner()->getTag() == "Fireball") {
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::KOOPA_RED_DEATH), true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "300"));
        mWorld.receivePoint(300);
    }

    if (other.getLabel() == Category::MARIO && side == Side::TOP) {
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::KOOPA_RED_SHELL), false));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "300"));
        mWorld.receivePoint(300);
    }
}
        
Vector2 FlyingKoopa::getSize() {
    return {48, 72};
}

std::string FlyingKoopa::getTag() {
    return "FlyingKoopa";
}

void FlyingKoopa::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"speed", mSpeed},
        {"fixedPoint", mFixedPoint},
        {"class", "flyingKoopa"}
    };
}