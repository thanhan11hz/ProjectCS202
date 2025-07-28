#pragma once

#include <memory>
#include <vector>
#include <raylib.h>
#include <raymath.h>

#include "Entity/Animation.hpp"
#include "Global.hpp"

class Effect {
    public:
        Effect() = default;
        virtual void draw() = 0;
        virtual bool update(float dt) = 0;
    private:
};

class EffectManager {
    public:
        EffectManager();
        void draw();
        void update(float dt);
        void addEffect(std::unique_ptr<Effect> effect);
    private:
        std::vector<std::unique_ptr<Effect>> mEffect;

};

class PointEffect : public Effect {
    public:
        PointEffect();
        virtual void draw();
        virtual bool update(float dt);
    private:
        std::string mText;
        static constexpr float mDuration = 2.0f;
        float mTimer = 0.0f;
        Vector2 mPosition;
};

class CoinEffect : public Effect {
    public:
        CoinEffect();
        virtual void draw();
        virtual bool update(float dt);
    private:
        // Animation mAnim;
        Vector2 mPosition;
        Vector2 mVelocity;
        Vector2 startPosition;
};

class DeathEffect : public Effect {
    public:
        DeathEffect();
        virtual void draw();
        virtual bool update(float dt);
    private:
        Texture2D mTexture;
        Vector2 mPosition;
        Vector2 mVelocity;
        static constexpr float mDuration = 2.0f;
};