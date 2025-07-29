#pragma once
#include <memory>
#include "Entity/Physics.hpp"
#include "Entity/Collide.hpp"

class Entity {
    public:
        Entity();

        Physics mPhysics;
        Collide mCollide;

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        void setDie(bool flag);
        bool isDie();

        virtual void handleCollision(Side side, Category other) = 0;
        virtual Vector2 getSize() = 0;

    private:
        bool mIsDie = false;
};