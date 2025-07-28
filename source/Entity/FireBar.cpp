#include "Entity/FireBar.hpp"

FireBar::FireBar() {
    mBodyCollide.setFilter(Category::NONE);
    mBodyCollide.setLabel(Category::ENEMY);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FIREBAR), 9, 9);
    mAnim.setRepeating(true, false);
    mAnim.restart();   
}

void FireBar::update(float dt) {
    mAngle += angularVelocity;
    if (mAngle > 360.0f) mAngle -= 360.0f;
    float angleRad = mAngle * PI / 180.0f;
    Vector2 position = {
        mCenter.x + mRadius * sinf(angleRad),
        mCenter.y + mRadius * cosf(angleRad)
    };
    mPhysics.setPosition(position);
    mAnim.update(dt);
}
        
void FireBar::handle() {
}
        
void FireBar::draw() {
    mAnim.draw(mPhysics.getPosition(), 3.0f, 0.0f);
}

void FireBar::handleCollision(Side side, Collide other) {

}
        
Vector2 FireBar::getSize() {
    return {27, 27};
}

std::string FireBar::getTag() {
    return "Podoboo";
}

void FireBar::setCircle(Vector2 center, float radius) {
    mCenter = center;
    mRadius = radius;
}

std::vector<std::unique_ptr<FireBar>> FireBar::spawnFireBar(Vector2 position) {
    std::vector<std::unique_ptr<FireBar>> mFireBar;
    for (int i = 0; i < 6; ++i) {
        std::unique_ptr<FireBar> firebar = std::make_unique<FireBar>();
        firebar->setCircle(position, 9 * (i + 1));
        mFireBar.push_back(std::move(firebar));
    }
    return mFireBar;
}
