
#include "Entity/Luigi.hpp"
#include "Global.hpp"

Luigi::Luigi() : Mario() {
    mAnimation = Animation(&Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE), 16, 16, 0.5f, true);
    setForm(Form::NORMAL);
}

void Luigi::draw() {
    mAnimation.draw(getPosition(), 2.f, 0.0f, !mIsRight);
}

void Luigi::update(float dt) {
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

void Luigi::startJump() {
    if (mIsGround && !mIsJump) {
        mIsGround = false;
        mIsJump = true;
        mVelocity.y = - std::sqrt(2.0f * Gravity * 128.f * 1.1f);
    }
}

// void Luigi::setAction(Action action) {
//     mAction = action;
//     Texture2D* texture = nullptr;
//     bool repeat = true;

//     switch (mForm) {
//         case Form::NORMAL :
//             switch (mAction) {
//                 case Action::IDLE:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_N_IDLE);
//                     break;
//                 case Action::RUN:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_N_RUN);
//                     break;
//                 case Action::JUMP:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_N_JUMP);
//                     repeat   = false;
//                     break;
//                 case Action::FALL:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_N_JUMP);
//                     repeat   = false;
//                     break;
//             }
//             break;

//         case Form::SUPER :
//             switch (mAction) {
//                 case Action::IDLE:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_S_IDLE);
//                     break;
//                 case Action::RUN:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_S_RUN);
//                     break;
//                 case Action::JUMP:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
//                     repeat   = false;
//                     break;
//                 case Action::FALL:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_S_JUMP);
//                     repeat   = false;
//                     break;
//             }
//             break;

//         case Form::FIRE :
//             switch (mAction) {
//                 case Action::IDLE:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_F_IDLE);
//                     break;
//                 case Action::RUN:
//                     texture = &Resource::mTexture.get(TextureIdentifier::LUIGI_F_RUN);
//                     break;
//                 case Action::JUMP:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_F_JUMP);
//                     repeat   = false;
//                     break;
//                 case Action::FALL:
//                     texture  = &Resource::mTexture.get(TextureIdentifier::LUIGI_F_JUMP);
//                     repeat   = false;
//                     break;
//             }
//             break;

//         default:
//             break;
//     }

//     if (texture) {
//         Vector2 size = (mForm == Form::NORMAL) ? Vector2{16, 16} : Vector2{16, 32};
//         mAnimation.setTexture(texture, size.x, size.y);
//         mAnimation.setRepeating(repeat, false);
//         mAnimation.restart();
//     }

//     if (mIsGround) mIsRight = (getVelocity().x >= 0);
// }

void Luigi::setForm(Form form) {
    if (mForm == form) return;
    mForm = form;
    setAction(mAction);
}

void Luigi::setImmortal(bool flag) {
    mIsImmortal = flag;
}