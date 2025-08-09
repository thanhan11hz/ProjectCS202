#include "Entity/Piranha.hpp"
#include "World/World.hpp"
#include "Entity/Character.hpp"

Piranha::Piranha() {
    mPhysics.setDensity(0.0f);
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setDensity(0.0f);
    mAnim.setFrameSize({16, 24});
    mAnim.setFrameDuration(0.5f);
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
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>();
    mPiranha->setTexture(Resource::mTexture.get(TextureIdentifier::PIRANHA));
    mPiranha->setFixedPoint(position);
    return std::move(mPiranha);
}

std::unique_ptr<Piranha> Piranha::spawnPiranha2(Vector2 position) {
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>();
    mPiranha->setTexture(Resource::mTexture.get(TextureIdentifier::PIRANHA2));
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

void Piranha::setTexture(Texture2D& texture) {
    mAnim.setTexture(&texture, 16, 24);
    mAnim.setRepeating(true, false);
    mAnim.restart();  
}