#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <cassert>

class Animation {
    public:
        explicit Animation(Texture2D* texture, float frameW, float frameH, float dur = 1.0f, bool repeat = true);
        void setTexture(Texture2D* texture, float frameW, float frameH);
        void setFrameDuration(float dt);
        void setRepeating(bool flag, bool restartWhenEnable);
        bool isFinished() const;
        bool isRepeating() const;
        void restart();
        void update(float dt);
        void draw(Vector2 position, float scale = 1.0f, float rotation = 0.0f, bool flipX = false, Color tint = WHITE);
        Vector2 getFrameSize() const;
    
    private:
        Texture2D* mTexture;
        Vector2 mFrameSize;
        int mFrameCount;
        int mCol, mRow;
        std::size_t mCurrentFrames;
        float mDuration;
        float mElapsed;
        bool mRepeat;
        void init();
};