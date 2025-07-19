#pragma once

#include <box2d/box2d.h>

class Listener {
    public:
        virtual void onSensorBegin(b2ShapeId self, b2ShapeId other) = 0;
        virtual void onSensorEnd(b2ShapeId self, b2ShapeId other) = 0;
        virtual void onContactBegin(b2ShapeId self, b2ShapeId other) = 0;
        virtual void onContactEnd(b2ShapeId self, b2ShapeId other) = 0;
};