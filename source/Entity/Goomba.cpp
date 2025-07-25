#include "Entity/Goomba.hpp"

Goomba::Goomba() : mAnim(nullptr, 16, 16, 1.0f, true) {

}

void Goomba::update(float dt) {
    if (mMove == Move::DEAD) {
        updateDead(dt);
        return;
    }
    mPhysics.accelerate(Vector2{mPhysics.isRight() ? 100.0f : -100.0f, 0});
}

void Goomba::handle() {

}
        
void Goomba::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
}

void Goomba::handleCollision(Side side, Category other) {

}
        
Vector2 Goomba::getSize() {
    if (mMove == Move::RUN) return {48, 48};
    return {48, 24};
}

void Goomba::updateDead(float dt) {
    if (mMove == Move::DEAD) {
        if (mDeadTimer < mDeadTime) mDeadTimer += dt;
        else setDie(true);
    }
}

void Goomba::setMove(Move move) {
    if (mMove == Move::DEAD) return;
    Texture2D* texture = nullptr;

    if (mMove == Move::RUN) texture = &mRun;
    else {
        texture = &mDie;
        mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y + 24});
    }

    mMove = move;

    if (texture) {
        mAnim.setTexture(texture, getSize().x / 3.0f, getSize().y / 3.0f);
        mAnim.setRepeating(true, false);
        mAnim.restart();   
    }
}

std::unique_ptr<Goomba> Goomba::spawnBrownGoomba() {
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>();
    mGoomba->mRun = Resource::mTexture.get(TextureIdentifier::GOOMBA_RUN);
    mGoomba->mDie = Resource::mTexture.get(TextureIdentifier::GOOMBA_DIE);
    mGoomba->setMove(Move::RUN);
    return std::move(mGoomba);
}
        
std::unique_ptr<Goomba> Goomba::spawnBlueGoomba() {
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>();
    mGoomba->mRun = Resource::mTexture.get(TextureIdentifier::GOOMBA2_RUN);
    mGoomba->mDie = Resource::mTexture.get(TextureIdentifier::GOOMBA2_DIE);
    mGoomba->setMove(Move::RUN);
    return std::move(mGoomba);
}