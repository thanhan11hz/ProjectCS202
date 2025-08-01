#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class Bowser : public Enemy {
    public:
        enum class Move {
            MOVE,
            ATTACK
        };
        Bowser();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        void setCenter(Vector2 position);

        static std::unique_ptr<Bowser> spawnBowser(Vector2 position);
    private:
        Move mMove = Move::MOVE;
        static constexpr float mAttackTime = 2.0f;
        float mAttackTimer = 0.0f;
        static constexpr float mCooldownTime = 2.0f;
        float mCooldownTimer = 0.0f;
        float mSpeed = 50.0f;
        Vector2 mCenter;
        float mAmplitude = 96.0f;
        float jumpChance = 0.3f;
        void setMove(Move move);
        void fire();
        size_t mLives = 3;
};