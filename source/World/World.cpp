#include "World/World.hpp"

World* World::instance = nullptr;

World::World() {
    mCam.offset = {targetWidth / 2.0f, targetHeight / 2.0f};
    mCam.target = {0, 0};
    mCam.zoom     = 1.0f;
    mCam.rotation = 0.0f;
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
    mMap[mCurrent]->update(dt);
    if (mCam.target.x < targetWidth / 2.0f) mCam.target.x = targetWidth / 2.0f;
    if (mCam.target.x > 10752 - targetWidth / 2.0f) mCam.target.x = 10752 - targetWidth / 2.0f;
    if (mCam.target.y < targetHeight / 2.0f) mCam.target.y = targetHeight / 2.0f;
    if (mCam.target.y > 1584 - targetHeight / 2.0f) mCam.target.y = 1584 - targetHeight / 2.0f;
    std::cout << mCam.target.x << " " << mCam.target.y << "\n";
}
        
void World::draw() {
    BeginMode2D(mCam);
    Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    mMap[mCurrent]->setTexture(tiles, object);
    mMap[mCurrent]->drawBackground();
    mMap[mCurrent]->drawItem();
    mMap[mCurrent]->drawMain();
    EndMode2D();
}

void World::handle() {
    if (IsKeyDown(KEY_LEFT)) mCam.target.x -= 100;
    if (IsKeyDown(KEY_RIGHT)) mCam.target.x += 100;
    if (IsKeyDown(KEY_UP)) mCam.target.y -= 100;
    if (IsKeyDown(KEY_DOWN)) mCam.target.y += 100;
}

void World::loadMap(const std::string folder) {
    std::unique_ptr<TileMap> newMap = std::make_unique<TileMap>();
    newMap->loadFromFile(folder);
    mMap.emplace_back(std::move(newMap));
}

void World::setCharater(int Character) {
    if (Character == 0) {
        if (mCharacter) {
            mCharacter = Character::spawnMario();
        }
    } else if (Character == 1) {
        if (mCharacter) {
            mCharacter = Character::spawnLuigi();
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
