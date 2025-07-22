#pragma once

#include "Entity/Character.hpp"

class Luigi : public Character {
    public:
        virtual void handle();
        virtual void draw();
        virtual void update(float dt);
    private:
};