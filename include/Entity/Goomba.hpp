#pragma once

#include <memory>

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class Goomba : public Entity {
    public:
        enum class Move {
            RUN,
            DEAD
        };

        Goomba();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Category other);
        virtual Vector2 getSize();

        Texture2D mRun;
        Texture2D mDie;

        static std::unique_ptr<Goomba> spawnGoomba1();
        static std::unique_ptr<Goomba> spawnGoomba2();

    private:
        Move mMove;
        Animation mAnim;
        static constexpr float mDeadTime = 1.0f;
        float mDeadTimer = 0;
        bool mIsDead = false;
        float mSpeed = 100.0f;
        void setMove(Move move);
};