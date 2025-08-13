#include "Entity/FireBar.hpp"

FireBar::FireBar() {
    mBodyCollide.setFilter(static_cast<Category>(Category::BLOCK | Category::ENEMY));
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setDensity(0.0f);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FIREBAR), 9, 9);
    mAnim.setRepeating(true, false);
    mAnim.restart();   
    setAfterBlock(false);
}

FireBar::FireBar(const nlohmann::json& j) {
    mBodyCollide.setFilter(static_cast<Category>(Category::BLOCK | Category::ENEMY));
    mBodyCollide.setLabel(Category::ENEMY);
    mPhysics.setDensity(0.0f);
    mAnim.setTexture(&Resource::mTexture.get(TextureIdentifier::FIREBAR), 9, 9);
    mAnim.setRepeating(true, false);
    mAnim.restart();   
    setAfterBlock(false);
    mPhysics.setPosition(j["position"].get<Vector2>());
    mPhysics.setVelocity(j["velocity"].get<Vector2>());
    mPhysics.setOnGround(j["ground"].get<bool>());
    mPhysics.setRight(j["right"].get<bool>());
    mCenter = j["center"].get<Vector2>();
    mRadius = j["radius"].get<float>();
    mAngle = j["angle"].get<float>();
}

void FireBar::update(float dt) {
    Enemy::update(dt);
    mAngle += angularVelocity;
    if (mAngle > 360.0f) mAngle -= 360.0f;
    float angleRad = mAngle * PI / 180.0f;
    Vector2 position = {
        mCenter.x + mRadius * sinf(angleRad),
        mCenter.y + mRadius * cosf(angleRad)
    };
    mPhysics.setPosition(position);
    Entity::update(dt);
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
    for (int i = 0; i < 5; ++i) {
        std::unique_ptr<FireBar> firebar = std::make_unique<FireBar>();
        firebar->setCircle(position + Vector2{10.5, 10.5}, 27 * i);
        mFireBar.push_back(std::move(firebar));
    }
    return mFireBar;
}

void FireBar::serialize(nlohmann::json& j) {
    j = {
        {"position", mPhysics.getPosition()},
        {"velocity", mPhysics.getVelocity()},
        {"ground", mPhysics.onGround()},
        {"right", mPhysics.isRight()},
        {"center", mCenter},
        {"radius", mRadius},
        {"angle", mAngle},
        {"class", "fireBar"}
    };
}
