#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "World/Effect.hpp"
#include "Global.hpp"

class Goomba : public Enemy {
    public:
        enum class Move : unsigned int {
            RUN,
            DEAD
        };

        enum class Type : unsigned int {
            BROWN_GOOMBA,
            BLUE_GOOMBA
        };

        Goomba(Type type);
        Goomba(const nlohmann::json& j);

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        virtual void serialize(nlohmann::json& j);

        static std::unique_ptr<Goomba> spawnGoomba1(Vector2 position);
        static std::unique_ptr<Goomba> spawnGoomba2(Vector2 position);
        std::unique_ptr<Enemy> clone() const {
            return Enemy::cloneImpl<Goomba>();
        }

    private:
        Move mMove;
        Type mType;
        static constexpr float mDeadTime = 0.25f;
        float mDeadTimer = 0.0f;
        float mSpeed = -100.0f;
        void setMove(Move move);
};