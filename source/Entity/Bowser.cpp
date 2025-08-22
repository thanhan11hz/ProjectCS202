#include "Entity/Bowser.hpp"
#include "World/World.hpp"
#include "Entity/Character.hpp"

Bowser::Bowser() {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
}

Bowser::Bowser(const nlohmann::json& j) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    setMove(static_cast<Move>(j["move"].get<unsigned int>()));
    mAttackTimer = j["attackTimer"].get<float>();
    mCooldownTimer = j["cooldownTimer"].get<float>();
    mJumpTimer = j["jumpTimer"].get<float>();
    mSpeed = j["speed"].get<float>();
    mCenter = j["center"].get<Vector2>();
    mLives = j["lives"].get<size_t>();
}

void Bowser::update(float dt) {
    Enemy::update(dt);
    if (!isActive()) return;
    if (isDie()) return;
    if (fabs(mWorld.getCharacter()->mPhysics.getPosition().x - mPhysics.getPosition().x) > 480) {
        if (mPhysics.getPosition().x < mCenter.x - mAmplitude) mSpeed = 50;
        else if (mPhysics.getPosition().x > mCenter.x + mAmplitude) mSpeed = -50;
    } else if (fabs(mWorld.getCharacter()->mPhysics.getPosition().x - mPhysics.getPosition().x) > 192) {
        if (mPhysics.getPosition().x < mCenter.x - 2/3.f * mAmplitude && mPhysics.onGround()) mSpeed = 100;
        else if (mPhysics.getPosition().x > mCenter.x + 2/3.f * mAmplitude && mPhysics.onGround()) mSpeed = -100;
        else {
            mPhysics.setRight(mWorld.getCharacter()->mPhysics.getPosition().x > mPhysics.getPosition().x);
            mSpeed = 0;
        }
    } else {
        if (mJumpTimer < mJumpTime) {
            mJumpTimer += dt;
        } else {
            mJumpTimer = 0.0f;
            mPhysics.startJump(3);
            if (mPhysics.getPosition().x > mWorld.getCharacter()->mPhysics.getPosition().x && !mPhysics.onGround()) mSpeed = -200;
            else if (mPhysics.getPosition().x < mWorld.getCharacter()->mPhysics.getPosition().x && !mPhysics.onGround()) mSpeed = 200;
        }
    }
    mPhysics.accelerate(mSpeed, 0); 
    Entity::update(dt);
    if (mMove == Move::MOVE) {
        if (mCooldownTimer < mCooldownTime) mCooldownTimer += dt;
        else if (mPhysics.isRest()) {
            mCooldownTimer = 0.0f;
            setMove(Move::ATTACK);
            fire();
        }
    } else {
        if (mAttackTimer < mAttackTime) mAttackTimer += dt;
        else {
            mAttackTimer = 0.0f;
            setMove(Move::MOVE);
        }
    }
    mAnim.update(dt);
    mPhysics.setOnGround(false);
}
        
void Bowser::handle() {

}

void Bowser::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f, !mPhysics.isRight());
}

void Bowser::handleCollision(Side side, Collide other) {
    Category otherLabel = other.getLabel();
    if (otherLabel == Category::PROJECTILE && other.getOwner()->getTag() == "FireBall") {
        mLives --;
        if (mLives == 0) {
            setDie(true);
            SetSoundVolume(Resource::mSound.get(SoundIdentifier::KICK), sfxVolume);
            if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::KICK));
            mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::BOWSER_SHELL), false));
            mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "500"));
            mWorld.receivePoint(500);
        }
    }

    if (otherLabel == Category::MARIO && side == Side::TOP) {
        setDie(true);
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::KICK), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::KICK));
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::BOWSER_SHELL), false));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "500"));
        mWorld.receivePoint(500);
    }

    if (otherLabel == Category::MARIO && static_cast<Character*>(other.getOwner())->isImmortal()) {
        setDie(true);
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::KICK), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::KICK));
        mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::BOWSER_SHELL), false));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "500"));
        mWorld.receivePoint(500);
    }

    if ((side == Side::RIGHT || side == Side::LEFT) && otherLabel == Category::BLOCK) {
        mSpeed = (side == Side::RIGHT) ? -100.0f : 100.0f;
    }

    if ((otherLabel == Category::ENEMY || otherLabel == Category::ITEM) && (side == Side::LEFT || side == Side::RIGHT)) {
        mSpeed *= -1;
        if (side == Side::LEFT) mPhysics.setPosition(mPhysics.getPosition() + Vector2{5, 0});
        else mPhysics.setPosition(mPhysics.getPosition() + Vector2{-5, 0});
    }
}

Vector2 Bowser::getSize() {
    return {99, 99};
}

std::string Bowser::getTag() {
    return "Bowser";
}

std::unique_ptr<Bowser> Bowser::spawnBowser(Vector2 position) {
    std::unique_ptr<Bowser> mBowser = std::make_unique<Bowser>();
    mBowser->mPhysics.setPosition(position);
    mBowser->mCenter = position;
    mBowser->setMove(Move::MOVE);
    return std::move(mBowser);
}

void Bowser::fire() {
    SetSoundVolume(Resource::mSound.get(SoundIdentifier::BOWSER_FIRE), sfxVolume);
    if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::BOWSER_FIRE));
    Vector2 position = mPhysics.getPosition();
    if (mPhysics.isRight()) position += {getSize().x, 0};
    else position += {-144, 0};
    if (!mWorld.getCharacter()->mPhysics.isRising()) position.y = mWorld.getCharacter()->mPhysics.getPosition().y;
    mWorld.addProjectile(BowserFire::spawnBowserFire(position, mPhysics.isRight()));
}

void Bowser::setMove(Move move) {
    Texture2D* texture = nullptr;

    if (move == Move::MOVE) texture = &Resource::mTexture.get(TextureIdentifier::BOWSER_MOVE);
    else {
        texture = &Resource::mTexture.get(TextureIdentifier::BOWSER_ATTACK);
    }

    mMove = move;

    if (texture) {
        mAnim.setTexture(texture, getSize().x / 3.0f, getSize().y / 3.0f);
        mAnim.setRepeating(true, false);
        mAnim.restart();   
    }
}

void Bowser::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"move", (unsigned int) mMove},
        {"attackTimer", mAttackTimer},
        {"cooldownTimer", mCooldownTimer},
        {"jumpTimer", mJumpTimer},
        {"speed", mSpeed},
        {"center", mCenter},
        {"lives", mLives},
        {"class", "bowser"}
    };
}