#include "Entity/TileItem.hpp"

TileObject::TileObject(int type, int row, int col) : TileBlock(type, row, col){
    if(type > 0){
        int x = (type) % 35;
        int y = (type) / 35;
        posTile = { x * TILE_SIZE, y * TILE_SIZE }; 
        mSource = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE };  
        mPhysics.setPosition({mRect.x, mRect.y});
        mBodyCollide.setStatic(false);
        createBehavior();
        if(getType() != normalCoin|| getType() != underCoin ) {
            isOn = false;
        }
        mBodyCollide.setLabel(Category::ITEM);
    }
    aniRect=mRect;
}

void TileObject::createBehavior()  {
    if(getType() == TileItem::fragment || getType() == TileItem::underfragment) {
        mBehavior = new FragmentBehavior();
    } 
    else if(getType() == TileItem::flower) {
        mBehavior = new SimpleBehavior();
    } 
    else if(getType() == TileItem::mushroom) {
        mBehavior = new MushroomBehavior();
    } 
    else if(getType() == TileItem::star) {
        mBehavior = new StarBehavior();
    } 
    else if(getType() == TileItem::normalCoin ) {
        mBehavior = new NormalCoinBehavior();
    }
    else if(getType() == TileItem::specialCoin ) {
        mBehavior = new SpecialCoinBehavior();
    } 
    else {
        mBehavior = nullptr;
    }
}
TileItem TileObject::getType() {
    switch (mType) {
        case mushroom: return TileItem::mushroom;
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
    if (mType != -1 && !isDestroyed && isOn) {
        float posX = mPhysics.getPosition().x;
        float posY = mPhysics.getPosition().y;
        {DrawTexturePro(object, mSource, {posX, posY, 48, 48}, {0, 0}, 0.0f, WHITE);}
    }
}

void TileObject::update(float dt) {
    Vector2 postion = mPhysics.getPosition();
    Vector2 size = getSize();
    if(getType()!= TileItem::invalidItem) {
    mBodyCollide.setHitBox({
        postion.x ,
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
