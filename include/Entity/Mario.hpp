#pragma once

#include "Entity/Character.hpp"
#include "Animation.hpp"
#include "Global.hpp"

class Mario : public Character {
    public:
        enum class Movement {IDLE, RUN, JUMP, FALL, CROUCH, SKID, DEAD};
        enum class Form {NORMAL, SUPER, FIRE};
        explicit Mario();  
        Animation mAnimation;
        virtual void handle();
        virtual void draw();
        virtual void update(float dt);

    private:
        Movement mMovement;
        Form mForm;
        bool mIsRight;
        bool mIsImmortal;

        static constexpr float mImmortalTime = 200.f;
        float mImmortalTimer;

        void updateMovement();
        void updateImmortal(float dt);
        void setMovement(Movement movement);
        void setForm(Form form);
        void setImmortal(bool flag);
};