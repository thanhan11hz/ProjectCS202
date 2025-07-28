#include "Entity/Character.hpp"

Character::Character(int length, int high) : MovingEntity(), mKey(mKeyBinding), mLength(length), mHigh(high) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setStatic(false);
    mAnim.setFrameSize({16, 16});
    mAnim.setFrameDuration(0.8f);
    mBodyCollide.setLabel(Category::MARIO);
}

void Character::handle() {
    if (mMove == Move::CROUCH) {
        if (IsKeyReleased(mKey[Action::DOWN])) {
            if (!mPhysics.onGround()) setMove(Move::JUMP);
            else setMove(Move::IDLE);
        }
    } else {
        if (IsKeyDown(mKey[Action::DOWN])) setMove(Move::CROUCH);
        if (IsKeyDown(mKey[Action::LEFT])) mPhysics.accelerate({-mLength, 0});
        if (IsKeyDown(mKey[Action::RIGHT])) mPhysics.accelerate({mLength, 0});
    }
    if (IsKeyDown(mKey[Action::JUMP]) && mPhysics.onGround()) {
        mPhysics.startJump(mHigh);
        if (mForm == Form::NORMAL) PlaySound(Resource::mSound.get(SoundIdentifier::NORMAL_JUMP));
        else PlaySound(Resource::mSound.get(SoundIdentifier::SUPER_JUMP));
    }
    if (IsKeyReleased(mKey[Action::JUMP])) mPhysics.endJump();
    if (mForm == Form::FIRE) {
        if (IsKeyPressed(mKey[Action::FIRE])) fire();
    }
}
        
void Character::draw() {
    if (mMove == Move::DEAD) return;
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, !mPhysics.isRight(), false, mIsImmortal);
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, BLACK);
    DrawRectangleLines(mFootCollide.getHitBox().x, mFootCollide.getHitBox().y, mFootCollide.getHitBox().width, mFootCollide.getHitBox().height, BLACK);

}
        
void Character::update(float dt) {
    if (mMove == Move::DEAD) return;
    MovingEntity::update(dt);
    updateMove();
    updateImmortal(dt);
    mAnim.update(dt);
    mPhysics.setOnGround(false);
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
            mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y - 30});
        } else if (move == Move::CROUCH) {
            mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y + 30});
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

void Character::fire() {
    
}

std::unique_ptr<Character> Character::spawnMario() {
    std::unique_ptr<Character> mChar = std::make_unique<Character>(300, 5);
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
    std::unique_ptr<Character> mChar = std::make_unique<Character>(250, 6);
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

void Character::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (side == Side::TOP && otherLabel == Category::BLOCK) {
        mPhysics.setVelocity({mPhysics.getVelocity().x, 0});
    }
    if ((side == Side::LEFT || side == Side::RIGHT) && otherLabel == Category::BLOCK) {
        
    }
}

std::string Character::getTag() {
    switch (mForm) {
        case Form::NORMAL:
            return "Normal";
            break;

        case Form::SUPER:
            return "Super";
            break;

        case Form::FIRE:
            return "Fire";
            break;
        
        default:
            return "";
            break;
    }
}

