#include "Entity/Bowser.hpp"

Bowser::Bowser() {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 16});
}

void Bowser::update(float dt) {
    if (isActive()) return;
    if (isDie()) return;
    Enemy::update(dt);
    if (mPhysics.getPosition().x < mCenter.x - mAmplitude) mSpeed = 50;
    else if (mPhysics.getPosition().x > mCenter.x + mAmplitude) mSpeed = -50;
    mPhysics.accelerate(mSpeed, 0);
    float random = GetRandomValue(0, 100) / 100.0f;
    if (random < jumpChance && mPhysics.onGround()) {
        mPhysics.startJump(3);
    }
    if (mMove == Move::MOVE) {
        if (mCooldownTimer < mCooldownTime) mCooldownTimer += dt;
        else {
            mCooldownTimer = 0.0f;
            setMove(Move::ATTACK);
        }
    } else {
        if (mAttackTimer < mAttackTime) mAttackTimer += dt;
        else {
            mAttackTimer = 0.0f;
            setMove(Move::MOVE);
        }
    }
    mAnim.update(dt);
}
        
void Bowser::handle() {

}

void Bowser::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, !mPhysics.isRight());
}

void Bowser::handleCollision(Side side, Collide other) {
    
}

Vector2 Bowser::getSize() {
    return {32, 32};
}

std::string Bowser::getTag() {
    return "Bowser";
}

std::unique_ptr<Bowser> Bowser::spawnBowser(Vector2 position) {
    std::unique_ptr<Bowser> mBowser = std::make_unique<Bowser>();
    mBowser->setCenter(position);
    return std::move(mBowser);
}

void Bowser::fire() {

}

void Bowser::setMove(Move move) {
    Texture2D* texture = nullptr;

    if (move == Move::MOVE) texture = &Resource::mTexture.get(TextureIdentifier::BOWSER_MOVE);
    else {
        texture = &Resource::mTexture.get(TextureIdentifier::BOWSER_ATTACK);
        fire();
    }

    mMove = move;

    if (texture) {
        mAnim.setTexture(texture, getSize().x / 3.0f, getSize().y / 3.0f);
        mAnim.setRepeating(true, false);
        mAnim.restart();   
    }
}

void Bowser::setCenter(Vector2 position) {
    mCenter = position;
    mPhysics.setPosition(position);
}