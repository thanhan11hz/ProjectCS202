#include "World/World.hpp"

World* World::instance = nullptr;

World::World() {
    mCam.offset = {targetWidth / 2.0f, targetHeight / 2.0f};
    mCam.target = {0, 500};
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
    mCam.target.x = mCharacter->mPhysics.getPosition().x;
    if (mCam.target.x < targetWidth / 2.0f) mCam.target.x = targetWidth / 2.0f;
    if (mCam.target.x > 10752 - targetWidth / 2.0f) mCam.target.x = 10752 - targetWidth / 2.0f;
    mCharacter->update(dt);
    mPiranha->update(dt);
    mCollision.handleCollision();
    mTimer -= dt;
}
        
void World::draw() {
    BeginMode2D(mCam);
    Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    mMap[mCurrent]->setTexture(tiles, object);
    mMap[mCurrent]->drawBackground();
    mMap[mCurrent]->drawItem();
    mMap[mCurrent]->drawMain();
    mCharacter->draw();
    mPiranha->draw();
    EndMode2D();
}

void World::handle() {
    mCharacter->handle();
    mPiranha->handle();
}

void World::loadMap(const std::string folder) {
    std::unique_ptr<TileMap> newMap = std::make_unique<TileMap>();
    newMap->loadFromFile(folder);
    mMap.emplace_back(std::move(newMap));
}

void World::setCharater(int Character) {
    if (Character == 0) {
        mCharacter = Character::spawnMario();
    } else if (Character == 1) {
        mCharacter = Character::spawnLuigi();
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

void World::reset() {
    mCollision.addCharacter(mCharacter.get());
    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mMap[mCurrent]->getMain();
    mCollision.addBlock(mBlock);
    // mPiranha = Piranha::spawnPiranha1();
    // mCollision.addEnemy(mPiranha.get());
    // mPiranha->setFixedPoint({200, 664});
    mTimer = 300.0f;
    mLives = 3;
    mCoins = 0;
    mCam.target = {0, 500};

}

void World::restart() {
    mCollision.addCharacter(mCharacter.get());
    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mMap[mCurrent]->getMain();
    mCollision.addBlock(mBlock);
    // mPiranha = Piranha::spawnPiranha1();
    // mCollision.addEnemy(mPiranha.get());
    // mPiranha->setFixedPoint({200, 672});
    mCam.target = {0, 500};
}

size_t World::getCurrentMap() {
    return mCurrent;
}

float World::getRestTime() {
    return mTimer;
}

size_t World::getRestLive() {
    return mLives;
}

size_t World::getCoinCollected() {
    return mCoins;
}

void World::receiveCoin() {
    mCoins ++;
}
        
void World::damage() {
    mLives --;
}

Camera2D& World::getCamera() {
    return mCam;
}