#pragma once

#include <raylib.h>

enum Category {
    NONE = 0,
    MARIO = 1 << 0,
    COIN = 1 << 1,
    BLOCK = 1 << 2,
    ITEM = 1 << 3,
    ENEMY = 1 << 4,
    FOOT = 1 << 5,
    BACKGROUND = 1 << 6
};

enum class Side {
    NONE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Entity;

class Collide {
    public:

        Collide(Entity* owner);
        void setStatic(bool flag);
        bool isStatic() const;
        void setLabel(Category label);
        void setFilter(Category filter);
        void setHitBox(Rectangle hitBox);
        Category getLabel() const;
        Rectangle getHitBox() const;
        Entity* getOwner() const;
        bool canOverlap(Collide other);

    private:
        Entity* mOwner;
        Rectangle mHitBox;
        bool mStatic;
        Category mLabel;
        Category mFilter;
};