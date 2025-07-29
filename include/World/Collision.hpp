#pragma once

#include "Entity/Character.hpp"
#include "Entity/TileItem.hpp"
#include "Entity/TileEntity.hpp"
#include "Entity/Entity.hpp"
class Collision {
    public:

        Collision();
        void addItem();
        void addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>>& block);
        void addCharacter(Character* character);
        
        void addEnemy(Entity* enemy);
        void clearCollidables(); 

        void handleCollision();

    private:

        Character* mCharacter;
        std::vector<std::vector<TileBlock*>> mMain;
        std::vector<std::vector<TileBlock>> mItem;
        std::vector<Entity*> mEnemies; 

        void checkCollision(Collide A, Collide B);
        bool checkBroadPhase(Collide A, Collide B);
        std::pair<Side,Side> checkNarrowPhase(Collide A, Collide B);
        void separate(Collide A, Collide B, Side sideA, Side sideB);
        Side getCollisionSide(Rectangle hitBox, Rectangle intersection);
};