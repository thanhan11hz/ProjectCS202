#include "Serialization.hpp"
#include "Entity/Goomba.hpp"
#include "Entity/Koopa.hpp"
#include "Entity/FireBar.hpp"
#include "Entity/Bowser.hpp"
#include "Entity/Podoboo.hpp"
#include "Entity/FlyingKoopa.hpp"
#include "Entity/Projectile.hpp"
#include "Entity/Character.hpp"
#include "World/Memento.hpp"

void to_json(nlohmann::json& j, const Vector2& v) {
    j = nlohmann::json{{"x", v.x}, {"y", v.y}};
}

void from_json(const nlohmann::json& j, Vector2& v) {
    v.x = j.value("x", 0.0f);
    v.y = j.value("y", 0.0f);
}

void to_json(nlohmann::json& j, const Rectangle& r) {
    j = nlohmann::json{{"x", r.x}, {"y", r.y}, {"width", r.width}, {"height", r.height}};
}

void from_json(const nlohmann::json& j, Rectangle& r) {
    r.x      = j.value("x", 0.0f);
    r.y      = j.value("y", 0.0f);
    r.width  = j.value("width", 0.0f);
    r.height = j.value("height", 0.0f);
}

void to_json(nlohmann::json& j, const Memento& s) {
    j["current"] = s.mCurrent;
    j["timer"] = s.mTimer;
    j["lives"] = s.mLives;
    j["coins"] = s.mCoins;
    j["points"] = s.mPoints;
    j["multiPlayers"] = s.mIsMultiPlayers;
    j["cameraTarget"] = s.cameraTarget;

    if (s.mCharacter) {
        nlohmann::json js;
        s.mCharacter->serialize(js);
        j["character"] = js;
    }

    if (s.mIsMultiPlayers && s.mCharacter2) {
        nlohmann::json js;
        s.mCharacter2->serialize(js);
        j["character2"] = js;
    }
    
    j["enemy"] = nlohmann::json::array();
    for (const auto& e: s.mEnemy) {
        nlohmann::json js;
        e->serialize(js);
        j["enemy"].push_back(js);
    }

    j["projectile"] = nlohmann::json::array();
    for (const auto& e: s.mProjectile) {
        nlohmann::json js;
        e->serialize(js);
        j["projectile"].push_back(js);
    }
}

void to_json(nlohmann::json& j, const std::unique_ptr<Memento>& s) {
    if (!s) j = nullptr;
    else j = *s;
}

void from_json(const nlohmann::json& j, std::unique_ptr<Memento>& s) {
    if (j.is_null()) s = nullptr;
    else s = std::make_unique<Memento>(j.get<Memento>());
}

void from_json(const nlohmann::json& j, Memento& s) {
    s.mCurrent = j.value("current", 0);
    s.mTimer = j.value("timer", 0.0f);
    s.mLives = j.value("lives", 3);
    s.mCoins = j.value("coins", 0);
    s.mPoints = j.value("points", 0);
    s.mIsMultiPlayers = j.value("multiPlayers", true);
    s.cameraTarget = j.value("cameraTarget", Vector2{0,0});

    if (j.contains("character")) {
        auto c = createEntityFromJson(j["character"]);
        s.mCharacter = std::unique_ptr<Character>(static_cast<Character*>(c.release()));
    }

    if (s.mIsMultiPlayers && j.contains("character2")) {
        auto c = createEntityFromJson(j["character2"]);
        s.mCharacter2 = std::unique_ptr<Character>(static_cast<Character*>(c.release()));
    }

    for (const auto& je : j["enemy"]) {
        auto e = createEntityFromJson(je);
        s.mEnemy.push_back(std::unique_ptr<Enemy>(static_cast<Enemy*>(e.release())));
    }

    for (const auto& jp : j["projectile"]) {
        auto p = createEntityFromJson(jp);
        s.mProjectile.push_back(std::unique_ptr<Entity>(static_cast<Entity*>(p.release())));
    }
}

std::unique_ptr<Entity> createEntityFromJson(const nlohmann::json& j) {
    std::string type = j["class"];
    if (type == "character") return std::make_unique<Character>(j);
    else if (type == "goomba") return std::make_unique<Goomba>(j);
    else if (type == "koopa") return std::make_unique<Koopa>(j);
    else if (type == "piranha") return std::make_unique<Piranha>(j);
    else if (type == "bowser") return std::make_unique<Bowser>(j);
    else if (type == "fireBar") return std::make_unique<FireBar>(j);
    else if (type == "podoboo") return std::make_unique<Podoboo>(j);
    else if (type == "fireBall") return std::make_unique<FireBall>(j);
    else if (type == "bowserFire") return std::make_unique<BowserFire>(j);
    else if (type == "flyingKoopa") return std::make_unique<FlyingKoopa>(j);
}