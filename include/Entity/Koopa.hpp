#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "Global.hpp"

class Koopa : public Enemy {
public:
    enum class State : unsigned int {
        WALKING,
        SHELL,
        SLIDING,
        WIGGLING
    };

    enum class Type : unsigned int {
        K_GREEN,
        K_RED,
        K_BLUE
    };

    Koopa(Type type);
    Koopa(const nlohmann::json& j);

    virtual void update(float dt) override;
    virtual void handle() override;
    virtual void draw() override;
    virtual void handleCollision(Side side, Collide other) override;
    virtual Vector2 getSize() override;
    virtual std::string getTag() override;

    virtual void serialize(nlohmann::json& j);

    static std::unique_ptr<Koopa> spawnKoopa(Vector2 position, Type type);

private:
    void setState(State state);

    State mState;
    Type mType;
    float mSpeed;
    float mLedgeCooldown;

    float mShellTimer;
    static constexpr float mTimeToWiggle = 5.0f;
    static constexpr float mTimeToEmerge = 2.0f;

    Texture2D mRunTexture;
    Texture2D mShellTexture;
    Texture2D mWiggleTexture;
    Texture2D mDeathTexture;
};