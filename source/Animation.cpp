#include "Animation.hpp"

Animation::Animation(Texture2D& texture, int frameW, int frameH, float dur, bool repeat) 
    : mTexture(texture), mCols(texture.width / frameW), mRows(texture.height / frameH),
    mFrameCount(mCols * mRows), mDuration(dur), mRepeat(repeat) {}
        
void Animation::setFrameDuration(float dt) {
    mDuration = dt;
}
        
void Animation::setRepeating(bool flag) {
    mRepeat = flag;
}
        
bool Animation::isFinished() const {
    return (!mRepeat && mCurrentFrames == mFrameCount - 1);
}
        
bool Animation::isRepeating() const {
    return mRepeat;
}
        
void Animation::restart() {
    mCurrentFrames = 0;
    mElapsedTime = 0.0f;
}
        
void Animation::update(float dt) {
    if (isFinished()) return;
    mElapsedTime += dt;
    while (mElapsedTime > mDuration) {
        mElapsedTime -= mDuration;
        mCurrentFrames ++;
        if (mCurrentFrames >= mFrameCount) {
            if (mRepeat) mCurrentFrames = 0;
            else {
                mCurrentFrames = mFrameCount - 1;
                break;
            }
        }
        int col = mCurrentFrames % mCols;
        int row = mCurrentFrames / mCols;
        mSource.x = (float) mSource.width * col;
        mSource.y = (float) mSource.height * row;
    }
}

void Animation::draw(Vector2 position, float scale, float rotation, Color tint) {
    Rectangle destination = {position.x, position.y, mSource.width * scale, mSource.height * scale};
    Vector2 origin = {destination.width / 2.0f, destination.height / 2.0f};
    DrawTexturePro(mTexture, mSource, destination, origin, rotation, tint);
}