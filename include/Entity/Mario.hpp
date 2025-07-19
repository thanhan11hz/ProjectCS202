#pragma once

#include "Entity/Listener.hpp"
#include "Entity/Animation.hpp"
#include "Entity/MarioForm.hpp"

class Mario : public Listener {
    public:
        explicit Mario();
        void input();
        void update(float dt);
        void draw();

        void onGround();

        void onSensorBegin(b2ShapeId self, b2ShapeId other);
        void onSensorEnd(b2ShapeId self, b2ShapeId other);
        void onContactBegin(b2ShapeId self, b2ShapeId other);
        void onContactEnd(b2ShapeId self, b2ShapeId other);

    private:

        MarioForm* mForm;
        Vector2 mPosition;
        float mAngle;
        b2BodyId mBody;
};