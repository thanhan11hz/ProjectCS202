#pragma once

#include <memory>

#include "Entity/MovingEntity.hpp"
#include "Global.hpp"

class FireBall : public MovingEntity {
    public:
        FireBall();
        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        std::unique_ptr<FireBall> spawnFireBall(Vector2 position);
    private:
        bool isDown = true;
        size_t mLives = 3;
};

class BowserFire: public MovingEntity {
    public:
        BowserFire();
        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        std::unique_ptr<BowserFire> spawnBowserFire(Vector2 position, float speed);

        void setSpeed(float speed);
        
    private:
        float mSpeed;
};