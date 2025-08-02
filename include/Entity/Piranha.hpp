#pragma once

#include <memory>

#include "Entity/Enemy.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class Piranha : public Enemy {
    public: 
        enum class Move {
            FLY,
            ATTACK
        };
        Piranha();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Collide other);
        virtual Vector2 getSize();

        virtual std::string getTag();

        static std::unique_ptr<Piranha> spawnPiranha1(Vector2 position);
        static std::unique_ptr<Piranha> spawnPiranha2(Vector2 position);

        void setFixedPoint(Vector2 point);
        void setTexture(Texture2D& texture);

    private:
        Move mMove = Move::FLY;
        static constexpr float attackTime = 2.0f;
        float attackTimer = 0.0f;
        float mSpeed = -50.0f;
        Vector2 mFixedPoint;
        void updateMove(float dt);
};