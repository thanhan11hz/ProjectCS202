#include "Entity/Piranha.hpp"

Piranha::Piranha() {
    mPhysics.setDensity(0.0f);
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 24});
}

void Piranha::update(float dt) {
    if (isActive()) return;
    if (isDie()) return;
    Enemy::update(dt);
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
        setDie(true);
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
            setMove(Move::FLY);
            mSpeed = 50.0f;
        }
    } else {
        if (mPhysics.getPosition().y <= mFixedPoint.y - 48 * 2) {
            mPhysics.setPosition({mPhysics.getPosition().x, mFixedPoint.y - 48 * 2});
            mPhysics.setVelocity({0, 0});
            setMove(Move::ATTACK);
        }
    }
}

void Piranha::setMove(Move move) {
    Texture2D* texture = nullptr;
    if (move == Move::FLY) texture = &mFly;
    else {
        texture = &mAttack;
    }

    mMove = move;

    if (texture) {
        mAnim.setTexture(texture, getSize().x / 3.0f, getSize().y / 3.0f);
        mAnim.setRepeating(true, false);
        mAnim.restart();
    }
}

std::unique_ptr<Piranha> Piranha::spawnPiranha1(Vector2 position) {
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>();
    mPiranha->mFly = Resource::mTexture.get(TextureIdentifier::PIRANHA_MOVE);
    mPiranha->mAttack = Resource::mTexture.get(TextureIdentifier::PIRANHA_ATTACK);
    mPiranha->setMove(Move::FLY);
    mPiranha->setFixedPoint(position);
    return std::move(mPiranha);
}

std::unique_ptr<Piranha> Piranha::spawnPiranha2(Vector2 position) {
    std::unique_ptr<Piranha> mPiranha = std::make_unique<Piranha>();
    mPiranha->mFly = Resource::mTexture.get(TextureIdentifier::PIRANHA2_MOVE);
    mPiranha->mAttack = Resource::mTexture.get(TextureIdentifier::PIRANHA2_ATTACK);
    mPiranha->setMove(Move::FLY);
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