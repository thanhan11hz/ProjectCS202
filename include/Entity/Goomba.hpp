#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "Entity/Animation.hpp"
#include "World/Effect.hpp"
#include "Global.hpp"

class Goomba : public Enemy {
    public:
        enum class Move {
            RUN,
            DEAD
        };

        Goomba();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        Texture2D mRun;
        Texture2D mDie;
        Texture2D mDeath;

        static std::unique_ptr<Goomba> spawnGoomba1(Vector2 position);
        static std::unique_ptr<Goomba> spawnGoomba2(Vector2 position);

    private:
        Move mMove;
        static constexpr float mDeadTime = 2.0f;
        float mDeadTimer = 0.f;
        float mSpeed = -100.0f;
        void setMove(Move move);
};