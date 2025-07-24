#pragma once

#include "Entity/Entity.hpp"

class Goomba : public Entity {
    public:
        Goomba();
        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;
    private:

};