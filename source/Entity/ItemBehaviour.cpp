#include "Entity/TileItem.hpp"
#include "Global.hpp"
#include "World/World.hpp"

void FragmentBehavior::onCollect(TileObject& item) {
  
}
void FragmentBehavior::update(TileObject& item, float dt) {
    if (item.isDoneAnimation) return;

    item.mPhysics.accelerate({0, -1.5f*TileObject::Gravity*dt});
    Vector2 v = item.mPhysics.getVelocity();
    Vector2 pos = item.mPhysics.getPosition();
    item.mPhysics.setPosition({pos.x + v.x * dt, pos.y - v.y * dt});
}
void SimpleBehavior::update(TileObject& item, float dt) {
    if(item.isOn && !item.isUp) {
        moveUp(item, dt);
    } 
    
}

void SimpleBehavior::handleCollision(TileObject& item) {
    //std::cout << "SimpleBehavior handleCollision called" << std::endl;
    // if(side == Side::BOTTOM && other == Category::MARIO && !item.isAbsorbed && !item.isUp){
    //     item.setOn(true);
    //     item.setAnimation();
    //     item.mPhysics.setVelocity({0, 96.0f});
    // }
    // if(other == Category::MARIO && !item.isAbsorbed && item.isUp) {
    //     item.isOn=false;
    //     //item.isAbsorbed = true;
    // }
    if(side == Side::BOTTOM && other == Category::MARIO && !item.isUp){
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, -96.0f});

    }
    if(other == Category::MARIO && item.isUp) {
        item.isOn=false;
        item.setDie(true);

    }
}

void SimpleBehavior::moveUp(TileObject& item, float dt) { 
    if (item.isDoneAnimation) return;
    item.aniTime += dt;
    if(item.aniTime < 0.5f){
        return;
    } 
        
    float startY = item.mRect.y-48.0f;
    float finalY = item.mRect.y+48.0f;

    item.mPhysics.setPosition({item.mPhysics.getPosition().x, item.mPhysics.getPosition().y + item.mPhysics.getVelocity().y * dt});

    if (item.mPhysics.getPosition().y <= startY || (item.mType==10 && item.mPhysics.getPosition().y >= finalY)) {
        if(item.mType == 10) {
            item.mPhysics.setPosition({item.mPhysics.getPosition().x, finalY});
        }
        else item.mPhysics.setPosition({item.mPhysics.getPosition().x, startY});
        
        if (getTag() != "Flower") {
            item.isMoving = true;
            item.mPhysics.setVelocity({50,0});
        }
        else item.mPhysics.setVelocity({0,0});
        item.isDoneAnimation = true;
        item.aniTime = 0.0f;
        item.isUp = true;
        side = Side::NONE;
        other = Category::NONE;
        oTag = "";
        // if(getTag() == "Star") {
        //     std::cout << item.mPhysics.getPosition().x << " " << item.mPhysics.getPosition().y << std::endl;
        // } 
    }
}

void NormalCoinBehavior::onCollect(TileObject& item) {
    // Logic for collecting a normal coin
}

void NormalCoinBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();

    // if(!item.isAbsorbed){
    //     if(item.aniTime <= 0.2f){
    //         item.aniTime+=dt;
    //     }
    //     else{
    //         if(item.mType==180 || item.mType==180) item.mType +=1 ;
    //         else if (item.mType == 181 || item.mType==190) item.mType+=1;
    //         else item.mType -= 2;
    //         int x = (item.mType) % 36;
    //         int y = (item.mType) / 36;
    //         item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
    //         item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
    //         item.aniTime = 0.0f;
    //     }
    // }
    if(item.isOn && item.isUp){
        if(item.aniTime <= 0.3f){
            item.aniTime+=dt;
        }
        else{
            if(item.mType==180 || item.mType==189 || item.mType==252) item.mType +=1 ;
            else if (item.mType == 181 || item.mType==190 || item.mType==253) item.mType+=1;
            else item.mType -= 2;
            int x = (item.mType) % 36;
            int y = (item.mType) / 36;
            item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
            item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
            item.aniTime = 0.0f;
        }
    }
 
}

