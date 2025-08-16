#pragma once

#include <raylib.h>
#include <nlohmann/json.hpp>

#include "World/TileMap.hpp"

class World;

class Character;

class Memento {
    friend class World;
    public:
        Memento() = default;
        Memento(const nlohmann::json& j);
        void serialize(nlohmann::json& j);
    private:
        size_t mCurrent;
        float mTimer;
        size_t mLives;
        size_t mCoins;
        size_t mPoints;
        bool mIsMultiPlayers;
        Vector2 cameraTarget;
        std::unique_ptr<Character> mCharacter;
        std::unique_ptr<Character> mCharacter2;
        std::vector<std::unique_ptr<Entity>> mProjectile;
        std::unique_ptr<TileMap> mCurrentMap;
    };