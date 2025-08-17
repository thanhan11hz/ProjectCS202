
#include "Entity/TileEntity.hpp"
#include "Entity/TileItem.hpp"
#include "World/World.hpp"
#include <iostream>
using namespace std;
IBlockBehavior::~IBlockBehavior() = default;
void SimpleBlockBehavior::update(TileBlock& block, float dt) {
    Vector2 mousePos = GetMousePosition();
    if(CheckCollisionPointRec(mousePos, block.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) ) {
        if(block.isSolid()){
            std::cout << "Block is solid, cannot hit." << std::endl;
        }
    }
    
    if(block.bumped) bump(block, dt);
    if(block.isDestroyed) destroy(block, dt);
}

void SimpleBlockBehavior::handleCollision(TileBlock& block) {
    if ((block.getType(block.calType()) == TileType::OwInitialTile || block.getType(block.calType()) == TileType::UnderTile) && side==Side::BOTTOM && other == Category::MARIO && oTag == "Normal") {
        if(block.isDoneAnimation){
            block.mPhysics.setVelocity({0, 192.5f});
            block.isDoneAnimation = false;
            block.aniTime = 0.0f;
            block.bumped = true;
        }
    }
    if ((block.getType(block.calType()) == TileType::OwInitialTile || block.getType(block.calType()) == TileType::UnderTile)  && side == Side::BOTTOM && other == Category::MARIO && (oTag == "Super" || oTag == "Fire")) {
        // std::cout << "Destroying block" << "\n";
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::BLOCK_BREAK), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::BLOCK_BREAK));
        block.frag[0]->mPhysics.setVelocity({-80.0f, 300});
        block.frag[0]->setOn(true);
        block.frag[0]->setAnimation();

        block.frag[1]->mPhysics.setVelocity({80.0f, 300});
        block.frag[1]->setOn(true);
        block.frag[1]->setAnimation();

        block.frag[2]->mPhysics.setVelocity({-80.0f, 200});
        block.frag[2]->setOn(true);
        block.frag[2]->setAnimation();

        block.frag[3]->mPhysics.setVelocity({80.0f, 200});
        block.frag[3]->setOn(true);
        block.frag[3]->setAnimation();

        block.isDestroyed = true;
        block.mBodyCollide.setLabel(Category::NONE);
        block.isDoneAnimation = false;
        block.aniTime = 0.0f;
    }
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
        side = Side::NONE; 
        other = Category::NONE;
        oTag ="";
    }
}

void SimpleBlockBehavior::destroy(TileBlock& block, float dt) {
    //std::cout << "SimpleBlockBehavior destroy called" << std::endl;
    if (block.isDoneAnimation) return;
    block.aniTime += dt;
    if(block.aniTime < 1.0f){
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
    if(block.mType!=26 && block.mType!=556){
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
    if(block.bumped) {
        bump(block, dt);};
}

void CoinBlockBehavior::handleCollision(TileBlock& block) {
    if(side == Side::BOTTOM  && other == Category::MARIO && block.mType != 26){
        if(block.isDoneAnimation){
            SetSoundVolume(Resource::mSound.get(SoundIdentifier::COIN), sfxVolume);
            if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::COIN));
            mWorld.receiveCoin();
            block.mPhysics.setVelocity({0, 192.5f});
            block.isDoneAnimation = false;
            block.aniTime = 0.0f;
            block.bumped = true;
        }
        int pre = block.mType;
        block.mType = 26;
        if(block.mType == 26 && pre == 556) block.isOn = true;
        int x = (block.mType) % 29;
        int y = (block.mType) / 29;
        block.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE}; 
        block.mSource = {block.posTile.x, block.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE}; 
    }
}

void MovingBlockBehavior::update(TileBlock& block, float dt) {
    if (block.mType == 292) {
        float minY = block.mRect.y - 48.0f * 3;
        float maxY = block.mRect.y + 48.0f * 3;

        Vector2 pos = block.mPhysics.getPosition();
        Vector2 vel = block.mPhysics.getVelocity();

        pos.y += vel.y * dt;

        if (pos.y <= minY) {
            pos.y = minY;
            vel.y = 50.0f;
        }
        if (pos.y >= maxY) {
            pos.y = maxY;
            vel.y = -50.0f;
        }

        block.mPhysics.setPosition(pos);
        block.mPhysics.setVelocity(vel);
    }

    if (block.mType == 301) { 
        float minX = block.mRect.x - 48.0f * 3;
        float maxX = block.mRect.x + 48.0f * 3;

        Vector2 pos = block.mPhysics.getPosition();
        Vector2 vel = block.mPhysics.getVelocity();

        pos.x += vel.x * dt;

        if (pos.x <= minX) {
            pos.x = minX;
            vel.x = 50.0f;
        }
        if (pos.x >= maxX) {
            pos.x = maxX;
            vel.x = -50.0f;
        }

        block.mPhysics.setPosition(pos);
        block.mPhysics.setVelocity(vel);
    }
}