// #pragma once

// #include "Mario.hpp"

// class MarioForm {
    
//     public:
//         MarioForm(Mario* mMario);
//         virtual void update(float dt) = 0;
//         virtual void draw() = 0;
//         virtual void fire() = 0;
//         virtual void onEnter() = 0;
//         virtual void onExit() = 0;
//         virtual ~MarioForm() = default;

//     private:
//         Mario* mMario;
// };

// class NormalForm : public MarioForm {

//     public:
//         NormalForm(Mario* mMario);
//         void update(float dt) override;
//         void draw() override;
//         void fire() override;

//     private:
// };

// class SuperForm : public MarioForm {

//     public:
//         SuperForm(Mario* mMario);
//         void update(float dt);
//         void draw() override;
//         void fire() override;

//     private:
// };

// class FireForm : public MarioForm {

//     public:
//         FireForm(Mario* mMario);
//         void update(float dt);
//         void draw() override;
//         void fire() override;

//     private:
// };