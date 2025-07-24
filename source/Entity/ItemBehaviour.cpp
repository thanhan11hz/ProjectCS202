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

void FlowerBehavior::update(TileObject& item, float dt) {
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

void FlowerBehavior::moveUp(TileObject& item, float dt) { 
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
