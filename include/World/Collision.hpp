#pragma once

#include "Entity/Character.hpp"
#include "Entity/Enemy.hpp"
#include "Entity/TileItem.hpp"
#include "Entity/TileEntity.hpp"

class Collision {
    public:

        Collision();
        void addItem();
        void addEnemy(Enemy* enemy);
        void addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>>& block);
        void addCharacter(Character* character);
        void handleCollision();

    private:

        Character* mCharacter;
        std::vector<std::vector<TileBlock*>> mMain;
        std::vector<std::vector<TileBlock>> mItem;
        std::vector<Enemy*> mEnemy;
        void checkCollision(Collide A, Collide B);
        void checkFootCollision(Collide A, Collide B);
        bool checkBroadPhase(Collide A, Collide B);
        std::pair<Side,Side> checkNarrowPhase(Collide A, Collide B);
        void separate(Collide A, Collide B, Side sideA, Side sideB);
        Side getCollisionSide(Rectangle hitBox, Rectangle intersection);
};