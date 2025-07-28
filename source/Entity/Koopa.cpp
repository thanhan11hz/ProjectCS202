#include "Entity/Koopa.hpp"
#include "Global.hpp"
#include <cassert>
#include <iostream>

std::unique_ptr<Koopa> Koopa::spawnGreenKoopa(Vector2 position) {
    return std::make_unique<Koopa>(position, Koopa::KoopaType::KOOPA_GREEN);
}

std::unique_ptr<Koopa> Koopa::spawnRedKoopa(Vector2 position) {
    return std::make_unique<Koopa>(position, Koopa::KoopaType::KOOPA_RED);
}

std::unique_ptr<Koopa> Koopa::spawnBlueKoopa(Vector2 position) {
    return std::make_unique<Koopa>(position, Koopa::KoopaType::KOOPA_BLUE);
}

Koopa::Koopa(Vector2 position, KoopaType type)
    : Entity(),
      mAnim(nullptr, 0, 0, 1.0f, true),
      mType(type),
      mCurrentState(State::WALKING),
      mFacingRight(true),
      mShellStillTimer(0.0f) {
    mPhysics.setPosition(position);
    mCollide.setLabel(Category::KOOPA);

    switch (mType) {
        case Koopa::KoopaType::KOOPA_GREEN:
            mWalkTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_WALK);
            mShellStillTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_GREEN_SHELL);
            break;
        case Koopa::KoopaType::KOOPA_RED:
            mWalkTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_RED_WALK);
            mShellStillTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_RED_SHELL);
            break;
        case Koopa::KoopaType::KOOPA_BLUE:
            mWalkTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_WALK);
            mShellStillTexture = &Resource::mTexture.get(TextureIdentifier::KOOPA_BLUE_SHELL);
            break;
        default:
            mWalkTexture = nullptr;
            mShellStillTexture = nullptr;
            std::cerr << "Error: Unknown KoopaType in constructor!" << std::endl;
            assert(false && "Unknown KoopaType in constructor!");
            break;
    }

    updateAnimationTexture();

    mCollide.setHitBox({mPhysics.getPosition().x, mPhysics.getPosition().y, (float)getSize().x, (float)getSize().y});
}

void Koopa::update(float dt) {
    switch (mCurrentState) {
        case State::WALKING:
            updateWalking(dt);
            break;
        case State::SHELL_STILL:
            updateShellStill(dt);
            break;
        case State::SHELL_SPINNING:
            updateShellSpinning(dt);
            break;
    }

    mAnim.update(dt);
    mPhysics.update(dt);

    Rectangle currentHitBox = mCollide.getHitBox();
    currentHitBox.x = mPhysics.getPosition().x;
    currentHitBox.y = mPhysics.getPosition().y;
    mCollide.setHitBox(currentHitBox);
}

void Koopa::handle() {
}

void Koopa::draw() {
    Vector2 drawPosition = mPhysics.getPosition();

    float scale = 1.0f;
    bool flipX = !mFacingRight;

    float rotation = 0.0f;
    if (mCurrentState == State::SHELL_SPINNING) {
        rotation = (float)GetTime() * 720.0f;
    }

    mAnim.draw(drawPosition, scale, rotation, flipX, false, WHITE);
}

void Koopa::handleCollision(Side side, Category other) {
    if (isDie()) return;

    if (mCurrentState == State::WALKING) {
        if (other == Category::BLOCK) {
            if (side == Side::LEFT || side == Side::RIGHT) {
                mFacingRight = !mFacingRight;
                mPhysics.setVelocity(-mPhysics.getVelocity().x, mPhysics.getVelocity().y);
            }
        } else if (other == Category::NORMAL_MARIO || other == Category::FIRE_MARIO || other == Category::SUPER_MARIO) {
            if (side == Side::LEFT || side == Side::RIGHT) {
            } else if (side == Side::TOP) {
                onStomped(other);
            }
        }
    } else if (mCurrentState == State::SHELL_STILL) {
        if (other == Category::NORMAL_MARIO || other == Category::FIRE_MARIO || other == Category::SUPER_MARIO) {
            if (side == Side::LEFT || side == Side::RIGHT) {
                Side kickDir = (side == Side::LEFT) ? Side::RIGHT : Side::LEFT;
                onKicked(kickDir, other);
            } else if (side == Side::TOP) {
                onKicked(mFacingRight ? Side::RIGHT : Side::LEFT, other);
            }
        }
    } else if (mCurrentState == State::SHELL_SPINNING) {
        if (other == Category::BLOCK) {
            if (side == Side::LEFT || side == Side::RIGHT) {
                mPhysics.setVelocity(-mPhysics.getVelocity().x, mPhysics.getVelocity().y);
                mFacingRight = !mFacingRight;
            }
        } else if (other == Category::NORMAL_MARIO || other == Category::FIRE_MARIO || other == Category::SUPER_MARIO) {
        } else if (other == Category::GOOMBA || other == Category::KOOPA || other == Category::PIRANHA_PLANT) {
        }
    }
}

