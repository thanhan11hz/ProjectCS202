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
    if (mCharacter->isDie() && mLives > 0) {
        if (mEffect.isEmpty()) {
            mLives--;
            restart();
        }
    }

    if (mIsMultiPlayers && mCharacter2->isDie() && mLives > 0) {
        if (mEffect.isEmpty()) {
            mLives--;
            restart();
        }
    }
    
    mMap[mCurrent]->update(dt);
    mCharacter->update(dt);

    if (mIsMultiPlayers) mCharacter2->update(dt);

    for (auto itr = mProjectile.begin(); itr != mProjectile.end(); ) {
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = mProjectile.erase(itr);
        }
    }

    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ) {
        // If an enemy falls too far down, mark it as dead.
        const float deathPlaneY = 2000.0f;
        if ((*itr)->mPhysics.getPosition().y > deathPlaneY) {
            (*itr)->setDie(true);
        }
        // ----------------------
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = mEnemy.erase(itr);
        }
    }
    for (auto itr = mItem.begin(); itr != mItem.end(); ) {
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = mItem.erase(itr);
            
        }
    }
    
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

    // mMap[mCurrent]->drawBackground();
    mMap[mCurrent]->drawBackground(mCam);

    // mMap[mCurrent]->drawItem();

    mMap[mCurrent]->drawItem(mCam);
    
    if (!mCharacter->isDie() && mCharacter->isAfterBlock()) mCharacter->draw();

    // Rectangle that represents what the camera can currently see.
    Rectangle cameraView = {
        mCam.target.x - mCam.offset.x,
        mCam.target.y - mCam.offset.y,
        (float)targetWidth,
        (float)targetHeight
    };

    // Only draw the ones inside view.
    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ++itr) {
        // Get the enemy's bounding box
        Vector2 enemyPos = (*itr)->mPhysics.getPosition();
        Vector2 enemySize = (*itr)->getSize();
        Rectangle enemyRect = { enemyPos.x, enemyPos.y, enemySize.x, enemySize.y };

        // Check if the enemy's rectangle overlaps with the camera's view
        if (CheckCollisionRecs(cameraView, enemyRect) && (*itr)->isAfterBlock()) {
            (*itr)->draw(); // Only draw the enemy if it's visible
        }
    }
    
    // for (auto itr = mItem.begin(); itr != mItem.end(); ++itr) {
        //     (*itr)->draw();
        // }
        
    // mMap[mCurrent]->drawMain();
    mMap[mCurrent]->drawMain(mCam);

    if (!mCharacter->isDie()) mCharacter->draw();

    if (mIsMultiPlayers && !mCharacter2->isDie()) mCharacter2->draw();

    for (auto itr = mProjectile.begin(); itr != mProjectile.end(); ++itr) {
        (*itr)->draw();
    }

    // Only draw the ones inside view.
    for (auto itr = mEnemy.begin(); itr != mEnemy.end(); ++itr) {
        // Get the enemy's bounding box
        Vector2 enemyPos = (*itr)->mPhysics.getPosition();
        Vector2 enemySize = (*itr)->getSize();
        Rectangle enemyRect = { enemyPos.x, enemyPos.y, enemySize.x, enemySize.y };

        // Check if the enemy's rectangle overlaps with the camera's view
        if (CheckCollisionRecs(cameraView, enemyRect) && !(*itr)->isAfterBlock()) {
            (*itr)->draw(); // Only draw the enemy if it's visible
        }
    }

    // mEffect.draw();
    mEffect.draw(mCam);

    EndMode2D();
}

void World::handle() {
    if (!mCharacter->isDie()) mCharacter->handle();

    if (mIsMultiPlayers && !mCharacter2->isDie()) mCharacter2->handle();

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
    return isComplete;
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
    mMap[mCurrent]->reset();
    mEnemy.clear();
    if (mIsMultiPlayers) {
        mCharacter = Character::spawnMario();
        mCharacter2 = Character::spawnLuigi();
        mCharacter->setKeyBind(mKeyBinding);
        mCharacter2->setKeyBind(mKeyBinding2);
    } else mCharacter2 = nullptr;
    if (mCurrent == 0) mCharacter->mPhysics.setPosition({150, 672});
    else if (mCurrent == 1) mCharacter->mPhysics.setPosition({150, 624});
    else if (mCurrent == 4) mCharacter->mPhysics.setPosition({96, 576});
    else if (mCurrent == 10) mCharacter->mPhysics.setPosition({0, 336});
    else mCharacter->mPhysics.setPosition({150, 624});
    if (mIsMultiPlayers) mCharacter2->mPhysics.setPosition(mCharacter->mPhysics.getPosition() + Vector2{60, 0});
    mCollision.clearCollidables();
    mItem.clear();
    std::vector<std::unique_ptr<Enemy>>& Enemy = mMap[mCurrent]->getEnemy();
    mCollision.addEnemy(Enemy);
    mEnemy = mMap[mCurrent]->takeEnemies();

    std::vector<std::unique_ptr<TileObject>>& Items = mMap[mCurrent]->getItems();
    mCollision.addItem(Items);
    mItem = mMap[mCurrent]->takeItems();
    mMap[mCurrent]->resetItem();
    mCollision.addCharacter(mCharacter.get());
    if (mIsMultiPlayers) mCollision.addCharacter2(mCharacter2.get());
    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mMap[mCurrent]->getMain();
    mCollision.addBlock(mBlock);
    mTimer = 100.0f;
    mLives = 3;
    mCoins = 0;
    mCam.target = {0, 500};

}

void World::restart() {
    mEnemy.clear();
    if (mCurrent == 0) mCharacter->mPhysics.setPosition({150, 672});
    else if (mCurrent == 1) mCharacter->mPhysics.setPosition({150, 624});
    else if (mCurrent == 4) mCharacter->mPhysics.setPosition({96, 576});
    else if (mCurrent == 10) mCharacter->mPhysics.setPosition({0, 336});
    else mCharacter->mPhysics.setPosition({150, 624});
    mCharacter->setDie(false);
    if (mIsMultiPlayers) {
        mCharacter2->setDie(false);
        mCharacter2->mPhysics.setPosition(mCharacter->mPhysics.getPosition() + Vector2{60, 0});
    }
    mCollision.clearCollidables();
    std::vector<std::unique_ptr<Enemy>>& mEnemy = mMap[mCurrent]->getEnemy();
    mCollision.addEnemy(mEnemy);
    mCollision.addItem(mItem);
    mCollision.addCharacter(mCharacter.get());
    if (mIsMultiPlayers) mCollision.addCharacter2(mCharacter2.get());
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
        
void World::heal() {
    mLives ++;
}

Camera2D& World::getCamera() {
    return mCam;
}

bool World::isSolidTileAt(Vector2 worldPosition) {
    // Get the main tile grid from the current map
    auto& grid = mMap[mCurrent]->getMain();

    if (grid.empty()) {
        return false;
    }

    int col = worldPosition.x / 48;
    int row = worldPosition.y / 48;

    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
        return false;
    }

    // Check if the tile at the grid index exists and is collidable
    if (grid[row][col] && grid[row][col]->isSolid()) {
        return true;
    }

    return false;
}
        
void World::setMultiPlayers(bool flag) {
    mIsMultiPlayers = flag;
}
        
bool World::isMultiPlayers() const {
    return mIsMultiPlayers;
}

bool World::isEndEffect() const {
    return mEffect.isEmpty();
}