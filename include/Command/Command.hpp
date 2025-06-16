#pragma once

#include <functional>

#include "Command/Category.hpp"

class SceneNode;

struct Command {
    std::function<void(SceneNode& node, float dt)> action;
    Category mCategory;    
};

template<typename GameObject, typename Function>
std::function<void(SceneNode& node, float dt)> derivedAction(Function fn) {
    return [=](SceneNode& node, float dt) {
        assert(dynamic_cast<GameObject*>(&node) && "Derived action: wrong category/cast!");
        fn(static_cast<GameObject&>(node), dt);
    };
}