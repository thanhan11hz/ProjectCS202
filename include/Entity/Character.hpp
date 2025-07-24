#pragma once

#include <memory>
#include <map>

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"
#include "Global.hpp"

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
        
        Character();
        virtual void handle();
        virtual void draw();
        virtual void update(float dt);

        static std::unique_ptr<Character> spawnMario();
        static std::unique_ptr<Character> spawnLuigi();

        virtual Vector2 getSize();

        std::map<Move,Texture2D> mNormal;
        std::map<Move,Texture2D> mFire;
        std::map<Move,Texture2D> mSuper;

    private:
        Move mMove;
        Form mForm;
        static constexpr float mImmortalTime = 5.0f;
        float mImmortalTimer;
        bool mIsImmortal;
        void updateMove();
        void setMove(Move move);
        void updateImmortal(float dt);
        void setImmortal(bool flag);
        void setForm(Form form);

        Animation mAnim;

        std::map<Action, KeyboardKey> &mKey;
};