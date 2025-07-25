#include "World/World.hpp"

World* World::instance = nullptr;

World::World() {
    mCam.offset = {targetWidth / 2.0f, targetHeight / 2.0f};
    mCam.target = {0, 400};
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
    Rectangle rec = mCharacter->mCollide.getHitBox();
    std::cout << "Before update" << rec.x << " " << rec.y << " " << rec.width << " " << rec.height << "\n";
    mMap[mCurrent]->update(dt);
    mCam.target = mCharacter->mPhysics.getPosition();
    if (mCam.target.x < targetWidth / 2.0f) mCam.target.x = targetWidth / 2.0f;
    if (mCam.target.x > 10752 - targetWidth / 2.0f) mCam.target.x = 10752 - targetWidth / 2.0f;
    // if (mCam.target.y < targetHeight / 2.0f) mCam.target.y = targetHeight / 2.0f;
    // if (mCam.target.y > 1584 - targetHeight / 2.0f) mCam.target.y = 1584 - targetHeight / 2.0f;
    mCharacter->update(dt);
    mCollision.handleCollision();
    rec = mCharacter->mCollide.getHitBox();
    std::cout << "After update" << rec.x << " " << rec.y << " " << rec.width << " " << rec.height << "\n";
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
    EndMode2D();
}

void World::handle() {
    // if (IsKeyDown(KEY_LEFT)) mCam.target.x -= 100;
    // if (IsKeyDown(KEY_RIGHT)) mCam.target.x += 100;
    // if (IsKeyDown(KEY_UP)) mCam.target.y -= 100;
    // if (IsKeyDown(KEY_DOWN)) mCam.target.y += 100;
    mCharacter->handle();
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
}
