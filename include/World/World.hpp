#pragma once

#include <memory>

#include "World/SceneNode.hpp"
#include "State/Context.hpp"
#include "Command/CommandQueue.hpp"

class World {
    public:
        World(Context ctx);
        void update(float dt);
        void draw();
        CommandQueue& getCommandQueue();

    private:
        std::unique_ptr<SceneNode> mSceneGraph;
        CommandQueue mCommandQueue;
        Context mContext;
        void buildScene();
        void loadLevel();
};