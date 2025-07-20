#pragma once

#include "Entity/Entity.hpp"

class Goomba : public Entity {
    public:
        Goomba();
        void update(float dt);
        void draw();
        void die();
    private:
        bool isDead;
};