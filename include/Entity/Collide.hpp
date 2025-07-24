#pragma once

#include <raylib.h>

enum Category {
    NORMAL_MARIO,
    FIRE_MARIO,
    SUPER_MARIO,
    COIN,
    BLOCK,
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
        void setFiler(Category filter);
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