void NormalCoinBehavior::handleCollision(TileObject& item) {
    // if(side == Side::BOTTOM && other == Category::BLOCK && !item.isAbsorbed) {
    //     item.setOn(false);
    //     item.isAbsorbed = true;
    // }
    // if(other == Category::MARIO && !item.isAbsorbed && item.isUp) {
    //     item.setOn(false);
    //     item.isAbsorbed = true;
    // }

    if(side == Side::BOTTOM && other == Category::BLOCK && item.isUp ) {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::COIN), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::COIN));
        item.setOn(false);
        item.mBodyCollide.setLabel(Category::NONE);
        item.mBodyCollide.setFilter(Category::MARIO);
        item.setDie(true);
        mWorld.receiveCoin();
    }
    if(other == Category::MARIO && item.isUp) {
        // std::cout << "NormalCoinBehavior handleCollision called" << std::endl;
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::COIN), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::COIN));
        item.setOn(false);
        item.mBodyCollide.setLabel(Category::NONE);
        item.mBodyCollide.setFilter(Category::MARIO);
        item.setDie(true);
    }
}

void SpecialCoinBehavior::onCollect(TileObject& item) {
    // Logic for collecting a special coin
}

void SpecialCoinBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();
    
    // if(!item.isAbsorbed && !item.isDoneAnimation){
    //     if(item.aniTime <= 0.05f){
    //         item.aniTime+=dt;
    //     }
    //     else{
    //         if(item.mType==216 ) item.mType +=1 ;
    //         else if (item.mType == 217) item.mType+=1;
    //         else item.mType -= 2;
    //         int x = (item.mType) % 36;
    //         int y = (item.mType) / 36;
    //         item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
    //         item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
    //         item.aniTime = 0.0f;
    //     }
    // }
    // if(item.isOn && !item.isAbsorbed) {
        
    //     moveUp(item, dt);
    // }
    if(!item.isDoneAnimation){
        if(item.aniTime <= 0.05f){
            item.aniTime+=dt;
        }
        else{
            if(item.mType==216 ) item.mType +=1 ;
            else if (item.mType == 217) item.mType+=1;
            else item.mType -= 2;
            int x = (item.mType) % 36;
            int y = (item.mType) / 36;
            item.posTile = { x * TileBlock::TILE_SIZE, y * TileBlock::TILE_SIZE };
            item.mSource = {item.posTile.x, item.posTile.y, TileBlock::TILE_SIZE, TileBlock::TILE_SIZE };
            item.aniTime = 0.0f;
        }
    }
    if(item.isOn) {
        
        moveUp(item, dt);
    }
    
}
void SpecialCoinBehavior::handleCollision(TileObject& item) {

    // if(side == Side::BOTTOM && other == Category::MARIO && !item.isAbsorbed  && item.isDoneAnimation && !item.isUp){
    //     item.setOn(true);
    //     item.setAnimation();
    //     item.mPhysics.setVelocity({0, -500.0f});
        
    // }
   if(side == Side::BOTTOM && other == Category::MARIO  && item.isDoneAnimation && !item.isUp){
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::COIN), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::COIN));
        mWorld.receiveCoin();
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, -500.0f});
    }
}

void SpecialCoinBehavior::moveUp(TileObject& item, float dt) {
    // if (item.isDoneAnimation) return;
    // float startY = item.mRect.y;
    // item.mPhysics.accelerate({0, TileObject::Gravity*dt});
    // Vector2 v = item.mPhysics.getVelocity();
    // Vector2 pos = item.mPhysics.getPosition();
    // item.mPhysics.setPosition({pos.x + v.x * dt, pos.y + v.y * dt});
    // if (item.mPhysics.getPosition().y >= startY) {
    //     item.mPhysics.setPosition({item.mPhysics.getPosition().x, startY});
    //     item.isDoneAnimation = true;
    //     item.isAbsorbed= true;
    //     item.isOn = false;
    //     item.isUp = true;
    //     side = Side::NONE;
    //     other = Category::NONE;
    //     oTag = "";
    // }
    if (item.isDoneAnimation) return;
    float startY = item.mRect.y;
    item.mPhysics.accelerate({0, TileObject::Gravity*dt});
    Vector2 v = item.mPhysics.getVelocity();
    Vector2 pos = item.mPhysics.getPosition();
    item.mPhysics.setPosition({pos.x + v.x * dt, pos.y + v.y * dt});
    if (item.mPhysics.getPosition().y >= startY) {
        item.mPhysics.setPosition({item.mPhysics.getPosition().x, startY});
        item.isDoneAnimation = true;
        item.isOn = false;
        item.setDie(true);
        item.isUp = true;
        side = Side::NONE;
        other = Category::NONE;
        oTag = "";
    }
}

