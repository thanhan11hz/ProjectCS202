
#include "Entity/TileEntity.hpp"
#include "Entity/TileItem.hpp"
#include <iostream>
using namespace std;
void SimpleBlockBehavior::update(TileBlock& block, float dt) {
    Vector2 mousePos = GetMousePosition();
    if(CheckCollisionPointRec(mousePos, block.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) ) {
        if(block.isSolid()){
            std::cout << "Block is solid, cannot hit." << std::endl;
        }
    }
    if (block.getType(block.calType()) == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, block.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(block.isDoneAnimation){
            block.mPhysics.setVelocity({0, 192.5f});
            block.isDoneAnimation = false;
            block.aniTime = 0.0f;
            block.bumped = true;
        }
        std::cout << "Block hit!" << std::endl;
    }
    if(block.bumped) bump(block, dt);
    if (block.getType(block.calType()) == TileType::OwInitialTile && CheckCollisionPointRec(mousePos, block.mRect) && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        block.frag[0]->mPhysics.setVelocity({-10.0f, block.frag[0]->calculateVec(0.2f, 10)});
        block.frag[0]->setOn(true);
        block.frag[0]->setAnimation();

        block.frag[1]->mPhysics.setVelocity({10.0f, block.frag[1]->calculateVec(0.2f, 10)});
        block.frag[1]->setOn(true);
        block.frag[1]->setAnimation();

        block.frag[2]->mPhysics.setVelocity({-10.0f, block.frag[2]->calculateVec(0.2f, 5)});
        block.frag[2]->setOn(true);
        block.frag[2]->setAnimation();

        block.frag[3]->mPhysics.setVelocity({10.0f, block.frag[3]->calculateVec(0.2f, 5)});
        block.frag[3]->setOn(true);
        block.frag[3]->setAnimation();

        block.isDestroyed = true;
        block.isDoneAnimation = false;
        block.aniTime = 0.0f;
    }
    if(block.isDestroyed) destroy(block, dt);
}

void SimpleBlockBehavior::onHit(TileBlock& block, float dt) {
    if (block.isDoneAnimation) return;
    block.setAnimation();
    block.aniTime = 0.0f;
    block.bumped = true;
    block.setVelocity({0, 192.5f});
}
void SimpleBlockBehavior::bump(TileBlock& block, float dt) {
    if (block.isDoneAnimation) return;
    float startY = block.mRect.y;
    block.mPhysics.accelerate({0, -TileBlock::Gravity * dt});
    block.mPhysics.setPosition({block.mPhysics.getPosition().x, block.mPhysics.getPosition().y - block.mPhysics.getVelocity().y * dt});

    if (block.mPhysics.getPosition().y >= startY) {
        block.mPhysics.setPosition({block.mPhysics.getPosition().x, startY});
        block.isDoneAnimation = true;
        block.aniTime = 0.0f;
    }
}

void SimpleBlockBehavior::destroy(TileBlock& block, float dt) {
    //std::cout << "SimpleBlockBehavior destroy called" << std::endl;
    if (block.isDoneAnimation) return;
    block.aniTime += dt;
    if(block.aniTime < 100.0f){
        for (int i = 0; i < 4; i++){
            block.frag[i]->update(dt);
        }
    }
    else{
        block.mType = -1;
    }
}

/// @brief ///////////////////////////////////
/// @param block 
/// @param dt 
void CoinBlockBehavior::update(TileBlock& block, float dt) {
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, block.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && block.mType != 26){
        if(block.isDoneAnimation){
            block.setVelocity({0, 192.5f});
            block.isDoneAnimation = false;
            block.aniTime = 0.0f;
            block.bumped = true;
        }
        block.mType = 26;
        int x = (block.mType) % 29;
        int y = (block.mType) / 29;
        block.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE}; 
        block.mSource = {block.posTile.x, block.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE}; 
    }
    else if(block.mType!=26 && block.mType!=556){
        if(block.aniTime <= 0.2f){
            block.aniTime+=dt;
        }
        else{
            if(block.mType==23) block.mType = 24;
            else if (block.mType == 24) block.mType=25;
            else block.mType = 23;
            int x = (block.mType) % 29;
            int y = (block.mType) / 29;
            block.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE }; 
            block.mSource = {block.posTile.x, block.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };  
            block.aniTime = 0.0f;
        }
    }
    if(block.bumped) bump(block, dt);
}