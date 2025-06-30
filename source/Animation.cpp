#include "Animation.hpp"

Animation::Animation(Texture2D* texture, float frameW, float frameH, float dur, bool repeat) 
    : mTexture(texture), mFrameSize{frameW, frameH}, mDuration(dur), mRepeat(repeat) {
        if (texture) init();
    }

void Animation::setTexture(Texture2D* texture, float frameW, float frameH) {
    mTexture = texture;
    mFrameSize = {frameW, frameH};
    if (texture) init();
}
        
void Animation::setFrameDuration(float dt) {
    mDuration = dt;
}
        
void Animation::setRepeating(bool flag, bool restartWhenEnable) {
    if (!mRepeat && flag && restartWhenEnable) restart();
    mRepeat = flag;
}
        
bool Animation::isFinished() const {
    return (!mRepeat && mCurrentFrames >= mFrameCount - 1 && mElapsed >= mDuration);
}
        
bool Animation::isRepeating() const {
    return mRepeat;
}
        
void Animation::restart() {
    mCurrentFrames = 0;
    mElapsed = 0.0f;
}
        
void Animation::update(float dt) {
    if (!mTexture) return;
    mElapsed += dt;
    if (mDuration <= 0) return;
    float frameLength = mDuration / (float) mFrameCount;
    size_t newFrame = mElapsed / frameLength;
    if (mRepeat) mCurrentFrames = newFrame % mFrameCount;
    else mCurrentFrames = (newFrame < mFrameCount) ? newFrame : mFrameCount - 1;
}

void Animation::draw(Vector2 position, float scale, float rotation, bool flipX, Color tint) {
    if (!mTexture) return;
    Rectangle src = {
        (float) (mCurrentFrames % mCol) * mFrameSize.x,
        (float) (mCurrentFrames / mCol) * mFrameSize.y,
        mFrameSize.x,
        mFrameSize.y
    };
    if (flipX) {
        src.x += src.width;   
        src.width = -src.width;  
    }

    Rectangle dst = {
        position.x,
        position.y,
        mFrameSize.x * scale,
        mFrameSize.y * scale
    };
    DrawTexturePro(*mTexture, src, dst, {dst.width / 2.0f, dst.height / 2.0f}, rotation, tint);
}

Vector2 Animation::getFrameSize() const {
    return mFrameSize;
}

void Animation::init() {
    assert(mTexture && "Animation: texture cannot be nullptr");
    mCol = mTexture->width / mFrameSize.x;
    mRow = mTexture->height / mFrameSize.y;
    mFrameCount = mCol * mRow;
    restart();
}