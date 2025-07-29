#pragma once

#include "Entity/MovingEntity.hpp"
#include "Global.hpp"

class Enemy : public MovingEntity {
    public:
        Enemy();

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual Vector2 getSize() = 0;

        virtual std::string getTag();

        void setActive(bool flag);
        bool isActive();

        virtual ~Enemy() = default;
    private:
        bool mIsActive = false;

};