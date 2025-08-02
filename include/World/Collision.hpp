#pragma once

#include "Entity/Enemy.hpp"
#include "Entity/TileItem.hpp"
#include "Entity/TileEntity.hpp"

class Character;

class Collision {
    public:

        Collision();
        void addItem(std::vector<std::unique_ptr<TileObject>>& item);
        void addEnemy(std::vector<std::unique_ptr<Enemy>>& enemy);
        void addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>>& block);
        void addProjectile(MovingEntity* projectile);
        void addCharacter(Character* character);
        void handleCollision();
        void clearCollidables();

    private:

        Character* mCharacter;
        std::vector<std::vector<TileBlock*>> mMain;
        std::vector<TileObject*> mItem;
        std::vector<Enemy*> mEnemy;
        std::vector<MovingEntity*> mProjectile;
        void checkCollision(Collide A, Collide B);
        void checkFootCollision(Collide A, Collide B);
        bool checkBroadPhase(Collide A, Collide B);
        std::pair<Side,Side> checkNarrowPhase(Collide A, Collide B);
        void separate(Collide A, Collide B);
        Side getCollisionSide(Rectangle hitBox, Rectangle intersection);
};