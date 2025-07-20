#pragma once

#include "Entity/Entity.hpp"
#include "Entity/Animation.hpp"

class Coin: public Entity {
    public:
        Coin();
        void update(float dt);
        void draw();
    private:
        Animation mAnim;
        bool isCollected;
};