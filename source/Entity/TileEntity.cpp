#include "Entity/TileEntity.hpp"
#include <iostream>
#include <raylib.h>

TileBlock::TileBlock(int type, int col, int row, Texture2D& tile, Texture2D& object)
    : mType(type), mRect({(col * 48.0f), (row * 48.0f), 48, 48}), posTile({0, 0}), printed(false), tileTex(tile), objectTex(object) {
    
    if(type > 0){
        int x = (type - 1) % 29;
        int y = (type - 1) / 29;
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        addFragment();
    }
    else {
        posTile= {432.0f, 0.0f};
    }
    aniRect=mRect;
}


void TileBlock::draw(Texture2D& tile, Texture2D& object) {
    if (mType != 0 && !isDestroyed) {
        if(isUsingTile) {DrawTexturePro(tile, mSource, aniRect, {0, 0}, 0.0f, WHITE);}
        else {DrawTexturePro(object, mSource, aniRect, {0, 0}, 0.0f, WHITE);}
    }
    else if(mType != 0 && isDestroyed ) {
        for(int i =0; i < 4; i++){
            frag[i].draw(tile, object);
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

TileType TileBlock::getType(){
    if(static_cast<int>(TileType::OwInitialTile) == mType) {return TileType::OwInitialTile;}
    if(static_cast<int>(TileType::OwCoinBlock1) == mType) {return TileType::OwCoinBlock1;}
    return TileType::Empty;
}

void TileBlock::setVelocity(Vector2 velocity){
    mVelocity = velocity;
}

void TileBlock::applyGravity(float dt){
    mVelocity.y -= Gravity * dt;
}

void TileBlock::usingBlockTexture(){
    isUsingTile = false;
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
    std::cout << "addFragment" << "\n";
    if (getType() == TileType::OwInitialTile) {
        frag.clear(); 

        const float fragSize = 24.0f;
        const float texSize = 8.0f;
        Vector2 baseTilePos = {4 * 16.0f, 0.0f}; 

        for (int i = 0; i < 4; ++i) {
            float offsetX = (i % 2) * fragSize;
            float offsetY = (i / 2) * fragSize;

            Vector2 fragWorldPos = { mRect.x + offsetX, mRect.y + offsetY };
            Vector2 fragTilePos = { baseTilePos.x + (i % 2) * texSize, baseTilePos.y + (i / 2) * texSize };

            frag.emplace_back(TileBlock(4, mRect.x, mRect.y, tileTex, objectTex));
            frag[i].setRect({ fragWorldPos.x, fragWorldPos.y, fragSize, fragSize });
            frag[i].setPostile(fragTilePos);
            frag[i].setSource({ fragTilePos.x, fragTilePos.y, texSize, texSize });
        }
    }
}


void TileBlock::update(float dt){
    Vector2 mousePos = GetMousePosition();
    if (mType == 0) return;  
    if (getType() == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(isDoneAnimation){
            setVelocity({0, 192.5f});
            isDoneAnimation = false;
            aniTime = 0.0f;
            bumped = true;
        }
    }
    if(bumped) moveUp(dt);
    if (getType() == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        frag[0].setVelocity({-10.0f, frag[0].calculateVec(0.2f, 10)});
        frag[0].usingBlockTexture();
        frag[0].setAnimation();

        frag[1].setVelocity({10.0f, frag[1].calculateVec(0.2f, 10)});
        frag[1].usingBlockTexture();
        frag[1].setAnimation();

        frag[2].setVelocity({-10.0f, frag[2].calculateVec(0.2f, 5)});
        frag[2].usingBlockTexture();
        frag[2].setAnimation();

        frag[3].setVelocity({10.0f, frag[3].calculateVec(0.2f, 5)});
        frag[3].usingBlockTexture();
        frag[3].setAnimation();

        isUsingTile = false;
        isDestroyed = true;
        isDoneAnimation = false;
        aniTime = 0.0f;
    }
    if(isDestroyed) destroy(dt);
}

void TileBlock::moveUp(float dt) {
    if (isDoneAnimation) return;

    aniTime += dt;
    //float velocity = mVelocity.y - Gravity * aniTime;

    float displacement = mVelocity.y * aniTime - 0.5f * Gravity * aniTime * aniTime;
    float startY = mRect.y;

    aniRect.y = startY - displacement;

    if (aniRect.y >= startY) {
        aniRect.y = startY;
        isDoneAnimation = true;
        aniTime = 0.0f;
    }
}


void TileBlock::destroy(float dt){
    if (isDoneAnimation) return;
    aniTime += dt;
    if(aniTime < 100.0f){
        //std::cout << "\n" << aniTime << "\n";
        for (int i = 0; i < 4; i++){
            frag[i].destroyAnimation(dt);
        }
    }
    else{
        mType = 0;
        isUsingTile = true;
    }
}

void TileBlock::destroyAnimation(float dt) {
    if (isDoneAnimation) return;
    aniTime += dt;
    aniRect.x +=  mVelocity.x * aniTime;
    aniRect.y -= mVelocity.y * aniTime - (0.5f * Gravity * aniTime * aniTime);


}
