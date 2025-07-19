#include "World/Physics.hpp"

Physics::Physics() {
    b2Vec2 gravity = {0.0f, 10.0f};
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;
    mWorld = b2CreateWorld(&worldDef);
}

void Physics::update(float dt) {
    b2World_Step(mWorld, dt, 4);
    updateSensor();
    updateContact();
}

void Physics::debugDraw() {
    b2World_Draw(mWorld, &mDraw.mDebugDraw);
}

void Physics::updateSensor() {
    
    b2SensorEvents se = b2World_GetSensorEvents(mWorld);

    for (int i = 0; i < se.beginCount; ++i) {
        
        const b2SensorBeginTouchEvent& e = se.beginEvents[i];

        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;

        UserData* sensorOwner  = (UserData*)b2Shape_GetUserData(e.sensorShapeId);
        UserData* otherVisitor = (UserData*)b2Shape_GetUserData(e.visitorShapeId);
        
        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;

        if (sensorOwner && sensorOwner->mListener)  sensorOwner->mListener->onSensorBegin(e.sensorShapeId, e.visitorShapeId);
        
        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;

        if (otherVisitor && otherVisitor->mListener) otherVisitor->mListener->onSensorBegin(e.visitorShapeId, e.sensorShapeId);

    }

    for (int i = 0; i < se.endCount; ++i) {

        const b2SensorEndTouchEvent& e = se.endEvents[i];

        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;

        UserData* sensorOwner  = (UserData*)b2Shape_GetUserData(e.sensorShapeId);
        UserData* otherVisitor = (UserData*)b2Shape_GetUserData(e.visitorShapeId);

        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;
        

        if (sensorOwner && sensorOwner->mListener)  sensorOwner->mListener->onSensorEnd(e.sensorShapeId, e.visitorShapeId);
        
        if (!b2Shape_IsValid(e.sensorShapeId)) continue;
        if (!b2Shape_IsValid(e.visitorShapeId)) continue;

        if (otherVisitor && otherVisitor->mListener) otherVisitor->mListener->onSensorEnd(e.visitorShapeId, e.sensorShapeId);
    }
}

void Physics::updateContact() {

    b2ContactEvents ce = b2World_GetContactEvents(mWorld);

    for (int i = 0; i < ce.beginCount; ++i) {
        
        const b2ContactBeginTouchEvent& e = ce.beginEvents[i];

        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        UserData* sensorOwner  = (UserData*)b2Shape_GetUserData(e.shapeIdA);
        UserData* otherVisitor = (UserData*)b2Shape_GetUserData(e.shapeIdB);
        
        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        if (sensorOwner && sensorOwner->mListener)  sensorOwner->mListener->onContactBegin(e.shapeIdA, e.shapeIdB);
        
        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        if (otherVisitor && otherVisitor->mListener) otherVisitor->mListener->onContactBegin(e.shapeIdA, e.shapeIdB);

    }

    for (int i = 0; i < ce.endCount; ++i) {
        
        const b2ContactEndTouchEvent& e = ce.endEvents[i];

        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        UserData* sensorOwner  = (UserData*)b2Shape_GetUserData(e.shapeIdA);
        UserData* otherVisitor = (UserData*)b2Shape_GetUserData(e.shapeIdB);
        
        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        if (sensorOwner && sensorOwner->mListener)  sensorOwner->mListener->onContactEnd(e.shapeIdA, e.shapeIdB);
        
        if (!b2Shape_IsValid(e.shapeIdA)) continue;
        if (!b2Shape_IsValid(e.shapeIdB)) continue;

        if (otherVisitor && otherVisitor->mListener) otherVisitor->mListener->onContactEnd(e.shapeIdA, e.shapeIdB);

    }
}
