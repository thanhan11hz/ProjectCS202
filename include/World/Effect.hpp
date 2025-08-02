#pragma once

#include <memory>
#include <vector>
#include <raylib.h>

#include "Entity/Animation.hpp"
#include "Global.hpp"

class Effect {
    public:
        Effect() = default;
        virtual void draw() = 0;
        virtual bool update(float dt) = 0;
        virtual Rectangle getBounds() = 0;
        virtual ~Effect() = default;
    private:
};

class EffectManager {
    public:
        EffectManager();
        // void draw();
        void draw(Camera2D& camera);
        void update(float dt);
        void addEffect(std::unique_ptr<Effect> effect);
        
    private:
        std::vector<std::unique_ptr<Effect>> mEffect;

};

class PointEffect : public Effect {
    public:
        PointEffect(Vector2 position, std::string text);
        virtual void draw();
        virtual bool update(float dt);
        virtual Rectangle getBounds() override;
        static std::unique_ptr<PointEffect> spawnPointEffect(Vector2 position, std::string text);
    private:
        std::string mText;
        static constexpr float mDuration = 2.0f;
        float mTimer = 0.0f;
        Vector2 mPosition;
};

class CoinEffect : public Effect {
    public:
        CoinEffect(Vector2 position);
        virtual void draw();
        virtual bool update(float dt);
        virtual Rectangle getBounds() override;
        static std::unique_ptr<CoinEffect> spawnCoinEffect(Vector2 position);
    private:
        Animation mAnim;
        Vector2 mPosition;
        Vector2 mVelocity;
        Vector2 startPosition;
};

class DeathEffect : public Effect {
    public:
        DeathEffect(Vector2 position, Texture2D texture, bool flipY);
        virtual void draw();
        virtual bool update(float dt);
        virtual Rectangle getBounds() override;
        static std::unique_ptr<DeathEffect> spawnDeathEffect(Vector2 position, Texture2D texture, bool flipY);
    private:
        Texture2D mTexture;
        Vector2 mPosition;
        Vector2 mVelocity;
        bool isFlipY;
        static constexpr float mDuration = 2.0f;
};

class ExplosionEffect: public Effect {
    public:
        ExplosionEffect(Vector2 position);
        virtual void draw();
        virtual bool update(float dt);
        virtual Rectangle getBounds() override;
        static std::unique_ptr<ExplosionEffect> spawnExplosionEffect(Vector2 position);
    private:
        Vector2 mPosition;
        Animation mAnim;
};