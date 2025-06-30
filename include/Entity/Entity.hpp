#pragma once

#include <raylib.h>
#include <raymath.h>
#include <algorithm>  
#include <cmath>

#include "World/SceneNode.hpp"

class Entity : public SceneNode {
    public:
        explicit Entity(int hitPoint = 1);

        void setPosition(Vector2 postion);
        Vector2 getPosition() const;

        void setVelocity(Vector2 velocity);
        void setVelocity(float vx, float vy);
        Vector2 getVelocity() const;

        void accelerate(Vector2 dv);
        void accelerate(float vx, float vy);

        void repair(int points);
        void damage(int points);
        void destroy();
        int getHitPoints();
        bool isDestroy();

        void startJump();
        void endJump();

    protected:

        bool mIsJump;
        bool mIsGround;
        virtual void updateCurrent(float dt);
        bool isRunning();
        bool isRest();
        bool isRising();

    private:
        Vector2 mPosition;
        Vector2 mVelocity;
        int mHitPoint;

        static constexpr float Gravity  = 950.f;
        static constexpr float Friction = 30.f;
        static constexpr float AirDrag  = 40.f;
        static constexpr float Eps      = 5.f;
        void applyGravity(float dt);
        void applyDrag(float dt);
};