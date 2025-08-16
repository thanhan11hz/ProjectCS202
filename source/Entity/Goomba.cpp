#include "Entity/Goomba.hpp"
#include "World/World.hpp"
#include "Entity/Character.hpp"

Goomba::Goomba(Type type) : mType(type) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 16});
    setMove(Move::RUN);
}

Goomba::Goomba(const nlohmann::json& j) {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setFrameSize({16, 16});
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mType = static_cast<Type>(j["type"].get<unsigned int>());
    setMove(static_cast<Move>(j["move"].get<unsigned int>()));
    mSpeed = j["speed"].get<float>();
}

void Goomba::update(float dt) {
    Enemy::update(dt);
    if (!isActive()) return;
    if (isDie()) return;
    Entity::update(dt);
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
    if (side == Side::TOP && otherLabel == Category::MARIO && mMove == Move::RUN) {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::KICK), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::KICK));
        setMove(Move::DEAD);
    }

    if (otherLabel == Category::MARIO && static_cast<Character*>(other.getOwner())->isImmortal()) {
        setDie(true);
        if (mType == Type::BROWN_GOOMBA) mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA_DEATH), true));
        else mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA2_DEATH), true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
    }

    if ((side == Side::RIGHT || side == Side::LEFT) && otherLabel == Category::BLOCK) {
        mSpeed = (side == Side::RIGHT) ? -100.0f : 100.0f;
    }

    if (otherLabel == Category::PROJECTILE && other.getOwner()->getTag() == "FireBall") {
        setDie(true);
        if (mType == Type::BROWN_GOOMBA) mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA_DEATH), true));
        else mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA2_DEATH), true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
    }

    if (otherLabel == Category::ENEMY && (side == Side::LEFT || side == Side::RIGHT)) {
        mSpeed *= -1;
        if (side == Side::LEFT) mPhysics.setPosition(mPhysics.getPosition() + Vector2{10, 0});
        else mPhysics.setPosition(mPhysics.getPosition() + Vector2{-10, 0});
    }

    if (otherLabel == Category::ITEM && other.getOwner()->getTag() == "Koopa") {
        setDie(true);
        if (mType == Type::BROWN_GOOMBA) mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA_DEATH), true));
        else mWorld.addEffect(DeathEffect::spawnDeathEffect(mPhysics.getPosition(), Resource::mTexture.get(TextureIdentifier::GOOMBA2_DEATH), true));
        mWorld.addEffect(PointEffect::spawnPointEffect(mPhysics.getPosition(), "200"));
        mWorld.receivePoint(200);
    }
}
        
Vector2 Goomba::getSize() {
    if (mMove == Move::RUN) return {48, 48};
    if (isDie()) return {0,0};
    return {48, 24};
}

void Goomba::setMove(Move move) {
    Texture2D* texture = nullptr;

    if (move == Move::RUN) {
        if (mType == Type::BROWN_GOOMBA) texture = &Resource::mTexture.get(TextureIdentifier::GOOMBA_RUN);
        else texture = &Resource::mTexture.get(TextureIdentifier::GOOMBA2_RUN);
    }
    else {
        if (mType == Type::BROWN_GOOMBA) texture = &Resource::mTexture.get(TextureIdentifier::GOOMBA_DIE);
        else texture = &Resource::mTexture.get(TextureIdentifier::GOOMBA2_DIE);
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
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>(Type::BROWN_GOOMBA);
    mGoomba->mPhysics.setPosition(position);
    return std::move(mGoomba);
}
        
std::unique_ptr<Goomba> Goomba::spawnGoomba2(Vector2 position) {
    std::unique_ptr<Goomba> mGoomba = std::make_unique<Goomba>(Type::BLUE_GOOMBA);
    mGoomba->mPhysics.setPosition(position);
    return std::move(mGoomba);
}

std::string Goomba::getTag() {
    return "Goomba";
}

void Goomba::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"move", (unsigned int) mMove},
        {"type", (unsigned int) mType},
        {"speed", mSpeed},
        {"class", "goomba"}
    };
}