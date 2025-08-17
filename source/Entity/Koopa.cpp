#include "Entity/Koopa.hpp"
#include "World/World.hpp"
#include "Entity/Character.hpp"

Koopa::Koopa(Type type) : mType(type), mState(State::WALKING), mShellTimer(0.f) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 24}); 
    mSpeed = (mType == Type::K_BLUE) ? -100.0f : -80.0f;
    switch (type) {
        case Type::K_GREEN:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_DEATH);
            break;
        case Type::K_RED:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_DEATH);
            break;
        case Type::K_BLUE:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_DEATH);
            break;
    }
    setState(State::WALKING);
}

Koopa::Koopa(const nlohmann::json& j) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 24});
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mType = static_cast<Type>(j["type"].get<unsigned int>());
    switch (mType) {
        case Type::K_GREEN:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_DEATH);
            break;
        case Type::K_RED:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_RED_DEATH);
            break;
        case Type::K_BLUE:
            mRunTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_RUN);
            mShellTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_SHELL);
            mWiggleTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_WIGGLE);
            mDeathTexture = Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_DEATH);
            break;
    }
    setState(static_cast<State>(j["state"].get<unsigned int>()));
    mSpeed = j["speed"].get<float>();
    mLedgeCooldown = j["ledgeCooldown"].get<float>();
    mShellTimer = j["shellTimer"].get<float>();
}

std::unique_ptr<Koopa> Koopa::spawnKoopa(Vector2 position, Type type) {
    std::unique_ptr<Koopa> koopa = std::make_unique<Koopa>(type);
    koopa->mPhysics.setPosition(position);
    
    return std::move(koopa);
}

void Koopa::update(float dt) {
    if (mLedgeCooldown > 0) mLedgeCooldown -= dt;
    Enemy::update(dt);
    if (!isActive() || isDie()) return;
    Entity::update(dt);
    switch (mState) {
        case State::WALKING:
            // Ledge Detection for Red and Blue Koopas
            if (mLedgeCooldown <= 0 && (mType == Type::K_RED || mType == Type::K_BLUE)) {
                Vector2 currentPos = mPhysics.getPosition();
                Vector2 koopaSize = getSize();

                float probeX = (mSpeed < 0) ? currentPos.x - 1 : currentPos.x + koopaSize.x;
                float probeY = currentPos.y + koopaSize.y + 1;

                if (!World::getInstance().isSolidTileAt({probeX, probeY})) {
                    mSpeed *= -1;
                }
            }

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
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), mDeathTexture, true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
        return;
    }
    
    if ((side == Side::RIGHT || side == Side::LEFT) && otherLabel == Category::BLOCK) {
        if (side == Side::RIGHT) mSpeed = -fabs(mSpeed);
        else mSpeed = fabs(mSpeed);
        
        mPhysics.setVelocity(0, mPhysics.getVelocity().y);

        Rectangle blockHitBox = other.getHitBox();
        Vector2 newPos = mPhysics.getPosition();
        if (side == Side::LEFT) {
            newPos.x = blockHitBox.x + blockHitBox.width;
        } 
        else if (side == Side::RIGHT) {
            newPos.x = blockHitBox.x - getSize().x;
        }
        mPhysics.setPosition(newPos);
        mLedgeCooldown = 0.2f;
    }

    if (otherLabel == Category::MARIO && static_cast<Character*>(other.getOwner())->isImmortal()) {
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), mDeathTexture, true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
    }
    
    if (otherLabel == Category::MARIO) {
         if (mState == State::WALKING) {
         } else if (mState == State::SHELL) {
            float pushDirection = (other.getOwner()->mPhysics.getPosition().x < mPhysics.getPosition().x) ? 1.0f : -1.0f;
            mSpeed = 400.0f * pushDirection;
            setState(State::SLIDING);
         }
    }

        if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Koopa") {
        setDie(true);
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), mDeathTexture, true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
    }

    if (otherLabel == Category::ENEMY && (side == Side::LEFT || side == Side::RIGHT)) {
        mSpeed *= -1;
        if (side == Side::LEFT) mPhysics.setPosition(mPhysics.getPosition() + Vector2{10, 0});
        else mPhysics.setPosition(mPhysics.getPosition() + Vector2{-10, 0});
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

void Koopa::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"state", (unsigned int) mState},
        {"type", (unsigned int) mType},
        {"speed", mSpeed},
        {"ledgeCooldown", mLedgeCooldown},
        {"shellTimer", mShellTimer},
        {"class", "koopa"}
    };
}