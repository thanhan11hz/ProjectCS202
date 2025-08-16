#include "World/Memento.hpp"
#include "Entity/Character.hpp"

Memento::Memento(const nlohmann::json& j) {
    mCurrent = j.value("current", 0);
    mTimer = j.value("timer", 0.0f);
    mLives = j.value("lives", 3);
    mCoins = j.value("coins", 0);
    mPoints = j.value("points", 0);
    mIsMultiPlayers = j.value("multiPlayers", true);
    cameraTarget = j.value("cameraTarget", Vector2{0,0});

    if (j.contains("character")) {
        auto c = createEntityFromJson(j["character"]);
        mCharacter = std::unique_ptr<Character>(static_cast<Character*>(c.release()));
    }

    if (mIsMultiPlayers && j.contains("character2")) {
        auto c = createEntityFromJson(j["character2"]);
        mCharacter2 = std::unique_ptr<Character>(static_cast<Character*>(c.release()));
    }

    for (const auto& jp : j["projectile"]) {
        auto p = createEntityFromJson(jp);
        mProjectile.push_back(std::unique_ptr<Entity>(static_cast<Entity*>(p.release())));
    }

    mCurrentMap = std::make_unique<TileMap>(j["map"]);
}

void Memento::serialize(nlohmann::json& j) {
    j["current"] = mCurrent;
    j["timer"] = mTimer;
    j["lives"] = mLives;
    j["coins"] = mCoins;
    j["points"] = mPoints;
    j["multiPlayers"] = mIsMultiPlayers;
    j["cameraTarget"] = cameraTarget;

    if (mCharacter) {
        nlohmann::json js;
        mCharacter->serialize(js);
        j["character"] = js;
    }

    if (mIsMultiPlayers && mCharacter2) {
        nlohmann::json js;
        mCharacter2->serialize(js);
        j["character2"] = js;
    }

    j["projectile"] = nlohmann::json::array();
    for (const auto& e: mProjectile) {
        nlohmann::json js;
        e->serialize(js);
        j["projectile"].push_back(js);
    }

    if (mCurrentMap) {
        nlohmann::json js;
        mCurrentMap->serialize(js);
        j["map"] = js;
    }
}