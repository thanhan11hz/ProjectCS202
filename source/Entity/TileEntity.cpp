
#include "Entity/TileEntity.hpp"
#include "Entity/TileItem.hpp"
#include "Global.hpp"
#include <iostream>
#include <raylib.h>
#include <algorithm>
bool updated = false;
bool drawed = false;
std::vector<int> tileItemValues = {
    -1,     // Empty
    0,      // OwGround
    1,      // OwInitialTile
    2,      // OwWall
    3,      // OwBlock
    26,     // OwAfterHitBlock
    23, 24, 25, // OwCoinBlock1..3
    232, 233,   // OwPipeTop1..2
    261, 262,   // OwPipeBottom1..2
    32,         // OWBridge
    29,         // BrownCube
    237, 238, 239, // GrassPlatform1..3
    266, 267, 268, 277, // GreenDotPlatform1..3
    234, 263, 556, 700, 147,     // HoriPipe1..2
    60, 382, 383, 384, 567,          // UnderTile
};
TileBlock::TileBlock(int type, int col, int row)
    : mType(type), mRect({(col * 48.0f), (row * 48.0f), 48, 48}), posTile({0, 0}), printed(false), mCol(col), mRow(row) {
    mBodyCollide.setLabel(Category::NONE);
    if(type >= 0){
        int x = type % 29;
        int y = type / 29;
        if(type == 301 || type == 292) {
           x = type % 36;
           y = type / 36;
        }
        
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        addFragment();
        createBehavior();

        if(getType(calType())!= TileType::Empty) {
            solid = true;
            mBodyCollide.setLabel(Category::BLOCK);
        } 
        else {
            mBodyCollide.setLabel(Category::NONE);}
        if(mType!= 556 && mType != 567) isOn = true;
        mBodyCollide.setStatic(true);
        mBodyCollide.setFilter(Category::NONE);
        mPhysics.setPosition({mRect.x, mRect.y});
        
    }
    aniRect=mRect;
}

TileBlock::TileBlock(const nlohmann::json& j) {
    mType = j["type"].get<int>();
    mRect = j["rect"].get<Rectangle>();
    mCol = j["col"].get<int>();
    mRow = j["row"].get<int>();

    mBodyCollide.setLabel(Category::NONE);
    if(mType >= 0){
        int x = mType % 29;
        int y = mType / 29;
        if(mType == 301 || mType == 292) {
           x = mType % 36;
           y = mType / 36;
        }
        
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE }; 
        createBehavior();

        if(getType(calType())!= TileType::Empty) {
            solid = true;
            mBodyCollide.setLabel(Category::BLOCK);
        } 
        else {
            mBodyCollide.setLabel(Category::NONE);}
        if(mType!= 556 && mType != 567) isOn = true;
        mBodyCollide.setStatic(true);
        mBodyCollide.setFilter(Category::NONE);
        mPhysics.setPosition({mRect.x, mRect.y});
    }
    aniRect=mRect;
    
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mSource = j["source"].get<Rectangle>();
    posTile = j["posTile"].get<Vector2>();
    mVelocity = j["speed"].get<Vector2>();
    aniRect = j["aniRect"].get<Rectangle>();
    printed = j["printed"].get<bool>();
    isOn = j["isOn"].get<bool>();
    isDoneAnimation = j["isDoneAnimation"].get<bool>();
    bumped = j["bumped"].get<bool>();
    isDestroyed = j["isDestroyed"].get<bool>();
    solid = j["solid"].get<bool>();
    aniTime = j["aniTime"].get<float>();
    for (const auto& js: j["frag"]) {
        frag.push_back(std::make_unique<TileObject>(js));
    }
}

void TileBlock::createBehavior()  {
    if(getType(calType()) == TileType::OwCoinBlock1||getType(calType()) == TileType::HiddenBox ) {
        mBehavior = std::make_unique<CoinBlockBehavior>();
    } 
    else if(getType(calType()) == TileType::OwInitialTile || getType(calType()) == TileType::UnderTile) {
        mBehavior = std::make_unique<SimpleBlockBehavior>();
    }
    else if(getType(calType()) == TileType::HoriMovingBlock ) {
        mPhysics.setVelocity({50.0f,0});
        mBehavior = std::make_unique<MovingBlockBehavior>(301);
    }
    else if(getType(calType()) == TileType::VertMovingBlock ) {
        mPhysics.setVelocity({0,50.0f});
        mBehavior = std::make_unique<MovingBlockBehavior>(292);
    }
}

void TileBlock::draw( Texture2D& background, Texture2D& object) {
    //std::cout << "Draw TileBlock with type: " << mType << "\n\n\n\n\n";
    if (mType != -1 && !isDestroyed && isOn) {
        float posX = mPhysics.getPosition().x;
        float posY = mPhysics.getPosition().y;
        if (mType == 301 || mType ==292){
            DrawTexturePro(object, mSource, {posX, posY, mRect.width, mRect.height}, {0, 0}, 0.0f, WHITE);
        }
        else  {DrawTexturePro(background, mSource, {posX, posY, mRect.width, mRect.height}, {0, 0}, 0.0f, WHITE);}
        //print();
    }
    else if(mType != -1 && isDestroyed ) {
        for(int i =0; i < 4; i++){
            frag[i]->draw( background, object);
        }
    }
    // DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, mColor);

}


