#pragma once

#include <box2d/box2d.h>
#include <box2d/base.h>
#include "World/DebugDraw.hpp"
#include "Entity/UserData.hpp"

class Physics {
    public:
        explicit Physics();
        void update(float dt);
        void debugDraw();
        b2WorldId mWorld;
        MyDebugDraw mDraw;

    private:
        void updateSensor();
        void updateContact();
};