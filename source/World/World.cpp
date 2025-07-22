#include "World/World.hpp"

World::World() {}
        
void World::update(float dt) {
    
}
        
void World::draw() {
    mMario->draw();
    mMap[mCurrentMap]->draw();
}

void World::loadMap(const std::string filename) {
    TileMap* newMap = new TileMap();
    newMap->loadFromFile(filename);
    mMap.push_back(newMap);
}

void World::loadCharater(const std::string character) {
    if (character == "Mario") {
        if (mMario) delete mMario;
        mMario = new Mario();
    }
}
        
bool World::isLevelComplete() {

}
        
bool World::hasNextMap() {
    if (mCurrentMap >= mMap.size() - 1) return false;
    return true;
}
        
bool World::nextMap() {
    mCurrentMap = (mCurrentMap + 1) % mMap.size();
    return true;
}
        
bool World::backMap() {
    mCurrentMap = (mCurrentMap - 1 + mMap.size()) % mMap.size();
    return true;
}
