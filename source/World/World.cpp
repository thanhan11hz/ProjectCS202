#include "World/World.hpp"

World::World(Context ctx) : mContext(ctx) {}
        
void World::update(float dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph->onCommand(mCommandQueue.pop(), dt);
    }
    mSceneGraph->update(dt);
}
        
void World::draw() {
    mSceneGraph->draw();
}

void World::buildScene() {

}
    
void World::loadLevel() {

}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}