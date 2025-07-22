#include "Entity/TileItem.hpp"

void FragmentBehavior::onCollect(TileObject& item) {
  
}
void FragmentBehavior::update(TileObject& item, float dt) {
    //std::cout << "FragmentBehavior update called" << std::endl;
    if (item.isDoneAnimation) return;
    item.aniTime += dt;
    item.aniRect.x +=  item.mVelocity.x * item.aniTime;
    item.aniRect.y -= item.mVelocity.y * item.aniTime - (0.5f * TileBlock::Gravity * item.aniTime * item.aniTime);
}

void FlowerBehavior::update(TileObject& item, float dt) {
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, item.mRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        item.setOn(true);
        item.setAnimation();
        item.setVelocity({0, 96.0f});
    }
    if(item.isDoneAnimation) ;
}

void FlowerBehavior::moveUp(TileObject& item, float dt) { //xử lý lại để không có animation nào
    if (item.isDoneAnimation) return;

    item.aniTime += dt;

    float displacement = item.mVelocity.y * item.aniTime;
    float startY = item.mRect.y-48.0f;

    item.aniRect.y = startY - displacement;

    if (item.aniRect.y <= startY) {
        item.aniRect.y = startY;
        item.isDoneAnimation = true;
        item.aniTime = 0.0f;
    }
}
