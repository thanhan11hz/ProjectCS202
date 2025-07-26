#pragma once

#include <memory>
#include <vector>

class Effect {

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