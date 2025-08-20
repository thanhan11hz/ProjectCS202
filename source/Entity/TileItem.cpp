#include "Entity/TileItem.hpp"

TileObject::TileObject(int type, int col, int row) : TileBlock(type, col, row){
    if(type > -1){
        int x = (type) % 36;
        int y = (type) / 36;
        mRect = {(col * TILE_RENDER_SIZE), (row * TILE_RENDER_SIZE), TILE_RENDER_SIZE, TILE_RENDER_SIZE};
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        mPhysics.setPosition({mRect.x, mRect.y});
        mBodyCollide.setStatic(false);
        createBehavior();
        //isOn = true;
        mBodyCollide.setLabel(Category::ITEM);
        mBodyCollide.setFilter(Category::ENEMY);

       if (type != 180 && type != 189 && type != 44 && type != 252) {
            isOn = false;
            isUp = false;
            // if (type != 4 && type != 13)
            //     std::cout << "1.TileObject created with type: " << type << std::endl;
        } else {
            isOn = true;
            isUp = true;
            // std::cout << "2.TileObject created with type: " << type << std::endl;
        }

        if(getType() == specialCoin) {
            mBodyCollide.setFilter(Category::BLOCK);
            
        }
        mCol = col;
        mRow = row;
    }
    aniRect=mRect;
}

TileObject::TileObject(const nlohmann::json& j) : TileBlock(j) {
    if(mType > -1){
        // int x = (type) % 36;
        // int y = (type) / 36;
        // mRect = {(col * TILE_RENDER_SIZE), (row * TILE_RENDER_SIZE), TILE_RENDER_SIZE, TILE_RENDER_SIZE};
        // posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        // mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        mPhysics.setPosition({mRect.x, mRect.y});
        mBodyCollide.setStatic(false);
        createBehavior();
        //isOn = true;
        mBodyCollide.setLabel(Category::ITEM);
        mBodyCollide.setFilter(Category::ENEMY);

    //    if (type != 180 && type != 189 && type != 44 && type != 252) {
    //         isOn = false;
    //         isUp = false;
    //         // if (type != 4 && type != 13)
    //         //     std::cout << "1.TileObject created with type: " << type << std::endl;
    //     } else {
    //         isOn = true;
    //         isUp = true;
    //         // std::cout << "2.TileObject created with type: " << type << std::endl;
    //     }

        if(getType() == specialCoin) {
            mBodyCollide.setFilter(Category::BLOCK);
            
        }
        // mCol = col;
        // mRow = row;
    }
    isUp = j["up"].get<bool>();
    isMoving = j["moving"].get<bool>();
    isAbsorbed = j["absorbed"].get<bool>();
}

void TileObject::createBehavior()  {
    if(getType() == TileItem::fragment || getType() == TileItem::underfragment) {
        mBehavior = std::make_unique<FragmentBehavior>();
    } 
    else if(getType() == TileItem::flower) {
        mBehavior = std::make_unique<SimpleBehavior>();
    } 
    else if(getType() == TileItem::mushroom ||getType() == TileItem::underMushroom ) {
        mBehavior = std::make_unique<MushroomBehavior>();
    } 
    else if(getType() == TileItem::greenMushroom) {
        mBehavior = std::make_unique<GreenMushroomBehavior>();
    } 
    else if(getType() == TileItem::star) {
        mBehavior = std::make_unique<StarBehavior>();
    } 
    else if(getType() == TileItem::normalCoin || getType() == TileItem::underCoin) {
        mBehavior = std::make_unique<NormalCoinBehavior>();
    }
    else if(getType() == TileItem::specialCoin ) {
        mBehavior = std::make_unique<SpecialCoinBehavior>();
    } 
    else if( getType() == TileItem::hammer) {
        mBehavior = std::make_unique<NormalCoinBehavior>();
    } 
    
    else {
        mBehavior = nullptr;
    }
}
TileItem TileObject::getType() {
    switch (mType) {
        case mushroom: return TileItem::mushroom;
        case greenMushroom: return TileItem::greenMushroom;
        case underMushroom: return TileItem::underMushroom; 
        case flag: return TileItem::flag;
        case hammer: return TileItem::hammer;
        case fragment: return TileItem::fragment;
        case underfragment: return TileItem::underfragment;
        case flower: return TileItem::flower;
        case star: return TileItem::star;
        case normalCoin: return TileItem::normalCoin;
        case underCoin: return TileItem::underCoin;
        case specialCoin: return TileItem::specialCoin;
        default: return TileItem::invalidItem;
    }
}
void TileObject::draw(Texture2D& background, Texture2D& object){
    // if (mType != -1 && !isAbsorbed && isOn) {
    //     float posX = mPhysics.getPosition().x;
    //     float posY = mPhysics.getPosition().y;
    //     {DrawTexturePro(object, mSource, {posX, posY, mRect.width, mRect.height}, {0, 0}, 0.0f, WHITE);}
    // }
    if (mType != -1 && isOn) {
        float posX = mPhysics.getPosition().x;
        float posY = mPhysics.getPosition().y;
        {DrawTexturePro(object, mSource, {posX, posY, mRect.width, mRect.height}, {0, 0}, 0.0f, WHITE);}
    }
    DrawRectangleLines(mBodyCollide.getHitBox().x, mBodyCollide.getHitBox().y, mBodyCollide.getHitBox().width, mBodyCollide.getHitBox().height, mColor);
}

void TileObject::update(float dt) {
    if(!isOn && isUp) return;
    if (mBehavior) {
        mBehavior->update(*this, dt);
    }
    Vector2 position = mPhysics.getPosition();
    Vector2 size = getSize();
    if(getType()!= TileItem::invalidItem) {
        mBodyCollide.setHitBox({
            position.x ,
            position.y,
            size.x,
            size.y
        });
        
    } 
    
    else {
        mBodyCollide.setHitBox({0, 0, 0, 0});
    } 

    // if(!isOn && isUp){
    //     mBodyCollide.setHitBox({0, 0, 0, 0});
    // }
    mFootCollide.setHitBox({
        position.x + 4,
        position.y + size.y,
        size.x - 8,
        1
    });
    // float mSpeed = mPhysics.getVelocity().x;
    // mPhysics.accelerate(Vector2{mSpeed, 0});
    mPhysics.setOnGround(false);
}

void TileObject::handleCollision(Side side, Collide other) {
   if(mBehavior) {
        mBehavior->setSide(side);
        mBehavior->setOther(other.getLabel());
        mBehavior->setTag(other.getOwner()->getTag());
        mBehavior->handleCollision(*this);
    }
    
    mColor = RED;
}

std::string TileObject::getTag(){
    if(mBehavior){
        return mBehavior->getTag();
    }
    return "Tille Item";
}

void TileObject::serialize(nlohmann::json& j) {
    TileBlock::serialize(j);
    j["up"] = isUp;
    j["moving"] = isMoving;
    j["absorbed"] = isAbsorbed;
}