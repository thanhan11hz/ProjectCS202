#include "World/World.hpp"
#include "Entity/Character.hpp"

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

    mCharacter->update(dt);

    for (auto itr = mProjectile.begin(); itr != mProjectile.end(); ) {
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = mProjectile.erase(itr);
        }
    }

    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ) {
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = mEnemy.erase(itr);
        }
    }

    // for (auto itr = mItem.begin(); itr != mItem.end(); ) {
    //     if (*itr && !(*itr)->isDie()) {
    //         (*itr)->update(dt);
    //         ++itr;
    //     } else {
    //         itr = mItem.erase(itr);
    //     }
    // }
    
    mCollision.handleCollision();

    mEffect.update(dt);

    mCam.target.x = mCharacter->mPhysics.getPosition().x;
    if (mCam.target.x < targetWidth / 2.0f) mCam.target.x = targetWidth / 2.0f;
    if (mCam.target.x > 10752 - targetWidth / 2.0f) mCam.target.x = 10752 - targetWidth / 2.0f;

    mTimer -= dt;
}
        
void World::draw() {
    BeginMode2D(mCam);

    Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    mMap[mCurrent]->setTexture(tiles, object);

    mMap[mCurrent]->drawBackground();

    mMap[mCurrent]->drawItem();
    //mMap[mCurrent]->drawEnemy();
    mCharacter->draw();
    
    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ++itr) {
        (*itr)->draw();
    }
    
    // for (auto itr = mItem.begin(); itr != mItem.end(); ++itr) {
        //     (*itr)->draw();
        // }
        
    mMap[mCurrent]->drawMain();

    for (auto itr = mProjectile.begin(); itr != mProjectile.end(); ++itr) {
        (*itr)->draw();
    }

    mEffect.draw();

    EndMode2D();
}

void World::handle() {
    mCharacter->handle();

    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ++itr) {
        (*itr)->handle();
    }

    for (auto itr = mItem.begin(); itr != mItem.end(); ++itr) {
        (*itr)->handle();
    }
}

void World::loadMap(const std::string folder) {
    std::unique_ptr<TileMap> newMap = std::make_unique<TileMap>();
    newMap->loadFromFile(folder);
    mMap.emplace_back(std::move(newMap));
}

void World::setMap(size_t index) {
    mCurrent = index;
}

void World::setCharater(int Character) {
    if (Character == 0) {
        mCharacter = Character::spawnMario();
    } else if (Character == 1) {
        mCharacter = Character::spawnLuigi();
    }
}

void World::addEffect(std::unique_ptr<Effect> effect) {
    mEffect.addEffect(std::move(effect));
}

void World::addProjectile(std::unique_ptr<MovingEntity> projectile) {
    mCollision.addProjectile(projectile.get());
    mProjectile.push_back(std::move(projectile));
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
    mEnemy.push_back(Goomba::spawnGoomba1({200, 600}));
    //
    mEnemy.push_back(Koopa::spawnKoopa({200, 300}, Koopa::Type::K_GREEN));
    //
    mCollision.clearCollidables();
    mCollision.addEnemy(mEnemy);
    mCollision.addItem(mItem);
    mCollision.addCharacter(mCharacter.get());
    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mMap[mCurrent]->getMain();
    mCollision.addBlock(mBlock);
    mTimer = 300.0f;
    mLives = 3;
    mCoins = 0;
    mCam.target = {0, 500};

}

void World::restart() {
    mEnemy.push_back(Goomba::spawnGoomba1({200, 600}));
    //
    mEnemy.push_back(Koopa::spawnKoopa({200, 300}, Koopa::Type::K_GREEN));
    //
    mCollision.clearCollidables();
    mCollision.addEnemy(mEnemy);
    mCollision.addItem(mItem);
    mCollision.addCharacter(mCharacter.get());
    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mMap[mCurrent]->getMain();
    mCollision.addBlock(mBlock);
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