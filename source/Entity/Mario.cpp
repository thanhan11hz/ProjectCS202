#include "Entity/Mario.hpp"

Mario::Mario(): mAnimation(nullptr, 16, 16, 0.5f, true), mAction(Action::IDLE) , mIsRight(true)
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
    updateAction();
    mAnimation.update(dt);
}

void Mario::updateAction() {
    Action next = mAction;           

    if (!mIsGround)                      
        next = isRising() ? Action::JUMP : Action::FALL;
    else if (isRunning())
        next = Action::RUN;
    else
        next = Action::IDLE;

    if (next != mAction) setAction(next);
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

void Mario::setAction(Action action) {
    mAction = action;
    Texture2D* texture = nullptr;
    bool repeat = true;

    switch (mForm) {
        case Form::NORMAL :
            switch (mAction) {
                case Action::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_N_IDLE);
                    break;
                case Action::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_N_RUN);
                    break;
                case Action::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
                    repeat   = false;     
                    break;
                case Action::FALL:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_N_JUMP);
                    repeat   = false;
                    break;
            }
            break;

        case Form::SUPER :
            switch (mAction) {
                case Action::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_S_IDLE);
                    break;
                case Action::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_S_RUN);
                    break;
                case Action::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
                    repeat   = false;
                    break;
                case Action::FALL:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_S_JUMP);
                    repeat   = false;
                    break;
            }
            break;

        case Form::FIRE :
            switch (mAction) {
                case Action::IDLE:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_F_IDLE);
                    break;
                case Action::RUN:
                    texture = &Resource::mTexture.get(TextureIdentifier::MARIO_F_RUN);
                    break;
                case Action::JUMP:
                    texture  = &Resource::mTexture.get(TextureIdentifier::MARIO_F_JUMP);
                    repeat   = false;     
                    break;
                case Action::FALL:
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
    setAction(mAction);
}

void Mario::setImmortal(bool flag) {
    mIsImmortal = flag;
}