#include "Entity/Character.hpp"

Character::Character(int length, int high) : MovingEntity(), mKey(mKeyBinding), mLength(length), mHigh(high) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setStatic(false);
    mAnim.setFrameSize({16, 16});
    mAnim.setFrameDuration(0.8f);
    mBodyCollide.setLabel(Category::MARIO);
}

Character::Character(const nlohmann::json& j) : mKey(mKeyBinding) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setStatic(false);
    mAnim.setFrameSize({16, 16});
    mAnim.setFrameDuration(0.8f);
    mBodyCollide.setLabel(Category::MARIO);
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    setForm(static_cast<Form>(j["form"].get<unsigned int>()));
    setImmortal(j["immortal"].get<bool>());
    if (j["length"].get<int>() == 300) {
        mNormal[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
        mNormal[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_N_RUN);
        mNormal[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
        mNormal[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
        mSuper[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
        mSuper[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_S_RUN);
        mSuper[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
        mSuper[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_S_CROUCH);
        mFire[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
        mFire[Move::RUN] = Resource::mTexture.get(TextureIdentifier::MARIO_F_RUN);
        mFire[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
        mFire[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::MARIO_F_CROUCH);
        mDeath = Resource::mTexture.get(TextureIdentifier::MARIO_DEATH);
    } else {
        mNormal[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_JUMP);
        mNormal[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_RUN);
        mNormal[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE);
        mNormal[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE);
        mSuper[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
        mSuper[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_RUN);
        mSuper[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_IDLE);
        mSuper[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_CROUCH);
        mFire[Move::JUMP] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
        mFire[Move::RUN] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_RUN);
        mFire[Move::IDLE] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_IDLE);
        mFire[Move::CROUCH] = Resource::mTexture.get(TextureIdentifier::LUIGI_S_CROUCH);
        mDeath = Resource::mTexture.get(TextureIdentifier::LUIGI_DEATH);
    }
    setMove(static_cast<Move>(j["move"].get<unsigned int>()));
}

void Character::handle() {
    if (mMove == Move::CROUCH) {
        if (IsKeyReleased(mKey[Action::DOWN])) {
            if (!mPhysics.onGround()) setMove(Move::JUMP);
            else setMove(Move::IDLE);
        }
    } else {
        if (IsKeyDown(mKey[Action::DOWN])) setMove(Move::CROUCH);
        if (IsKeyDown(mKey[Action::LEFT])) mPhysics.accelerate({mIsImmortal ? -3 * mLength : -mLength, 0});
        if (IsKeyDown(mKey[Action::RIGHT])) mPhysics.accelerate({mIsImmortal ? 3 * mLength : mLength, 0});
    }
    if (IsKeyDown(mKey[Action::JUMP]) && mPhysics.onGround()) {
        mPhysics.startJump(mHigh);
        if (mForm == Form::NORMAL) {
            SetSoundVolume(Resource::mSound.get(SoundIdentifier::NORMAL_JUMP), sfxVolume);
            PlaySound(Resource::mSound.get(SoundIdentifier::NORMAL_JUMP));
        } else {
            SetSoundVolume(Resource::mSound.get(SoundIdentifier::SUPER_JUMP), sfxVolume);
            PlaySound(Resource::mSound.get(SoundIdentifier::SUPER_JUMP));
        }
    }
    if (IsKeyReleased(mKey[Action::JUMP])) mPhysics.endJump();
    if (mForm == Form::FIRE) {
        if (IsKeyPressed(mKey[Action::FIRE])) 
            if (mCooldown >= mCooldownTime) fire();
    }
}
        
void Character::draw() {
    if (isDie()) return;
    if (transitionProgress < 1.0f) {
        if (mForm == Form::NORMAL) mAnim.drawScale(mPhysics.getPosition() - Vector2{0, 48 - transitionProgress * 48}, 3.0f, 3.0f * (32 - transitionProgress * 16) / 16.0f, !mPhysics.isRight(), false, mIsImmortal);
        else mAnim.drawScale(mPhysics.getPosition() + Vector2{0, 48 - transitionProgress * 48}, 3.0f, 3.0f * (16 + transitionProgress * 16) / 32.0f, !mPhysics.isRight(), false, mIsImmortal);
    } else mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, !mPhysics.isRight(), false, mIsImmortal);
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, BLACK);
    DrawRectangleLines(mFootCollide.getHitBox().x, mFootCollide.getHitBox().y, mFootCollide.getHitBox().width, mFootCollide.getHitBox().height, BLACK);
}
        
void Character::update(float dt) {
    if (isDie()) return;
    MovingEntity::update(dt);
    updateMove();
    updateImmortal(dt);
    if (transitionProgress < 1.0f) {
        transitionProgress += 5 * dt;
        if (transitionProgress >= 1.0f) {
            transitionProgress = 1.0f;
        }
    }
    
    if (mCooldown < mCooldownTime) mCooldown += dt;
    if (invincibleTimer < invincibleTime) invincibleTimer += dt;
    
    mAnim.update(dt);
    mPhysics.setOnGround(false);
}

void Character::updateMove() {
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
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::POWER_UP), sfxVolume);
        PlaySound(Resource::mSound.get(SoundIdentifier::POWER_UP));
        transitionProgress = 0.0f;
        mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y - 48});
    }
    if (form == Form::NORMAL) {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::PIPE), sfxVolume);
        PlaySound(Resource::mSound.get(SoundIdentifier::PIPE));
        invincibleTimer = 0.0f;
        transitionProgress = 0.0f;
        mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y + 48});
    }
    mForm = form;
    setMove(mMove);
}

