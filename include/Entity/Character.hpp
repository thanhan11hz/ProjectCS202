#pragma once

#include <memory>
#include <map>

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"
#include "Entity/Collide.hpp"

class Character : public Entity {
    public:
        enum class Move {
            IDLE, 
            RUN, 
            JUMP, 
            CROUCH, 
            SKID,
            DEAD
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

        // handleCollision signature remains consistent with Entity.hpp
        virtual void handleCollision(Side side, Category other); 

    private:
        Move mMove = Move::IDLE;
        Form mForm = Form::FIRE;
        static constexpr float mImmortalTime = 5.0f;
        float mImmortalTimer;
        bool mIsImmortal = false;
        void updateMove();
        void setMove(Move move);
        void updateImmortal(float dt);
        void setImmortal(bool flag);
        void setForm(Form form);

        Animation mAnim;

        float mHigh;
        float mLength;

        std::map<Action, KeyboardKey> &mKey;
};