void MushroomBehavior::onCollect(TileObject& item) {
    // Logic for collecting a mushroom
}

void MushroomBehavior::update(TileObject& item, float dt) {
    // if(item.isUp) std::cout << "Mushroom is up" << std::endl;
    SimpleBehavior::update(item, dt);
    if(item.isOn && item.isUp){

        if(!item.mPhysics.onGround()){
            item.mPhysics.accelerate({0, TileObject::Gravity*dt});
        }
        else {
            float x =item.mPhysics.getVelocity().x;
            item.mPhysics.setVelocity({x, 0});
        }
        Vector2 v = item.mPhysics.getVelocity();
        Vector2 pos = item.mPhysics.getPosition();
        item.mPhysics.setPosition({pos.x + v.x * dt, pos.y + v.y * dt});
    }
}

void MushroomBehavior::handleCollision(TileObject& item) {
    // if(side == Side::BOTTOM && other == Category::MARIO && !item.isAbsorbed && !item.isUp){
    //     item.setOn(true);
    //     item.setAnimation();
    //     item.mPhysics.setVelocity({0, 96.0f});
    // }

    // if((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK && !item.isAbsorbed && item.isMoving) {
    //     float x = (side == Side::RIGHT) ? -50.0f : 50.0f;
    //     item.mPhysics.setVelocity({x, 0});
    //     side = Side::NONE;
    //     other = Category::NONE; 
    //     oTag = "";
    // }
    // if(other == Category::MARIO && !item.isAbsorbed && item.isUp) {
    //     item.setOn(false);
    //     item.mBodyCollide.setFilter(Category::MARIO);
    //     item.mBodyCollide.setLabel(Category::NONE);
    //     side = Side::NONE;
    //     other = Category::NONE; 
    //     oTag = "";
    //     item.isAbsorbed = true;
    // }
    if(side == Side::BOTTOM && other == Category::MARIO  && !item.isUp){
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::POWER_UP_APPEAR), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::POWER_UP_APPEAR));
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, -96.0f});
        if(item.mType == 10) {
            item.mPhysics.setVelocity({0, 96.0f});
        }
    }

    if((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK  && item.isMoving) {
        float x = (side == Side::RIGHT) ? -50.0f : 50.0f;
        item.mPhysics.setVelocity({x, 0});
        side = Side::NONE;
        other = Category::NONE; 
        oTag = "";
    }
    if(other == Category::MARIO && item.isUp) {
        item.setOn(false);
        item.setDie(true);
        item.mBodyCollide.setFilter(Category::MARIO);
        item.mBodyCollide.setLabel(Category::NONE);
        side = Side::NONE;
        other = Category::NONE; 
        oTag = "";

    }
    
}

void StarBehavior::onCollect(TileObject& item) {
    // Logic for collecting a star
}

void StarBehavior::update(TileObject& item, float dt) {
    SimpleBehavior::update(item, dt);

    if (!item.isOn || !item.isUp) return;

    if (!item.mPhysics.onGround()) {
        item.mPhysics.accelerate({0, TileObject::Gravity * dt});
    }

    Vector2 v = item.mPhysics.getVelocity();
    if(v.x < 0 && v.x >-100) item.mPhysics.setVelocity({-100, v.y});
    else if(v.x > 0 && v.x < 100) item.mPhysics.setVelocity({100, v.y});
    Vector2 pos = item.mPhysics.getPosition();
    item.mPhysics.setPosition({pos.x + v.x * dt, pos.y + v.y * dt});
}

// void StarBehavior::update(TileObject& item, float dt) {
//     SimpleBehavior::update(item, dt);

//     if(item.isOn && item.isUp){
//         if(!item.mPhysics.onGround()){
//             item.mPhysics.accelerate({0, TileObject::Gravity*dt});
//         }
//         else {
//             Vector2 vec = item.mPhysics.getVelocity();
//             item.mPhysics.setVelocity({vec.x, 0-vec.y});
//         }
//         Vector2 v = item.mPhysics.getVelocity();
//         Vector2 pos = item.mPhysics.getPosition();
//         item.mPhysics.setPosition({pos.x + v.x * dt, pos.y + v.y * dt});
//         // std::cout << "Star velocity: " << v.x << ", " << v.y << std::endl;
//         // std::cout << item.mPhysics.getPosition().x << " " << item.mPhysics.getPosition().y << std::endl;
//     }

