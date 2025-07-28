#pragma once

#include <memory>
#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"
#include "Entity/Collide.hpp"

class Koopa : public Entity {
public:
    enum class State {
        WALKING, 
        SHELL_STILL,
        SHELL_SPINNING,
    };

    enum class KoopaType {
        KOOPA_GREEN,
        KOOPA_RED,
        KOOPA_BLUE
    };

    Koopa(Vector2 position, KoopaType type); 
    
    virtual void update(float dt) override;
    virtual void handle() override;
    virtual void draw() override;

    virtual void handleCollision(Side side, Category other) override; 
    virtual Vector2 getSize() override;


    void onStomped(Category stomperCategory);
    void onKicked(Side kickDirection, Category kickerCategory);
    
    State getState() const;

    static std::unique_ptr<Koopa> spawnGreenKoopa(Vector2 position);
    static std::unique_ptr<Koopa> spawnRedKoopa(Vector2 position);
    static std::unique_ptr<Koopa> spawnBlueKoopa(Vector2 position);

private:
    State mCurrentState;
    Animation mAnim;

    Texture2D* mWalkTexture;
    Texture2D* mShellStillTexture;
    
    float mWalkSpeed = 100.0f;
    float mShellSpinSpeed = 300.0f;

    float mShellStillTimer = 0.0f;
    const float SHELL_STILL_DURATION = 5.0f;

    bool mFacingRight = false;
    KoopaType mType;

    void setState(State newState);

    void updateWalking(float dt);
    void updateShellStill(float dt);
    void updateShellSpinning(float dt);

    void updateAnimationTexture(); 
};