#include "Serialization.hpp"
#include "Entity/Physics.hpp"
#include "Entity/Collide.hpp"
#include "Entity/Goomba.hpp"
#include "Entity/Koopa.hpp"
#include "Entity/FireBar.hpp"
#include "Entity/Bowser.hpp"
#include "Entity/Podoboo.hpp"
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

void to_json(nlohmann::json& j, const Character& c) {
    j = {
        {"position", c.mPhysics.getPosition()},
        {"velocity", c.mPhysics.getVelocity()},
        {"ground", c.mPhysics.onGround()},
        {"right", c.mPhysics.isRight()},
        {"form", (unsigned int)c.mForm},
        {"move", (unsigned int)c.mMove},
        {"immortal", c.mIsImmortal},
        {"height", c.mHigh},
        {"length", c.mLength},
        {"class", "character"}
    };
}

void to_json(nlohmann::json& j, const Memento& s) {
    j["current"] = s.mCurrent;
    j["timer"] = s.mTimer;
    j["lives"] = s.mLives;
    j["coins"] = s.mCoins;

    if (s.mCharacter)
    j["character"] = *s.mCharacter;
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

    if (j.contains("character")) {
        auto c = createEntityFromJson(j["character"]);
        s.mCharacter = std::unique_ptr<Character>(dynamic_cast<Character*>(c.release()));
    }

}

std::unique_ptr<Entity> createEntityFromJson(const nlohmann::json& j) {
    std::string type = j["class"];
    if (type == "character") return std::make_unique<Character>(j);
}