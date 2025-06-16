#pragma once

#include <raylib.h>

class Component {
    public:
        virtual ~Component() = default;
        virtual bool isSelectable() = 0;
        virtual void select();
        virtual void deselect();
        virtual void activate();
        virtual void deactivate();
        virtual void handle() = 0;
        virtual void draw() = 0;
        bool isActive();
        bool isSelected();

    protected:
        bool mIsActive = false;
        bool mIsSelected = false;

};