#pragma once

#include "Mario.hpp"

class MarioForm {

    friend class Mario;
    
    public:
        MarioForm(Mario* mMario);
        virtual void update(float dt) = 0;
        virtual void draw() = 0;
        virtual void fire() = 0;

    private:
        Mario* mMario;
        virtual ~MarioForm() = default;
};

class NormalForm : public MarioForm {

    public:
        explicit NormalForm(Mario* mMario);
        void update(float dt);
        void draw();
        void fire();

    private:
        Animation mRun;
        Animation mIdle;
        Animation mJump;
};

class SuperForm : public MarioForm {

    public:
        explicit SuperForm(Mario* mMario);
        void update(float dt);
        void draw();
        void fire();

    private:
        Animation mRun;
        Animation mIdle;
        Animation mJump;
        Animation mCrouch;
};

class FireForm : public MarioForm {

    public:
        explicit FireForm(Mario* mMario);
        void update(float dt);
        void draw();
        void fire();

    private:
        Animation mRun;
        Animation mIdle;
        Animation mJump;
        Animation mCrouch;
};