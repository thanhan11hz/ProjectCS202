#pragma once

#include <memory>
#include <vector>
#include <string>

#include "World/TileMap.hpp"
#include "Entity/Mario.hpp"
#include "Entity/Luigi.hpp"

class World {

    public:
        World(const World& other) = delete;
        void operator=(const World&) = delete;
        static World& getInstance();
        static void destroyInstance();
        void setCharater(int character);
        void handle();
        void update(float dt);
        void draw();
        ~World();

    protected:
        World();
        static World* instance;

    private:
        std::vector<TileMap*> mMap;
        size_t mCurrent;
        Character* mChar;
        Camera2D mCam;
        void loadMap(const std::string fileName);
        bool isLevelComplete();
        bool hasNextMap();
        void nextMap();
        void backMap();
        void reset();
};