#pragma once

#include <memory>
#include <vector>
#include <string>

#include "World/TileMap.hpp"
#include "Entity/Mario.hpp"
#include "World/Physics.hpp"

class World {
    public:
        World();
        void update(float dt);
        void draw();

    private:
        std::vector<TileMap*> mMap;
        size_t mCurrentMap;
        Mario* mMario;
        Physics mPhysics;
        void loadMap(const std::string fileName);
        void loadCharater(const std::string character);
        bool isLevelComplete();
        bool hasNextMap();
        bool nextMap();
        bool backMap();
        void reset();
};