#pragma once

#include "Entity/Entity.hpp"
#include "Animation.hpp"
#include "Global.hpp"

class Mario : public Entity {
    public:
        enum class Action {IDLE, RUN, JUMP, FALL, CROUCH, SKID, DEAD};
        enum class Form {NORMAL, SUPER, FIRE};
        explicit Mario();  
        Animation mAnimation;
        virtual void draw();
        virtual void update(float dt);

    private:
        Action mAction;
        Form mForm;
        bool mIsRight;
        bool mIsImmortal;

        static constexpr float mImmortalTime = 200.f;
        float mImmortalTimer;

        void updateAction();
        void updateImmortal(float dt);
        void setAction(Action action);
        void setForm(Form form);
        void setImmortal(bool flag);
};