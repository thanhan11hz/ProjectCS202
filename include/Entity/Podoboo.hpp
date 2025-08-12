#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "Global.hpp"

class Podoboo : public Enemy {
    public:
        Podoboo();
        Podoboo(const nlohmann::json& j);

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        virtual void serialize(nlohmann::json& j);

        void setRestPoint(Vector2 position);
        std::unique_ptr<Enemy> clone() const {
            return Enemy::cloneImpl<Podoboo>();
        }

        static std::unique_ptr<Podoboo> spawnPodoboo(Vector2 postion);

    private:
        static constexpr float mRestTime = 2.0f;
        float mRestTimer = 0.0f;
        bool mIsRest = false;
        Vector2 mRestPoint;

};