Vector2 Koopa::getSize() {
    return mAnim.getFrameSize();
}

void Koopa::onStomped(Category stomperCategory) {
    if (mCurrentState == State::WALKING) {
        setState(State::SHELL_STILL);
        mPhysics.setVelocity({0.0f, 0.0f});
        mPhysics.setVelocity(mPhysics.getVelocity().x, -300.0f);
        mShellStillTimer = SHELL_STILL_DURATION;
    }
}

void Koopa::onKicked(Side kickDirection, Category kickerCategory) {
    if (mCurrentState == State::SHELL_STILL) {
        setState(State::SHELL_SPINNING);

        if (kickDirection == Side::LEFT) {
            mPhysics.setVelocity(-mShellSpinSpeed, mPhysics.getVelocity().y);
            mFacingRight = false;
        } else if (kickDirection == Side::RIGHT) {
            mPhysics.setVelocity(mShellSpinSpeed, mPhysics.getVelocity().y);
            mFacingRight = true;
        }
        mCollide.setLabel(Category::ENEMY_SHELL);
    }
}

Koopa::State Koopa::getState() const {
    return mCurrentState;
}

void Koopa::setState(State newState) {
    if (mCurrentState == newState) return;

    mCurrentState = newState;
    updateAnimationTexture();

    if (mCurrentState == State::WALKING) {
        mCollide.setLabel(Category::KOOPA);
    } else if (mCurrentState == State::SHELL_STILL) {
        mShellStillTimer = SHELL_STILL_DURATION;
        mPhysics.setVelocity({0.0f, 0.0f});
        mCollide.setLabel(Category::KOOPA);
    } else if (mCurrentState == State::SHELL_SPINNING) {
        mCollide.setLabel(Category::ENEMY_SHELL);
    }
}

void Koopa::updateWalking(float dt) {
    if (mFacingRight) {
        mPhysics.setVelocity(mWalkSpeed, mPhysics.getVelocity().y);
    } else {
        mPhysics.setVelocity(-mWalkSpeed, mPhysics.getVelocity().y);
    }
}

void Koopa::updateShellStill(float dt) {
    mShellStillTimer -= dt;
    if (mShellStillTimer <= 0.0f) {
        setState(State::WALKING);
    }
    mPhysics.setVelocity(0.0f, mPhysics.getVelocity().y);
}

void Koopa::updateShellSpinning(float dt) {
    if (mFacingRight) {
        mPhysics.setVelocity(mShellSpinSpeed, mPhysics.getVelocity().y);
    } else {
        mPhysics.setVelocity(-mShellSpinSpeed, mPhysics.getVelocity().y);
    }
}

void Koopa::updateAnimationTexture() {
    Texture2D* textureToUse = nullptr;
    float frameWidth = 0.0f;
    float frameHeight = 0.0f;
    float duration = timePerFrame;

    switch (mCurrentState) {
        case State::WALKING:
            textureToUse = mWalkTexture;
            frameWidth = 16.0f;
            frameHeight = 24.0f;
            duration = 0.15f;
            break;
        case State::SHELL_STILL:
            textureToUse = mShellStillTexture;
            frameWidth = 16.0f;
            frameHeight = 16.0f;
            duration = 0.5f;
            break;
        case State::SHELL_SPINNING:
            textureToUse = mShellStillTexture;
            frameWidth = 16.0f;
            frameHeight = 16.0f;
            duration = 0.05f;
            break;
    }

    if (textureToUse) {
        assert(textureToUse->id != 0 && "Texture for Koopa state is not loaded! Check ResourceHolder loading.");
        mAnim.setTexture(textureToUse, frameWidth, frameHeight);
        mAnim.setFrameDuration(duration);
        mAnim.setRepeating(true, true);
        mAnim.restart();
    } else {
        std::cerr << "Error: No texture found for Koopa state " << static_cast<int>(mCurrentState) << "!" << std::endl;
    }
}