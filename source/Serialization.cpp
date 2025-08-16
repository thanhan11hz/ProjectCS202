#include "Serialization.hpp"
#include "Entity/Character.hpp"
#include "World/TileMap.hpp"
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