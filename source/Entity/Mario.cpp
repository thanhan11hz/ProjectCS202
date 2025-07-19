#include "Mario.hpp"

Mario::Mario() {

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{mPosition.x, mPosition.y};
    bodyDef.motionLocks.angularZ = true;
    //mBody = b2CreateBody(Physics::mWorld, &bodyDef);

    mForm = new NormalForm(this);

}

void Mario::input() {

}

void Mario::update(float dt) {
    mPosition = Vector2{b2Body_GetPosition(mBody).x, b2Body_GetPosition(mBody).y};
    mAngle = b2Rot_GetAngle(b2Body_GetRotation(mBody));
}

void Mario::draw() {

}
