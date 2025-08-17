#include "World/World.hpp"
#include "Entity/Character.hpp"

World* World::instance = nullptr;

World::World() {
    mCam.offset = {targetWidth / 2.0f, targetHeight / 2.0f};
    mCam.target = {0, 500};
    mCam.zoom     = 1.0f;
    mCam.rotation = 0.0f;
    mCollision.addProjectile(mProjectile);
}

World::~World() {
    if (!isComplete && mCurrentMap) saveSnapshot(); 
    std::ofstream out("resource\\save.json");
    nlohmann::json j;
    if (!mSnapshot) j = nullptr;
    else mSnapshot->serialize(j);
    out << std::setw(4) << j;
    out.close();
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
    mCurrentMap->update(dt);
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

    mCurrentMap->updateEnemy(dt);

    mCurrentMap->updateItem(dt);

    mCollision.handleCollision();
    
    mEffect.update(dt);

    float maxX = mCharacter->mPhysics.getPosition().x;
    float minX = mCharacter->mPhysics.getPosition().x;
    if (mIsMultiPlayers) {
        maxX = std::max(maxX, mCharacter2->mPhysics.getPosition().x);
        minX = std::max(minX, mCharacter2->mPhysics.getPosition().x);
    }
    if (mCam.target.x <  maxX) mCam.target.x = maxX;
    if (mCam.target.x - targetWidth / 2.0f > minX) mCam.target.x = minX + targetWidth / 2.0f;
    if (mCam.target.x < targetWidth / 2.0f) mCam.target.x = targetWidth / 2.0f;
    if (mCam.target.x > mCurrentMap->getBound() - targetWidth / 2.0f) mCam.target.x = mCurrentMap->getBound() - targetWidth / 2.0f;
    
    mTimer -= dt;
}
        
void World::draw() {
    BeginMode2D(mCam);

    mCurrentMap->drawBackground(mCam);
    
    Rectangle cameraView = {
        mCam.target.x - mCam.offset.x,
        mCam.target.y - mCam.offset.y,
        (float)targetWidth,
        (float)targetHeight
    };
    
    mCurrentMap->drawItem(cameraView);

    if (!mCharacter->isDie() && mCharacter->isAfterBlock()) mCharacter->draw();

    mCurrentMap->drawEnemy1(cameraView);

    mCurrentMap->drawMain(mCam);

    if (!mCharacter->isDie()) mCharacter->draw();

    if (mIsMultiPlayers && !mCharacter2->isDie()) mCharacter2->draw();

    for (auto itr = mProjectile.begin(); itr != mProjectile.end(); ++itr) {
        (*itr)->draw();
    }

    mCurrentMap->drawEnemy2(cameraView);

    mEffect.draw(mCam);

    EndMode2D();
}

