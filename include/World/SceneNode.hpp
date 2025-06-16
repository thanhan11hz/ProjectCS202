#pragma once

#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>

#include "Command/Command.hpp"
#include "Command/Category.hpp"

class SceneNode {
    public:
        using Ptr = std::unique_ptr<SceneNode>;

    public:
        SceneNode() = default;
        virtual ~SceneNode() = default;
        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);
        void update(float dt);
        void draw();
        virtual Category getCategory();
        void onCommand(const Command& command, float dt);

    private:
        std::vector<Ptr> mChildren;
        SceneNode* mParent = nullptr;
        virtual void drawCurrent();
        void drawChildren();
        virtual void updateCurrent(float dt);
        void updateChildren(float dt);
};