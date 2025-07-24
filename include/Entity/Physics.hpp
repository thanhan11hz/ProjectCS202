#pragma once

#include <raylib.h>
#include <raymath.h>
#include <algorithm>  
#include <cmath>
#include <iostream>

class Physics {
    public:

        Physics();
        void setPosition(Vector2 postion);
        Vector2 getPosition() const;
        void setVelocity(Vector2 velocity);
        void setVelocity(float vx, float vy);
        Vector2 getVelocity() const;
        void accelerate(Vector2 dv);
        void accelerate(float vx, float vy);
        void startJump(int high);
        void endJump();
        bool onGround();
        void setOnGround(bool flag);
        bool isRunning();
        bool isRest();
        bool isRising();
        bool isRight();
        void setDensity(float density);
        void update(float dt);

    private:

        Vector2 mPosition;
        Vector2 mVelocity;
        bool mIsGround;
        bool mIsRight;
        float mDensity = 1.0f;
        static constexpr float Gravity  = 950.0f;
        static constexpr float Friction = 30.0f;
        static constexpr float AirDrag  = 40.0f;
        static constexpr float Eps      = 5.0f;
        void applyGravity(float dt);
        void applyDrag(float dt);
};