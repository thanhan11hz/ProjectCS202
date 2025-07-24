#include "Entity/Character.hpp"

Character::Character() : mAnim(nullptr, 16, 16, 1.0f, true), mKey(mKeyBinding), mMove(Move::IDLE) {

}

void Character::handle() {
    if (IsKeyDown(mKey[Action::DOWN])) setMove(Move::CROUCH);
    if (mMove == Move::CROUCH) {
        if (IsKeyReleased(mKey[Action::DOWN])) {
            if (!mPhysics.onGround()) setMove(Move::JUMP);
            else setMove(Move::IDLE);
        }
    } else {
        if (IsKeyDown(mKey[Action::LEFT])) mPhysics.accelerate({-100, 0});
        if (IsKeyDown(mKey[Action::RIGHT])) mPhysics.accelerate({100, 0});
    }
    if (IsKeyDown(mKey[Action::JUMP]) && mPhysics.onGround()) mPhysics.startJump();
    if (IsKeyReleased(mKey[Action::JUMP])) mPhysics.endJump();
}
        
void Character::draw() {
    if (mMove == Move::DEAD) return;
    mAnim.draw(mPhysics.getPosition(), 2.f, 0.0f, !mPhysics.isRight());
}
        
void Character::update(float dt) {
    if (mMove == Move::DEAD) return;
    Entity::update(dt);
    updateMove();
    updateImmortal(dt);
    mAnim.update(dt);
}

void Character::updateMove() {
    if (mMove == Move::DEAD) return;
    if (mMove == Move::CROUCH) return;
    Move next = mMove;           
    if (!mPhysics.onGround())                      
        next = Move::JUMP;
    else if (mPhysics.isRunning())
        next = Move::RUN;
    else
        next = Move::IDLE;

    if (next != mMove) setMove(next);
}
        
void Character::setMove(Move move) {
    mMove = move;
    Texture2D* texture = nullptr;
    // bool repeat = true;

    switch (mForm) {
        case Form::NORMAL :
            texture = &mNormal[mMove];
            break;

        case Form::SUPER :
            texture = &mSuper[mMove];
            break;

        case Form::FIRE :
            texture = &mFire[mMove];
            break;

        default:
            break;
    }

    if (texture) {
        mAnim.setTexture(texture, getSize().x, getSize().y);
        mAnim.setRepeating(true, false);
        mAnim.restart();   
    }
}
        
void Character::updateImmortal(float dt) {
    if (mIsImmortal) {
        mImmortalTimer -= dt;
        if (mImmortalTimer <= 0) {
            mImmortalTimer = mImmortalTime;
            mIsImmortal = false;
        }
    }
}
        
void Character::setImmortal(bool flag) {
    mIsImmortal = flag;
}
        
void Character::setForm(Form form) {
    if (mForm == form) return;
    if (mForm == Form::NORMAL) {
        Vector2 position = mPhysics.getPosition();
        position.y += 24;
        mPhysics.setPosition(position);
    }
    if (form == Form::NORMAL) {
        Vector2 position = mPhysics.getPosition();
        position.y -= 24;
        mPhysics.setPosition(position);
    }
    mForm = form;
    setMove(mMove);
}

std::unique_ptr<Character> Character::spawnMario() {
    std::unique_ptr<Character> mChar = std::make_unique<Character>();
    mChar->mNormal[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
    mChar->mNormal[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_N_RUN);
    mChar->mNormal[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
    mChar->mNormal[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
    mChar->mSuper[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
    mChar->mSuper[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_S_RUN);
    mChar->mSuper[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
    mChar->mSuper[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
    mChar->mFire[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
    mChar->mFire[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_F_RUN);
    mChar->mFire[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
    mChar->mFire[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
    return std::move(mChar);
}
        
std::unique_ptr<Character> Character::spawnLuigi() {
    std::unique_ptr<Character> mChar = std::make_unique<Character>();
    return std::move(mChar);
}

Vector2 Character::getSize() {
    if (mForm == Form::NORMAL || mMove == Move::CROUCH) return {48, 48};
    return {48, 96};
}