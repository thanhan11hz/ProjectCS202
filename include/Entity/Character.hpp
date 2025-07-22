#pragma once

#include "Entity/Entity.hpp"

class Character : public Entity {
    public:
        virtual void handle() = 0;
        virtual void draw() = 0;
        virtual void update(float dt) = 0;
    private:
};