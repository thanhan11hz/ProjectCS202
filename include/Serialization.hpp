#pragma once

#include <raylib.h>
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& j, const Vector2& v);

void from_json(const nlohmann::json& j, Vector2& v);

void to_json(nlohmann::json& j, const Rectangle& r);

void from_json(const nlohmann::json& j, Rectangle& r);

class Entity;

std::unique_ptr<Entity> createEntityFromJson(const nlohmann::json& j);