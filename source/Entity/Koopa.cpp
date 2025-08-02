#include "Entity/Koopa.hpp"
#include "World/World.hpp"

Koopa::Koopa(Type type) 
    : mType(type), mState(State::WALKING), mShellTimer(0.f) {
    
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);

    mAnim.setFrameSize({16, 24}); 

    mSpeed = (mType == Type::K_BLUE) ? -150.0f : -100.0f;
}

std::unique_ptr<Koopa> Koopa::spawnKoopa(Vector2 position, Type type) {
    std::unique_ptr<Koopa> koopa = std::make_unique<Koopa>(type);

    switch (type) {
        case Type::K_GREEN:
            koopa->mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_RUN);
            koopa->mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_SHELL);
            koopa->mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_WIGGLE);
            break;
        case Type::K_RED:
            koopa->mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_RUN);
            koopa->mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_SHELL);
            koopa->mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_WIGGLE);
            break;
        case Type::K_BLUE:
            koopa->mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_RUN);
            koopa->mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_SHELL);
            koopa->mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_WIGGLE);
            break;
    }

    koopa->mPhysics.setPosition(position);
    koopa->setState(State::WALKING);
    return std::move(koopa);
}

void Koopa::update(float dt) {
    Enemy::update(dt);
    if (!isActive() || isDie()) return;
    MovingEntity::update(dt);

    switch (mState) {
        case State::WALKING:
            mPhysics.accelerate({mSpeed, 0});
            break;

        case State::SHELL:
            mShellTimer += dt;
            if (mShellTimer > mTimeToWiggle) {
                setState(State::WIGGLING);
            }
            break;

        case State::SLIDING:
            mPhysics.accelerate({mSpeed, 0});
            break;

        case State::WIGGLING:
            mShellTimer += dt;
            if (mShellTimer > mTimeToWiggle + mTimeToEmerge) {
                mPhysics.setPosition({mPhysics.getPosition().x, mPhysics.getPosition().y - 16});
                setState(State::WALKING);
            }
            break;
    }

    mAnim.update(dt);
    mPhysics.setOnGround(false);
}

void Koopa::handleCollision(Side side, Collide other) {
    if (isDie()) return;

    Category otherLabel = other.getLabel();

    if (side == Side::TOP && otherLabel == Category::MARIO) {
        if (mState == State::WALKING) {
            setState(State::SHELL);
        } else if (mState == State::SHELL) {
            float pushDirection = (other.getOwner()->mPhysics.getPosition().x < mPhysics.getPosition().x) ? 1.0f : -1.0f;
            mSpeed = 400.0f * pushDirection;
            setState(State::SLIDING);
        } else if (mState == State::SLIDING) {
            setState(State::SHELL);
        }
        return;
    }

    if (otherLabel == Category::PROJECTILE && other.getOwner()->getTag() == "FireBall") {
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), mRunTexture, true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "100"));
        return;
    }
    
    if ((side == Side::RIGHT || side == Side::LEFT) && otherLabel == Category::BLOCK) {
        mSpeed *= -1;
    }
    
    if (otherLabel == Category::MARIO) {
         if (mState == State::WALKING) {
         } else if (mState == State::SHELL) {
            float pushDirection = (other.getOwner()->mPhysics.getPosition().x < mPhysics.getPosition().x) ? 1.0f : -1.0f;
            mSpeed = 400.0f * pushDirection;
            setState(State::SLIDING);
         }
    }
}

void Koopa::setState(State state) {
    mState = state;
    mShellTimer = 0.f;

    switch (mState) {
        case State::WALKING:
            mBodyCollide.setLabel(Category::ENEMY);
            mPhysics.setVelocity(mSpeed, 0);
            mAnim.setTexture(&mRunTexture, 16, 24);
            mAnim.setRepeating(true, true);
            break;
        case State::SHELL:
            mBodyCollide.setLabel(Category::ITEM);
            mPhysics.setVelocity(0, 0);
            mAnim.setTexture(&mShellTexture, 16, 16);
            mAnim.setRepeating(false, true);
            break;
        case State::SLIDING:
            mBodyCollide.setLabel(Category::ENEMY);
            mPhysics.setVelocity(mSpeed, 0);
            mAnim.setTexture(&mShellTexture, 16, 16);
            mAnim.setRepeating(true, true);
            break;
        case State::WIGGLING:
            mBodyCollide.setLabel(Category::ITEM);
            mPhysics.setVelocity(0, 0);
            mAnim.setTexture(&mWiggleTexture, 16, 16);
            mAnim.setRepeating(true, true);
            break;
    }
    mAnim.restart();
}

void Koopa::draw() {
    bool flipX = mPhysics.getVelocity().x < 0;
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, flipX);
}

Vector2 Koopa::getSize() {
    if (mState == State::WALKING) return {48, 72};
    return {48, 48};
}

std::string Koopa::getTag() {
    return "Koopa";
}

void Koopa::handle() {
}