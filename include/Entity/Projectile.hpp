#pragma once

#include <memory>
#include <cmath>

#include "Entity/MovingEntity.hpp"
#include "Global.hpp"

class FireBall : public MovingEntity {
    public:
        FireBall(bool isRight);
        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        static std::unique_ptr<FireBall> spawnFireBall(Vector2 position, bool isRight);
    private:
        float mSpeedX = 400.0f;
        float mBoundSpeed = -std::sqrt(2 * 850 * 2 * 48.0f);
};

class BowserFire: public MovingEntity {
    public:
        BowserFire(bool isRight);
        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        static std::unique_ptr<BowserFire> spawnBowserFire(Vector2 position, bool isRight);
        
    private:
        float mSpeed = 300.0f;
        bool isRight;
};