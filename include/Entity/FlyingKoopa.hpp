#pragma once

#include "Entity/Enemy.hpp"
#include "Global.hpp"

class FlyingKoopa : public Enemy {
    public:
        FlyingKoopa();
        FlyingKoopa(const nlohmann::json& j);

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        virtual void serialize(nlohmann::json& j);

    private:
        Vector2 mFixedPoint;
        float mSpeed = -50.0f;
};