#include "Entity/Mario.hpp"

Mario::Mario(): mAnimation(nullptr, 16, 16, 0.5f, true), mMovement(Movement::IDLE) , mIsRight(true)
                          , mIsImmortal(true), mForm(Form::FIRE), mImmortalTimer(mImmortalTime)
{}

void Mario::draw() {
    mAnimation.draw(getPosition(), 2.f, 0.0f, !mIsRight);
}

void Mario::update(float dt) {
    Entity::updateCurrent(dt); 

    if (getPosition().y >= 600.f) {
        setPosition({getPosition().x, 600.f});
        setVelocity(getVelocity().x, 0.0f);
        mIsGround   = true;
        mIsJump     = false;
    } else mIsGround = false;

    updateImmortal(dt);
    updateMovement();
    mAnimation.update(dt);
}

void Mario::updateMovement() {
    Movement next = mMovement;           

    if (!mIsGround)                      
        next = isRising() ? Movement::JUMP : Movement::FALL;
    else if (isRunning())
        next = Movement::RUN;
    else
        next = Movement::IDLE;

    if (next != mMovement) setMovement(next);
}

void Mario::updateImmortal(float dt) {
    if (mIsImmortal) {
        mImmortalTimer -= dt;
        if (mImmortalTimer <= 0) {
            mImmortalTimer = mImmortalTime;
            mIsImmortal = false;
        }
    }
}

void Mario::setMovement(Movement Movement) {
    mMovement = Movement;
    Texture2D* texture = nullptr;
    bool repeat = true;

    switch (mForm) {
        case Form::NORMAL :
            switch (mMovement) {
                case Movement::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
                    break;
                case Movement::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_N_RUN);
                    break;
                case Movement::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
                    repeat   = false;     
                    break;
                case Movement::FALL:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
                    repeat   = false;
                    break;
            }
            break;

        case Form::SUPER :
            switch (mMovement) {
                case Movement::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
                    break;
                case Movement::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_S_RUN);
                    break;
                case Movement::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
                    repeat   = false;
                    break;
                case Movement::FALL:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
                    repeat   = false;
                    break;
            }
            break;

        case Form::FIRE :
            switch (mMovement) {
                case Movement::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
                    break;
                case Movement::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_F_RUN);
                    break;
                case Movement::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
                    repeat   = false;     
                    break;
                case Movement::FALL:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
                    repeat   = false;
                    break;
            }
            break;

        default:
            break;
    }

    if (texture) {
        Vector2 size = (mForm == Form::NORMAL) ? Vector2{16, 16} : Vector2{16, 32};
        mAnimation.setTexture(texture, size.x, size.y);
        mAnimation.setRepeating(repeat, false);
        mAnimation.restart();   
    }

    if (mIsGround) mIsRight = (getVelocity().x >= 0);
}

void Mario::setForm(Form form) {
    if (mForm == form) return;
    mForm = form;
    setMovement(mMovement);
}

void Mario::setImmortal(bool flag) {
    mIsImmortal = flag;
}

void Mario::handle() {
    
}