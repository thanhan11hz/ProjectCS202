#include "Entity/Coin.hpp"

Coin::Coin() : mAnim(nullptr, 16, 16) {    

}

void Coin::update(float dt) {
    if (isCollected) {
        startJump();
        if (mIsGround) delete this;
    } 
}

void Coin::draw() {
    mAnim.draw(getPosition());
}

