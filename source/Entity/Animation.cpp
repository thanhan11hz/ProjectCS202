#include "Entity/Animation.hpp"

Animation::Animation(Texture2D* texture, float frameW, float frameH, float dur, bool repeat) 
    : mTexture(texture), mFrameSize{frameW, frameH}, mDuration(dur), mRepeat(repeat), mCurrentColor(0) {
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
    if (mRepeat) {
        mCurrentFrames = newFrame % mFrameCount;
    }
    else mCurrentFrames = (newFrame < mFrameCount) ? newFrame : mFrameCount - 1;

}

void Animation::draw(Vector2 position, float scale, float rotation, bool flipX, bool flipY, bool colorBlink, Color tint) {
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

    if (flipY) {
        src.width *= -1;
    }

    Rectangle dst = {
        position.x,
        position.y,
        mFrameSize.x * scale,
        mFrameSize.y * scale
    };
    if (colorBlink) {
        switch (mCurrentColor) {
        case 0:
            tint = WHITE;
            break;
        case 1:
            tint = RED;
            break;
        case 2:
            tint = ORANGE;
            break; 
        case 3:
            tint = YELLOW;
            break;
        case 4:
            tint = GREEN;
            break;
        case 5:
            tint = BLUE;
            break;
        case 6:
            tint = PURPLE;
            break;
        case 7:
            tint = VIOLET;
            break;
        default:
            break;
        }

        mCurrentColor = (mCurrentColor + 1) % 8;
    } 

    DrawTexturePro(*mTexture, src, dst, {0, 0}, rotation, tint);
}

void Animation::drawScale(Vector2 position, float scaleX, float scaleY, float rotation, bool flipX, bool flipY, bool colorBlink, Color tint) {
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

    if (flipY) {
        src.width *= -1;
    }

    Rectangle dst = {
        position.x,
        position.y,
        mFrameSize.x * scaleX,
        mFrameSize.y * scaleY
    };

    if (colorBlink) {
        switch (mCurrentColor) {
        case 0:
            tint = {231, 32, 32};
            break;
        case 1:
            tint = {77, 227, 42};
            break;
        case 2:
            tint = {40, 202, 225};
            break; 
        case 3:
            tint = {244, 119, 220};
            break;
        case 4:
            tint = {251, 242, 48};
            break;
        default:
            break;
        }

        mCurrentColor = (mCurrentColor + 1) % 5;
    } 
    DrawTexturePro(*mTexture, src, dst, {0, 0}, rotation, tint);
}


void Animation::setFrameSize(Vector2 size) {
    mFrameSize = size;
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