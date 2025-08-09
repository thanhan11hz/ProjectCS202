#pragma once

#include <memory>
#include <cmath>

#include "Entity/Enemy.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class FireBar : public Enemy {
    public:
        FireBar();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        void setCircle(Vector2 center, float radius);

        static std::vector<std::unique_ptr<FireBar>> spawnFireBar(Vector2 position);

    private:
        Vector2 mCenter;
        float mRadius;
        static constexpr float angularVelocity = 3.0f;
        float mAngle = 0.0f;

};