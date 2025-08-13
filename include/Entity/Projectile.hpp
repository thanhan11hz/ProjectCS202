#pragma once

#include <memory>
#include <cmath>

#include "Entity/Entity.hpp"
#include "Global.hpp"

class FireBall : public Entity {
    public:
        FireBall(bool isRight);
        FireBall(const nlohmann::json& j);

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        virtual void serialize(nlohmann::json& j);

        static std::unique_ptr<FireBall> spawnFireBall(Vector2 position, bool isRight);
    private:
        float mSpeedX = 400.0f;
};

class BowserFire: public Entity {
    public:
        BowserFire(bool isRight);
        BowserFire(const nlohmann::json& j);

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);

        virtual Vector2 getSize();

        virtual std::string getTag();

        virtual void serialize(nlohmann::json& j);

        static std::unique_ptr<BowserFire> spawnBowserFire(Vector2 position, bool isRight);
        
    private:
        float mSpeed = 300.0f;
        bool isRight;
};