void Character::fire() {
    mCooldown = 0.0f;
    SetSoundVolume(Resource::mSound.get(SoundIdentifier::FIREBALL), sfxVolume);
    PlaySound(Resource::mSound.get(SoundIdentifier::FIREBALL));
    Vector2 position = mPhysics.isRight() ? mPhysics.getPosition() + Vector2{getSize().x, getSize().y / 2.0f} : mPhysics.getPosition() + Vector2{0, getSize().y / 2.0f};
    std::unique_ptr<FireBall> fireBall = FireBall::spawnFireBall(position, mPhysics.isRight());
    mWorld.addProjectile(std::move(fireBall));
}

void Character::damage() {
    if (isDie()) return;
    if (mForm == Form::NORMAL) {
        if (invincibleTimer < invincibleTime) return;
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::MARIO_DEATH), sfxVolume);
        PlaySound(Resource::mSound.get(SoundIdentifier::MARIO_DEATH));
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), mDeath, false));
    } else {
        invincibleTimer = 0.0f;
        setForm(Form::NORMAL);
    }
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
    mChar->mDeath = Resource::mTexture.get(TextureIdentifier::MARIO_DEATH);
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
    mChar->mDeath = Resource::mTexture.get(TextureIdentifier::LUIGI_DEATH);
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

    if (otherLabel == Category::ENEMY && side != Side::BOTTOM && !mIsImmortal) {
        if (other.getOwner()->getTag() != "Goomba" || !other.getOwner()->mPhysics.isRest())
        damage();
    }

    if (otherLabel == Category::PROJECTILE && other.getOwner()->getTag() == "BowserFire" && !mIsImmortal) {
        damage();
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Mushroom") {
        if (!static_cast<TileObject*>(other.getOwner())->up()) setForm(Form::SUPER);
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "GreenMushroom") {
        if (!static_cast<TileObject*>(other.getOwner())->up()) {
            mWorld.heal();
            mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "1-UP"));
        }
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Flower") {
        if (!static_cast<TileObject*>(other.getOwner())->up()) setForm(Form::FIRE);
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Coin") {
        if (!static_cast<TileObject*>(other.getOwner())->up()) mWorld.receiveCoin();
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Star") {
        if (!static_cast<TileObject*>(other.getOwner())->up()) setImmortal(true);
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

void Character::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"form", (unsigned int)mForm},
        {"move", (unsigned int)mMove},
        {"immortal", mIsImmortal},
        {"height", mHigh},
        {"length", mLength},
        {"class", "character"}
    };

bool Character::isImmortal() const {
    return mIsImmortal;
}