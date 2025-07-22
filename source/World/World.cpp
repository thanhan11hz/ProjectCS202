#include "World/World.hpp"

World* World::instance = nullptr;

World::World() {

}

World& World::getInstance() {
    if (!instance) {
        instance = new World();
    }
    return *instance;
}

void World::destroyInstance() {
    delete instance;
    instance = nullptr;
}

World::~World() {

}
        
void World::update(float dt) {
    
}
        
void World::draw() {
    mMap[mCurrent]->drawBackground();
    mMap[mCurrentMap]->drawItem();
    mMap[mCurrentMap]->drawMain();
}

void World::handle() {
    
}

void World::loadMap(const std::string filename) {
    TileMap* newMap = new TileMap();
    newMap->loadFromFile(filename);
    mMap.push_back(newMap);
}

void World::setCharater(int character) {
    if (character == 0) {
        if (mChar) {
            delete mChar;
            mChar = new Mario();
        }
    } else if (character == 1) {
        if (mChar) {
            delete mChar;
            mChar = new Luigi();
        }
    }
}
        
bool World::isLevelComplete() {
    return false;
}
        
bool World::hasNextMap() {
    if (mCurrent >= mMap.size() - 1) return false;
    return true;
}
        
void World::nextMap() {
    mCurrent = (mCurrent + 1) % mMap.size();
}
        
void World::backMap() {
    mCurrent = (mCurrent - 1 + mMap.size()) % mMap.size();
}
