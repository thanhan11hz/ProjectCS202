#pragma once

#include <raylib.h>

class Entity; 

// THIS IS THE DEFINITIVE BITMASK CATEGORY ENUM.
enum Category {
    NONE            = 0,
    // Players (bit flags)
    NORMAL_MARIO    = 1 << 0,  // 1
    FIRE_MARIO      = 1 << 1,  // 2
    SUPER_MARIO     = 1 << 2,  // 4
    PLAYER          = NORMAL_MARIO | FIRE_MARIO | SUPER_MARIO, // Composite for any player

    // Environment/Objects (bit flags)
    BLOCK           = 1 << 3,  // 8
    BACKGROUND      = 1 << 4,  // 16 
    ITEM            = 1 << 5,  // 32
    COIN            = 1 << 6,  // 64

    // Enemies (bit flags)
    ENEMY           = 1 << 7,  // 128 (General enemy type)
    GOOMBA          = 1 << 8,  // 256
    KOOPA           = 1 << 9,  // 512
    PIRANHA_PLANT   = 1 << 10, // 1024
    ENEMY_SHELL     = 1 << 11, // 2048 (For kicked Koopa shells)
    PROJECTILE      = 1 << 12, // 4096 (For fireballs, etc.)
};

enum class Side {
    NONE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

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