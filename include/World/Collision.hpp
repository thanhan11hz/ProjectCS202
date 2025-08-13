#pragma once

#include "Entity/Enemy.hpp"
#include "Entity/TileItem.hpp"
#include "Entity/TileEntity.hpp"

class Character;

class Collision {
    public:

        Collision();
        void addItem(std::vector<std::unique_ptr<TileObject>> &item);
        void addEnemy(std::vector<std::unique_ptr<Enemy>> &enemy);
        void addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>> &block);
        void addProjectile(std::vector<std::unique_ptr<Entity>> &projectile);
        void addCharacter(Character* character);
        void addCharacter2(Character* character);
        void handleCollision();

    private:
        Character* mCharacter;
        Character* mCharacter2;
        std::vector<std::vector<std::unique_ptr<TileBlock>>> *mMain;
        std::vector<std::unique_ptr<TileObject>> *mItem;
        std::vector<std::unique_ptr<Enemy>> *mEnemy;
        std::vector<std::unique_ptr<Entity>> *mProjectile;

        void checkCollision(Collide A, Collide B);
        void checkFootCollision(Collide A, Collide B);
        bool checkBroadPhase(Collide A, Collide B);
        std::pair<Side,Side> checkNarrowPhase(Collide A, Collide B);
        void separate(Collide A, Collide B);
        Side getCollisionSide(Rectangle hitBox, Rectangle intersection);
};