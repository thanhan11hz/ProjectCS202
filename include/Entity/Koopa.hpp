#pragma once

#include <memory>

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

class Koopa : public Entity {
    public:
        enum class Move {
            RUN,
            SHELL
        };

        Koopa();

        virtual void update(float dt);
        virtual void handle();
        virtual void draw();

        virtual void handleCollision(Side side, Category other);
        virtual Vector2 getSize();

        Texture2D mRun;
        Texture2D mDie;

        static std::unique_ptr<Koopa> spawnKoopa1();
        static std::unique_ptr<Koopa> spawnKoopa2();

    private:
        Move mMove;
        Animation mAnim;
        float mSpeed = 100.0f;
        void setMove(Move move);
};