void TileBlock::print(){
    std::cout << "Print called: \n";
    if (printed == false && mType ==0) {
        if(mBodyCollide.getHitBox().x == 0 && mBodyCollide.getHitBox().y == 0 && mBodyCollide.getHitBox().width == 0 && mBodyCollide.getHitBox().height == 0) {
            Vector2 position = mPhysics.getPosition();
            Vector2 size = getSize();
            std::cout << "TileBlock: \n";
            std::cout << "Position: " << position.x << ", " << position.y << "\n";
            std::cout << "Size: " << size.x << ", " << size.y << "\n";
        }
        else
        {
            std::cout << "TileBlock: \n";
            std::cout << "HitBox: " << mBodyCollide.getHitBox().x << ", " << mBodyCollide.getHitBox().y << ", "
                      << mBodyCollide.getHitBox().width << ", " << mBodyCollide.getHitBox().height << "\n";
        }
        printed = true;
    }
}

int TileBlock::calType() {
    switch (mType) {

        case OwCoinBlock1:
        case OwCoinBlock2:
        case OwCoinBlock3:
            return TileType::OwCoinBlock1;

        case OwGround:           return TileType::OwGround;
        case OwInitialTile:     return TileType::OwInitialTile;
        case OwAfterHitBlock:   return TileType::OwAfterHitBlock;
        case OwPipeTop1:        return TileType::OwPipeTop1;
        case OwPipeTop2:        return TileType::OwPipeTop2;
        case OwPipeBottom1:     return TileType::OwPipeBottom1;
        case OwPipeBottom2:     return TileType::OwPipeBottom2;
        case HoriPipe1:         return TileType::HoriPipe1;
        case HoriPipe2:         return TileType::HoriPipe2;
        case UnderTile:         return TileType::UnderTile;
        case HoriMovingBlock: return TileType::HoriMovingBlock;
        case VertMovingBlock: return TileType::VertMovingBlock;

        case GrassPlatform1:
        case GrassPlatform2:
        case GrassPlatform3:
            return TileType::GrassPlatform1;

        case OrangeDotPlatForm1:
        case OrangeDotPlatForm2:
        case OrangeDotPlatForm3:
            return TileType::OrangeDotPlatForm1;

        case GreenDotPlatForm1:
        case GreenDotPlatForm2:
        case GreenDotPlatForm3:
            return TileType::GreenDotPlatForm1;
        case CastleTile:      return TileType::CastleTile;
        case CastleBrigde:      return TileType::CastleBrigde;
        case BrownCube:
            return TileType::BrownCube;
        case HiddenBox:
            return TileType::HiddenBox;
        case EndingPoint:
            return TileType::EndingPoint;
        default:
            break;
    }

    if(mType >= 0 ) {
        for(int i = 1; i < 4; i++) {
            int m = mType - 2*i*29;
            auto it = std::find(tileItemValues.begin(), tileItemValues.end(), m);
            if(it != tileItemValues.end()) {
                return m;
            }
        }
    }
    return TileType::Empty;
}


TileType TileBlock::getType(int n) {
    switch (n) {
        case OwCoinBlock1:
        case OwCoinBlock2:
        case OwCoinBlock3:
            return TileType::OwCoinBlock1;

        case OwGround:           return TileType::OwGround;
        case OwInitialTile:     return TileType::OwInitialTile;
        case OwAfterHitBlock:   return TileType::OwAfterHitBlock;
        case OwPipeTop1:        return TileType::OwPipeTop1;
        case OwPipeTop2:        return TileType::OwPipeTop2;
        case OwPipeBottom1:     return TileType::OwPipeBottom1;
        case OwPipeBottom2:     return TileType::OwPipeBottom2;
        case HoriPipe1:         return TileType::HoriPipe1;
        case HoriPipe2:         return TileType::HoriPipe2;
        case UnderTile:         return TileType::UnderTile;
        case CastleTile:      return TileType::CastleTile;
        case HoriMovingBlock: return TileType::HoriMovingBlock;
        case VertMovingBlock: return TileType::VertMovingBlock;
        case GrassPlatform1:
        case GrassPlatform2:
        case GrassPlatform3:
            return TileType::GrassPlatform1;
        case OrangeDotPlatForm1:
        case OrangeDotPlatForm2:
        case OrangeDotPlatForm3:
            return TileType::OrangeDotPlatForm1;
        case GreenDotPlatForm1:
        case GreenDotPlatForm2:
        case GreenDotPlatForm3:
            return TileType::GreenDotPlatForm1;
        case CastleBrigde:      return TileType::CastleBrigde;
        case BrownCube:
            return TileType::BrownCube;
        case HiddenBox:
            return TileType::HiddenBox;
        case EndingPoint:
            return TileType::EndingPoint;
        default:
             return TileType::Empty;
    }
}


