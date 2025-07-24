#include "Entity/Character.hpp"

Character::Character(int length, int high) : mAnim(nullptr, 16, 16, 1.0f, true), mKey(mKeyBinding), mLength(length), mHigh(high) {

}

void Character::handle() {
    if (IsKeyDown(mKey[Action::DOWN])) setMove(Move::CROUCH);
    if (mMove == Move::CROUCH) {
        if (IsKeyReleased(mKey[Action::DOWN])) {
            if (!mPhysics.onGround()) setMove(Move::JUMP);
            else setMove(Move::IDLE);
        }
    } else {
        if (IsKeyPressed(mKey[Action::LEFT])) {
            std::cout << "aaaaaaa";
            mPhysics.accelerate({-mLength, 0});
        }
        if (IsKeyDown(mKey[Action::RIGHT])) mPhysics.accelerate({mLength, 0});
    }
    if (IsKeyDown(mKey[Action::JUMP]) && mPhysics.onGround()) mPhysics.startJump(mHigh);
    if (IsKeyReleased(mKey[Action::JUMP])) mPhysics.endJump();
}
        
void Character::draw() {
    if (mMove == Move::DEAD) return;
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, !mPhysics.isRight(), mIsImmortal);
}
        
void Character::update(float dt) {
    if (mMove == Move::DEAD) return;
    Entity::update(dt);
    if (mPhysics.getPosition().y > 672){
        mPhysics.setPosition({mPhysics.getPosition().x, 672});
        mPhysics.setOnGround(true);
    }
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
    Texture2D* texture = nullptr;
    // bool repeat = true;

    switch (mForm) {
        case Form::NORMAL :
            texture = &mNormal[move];
            break;

        case Form::SUPER :
            texture = &mSuper[move];
            break;

        case Form::FIRE :
            texture = &mFire[move];
            break;

        default:
            break;
    }

    if (mForm == Form::FIRE || mForm == Form::SUPER) {
        if (mMove == Move::CROUCH) {
            mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y + 30});
        } else if (move == Move::CROUCH) {
            mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y - 30});
        }
    }

    mMove = move;

    if (texture) {
        mAnim.setTexture(texture, getSize().x / 3.0f, getSize().y / 3.0f);
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
        mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y + 48});
    }
    if (form == Form::NORMAL) {
        mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y - 48});
    }
    mForm = form;
    setMove(mMove);
}

std::unique_ptr<Character> Character::spawnMario() {
    std::unique_ptr<Character> mChar = std::make_unique<Character>(100, 192);
    mChar->mNormal[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
    mChar->mNormal[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_N_RUN);
    mChar->mNormal[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
    mChar->mNormal[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
    mChar->mSuper[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
    mChar->mSuper[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_S_RUN);
    mChar->mSuper[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
    mChar->mSuper[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_S_CROUCH);
    mChar->mFire[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
    mChar->mFire[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_F_RUN);
    mChar->mFire[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
    mChar->mFire[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_F_CROUCH);
    mChar->setMove(Move::IDLE);
    return std::move(mChar);
}
        
std::unique_ptr<Character> Character::spawnLuigi() {
    std::unique_ptr<Character> mChar = std::make_unique<Character>(80, 240);
    mChar->mNormal[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_JUMP);
    mChar->mNormal[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_RUN);
    mChar->mNormal[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE);
    mChar->mNormal[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE);
    mChar->mSuper[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
    mChar->mSuper[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_RUN);
    mChar->mSuper[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_IDLE);
    mChar->mSuper[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_CROUCH);
    mChar->mFire[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
    mChar->mFire[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_RUN);
    mChar->mFire[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_IDLE);
    mChar->mFire[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_CROUCH);
    mChar->setMove(Move::IDLE);
    return std::move(mChar);
}

Vector2 Character::getSize() {
    if (mForm == Form::NORMAL) return {48, 48};
    if (mMove == Move::CROUCH) return {48, 66};
    return {48, 96};
}

void Character::handleCollision(Side side, Category other) {

}