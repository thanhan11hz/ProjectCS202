
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
    234, 263,      // HoriPipe1..2
    60            // UnderTile
};
TileBlock::TileBlock(int type, int col, int row)
    : mType(type), mRect({(col * 48.0f), (row * 48.0f), 48, 48}), posTile({0, 0}), printed(false) {
    
    if(type >= 0){
        int x = type % 29;
        int y = type / 29;
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        addFragment();
        createBehavior();
        if(getType(calType())!= TileType::Empty) {
            solid = true;
        } 
    }
    aniRect=mRect;

}
void TileBlock::createBehavior()  {
    if(getType(calType()) == TileType::OwCoinBlock1 ) {
        mBehavior = new CoinBlockBehavior();
    } 
    else if(getType(calType()) == TileType::OwInitialTile || getType(calType()) == TileType::UnderTile) {
        mBehavior = new SimpleBlockBehavior();
    }
}

void TileBlock::draw( Texture2D& background, Texture2D& object) {
    if (mType != -1 && !isDestroyed) {
        {DrawTexturePro(background, mSource, aniRect, {0, 0}, 0.0f, WHITE);}
    }
    else if(mType != -1 && isDestroyed ) {
        for(int i =0; i < 4; i++){
            frag[i]->draw( background, object);
        }
    }

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

        case BrownCube:
            return TileType::BrownCube;

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
        case OwGround: return TileType::OwGround;
        case OwInitialTile: return TileType::OwInitialTile;
        case OwCoinBlock1: return TileType::OwCoinBlock1;
        case OwCoinBlock2: return TileType::OwCoinBlock1;
        case OwCoinBlock3: return TileType::OwCoinBlock1;
        case OwAfterHitBlock: return TileType::OwAfterHitBlock;
        case OwPipeTop1: return TileType::OwPipeTop1;
        case OwPipeTop2: return TileType::OwPipeTop2;
        case OwPipeBottom1: return TileType::OwPipeBottom1;
        case OwPipeBottom2: return TileType::OwPipeBottom2;
        case HoriPipe1: return TileType::HoriPipe1;
        case HoriPipe2: return TileType::HoriPipe2;
        case UnderTile: return TileType::UnderTile;
        default: return TileType::Empty;
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
    if (getType(calType()) == TileType::OwInitialTile ) {
        frag.clear();
        const float fragSize = 24.0f;
        const float texSize = 8.0f;
        Vector2 baseTilePos = {4 * 16.0f, 0.0f};
        for (int i = 0; i < 4; ++i) {
            float offsetX = (i % 2) * fragSize;
            float offsetY = (i / 2) * fragSize;
            Vector2 fragWorldPos = { mRect.x + offsetX, mRect.y + offsetY };
            Vector2 fragTilePos = { baseTilePos.x + (i % 2) * texSize, baseTilePos.y + (i / 2) * texSize };
            auto f = std::make_unique<TileObject>(TileItem::fragment, 0, 0);
            f->setRect({ fragWorldPos.x, fragWorldPos.y, fragSize, fragSize });
            f->setPostile(fragTilePos);
            f->setSource({ fragTilePos.x, fragTilePos.y, texSize, texSize });
            frag.push_back(std::move(f));
        }
    }

}


void TileBlock::update(float dt){
    Vector2 mousePos = GetMousePosition();
    if (mType == -1) return;  
    if (mBehavior) {
        mBehavior->update(*this, dt);
    }
    // if (getType()==TileType::OwCoinBlock1){
    //     if(CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
    //         mType = 26;
    //         int x = (mType) % 29;
    //         int y = (mType) / 29;
    //         posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
    //         mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE }; 
    //     }
    //     else if(mType!=26){
    //         if(aniTime <= 0.1f){
    //             aniTime+=dt;
    //         }
    //         else{
    //             if(mType==23) mType = 24;
    //             else if (mType == 24) mType=25;
    //             else mType = 23;
    //             int x = (mType) % 29;
    //             int y = (mType) / 29;
    //             posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
    //             mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
    //             aniTime = 0.0f;
    //         }
    //     }
    // }
    // if (getType() == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    //     if(isDoneAnimation){
    //         setVelocity({0, 192.5f});
    //         isDoneAnimation = false;
    //         aniTime = 0.0f;
    //         bumped = true;
    //     }
    // }
    // if(bumped) moveUp(dt);
    // if (getType() == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    //     frag[0]->setVelocity({-10.0f, frag[0]->calculateVec(0.2f, 10)});

    //     frag[0]->setAnimation();

    //     frag[1]->setVelocity({10.0f, frag[1]->calculateVec(0.2f, 10)});
     
    //     frag[1]->setAnimation();

    //     frag[2]->setVelocity({-10.0f, frag[2]->calculateVec(0.2f, 5)});

    //     frag[2]->setAnimation();

    //     frag[3]->setVelocity({10.0f, frag[3]->calculateVec(0.2f, 5)});
  
    //     frag[3]->setAnimation();

    //     isDestroyed = true;
    //     isDoneAnimation = false;
    //     aniTime = 0.0f;
    // }
    // if(isDestroyed) destroy(dt);
}

// void TileBlock::moveUp(float dt) {
//     if (isDoneAnimation) return;

//     aniTime += dt;
//     //float velocity = mVelocity.y - Gravity * aniTime;

//     float displacement = mVelocity.y * aniTime - 0.5f * Gravity * aniTime * aniTime;
//     float startY = mRect.y;

//     aniRect.y = startY - displacement;

//     if (aniRect.y >= startY) {
//         aniRect.y = startY;
//         isDoneAnimation = true;
//         aniTime = 0.0f;
//     }
// }


// void TileBlock::destroy(float dt){
//     if (isDoneAnimation) return;
//     aniTime += dt;
//     if(aniTime < 100.0f){
//         //std::cout << "\n" << aniTime << "\n";
//         for (int i = 0; i < 4; i++){
//             frag[i]->destroyAnimation(dt);
//         }
//     }
//     else{
//         mType = 0;
//     }
// }

bool TileBlock::isSolid(){
    return solid && !isDestroyed;
}


TileBlock::~TileBlock(){}

// void TileBlock::destroyAnimation(float dt) {
//     if (isDoneAnimation) return;
//     aniTime += dt;
//     aniRect.x +=  mVelocity.x * aniTime;
//     aniRect.y -= mVelocity.y * aniTime - (0.5f * Gravity * aniTime * aniTime);
// }

