#pragma once

#include <memory>
#include <vector>
#include <string>

#include "World/TileMap.hpp"
#include "Entity/Character.hpp"
#include "World/Collision.hpp"
#include "Entity/Goomba.hpp"
#include "Entity/Piranha.hpp"

class World {

    public:
        World(const World& other) = delete;
        void operator=(const World&) = delete;
        static World& getInstance();
        static void destroyInstance();
        void setCharater(int Character);
        void loadMap(const std::string folder);
        void handle();
        void update(float dt);
        void draw();
        void reset();
        void restart();
        float getRestTime();
        size_t getRestLive();
        size_t getCoinCollected();
        size_t getCurrentMap();
        Camera2D& getCamera();
        void receiveCoin();
        void damage();
        ~World();

    protected:
        World();
        static World* instance;

    private:
        std::vector<std::unique_ptr<TileMap>> mMap;
        size_t mCurrent = 0;
        std::unique_ptr<Character> mCharacter;
        std::unique_ptr<Piranha> mPiranha;
        Camera2D mCam;
        Collision mCollision;
        float mTimer = 300.0f;
        size_t mLives = 3;
        size_t mCoins = 0;
        bool isLevelComplete();
        bool hasNextMap();
        void nextMap();
        void backMap();
};