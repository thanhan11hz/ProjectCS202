#pragma once

#include <memory>
#include <map>

#include "Entity/MovingEntity.hpp"
#include "Entity/Animation.hpp"
#include "Entity/Projectile.hpp"
#include "World/World.hpp"
#include "Global.hpp"

class Character : public MovingEntity {
    public:
        enum class Move {
            IDLE, 
            RUN, 
            JUMP, 
            CROUCH, 
            SKID,
        };

        enum class Form {
            NORMAL, 
            SUPER, 
            FIRE
        };
        
        Character(int length, int high);
        virtual void handle();
        virtual void draw();
        virtual void update(float dt);

        static std::unique_ptr<Character> spawnMario();
        static std::unique_ptr<Character> spawnLuigi();

        virtual Vector2 getSize();

        std::map<Move,Texture2D> mNormal;
        std::map<Move,Texture2D> mFire;
        std::map<Move,Texture2D> mSuper;

        Texture2D mDeath;

        virtual void handleCollision(Side side, Collide other);

        virtual std::string getTag();

    private:
        Move mMove = Move::IDLE;
        void updateMove();
        void setMove(Move move);

        Form mForm = Form::NORMAL;
        void setForm(Form form);

        static constexpr float mImmortalTime = 5.0f;
        float mImmortalTimer;
        bool mIsImmortal = false;
        void updateImmortal(float dt);
        void setImmortal(bool flag);

        static constexpr float invincibleTime = 2.0f;
        float invincibleTimer = 2.0f;

        float transitionProgress = 1.0f;

        void fire();
        static constexpr float mCooldownTime = 1.0f;
        float mCooldown = 1.0f;

        float mHigh;
        float mLength;

        void damage();

        std::map<Action, KeyboardKey> &mKey;
};