void TileBlock::setVelocity(Vector2 velocity){
    mVelocity = velocity;
}

void TileBlock::applyGravity(float dt){
    mVelocity.y -= Gravity * dt;
}


void TileBlock::setRect(Rectangle rect){
    mRect = rect;
    aniRect = rect;
}

void TileBlock::setPostile(Vector2 pos){
    posTile = pos;
}

void TileBlock::setSource(Rectangle source){
    mSource = source;
}

float TileBlock::calculateVec(float duration, float dis){
    return ((dis + 0.5f * Gravity * duration * duration) / duration);
}

void TileBlock::setAnimation(){
    aniTime = 0;
    isDoneAnimation = false;
}

void TileBlock::addFragment() {
    int pos =0;
    bool isfrag = false;
    if (getType(calType()) == TileType::OwInitialTile ) {
        isfrag = true;
        pos =4;
    }
    else if (getType(calType()) == TileType::UnderTile) {
        isfrag = true;
        pos = 13;
    }
    if(isfrag){
        frag.clear();
        const float fragSize = 24.0f;
        const float texSize = 8.0f;
        Vector2 baseTilePos = {pos * 16.0f, 0.0f};
        for (int i = 0; i < 4; ++i) {
            float offsetX = (i % 2) * fragSize;
            float offsetY = (i / 2) * fragSize;
            Vector2 fragWorldPos = { mRect.x + offsetX, mRect.y + offsetY };
            Vector2 fragTilePos = { baseTilePos.x + (i % 2) * texSize, baseTilePos.y + (i / 2) * texSize };
            auto f = std::make_unique<TileObject>(static_cast<TileItem>(pos), 0, 0);
            f->setRect({ fragWorldPos.x, fragWorldPos.y, fragSize, fragSize });
            f->mPhysics.setPosition({fragWorldPos.x, fragWorldPos.y});
            f->setPostile(fragTilePos);
            f->setSource({ fragTilePos.x, fragTilePos.y, texSize, texSize });
            frag.push_back(std::move(f));
        }
    }

}


void TileBlock::update(float dt){
    Vector2 mousePos = GetMousePosition();
    //std::cout << "TileBlock update: " << mType << std::endl;
    if (mBehavior) {
        mBehavior->update(*this, dt);
    }
    Vector2 position = mPhysics.getPosition();
    Vector2 size = getSize();
    if(mType!= TileType::Empty && isSolid()) {
    mBodyCollide.setHitBox({
        position.x,
        position.y,
        size.x,
        size.y
        });
    if(mType == 292 || mType == 301) mBodyCollide.setHitBox({
        position.x,
        position.y,
        size.x/2.0f,
        size.y/2.0f
        });
    } 
    else {
        mBodyCollide.setHitBox({0, 0, 0, 0});
    }
    // if (mType == 0 && !printed) {
    //     std::cout <<"Update" << mBodyCollide.getHitBox().x << " " << mBodyCollide.getHitBox().y << " " << mBodyCollide.getHitBox().width << " " << mBodyCollide.getHitBox().height << std::endl;
    // }
    //print();
}


bool TileBlock::isSolid(){
    return solid && !isDestroyed;
}
std::string TileBlock::getTag() {
    if(mType == 567) {
        return "EndingPoint";
    }
    if (mBehavior) {
        return mBehavior->getTag();
    }
    return "TileBlock";
}
void TileBlock::draw() {}

void TileBlock::handle() {}

Vector2 TileBlock::getSize(){
    if(!isDestroyed) {
        return {mRect.width, mRect.height};
    }
    return {0, 0};
}

void TileBlock::handleCollision(Side side, Collide other) {
    if(mBehavior) {
        mBehavior->setSide(side);
        mBehavior->setOther(other.getLabel());
        mBehavior->setTag(other.getOwner()->getTag());
    }
    if (mBehavior) {
        mBehavior->handleCollision(*this);
    }
    mColor = RED;
}

void TileBlock::serialize(nlohmann::json& j) {
    j["position"] = mPhysics.getPosition();
    j["velocity"] = mPhysics.getVelocity();
    j["ground"] = mPhysics.onGround();
    j["right"] = mPhysics.isRight();
    if (mType == 180 || mType == 181 || mType == 182) mType = 180;
    if (mType == 189 || mType == 190 || mType == 191) mType = 189;
    if (mType == 252 || mType == 253 || mType == 254) mType = 252;
    j["type"] = mType;
    j["rect"] = mRect;
    j["source"] = mSource;
    j["posTile"] = posTile;
    j["speed"] = mVelocity;
    j["aniRect"] = aniRect;
    j["printed"] = printed;
    j["isOn"] = isOn;
    j["isDoneAnimation"] = isDoneAnimation;
    j["bumped"] = bumped;
    j["isDestroyed"] = isDestroyed;
    j["solid"] = solid;
    j["aniTime"] = aniTime;
    j["row"] = mRow;
    j["col"] = mCol;
    j["frag"] = nlohmann::json::array();
    for (const auto& f: frag) {
        nlohmann::json js;
        f->serialize(js);
        j["frag"].push_back(js);
    }
}