#include "Entity/Goomba.hpp"

Goomba::Goomba() {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 16});
}

void Goomba::update(float dt) {
    if (isActive()) return;
    if (isDie()) return;
    Enemy::update(dt);
    if (mMove == Move::DEAD) {
        if (mDeadTimer < mDeadTime) mDeadTimer += dt;
        else setDie(true);
        return;
    }
    mPhysics.accelerate(Vector2{mSpeed, 0});
    mAnim.update(dt);
    mPhysics.setOnGround(false);
}

void Goomba::handle() {

}
        
void Goomba::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, BLACK);
}

void Goomba::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (side == Side::TOP && otherLabel == Category::MARIO && mMove == Move::RUN)
        setMove(Move::DEAD);

    if ((side == Side::RIGHT || side == Side::LEFT) && otherLabel == Category::BLOCK) {
        mSpeed = (side == Side::RIGHT) ? -100.0f : 100.0f;
    }
}
        
Vector2 Goomba::getSize() {
    if (mMove == Move::RUN) return {48, 48};
    if (isDie()) return {0,0};
    return {48, 24};
}

void Goomba::setMove(Move move) {
    Texture2D* texture = nullptr;

    if (move == Move::RUN) texture = &mRun;
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

std::unique_ptr<Goomba> Goomba::spawnGoomba1(Vector2 position) {
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>();
    mGoomba->mRun = Resource::mTexture.get(TextureIdentifier::GOOMBA_RUN);
    mGoomba->mDie = Resource::mTexture.get(TextureIdentifier::GOOMBA_DIE);
    mGoomba->setMove(Move::RUN);
    mGoomba->mPhysics.setPosition(position);
    return std::move(mGoomba);
}
        
std::unique_ptr<Goomba> Goomba::spawnGoomba2(Vector2 position) {
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>();
    mGoomba->mRun = Resource::mTexture.get(TextureIdentifier::GOOMBA2_RUN);
    mGoomba->mDie = Resource::mTexture.get(TextureIdentifier::GOOMBA2_DIE);
    mGoomba->setMove(Move::RUN);
    mGoomba->mPhysics.setPosition(position);
    return std::move(mGoomba);
}

std::string Goomba::getTag() {
    return "Goomba";
}