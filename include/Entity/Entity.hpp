#pragma once

#include <raylib.h>
#include <raymath.h>

#include "World/SceneNode.hpp"

class Entity : public SceneNode {
    public:
        Entity(int hitPoint = 1);
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

    protected:
        void updateCurrent(float dt);
    
    private:
        Vector2 mVelocity;
        int mHitPoint;
};