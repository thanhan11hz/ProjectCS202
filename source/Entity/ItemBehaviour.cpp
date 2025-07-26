#include "Entity/TileItem.hpp"

void FragmentBehavior::onCollect(TileObject& item) {
  
}
void FragmentBehavior::update(TileObject& item, float dt) {
    //std::cout << "FragmentBehavior update called" << std::endl;
    if (item.isDoneAnimation) return;
    item.aniTime += dt;
    float offsetX = item.mPhysics.getVelocity().x * item.aniTime;
    item.mPhysics.accelerate({0, -TileBlock::Gravity * dt});
    item.mPhysics.setPosition({item.mPhysics.getPosition().x + offsetX, item.mPhysics.getPosition().y - item.mPhysics.getVelocity().y * dt});

}

void SimpleBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, item.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, 96.0f});
    }
    if(!item.isDoneAnimation && !item.isUp) {
        moveUp(item, dt);
    } 
}

void SimpleBehavior::moveUp(TileObject& item, float dt) { 
    if (item.isDoneAnimation) return;
    item.aniTime += dt;
    if(item.aniTime < 0.2f) return;
    float startY = item.mRect.y-48.0f;

    item.mPhysics.setPosition({item.mPhysics.getPosition().x, item.mPhysics.getPosition().y - item.mPhysics.getVelocity().y * dt});

    if (item.mPhysics.getPosition().y <= startY) {
        item.mPhysics.setPosition({item.mPhysics.getPosition().x, startY});
        item.isDoneAnimation = true;
        item.aniTime = 0.0f;
        item.isUp = true;
    }
}

void NormalCoinBehavior::onCollect(TileObject& item) {
    // Logic for collecting a normal coin
}

void NormalCoinBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, item.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !item.isAbsorbed) {
        item.setOn(false);
        item.isAbsorbed = true;
        item.mType = -1;
    }
    else if(!item.isAbsorbed){
        if(item.aniTime <= 0.2f){
            item.aniTime+=dt;
        }
        else{
            if(item.mType==180 || item.mType==180) item.mType +=1 ;
            else if (item.mType == 181 || item.mType==190) item.mType+=1;
            else item.mType -= 2;
            int x = (item.mType) % 35;
            int y = (item.mType) / 35;
            item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
            item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
            item.aniTime = 0.0f;
        }
    }
}

void SpecialCoinBehavior::onCollect(TileObject& item) {
    // Logic for collecting a special coin
}

void SpecialCoinBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, item.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !item.isAbsorbed) {
        item.bumped = true;
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, item.calculateVec(0.3f, 144.0f)});
    }
    else if(!item.isAbsorbed){
        if(item.aniTime <= 0.1f){
            item.aniTime+=dt;
        }
        else{
            if(item.mType==216 ) item.mType +=1 ;
            else if (item.mType == 217) item.mType+=1;
            else item.mType -= 2;
            int x = (item.mType) % 35;
            int y = (item.mType) / 35;
            item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
            item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
            item.aniTime = 0.0f;
        }
    }
    if(item.bumped && !item.isAbsorbed) moveUp(item, dt);
}

void SpecialCoinBehavior::moveUp(TileObject& item, float dt) {
    if (item.isDoneAnimation) return;
    float startY = item.mRect.y;
    item.mPhysics.accelerate({0, -TileBlock::Gravity * dt});
    item.mPhysics.setPosition({item.mPhysics.getPosition().x, item.mPhysics.getPosition().y - item.mPhysics.getVelocity().y * dt});

    if (item.mPhysics.getPosition().y >= startY) {
        item.mPhysics.setPosition({item.mPhysics.getPosition().x, startY});
        item.isDoneAnimation = true;
        item.isAbsorbed = true;
    }
}

void MushroomBehavior::onCollect(TileObject& item) {
    // Logic for collecting a mushroom
}

void MushroomBehavior::update(TileObject& item, float dt) {
    SimpleBehavior::update(item, dt);
    Vector2 mousePos = GetMousePosition();
    if(item.isUp){
        
    }
}

void StarBehavior::onCollect(TileObject& item) {
    // Logic for collecting a star
}

void StarBehavior::update(TileObject& item, float dt) {
    SimpleBehavior::update(item, dt);
    Vector2 mousePos = GetMousePosition();
    // if(item.isUp){
    //     if(side == Side::BOTTOM && other == Category::BLOCK ) {
    //         item.isMoving = true;
    //         Vector2 velocity = item.mPhysics.getVelocity();
    //         if(velocity.x == 0) item.mPhysics.setVelocity({50, 0});
            
    //     }
    //     else if((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK) {
    //         item.isMoving = true;
    //         Vector2 velocity = item.mPhysics.getVelocity();
    //         item.mPhysics.setVelocity({-velocity.x, velocity.y});
            
    //     }
        
    // }
    // item.mPhysics.setPosition({item.mPhysics.getPosition().x + item.mPhysics.getVelocity().x * dt, item.mPhysics.getPosition().y + item.mPhysics.getVelocity().y * dt});

}

