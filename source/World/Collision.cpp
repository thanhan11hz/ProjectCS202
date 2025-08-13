#include "World/Collision.hpp"
#include "Entity/Character.hpp"

Collision::Collision() : mCharacter(nullptr), mCharacter2(nullptr), mMain(nullptr), mEnemy(nullptr), mItem(nullptr), mProjectile(nullptr) {}

void Collision::addItem(std::vector<std::unique_ptr<TileObject>>& item) {
    mItem = &item;
}
        
void Collision::addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>>& block) {
    mMain = &block;
}

void Collision::addEnemy(std::vector<std::unique_ptr<Enemy>>& enemy) {
    mEnemy = &enemy;
}

void Collision::addProjectile(std::vector<std::unique_ptr<Entity>> &projectile) {
    mProjectile = &projectile;
}
        
void Collision::addCharacter(Character* character) {
    mCharacter = character;
}

void Collision::addCharacter2(Character* character) {
    mCharacter2 = character;
}

void Collision::handleCollision() {
    const float tileSize = 48.0f;

    // 1. Player vs. Blocks
    if (mCharacter && !mCharacter->isDie()) {
        Vector2 charPos = mCharacter->mPhysics.getPosition();
        int charCol = charPos.x / tileSize;
        int charRow = charPos.y / tileSize;
        int radius = 6;
        for (int i = charRow - radius; i <= charRow + radius; ++i) {
            for (int j = charCol - radius; j <= charCol + radius; ++j) {
                if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                    checkCollision(mCharacter->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                    checkFootCollision(mCharacter->mFootCollide, (*mMain)[i][j]->mBodyCollide);
                }
            }
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        Vector2 charPos = mCharacter2->mPhysics.getPosition();
        int charCol = charPos.x / tileSize;
        int charRow = charPos.y / tileSize;
        int radius = 4;

        for (int i = charRow - radius; i <= charRow + radius; ++i) {
            for (int j = charCol - radius; j <= charCol + radius; ++j) {
                if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                    checkCollision(mCharacter2->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                    checkFootCollision(mCharacter2->mFootCollide, (*mMain)[i][j]->mBodyCollide);
                }
            }
        }
    }
    
    // 2. Enemy .vs Block
    for (auto itr = (*mEnemy).begin(); itr != (*mEnemy).end();) {
        if (*itr && !(*itr)->isDie()) {
            const float tileSize = 48.0f;
            Vector2 enemyPos = (*itr)->mPhysics.getPosition();
            int enemyCol = enemyPos.x / tileSize;
            int enemyRow = enemyPos.y / tileSize;
            int radius = 6;

            for (int i = enemyRow - radius; i <= enemyRow + radius; ++i) {
                for (int j = enemyCol - radius; j <= enemyCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size()) {
                        checkCollision((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                        checkFootCollision((*itr)->mFootCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = (*mEnemy).erase(itr);
        }
    }
    // 2. Item vs Blocks
    for (auto itr = (*mItem).begin(); itr != (*mItem).end();) {
        if (*itr &&!(*itr)->isDie()) {
            const float tileSize = 48.0f;
            Vector2 itemPos = (*itr)->mPhysics.getPosition();
            int itemCol = itemPos.x / tileSize;
            int itemRow = itemPos.y / tileSize;
            int radius = 4;
            
            for (int i = itemRow - radius; i <= itemRow + radius; ++i) {
                for (int j = itemCol - radius; j <= itemCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*itr)->up()) {
                        checkCollision((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                        checkFootCollision((*itr)->mFootCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } 
        else if(!(*itr)->on() && (*itr)->up()) {
            itr = (*mItem).erase(itr);
        }
    }

    // 3. Projectile vs Blocks
    for (auto itr = (*mProjectile).begin(); itr != (*mProjectile).end();) {
        if (*itr && !(*itr)->isDie()) {
            Vector2 projectilePos = (*itr)->mPhysics.getPosition();
            int projectileCol = projectilePos.x / tileSize;
            int projectileRow = projectilePos.y / tileSize;
            int radius = 6;

            for (int i = projectileRow - radius; i <= projectileRow + radius; ++i) {
                for (int j = projectileCol - radius; j <= projectileCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                        checkCollision((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                        checkFootCollision((*itr)->mFootCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = (*mProjectile).erase(itr);
        }
    }

    // Player vs. Items
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mItem).size(); ++i) {
            checkCollision(mCharacter->mBodyCollide, (*mItem)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        for (int i = 0; i < (*mItem).size(); ++i) {
            checkCollision(mCharacter2->mBodyCollide, (*mItem)[i]->mBodyCollide);
        }
    }

    // 4. Player vs. Enemies
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mEnemy).size(); ++i) {
            checkCollision(mCharacter->mBodyCollide, (*mEnemy)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter->isDie()) {
        for (int i = 0; i < (*mEnemy).size(); ++i) {
            checkCollision(mCharacter2->mBodyCollide, (*mEnemy)[i]->mBodyCollide);
        }
    }

    // 5. Enemies vs. Projectiles
    for (int i = 0; i < (*mEnemy).size(); ++i) {
        for (int j = 0; j < (*mProjectile).size(); ++j) {
            checkCollision((*mEnemy)[i]->mBodyCollide, (*mProjectile)[j]->mBodyCollide);
        }
    }

    // 6. Character vs. Projectiles
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mProjectile).size(); ++i) {
            checkCollision(mCharacter->mBodyCollide, (*mProjectile)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        for (int i = 0; i < (*mProjectile).size(); ++i) {
            checkCollision(mCharacter2->mBodyCollide, (*mProjectile)[i]->mBodyCollide);
        }
    }

    // 7. Enemies vs. Enemies
    for (auto itr = (*mEnemy).begin(); itr != (*mEnemy).end();) {
        if (*itr && !(*itr)->isDie()) {
            for (auto itr2 = itr + 1; itr2 != (*mEnemy).end();) {
                if (*itr2 && !(*itr2)->isDie()) {
                    checkCollision((*itr)->mBodyCollide, (*itr2)->mBodyCollide);
                    itr2++;
                } else {
                    itr2 = (*mEnemy).erase(itr2);
                }
            }
            itr++;
        } else {
            itr = (*mEnemy).erase(itr);
        }
    }

    // 1. Player vs. Blocks
    if (mCharacter && !mCharacter->isDie()) {
        Vector2 charPos = mCharacter->mPhysics.getPosition();
        int charCol = charPos.x / tileSize;
        int charRow = charPos.y / tileSize;
        int radius = 6;

        for (int i = charRow - radius; i <= charRow + radius; ++i) {
            for (int j = charCol - radius; j <= charCol + radius; ++j) {
                if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                    separate(mCharacter->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                }
            }
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        Vector2 charPos = mCharacter2->mPhysics.getPosition();
        int charCol = charPos.x / tileSize;
        int charRow = charPos.y / tileSize;
        int radius = 4;

        for (int i = charRow - radius; i <= charRow + radius; ++i) {
            for (int j = charCol - radius; j <= charCol + radius; ++j) {
                if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                    separate(mCharacter2->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                }
            }
        }
    }

    // 2. Enemies vs. Blocks
    for (auto itr = (*mEnemy).begin(); itr != (*mEnemy).end();) {
        if (*itr && !(*itr)->isDie()) {
            Vector2 enemyPos = (*itr)->mPhysics.getPosition();
            int enemyCol = enemyPos.x / tileSize;
            int enemyRow = enemyPos.y / tileSize;
            int radius = 6;

            for (int i = enemyRow - radius; i <= enemyRow + radius; ++i) {
                for (int j = enemyCol - radius; j <= enemyCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                        separate((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = (*mEnemy).erase(itr);
        }
    }
    //Item vs Blocks
    for (auto itr = (*mItem).begin(); itr != (*mItem).end();) {
        if (*itr && !(*itr)->isDie()) {
            Vector2 itemPos = (*itr)->mPhysics.getPosition();
            int itemCol = itemPos.x / tileSize;
            int itemRow = itemPos.y / tileSize;
            int radius = 6;

            for (int i = itemRow - radius; i <= itemRow + radius; ++i) {
                for (int j = itemCol - radius; j <= itemCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j] && (*itr)->up()) {
                        separate((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } 
        else if(!(*itr)->on() && (*itr)->up()) {
            itr = (*mItem).erase(itr);
        }
    }

    // 3. Projectile vs Blocks
    for (auto itr = (*mProjectile).begin(); itr != (*mProjectile).end();) {
        if (*itr && !(*itr)->isDie()) {
            Vector2 projectilePos = (*itr)->mPhysics.getPosition();
            int projectileCol = projectilePos.x / tileSize;
            int projectileRow = projectilePos.y / tileSize;
            int radius = 6;

            for (int i = projectileRow - radius; i <= projectileRow + radius; ++i) {
                for (int j = projectileCol - radius; j <= projectileCol + radius; ++j) {
                    if (i >= 0 && i < (*mMain).size() && j >= 0 && j < (*mMain)[i].size() && (*mMain)[i][j]) {
                        separate((*itr)->mBodyCollide, (*mMain)[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = (*mProjectile).erase(itr);
        }
    }

    // 4. Player vs. Enemies
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mEnemy).size(); ++i) {
            separate(mCharacter->mBodyCollide, (*mEnemy)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        for (int i = 0; i < (*mEnemy).size(); ++i) {
            separate(mCharacter2->mBodyCollide, (*mEnemy)[i]->mBodyCollide);
        }
    }

    // Player vs. Items
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mItem).size(); ++i) {
            separate(mCharacter->mBodyCollide, (*mItem)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        for (int i = 0; i < (*mItem).size(); ++i) {
            separate(mCharacter2->mBodyCollide, (*mItem)[i]->mBodyCollide);
        }
    }

    // 5. Enemies vs. Projectiles
    for (int i = 0; i < (*mEnemy).size(); ++i) {
        for (int j = 0; j < (*mProjectile).size(); ++j) {
            separate((*mEnemy)[i]->mBodyCollide, (*mProjectile)[j]->mBodyCollide);
        }
    }

    // 6. Character vs. Projectiles
    if (mCharacter && !mCharacter->isDie()) {
        for (int i = 0; i < (*mProjectile).size(); ++i) {
            separate(mCharacter->mBodyCollide, (*mProjectile)[i]->mBodyCollide);
        }
    }

    if (mCharacter2 && !mCharacter2->isDie()) {
        for (int i = 0; i < (*mProjectile).size(); ++i) {
            separate(mCharacter2->mBodyCollide, (*mProjectile)[i]->mBodyCollide);
        }
    }

    // 7. Enemies vs. Enemies
    for (auto itr = (*mEnemy).begin(); itr != (*mEnemy).end();) {
        if (*itr && !(*itr)->isDie()) {
            for (auto itr2 = itr + 1; itr2 != (*mEnemy).end();) {
                if (*itr2 && !(*itr2)->isDie()) {
                    separate((*itr)->mBodyCollide, (*itr2)->mBodyCollide);
                    itr2++;
                } else {
                    itr2 = (*mEnemy).erase(itr2);
                }
            }
            itr++;
        } else {
            itr = (*mEnemy).erase(itr);
        }
    }
}
        
void Collision::checkCollision(Collide A, Collide B) {
    if (!checkBroadPhase(A, B)) return;
    std::pair<Side,Side> side = checkNarrowPhase(A, B);
    A.getOwner()->handleCollision(side.first, B);
    B.getOwner()->handleCollision(side.second, A);
}

void Collision::checkFootCollision(Collide A, Collide B) {
    if (!checkBroadPhase(A, B)) return;
    A.getOwner()->handleFootCollision(B);
}

bool Collision::checkBroadPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    return CheckCollisionRecs(hitBoxA, hitBoxB);
}
        
std::pair<Side,Side> Collision::checkNarrowPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    Rectangle intersection = {
        fmax(hitBoxA.x, hitBoxB.x),
        fmax(hitBoxA.y, hitBoxB.y),
        fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x),
        fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y),
    };
    return {getCollisionSide(hitBoxA, intersection), getCollisionSide(hitBoxB, intersection)};
}
        
void Collision::separate(Collide A, Collide B) {
    if (!checkBroadPhase(A, B)) return;
    if (A.canOverlap(B)) return;
    if (A.isStatic()) std::swap(A, B);
    std::pair<Side, Side> side = checkNarrowPhase(A, B);
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    Vector2 position = A.getOwner()->mPhysics.getPosition();
    switch (side.first) {
        case Side::TOP:
            position.y += fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y);
            A.getOwner()->mPhysics.setPosition(position);
            break;
        case Side::BOTTOM:
            position.y -= fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y);
            A.getOwner()->mPhysics.setPosition(position);
            break;
        case Side::LEFT:
            position.x += fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x);
            A.getOwner()->mPhysics.setPosition(position);
            break;
        case Side::RIGHT:
            position.x -= fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x);
            A.getOwner()->mPhysics.setPosition(position);
            break;
    }
    Vector2 postion = A.getOwner()->mPhysics.getPosition();
    Vector2 size = A.getOwner()->getSize();
    A.getOwner()->mBodyCollide.setHitBox({
        postion.x,
        postion.y,
        size.x,
        size.y
    });
}

Side Collision::getCollisionSide(Rectangle hitBoxA, Rectangle hitBoxB) {
    float halfWidthA = hitBoxA.width / 2.0f;
    float halfHeightA = hitBoxA.height / 2.0f;
    float halfWidthB = hitBoxB.width / 2.0f;
    float halfHeightB = hitBoxB.height / 2.0f;

    float centerA_x = hitBoxA.x + halfWidthA;
    float centerA_y = hitBoxA.y + halfHeightA;
    float centerB_x = hitBoxB.x + halfWidthB;
    float centerB_y = hitBoxB.y + halfHeightB;

    float diffX = centerA_x - centerB_x;
    float diffY = centerA_y - centerB_y;

    float overlapX = (halfWidthA + halfWidthB) - fabs(diffX);
    float overlapY = (halfHeightA + halfHeightB) - fabs(diffY);

    // The axis with the smallest overlap is the axis of collision
    if (overlapX < overlapY) {
        // This is a horizontal collision
        if (diffX > 0) {
            return Side::LEFT;
        } else {
            return Side::RIGHT;
        }
    } else {
        // This is a vertical collision
        if (diffY > 0) {
            return Side::TOP;
        } else {
            return Side::BOTTOM;
        }
    }
}