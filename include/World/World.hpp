#pragma once

#include <memory>

#include "State/Context.hpp"

class World {
    public:
        World(Context ctx);
        void update(float dt);
        void draw();

    private:
        Context mContext;
        void buildScene();
        void loadLevel();
};