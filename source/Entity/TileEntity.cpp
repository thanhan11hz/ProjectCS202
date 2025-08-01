
#include "Entity/TileEntity.hpp"
#include "Entity/TileItem.hpp"
#include "Global.hpp"
#include <iostream>
#include <raylib.h>
#include <algorithm>

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
    234, 263, 556,      // HoriPipe1..2
    60            // UnderTile
};
TileBlock::TileBlock(int type, int col, int row)
    : mType(type), mRect({(col * 48.0f), (row * 48.0f), 48, 48}), posTile({0, 0}), printed(false) {
    mBodyCollide.setLabel(Category::NONE);
    if(type >= 0){
        int x = type % 29;
        int y = type / 29;
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        addFragment();
        createBehavior();

        if(getType(calType())!= TileType::Empty) {
            solid = true;
            mBodyCollide.setLabel(Category::BLOCK);
        } 
        else {
            //std::cout << mType << "\n";
            mBodyCollide.setLabel(Category::NONE);}
        if(mType!= 556) isOn = true;
        mBodyCollide.setStatic(true);
        mBodyCollide.setFilter(Category::NONE);
        mPhysics.setPosition({mRect.x, mRect.y});
    }
    aniRect=mRect;

}
void TileBlock::createBehavior()  {
    if(getType(calType()) == TileType::OwCoinBlock1||getType(calType()) == TileType::HiddenBox ) {
        mBehavior = new CoinBlockBehavior();
    } 
    else if(getType(calType()) == TileType::OwInitialTile || getType(calType()) == TileType::UnderTile) {
        mBehavior = new SimpleBlockBehavior();
    }
}

void TileBlock::draw( Texture2D& background, Texture2D& object) {
    if (mType != -1 && !isDestroyed && isOn) {
        float posX = mPhysics.getPosition().x;
        float posY = mPhysics.getPosition().y;
        {DrawTexturePro(background, mSource, {posX, posY, mRect.width, mRect.height}, {0, 0}, 0.0f, WHITE);}
    }
    else if(mType != -1 && isDestroyed ) {
        for(int i =0; i < 4; i++){
            frag[i]->draw( background, object);
        }
    }
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, mColor);

}


void TileBlock::print(){
    if (printed == false) {
        if (mRect.x == 0 && mRect.y==0) std::cout << "Error! ";      
        std::cout << mType <<" " << mSource .x << " " << mSource.y <<  " " << mSource.width << " " << mSource.height  <<"\n";
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


        case GrassPlatform1:
        case GrassPlatform2:
        case GrassPlatform3:
            return TileType::GrassPlatform1;


        case GreenDotPlatForm1:
        case GreenDotPlatForm2:
        case GreenDotPlatForm3:
            return TileType::GreenDotPlatForm1;
        case CastleTile:      return TileType::CastleTile;
        case BrownCube:
            return TileType::BrownCube;
        case HiddenBox:
            return TileType::HiddenBox;

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

        case GrassPlatform1:
        case GrassPlatform2:
        case GrassPlatform3:
            return TileType::GrassPlatform1;


        case GreenDotPlatForm1:
        case GreenDotPlatForm2:
        case GreenDotPlatForm3:
            return TileType::GreenDotPlatForm1;

        case BrownCube:
            return TileType::BrownCube;
        case HiddenBox:
            return TileType::HiddenBox;
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
    else if (getType(calType()) == TileType::OwAfterHitBlock) {
        isfrag = true;
        pos = 13;
    }
    if(isfrag){
        std::cout << "Add fragment for " << pos << "\n";
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
    if (mType == -1) return;  
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    if(getType(calType())!= TileType::Empty && isSolid()) {
    mBodyCollide.setHitBox({
        postion.x,
        postion.y,
        size.x,
        size.y
        });
    } else {
        mBodyCollide.setHitBox({0, 0, 0, 0});
    }   
    if (mBehavior) {
        mBehavior->update(*this, dt);
    }
    
}


bool TileBlock::isSolid(){
    return solid && !isDestroyed;
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
    mColor = RED;
}
TileBlock::~TileBlock(){}

