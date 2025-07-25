#pragma once

#include <memory>

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class Piranha : public Entity {
    public: 
        enum class Move {
            FLY,
            ATTACK
        };
        Piranha();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Category other);
        virtual Vector2 getSize();

        Texture2D mFly;
        Texture2D mAttack;

        static std::unique_ptr<Piranha> spawnPiranha1();
        static std::unique_ptr<Piranha> spawnPiranha2();

        void setFixedPoint(Vector2 point);

    private:
        Move mMove;
        Animation mAnim;
        static constexpr float attackTime = 3.0f;
        float attackTimer = 0.0f;
        float mSpeed = 100.0f;
        Vector2 mFixedPoint;
        void updateMove(float dt);
        void setMove(Move move);
};