void World::handle() {
    if (!mCharacter->isDie()) mCharacter->handle();
    if (mIsMultiPlayers && !mCharacter2->isDie()) mCharacter2->handle();
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

void World::addProjectile(std::unique_ptr<Entity> projectile) {
    mProjectile.push_back(std::move(projectile));
}

void World::reset() {
    // Clone Map mới
    if(mMap[mCurrent]) {
        mCurrentMap = mMap[mCurrent]->clone();
    }

    Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    mCurrentMap->setTexture(tiles, object);

    std::vector<std::unique_ptr<Enemy>>& Enemy = mCurrentMap->getEnemy();
    mCollision.addEnemy(Enemy);

    std::vector<std::unique_ptr<TileObject>>& Items = mCurrentMap->getItems();
    mCollision.addItem(Items);

    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mCurrentMap->getMain();
    mCollision.addBlock(mBlock);

    mProjectile.clear();

    if (mIsMultiPlayers) {
        mCharacter = Character::spawnMario();
        mCharacter2 = Character::spawnLuigi();
        mCharacter->setKeyBind(mKeyBinding);
        mCharacter2->setKeyBind(mKeyBinding2);
    } else {
        if (mCharacter->isMario()) mCharacter = Character::spawnMario();
        else mCharacter = Character::spawnLuigi();
        mCharacter2 = nullptr;
    }

    // Đặt vị trí spawn

    if (mCurrent == 0) mCharacter->mPhysics.setPosition({150, 672});
    else if (mCurrent == 1) mCharacter->mPhysics.setPosition({150, 624});
    else if (mCurrent == 4) mCharacter->mPhysics.setPosition({96, 576});
    else if (mCurrent == 10) mCharacter->mPhysics.setPosition({0, 336});
    else mCharacter->mPhysics.setPosition({150, 624});

    if (mIsMultiPlayers) mCharacter2->mPhysics.setPosition(mCharacter->mPhysics.getPosition() + Vector2{60, 0});
    
    mCollision.addCharacter(mCharacter.get());
    if (mIsMultiPlayers) mCollision.addCharacter2(mCharacter2.get());
    else mCollision.addCharacter2(nullptr);

    mTimer = 100.0f;
    mLives = 3;
    mCoins = 0;
    mCam.target = {0, 500};
    isComplete = false;
}

void World::restart() {
    // Clone Map mới
    if(mMap[mCurrent]) {
        mCurrentMap = mMap[mCurrent]->clone();
    }

    Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    mCurrentMap->setTexture(tiles, object);

    std::vector<std::unique_ptr<Enemy>>& Enemy = mCurrentMap->getEnemy();
    mCollision.addEnemy(Enemy);

    std::vector<std::unique_ptr<TileObject>>& Items = mCurrentMap->getItems();
    mCollision.addItem(Items);

    std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mCurrentMap->getMain();
    mCollision.addBlock(mBlock);

    mProjectile.clear();


    if (mIsMultiPlayers) {
        mCharacter = Character::spawnMario();
        mCharacter2 = Character::spawnLuigi();
        mCharacter->setKeyBind(mKeyBinding);
        mCharacter2->setKeyBind(mKeyBinding2);
    } else {
        if (mCharacter->isMario()) mCharacter = Character::spawnMario();
        else mCharacter = Character::spawnLuigi();
        mCharacter2 = nullptr;
    }

    // Đặt vị trí spawn

    if (mCurrent == 0) mCharacter->mPhysics.setPosition({150, 672});
    else if (mCurrent == 1) mCharacter->mPhysics.setPosition({150, 624});
    else if (mCurrent == 4) mCharacter->mPhysics.setPosition({96, 576});
    else if (mCurrent == 10) mCharacter->mPhysics.setPosition({0, 336});
    else mCharacter->mPhysics.setPosition({150, 624});

    if (mIsMultiPlayers) mCharacter2->mPhysics.setPosition(mCharacter->mPhysics.getPosition() + Vector2{60, 0});
    
    mCollision.addCharacter(mCharacter.get());
    if (mIsMultiPlayers) mCollision.addCharacter2(mCharacter2.get());
    else mCollision.addCharacter2(nullptr);

    mCam.target = {0, 500};
}

void World::saveSnapshot() {
    std::unique_ptr<Memento> snapshot = std::make_unique<Memento>();

    snapshot->mCurrent = mCurrent;
    snapshot->mTimer = mTimer;
    snapshot->mLives = mLives;
    snapshot->mCoins = mCoins;
    snapshot->mPoints = mPoints;
    snapshot->mIsMultiPlayers = mIsMultiPlayers;
    snapshot->cameraTarget = mCam.target;

    snapshot->mCharacter = std::move(mCharacter);
    snapshot->mCharacter2 = std::move(mCharacter2);

    for (int i = 0; i < mProjectile.size(); ++i) {
        snapshot->mProjectile.push_back(std::move(mProjectile[i]));
    }

    snapshot->mCurrentMap = std::move(mCurrentMap);
    
    mSnapshot = std::move(snapshot);
}

void World::restore() {
    if (mSnapshot) {

        mCurrent = mSnapshot->mCurrent;
        mCoins = mSnapshot->mCoins;
        mLives = mSnapshot->mLives;
        mTimer = mSnapshot->mTimer;
        mPoints = mSnapshot->mPoints;
        mIsMultiPlayers = mSnapshot->mIsMultiPlayers;
        mCam.target = mSnapshot->cameraTarget;

        mCharacter = std::move(mSnapshot->mCharacter);
        mCharacter->setKeyBind(mKeyBinding);
        mCollision.addCharacter(mCharacter.get());

        if (mIsMultiPlayers) {
            mCharacter2 = std::move(mSnapshot->mCharacter2);
            mCharacter2->setKeyBind(mKeyBinding2);
            mCollision.addCharacter2(mCharacter2.get());
        } else mCharacter2 = nullptr;

        for (int i = 0; i < mSnapshot->mProjectile.size(); ++i) {
            mProjectile.push_back(std::move(mSnapshot->mProjectile[i]));
        }

        mCurrentMap = std::move(mSnapshot->mCurrentMap);

        Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
        Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
        mCurrentMap->setTexture(tiles, object);

        std::vector<std::unique_ptr<Enemy>>& Enemies = mCurrentMap->getEnemy();
        mCollision.addEnemy(Enemies);

        std::vector<std::unique_ptr<TileObject>>& Items = mCurrentMap->getItems();
        mCollision.addItem(Items);

        std::vector<std::vector<std::unique_ptr<TileBlock>>>& mBlock = mCurrentMap->getMain();
        mCollision.addBlock(mBlock);

        mSnapshot = nullptr;
    }
}

bool World::haveSnapshot() {
    if (mSnapshot) return true;
    return false;
}

void World::loadSnapshot() {
    std::ifstream in("resource\\save.json");
    if (in.is_open()) {
        nlohmann::json j;
        in >> j;
        if (j.is_null()) mSnapshot = nullptr;
        else mSnapshot = std::make_unique<Memento>(j);
    }
    in.close();
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

Character* World::getCharacter() {
    return mCharacter.get();
}

size_t World::getCurrentPoint() {
    return mPoints;
}

bool World::isSolidTileAt(Vector2 worldPosition) {
    // Get the main tile grid from the current map
    auto& grid = mCurrentMap->getMain();

    if (grid.empty()) {
        return false;
    }

    int col = worldPosition.x / 48;
    int row = worldPosition.y / 48;

    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
        return false;
    }

    // Check if the tile at the grid index exists and is collidables
    if (grid[row][col] && grid[row][col]->isSolid()) {
        return true;
    }

    return false;
}

void World::receivePoint(int points) {
    mPoints += points;
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

void World::setLevelComplete(bool flag) {
    isComplete = flag;
}