// }

// void StarBehavior::handleCollision(TileObject& item) {
//     // if(side == Side::BOTTOM && other == Category::MARIO && !item.isAbsorbed && !item.isUp){
//     //     item.setOn(true);
//     //     item.setAnimation();
//     //     item.mPhysics.setVelocity({0, 96.0f});
//     // }

//     // if((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK && !item.isAbsorbed && item.isMoving) {
//     //     Vector2 velocity = item.mPhysics.getVelocity();
//     //     item.mPhysics.setVelocity({0-velocity.x, velocity.y});
//     //     side = Side::NONE;
//     //     other = Category::NONE; 
//     //     oTag = "";
//     // }
//     // if(( side == Side::TOP) && other == Category::BLOCK && !item.isAbsorbed && item.isMoving) {
//     //     Vector2 velocity = item.mPhysics.getVelocity();
//     //     item.mPhysics.setVelocity({velocity.x, 0-velocity.y});
//     //     side = Side::NONE;
//     //     other = Category::NONE; 
//     //     oTag = "";
//     // }
//     // if(other == Category::MARIO && !item.isAbsorbed && item.isUp) {
//     //     item.setOn(false);
//     //     item.mBodyCollide.setFilter(Category::MARIO);
//     //     item.mBodyCollide.setLabel(Category::NONE);
//     //     side = Side::NONE;
//     //     other = Category::NONE; 
//     //     oTag = "";
//     //     item.isAbsorbed = true;
//     // }
//     if(side == Side::BOTTOM && other == Category::MARIO  && !item.isUp){
//         item.setOn(true);
//         item.setAnimation();
//         item.mPhysics.setVelocity({0, 96.0f});
//     }

//     if((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK  && item.isMoving) {
//         Vector2 velocity = item.mPhysics.getVelocity();
//         item.mPhysics.setVelocity({0-velocity.x, velocity.y});
//         side = Side::NONE;
//         other = Category::NONE; 
//         oTag = "";
//     }
//     if(( side == Side::TOP) && other == Category::BLOCK  && item.isMoving) {
//         Vector2 velocity = item.mPhysics.getVelocity();
//         item.mPhysics.setVelocity({velocity.x, 0-velocity.y});
//         side = Side::NONE;
//         other = Category::NONE; 
//         oTag = "";
//     }
//     if(other == Category::MARIO  && item.isUp) {
//         item.setDie(true);
//         item.setOn(false);
//         item.mBodyCollide.setFilter(Category::MARIO);
//         item.mBodyCollide.setLabel(Category::NONE);
//         side = Side::NONE;
//         other = Category::NONE; 
//         oTag = "";
//     }
    
// }

void StarBehavior::handleCollision(TileObject& item) {
    if (side == Side::BOTTOM && other == Category::MARIO && !item.isUp) {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::POWER_UP_APPEAR), sfxVolume);
        if (!isMute) PlaySound(Resource::mSound.get(SoundIdentifier::POWER_UP_APPEAR));
        item.setOn(true);
        item.setAnimation();
        item.mPhysics.setVelocity({0, -96.0f});
    }

    if ((side == Side::LEFT || side == Side::RIGHT) && other == Category::BLOCK && item.isMoving) {

        Vector2 velocity = item.mPhysics.getVelocity();
        item.mPhysics.setVelocity({-velocity.x, velocity.y});
    }

    if (side == Side::TOP && other == Category::BLOCK && item.isMoving) {
        Vector2 velocity = item.mPhysics.getVelocity();
        item.mPhysics.setVelocity({velocity.x, -velocity.y});
    }

    if (side == Side::BOTTOM && other == Category::BLOCK && item.isMoving) {
        item.mPhysics.setVelocity({item.mPhysics.getVelocity().x, -400.0f});
    }

    if (other == Category::MARIO && item.isUp) {
        item.setDie(true);
        item.setOn(false);
        item.mBodyCollide.setFilter(Category::MARIO);
        item.mBodyCollide.setLabel(Category::NONE);
    }

    side = Side::NONE;
    other = Category::NONE;
    oTag = "";
}
