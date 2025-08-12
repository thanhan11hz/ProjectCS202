#pragma once

#include <nlohmann/json.hpp>

#include "Entity/Character.hpp"

class World;

class Memento {
    friend class World;
    friend void to_json(nlohmann::json& j, const Memento& s);
    friend void to_json(nlohmann::json& j, const std::unique_ptr<Memento>& s);
    friend void from_json(const nlohmann::json& j, std::unique_ptr<Memento>& s);
    friend void from_json(const nlohmann::json& j, Memento& s);
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
        std::vector<std::unique_ptr<Enemy>> mEnemy;
        std::vector<std::unique_ptr<MovingEntity>> mProjectile;
    };