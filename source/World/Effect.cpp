#include "World/Effect.hpp"
#include "World/World.hpp"

// Effect Manager

EffectManager::EffectManager() {

}

void EffectManager::draw() {
    for (int i = 0; i < mEffect.size(); ++i) {
        mEffect[i]->draw();
    }
}

void EffectManager::update(float dt) {
    for (auto itr = mEffect.begin(); itr != mEffect.end(); ++itr) {
        if (!(*itr)->update(dt)) mEffect.erase(itr);
    }
}

void EffectManager::addEffect(std::unique_ptr<Effect> effect) {
    mEffect.push_back(std::move(effect));
}

// Point Effect

PointEffect::PointEffect(std::string text) : mText(text) {

}
    
void PointEffect::draw() {
    if (mTimer > mDuration) return;
    DrawTextEx(Resource::mFont.get(FontIdentifier::PixelifySans), mText.c_str(), mPosition, 20, 10, WHITE);
}
        
bool PointEffect::update(float dt) {
    if (mTimer > mDuration) return false;
    mTimer += dt;
    mPosition += Vector2{50, -50} * dt;
    return true;
}

std::unique_ptr<PointEffect> PointEffect::spawnPointEffect(std::string text) {
    std::unique_ptr<PointEffect> mEffect = std::make_unique<PointEffect>(text);
    return std::move(mEffect);
}

// Coin Effect

CoinEffect::CoinEffect(Vector2 position) : mAnim(nullptr, 8, 14, 1.0f, true){
    mVelocity = {0, - std::sqrt(2.0f * 800.0f * 2 * 48.0f)};
    startPosition = position;
    mPosition = position;
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::COIN_EFFECT), 8, 14);
}

void CoinEffect::draw() {
    if (mPosition.y > startPosition.y) return;
    mAnim.draw(mPosition, 3.0f, 0.0f);
}

bool CoinEffect::update(float dt) {
    if (mPosition.y > startPosition.y) return false;
    mVelocity += {0, 800.0f * dt};
    mPosition += mVelocity * dt;
    return true;
}

std::unique_ptr<CoinEffect> CoinEffect::spawnCoinEffect(Vector2 position) {
    std::unique_ptr<CoinEffect> mEffect = std::make_unique<CoinEffect>(position);
    return std::move(mEffect);
}

// Death Effect

DeathEffect::DeathEffect(Texture2D texture, bool flipY) {
    isFlipY = flipY;
    mTexture = texture;
}

void DeathEffect::draw() {
    Vector2 screenPos = GetWorldToScreen2D(mPosition, mWorld.getCamera());
    if (screenPos.y < targetWidth) return;
    DrawTexturePro(mTexture, {0, 0, (float)mTexture.width, (isFlipY ? -1 : 1) * (float)mTexture.height}, {mPosition.x, mPosition.y, (float)mTexture.width * 3, (float)mTexture.height * 3}, {0, 0}, 0.0f, WHITE);
}

bool DeathEffect::update(float dt) {
    Vector2 screenPos = GetWorldToScreen2D(mPosition, mWorld.getCamera());
    if (screenPos.y < targetWidth) return false;
    mPosition += {0, 800 * dt};
    return true;
}

std::unique_ptr<DeathEffect> DeathEffect::spawnDeathEffect(Texture2D texture, bool flipY) {
    std::unique_ptr<DeathEffect> mEffect = std::make_unique<DeathEffect>(texture, flipY);
    return std::move(mEffect);
}