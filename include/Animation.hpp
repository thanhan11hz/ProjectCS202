#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

class Animation {
    public:
        explicit Animation(Texture2D& texture, int frameW, int frameH, float dur, bool repeat);
        void setFrameDuration(float dt);
        void setRepeating(bool flag);
        bool isFinished() const;
        bool isRepeating() const;
        void restart();
        void update(float dt);
        void draw(Vector2 position, float scale, float rotation, Color tint);

    private:
        Texture2D& mTexture;
        Rectangle mSource;
        int mCols, mRows;
        int mFrameCount;
        std::size_t mCurrentFrames;
        float mDuration;
        float mElapsedTime;
        bool mRepeat;
};