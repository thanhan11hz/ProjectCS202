#pragma once

#include "Entity/Physics.hpp"
#include "Entity/Collide.hpp"

class Entity {
    public:
        Entity();

        Physics mPhysics;
        Collide mBodyCollide;

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual void handleFootCollision();
        virtual Vector2 getSize() = 0;

        virtual std::string getTag();

        virtual ~Entity() = default;
};