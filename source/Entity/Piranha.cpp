#include "Entity/Piranha.hpp"
#include "World/World.hpp"
#include "Entity/Character.hpp"

Piranha::Piranha(Type type) : mType(type) {
    mPhysics.setDensity(0.0f);
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setDensity(0.0f);
    mAnim.setFrameSize({16, 24});
    mAnim.setFrameDuration(0.5f);
    if (mType == Type::GREEN_PIRANHA) {
        mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::PIRANHA), getSize().x / 3, getSize().y / 3);
    } else {
        mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::PIRANHA2), getSize().x / 3, getSize().y / 3);
    }
}

Piranha::Piranha(const nlohmann::json& j) {
    mPhysics.setDensity(0.0f);
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setDensity(0.0f);
    mAnim.setFrameSize({16, 24});
    mAnim.setFrameDuration(0.5f);
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mMove = static_cast<Move>(j["move"].get<unsigned int>());
    mType = static_cast<Type>(j["type"].get<unsigned int>());
    if (mType == Type::GREEN_PIRANHA) {
        mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::PIRANHA), getSize().x / 3, getSize().y / 3);
    } else {
        mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::PIRANHA2), getSize().x / 3, getSize().y / 3);
    }
    attackTimer = j["attackTimer"].get<float>();
    mSpeed = j["speed"].get<float>();
    mFixedPoint = j["fixedPoint"].get<Vector2>();
}

void Piranha::update(float dt) {
    Enemy::update(dt);
    if (!isActive()) return;
    if (isDie()) return;
    MovingEntity::update(dt);
    if (mMove == Move::FLY) mPhysics.accelerate({0, mSpeed});
    if (mPhysics.getPosition().y > mFixedPoint.y) {
        mPhysics.setPosition(mFixedPoint);
        mSpeed = -50.0f;
    }
    updateMove(dt);
    mAnim.update(dt);
}
        
void Piranha::handle() {

}
        
void Piranha::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, BLACK);
}

void Piranha::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (side == Side::TOP && otherLabel == MARIO) {
        if (mMove == Move::FLY && mSpeed == -50.0f) mSpeed = 50.0f;
    }

    if (otherLabel == Category::PROJECTILE && other.getOwner()->getTag() == "FireBall") {
        setDie(true);
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
    }

    if (otherLabel == Category::MARIO && static_cast<Character*>(other.getOwner())->isImmortal()) {
        setDie(true);
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
    }
}
        
Vector2 Piranha::getSize() {
    return {48, 72};
}

void Piranha::updateMove(float dt) {
    if (mMove == Move::ATTACK) {
        if (attackTimer < attackTime) {
            attackTimer += dt;
        }
        else {
            attackTimer = 0.0f;
            mMove = Move::FLY;
            mSpeed = 50.0f;
        }
    } else {
        if (mPhysics.getPosition().y < mFixedPoint.y - 48 * 2) {
            mPhysics.setPosition({mPhysics.getPosition().x, mFixedPoint.y - 48 * 2});
            mPhysics.setVelocity({0, 0});
            mMove = Move::ATTACK;
        }
    }
}

std::unique_ptr<Piranha> Piranha::spawnPiranha1(Vector2 position) {
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>(Type::GREEN_PIRANHA);
    mPiranha->setFixedPoint(position);
    return std::move(mPiranha);
}

std::unique_ptr<Piranha> Piranha::spawnPiranha2(Vector2 position) {
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>(Type::BLUE_PIRANHA);
    mPiranha->setFixedPoint(position);
    return std::move(mPiranha);
}

void Piranha::setFixedPoint(Vector2 point) {
    mPhysics.setPosition(point);
    mFixedPoint = point;
}

std::string Piranha::getTag() {
    return "Piranha";
}

void Piranha::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"move", (unsigned int) mMove},
        {"type", (unsigned int) mType},
        {"attackTimer", attackTimer},
        {"speed", mSpeed},
        {"fixedPoint", mFixedPoint},
        {"class", "piranha"}
    };
}