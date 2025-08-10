#include "World/Effect.hpp"
#include "World/World.hpp"

// Effect Manager

EffectManager::EffectManager() {

}

// void EffectManager::draw() {
//     for (int i = 0; i < mEffect.size(); ++i) {
//         mEffect[i]->draw();
//     }
// }

void EffectManager::draw(Camera2D& camera) {
    Rectangle cameraView = {
        camera.target.x - camera.offset.x,
        camera.target.y - camera.offset.y,
        (float)targetWidth,
        (float)targetHeight
    };

    for (int i = 0; i < mEffect.size(); ++i) {
        Rectangle effectRect = mEffect[i]->getBounds();

        // Only draw if the effect is on screen
        if (CheckCollisionRecs(cameraView, effectRect)) {
            mEffect[i]->draw();
        }
    }
}

void EffectManager::update(float dt) {
    for (auto itr = mEffect.begin(); itr != mEffect.end();) {
        if (!(*itr)->update(dt)) itr = mEffect.erase(itr);
        else ++itr;
    }
}

void EffectManager::addEffect(std::unique_ptr<Effect> effect) {
    mEffect.push_back(std::move(effect));
}

bool EffectManager::isEmpty() const {
    return mEffect.size() == 0;
}

// Point Effect

PointEffect::PointEffect(Vector2 position, std::string text) : mText(text) {
    mPosition = position;
}
    
void PointEffect::draw() {
    if (mTimer > mDuration) return;
    DrawTextEx(GetFontDefault(), mText.c_str(), mPosition, 30, 5, WHITE);
}
        
bool PointEffect::update(float dt) {
    if (mTimer > mDuration) return false;
    mTimer += dt;
    mPosition += Vector2{50, -50} * dt;
    return true;
}

std::unique_ptr<PointEffect> PointEffect::spawnPointEffect(Vector2 position, std::string text) {
    std::unique_ptr<PointEffect> mEffect = std::make_unique<PointEffect>(position, text);
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

DeathEffect::DeathEffect(Vector2 position, Texture2D texture, bool flipY) {
    isFlipY = flipY;
    mTexture = texture;
    mPosition = position;
    mVelocity = {0, (float)- std::sqrt(2 * 850 * 48)};
}

void DeathEffect::draw() {
    DrawTexturePro(mTexture, {0, 0, (float)mTexture.width, (isFlipY ? -1 : 1) * (float)mTexture.height}, {mPosition.x, mPosition.y, (float)mTexture.width * 3, (float)mTexture.height * 3}, {0, 0}, 0.0f, WHITE);
}

bool DeathEffect::update(float dt) {
    Vector2 screenPos = GetWorldToScreen2D(mPosition, mWorld.getCamera());
    if (screenPos.y > targetWidth) return false;
    mVelocity += {100 * dt, 850 * dt};
    mPosition += mVelocity * dt;
    return true;
}

std::unique_ptr<DeathEffect> DeathEffect::spawnDeathEffect(Vector2 position, Texture2D texture, bool flipY) {
    std::unique_ptr<DeathEffect> mEffect = std::make_unique<DeathEffect>(position, texture, flipY);
    return std::move(mEffect);
}

// Explosion Effect

ExplosionEffect::ExplosionEffect(Vector2 position) : mAnim(nullptr, 16, 16, 0.3f, false) {
    mPosition = position;
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::EXPLOSION), 16, 16);
}

void ExplosionEffect::draw() {
    mAnim.draw(mPosition, 3.0f);
}

bool ExplosionEffect::update(float dt) {
    if (mAnim.isFinished()) return false;
    mAnim.update(dt);
    return true;
}
        
std::unique_ptr<ExplosionEffect> ExplosionEffect::spawnExplosionEffect(Vector2 position) {
    std::unique_ptr<ExplosionEffect> explosion = std::make_unique<ExplosionEffect>(position);
    return std::move(explosion);
}

Rectangle PointEffect::getBounds() {
    return { mPosition.x, mPosition.y, 120, 30 };
}

Rectangle CoinEffect::getBounds() {
    Vector2 size = mAnim.getFrameSize();
    return { mPosition.x, mPosition.y, size.x * 3.0f, size.y * 3.0f };
}

Rectangle DeathEffect::getBounds() {
    return { mPosition.x, mPosition.y, mTexture.width * 3.0f, mTexture.height * 3.0f };
}

Rectangle ExplosionEffect::getBounds() {
    Vector2 size = mAnim.getFrameSize();
    return { mPosition.x, mPosition.y, size.x * 3.0f, size.y * 3.0f };
}