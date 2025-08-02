#include "World/Collision.hpp"
#include "Entity/Character.hpp"

static bool check = false;

Collision::Collision() : mCharacter(nullptr) {

}

void Collision::addItem(std::vector<std::unique_ptr<TileObject>>& item) {
    for (int i = 0; i < item.size(); ++i) {
        mItem.push_back(item[i].get());
    }
}
        
void Collision::addBlock(std::vector<std::vector<std::unique_ptr<TileBlock>>>& block) {
    mMain.clear();
    for (int i = 0; i < block.size(); ++i) {
        std::vector<TileBlock*> mRow;
        for (int j = 0; j < block[i].size(); ++j) {
            mRow.push_back(block[i][j].get());
        }
        mMain.push_back(mRow);
    }
}

void Collision::addEnemy(std::vector<std::unique_ptr<Enemy>>& enemy) {
    for (int i = 0; i < enemy.size(); ++i) {
        mEnemy.push_back(enemy[i].get());
    }
}

void Collision::addProjectile(MovingEntity* projectile) {
    mProjectile.push_back(projectile);
}
        
void Collision::addCharacter(Character* character) {
    mCharacter = character;
}

void Collision::clearCollidables() {
    mCharacter = nullptr;
    mMain.clear();
    mEnemy.clear();
    mItem.clear();
    mProjectile.clear();
}

void Collision::handleCollision() {
    if (mCharacter) {
        for (int i = 0; i < mMain.size(); ++i) {
            for (int j = 0; j < mMain[i].size(); ++j) {
                checkCollision(mCharacter->mBodyCollide, mMain[i][j]->mBodyCollide);
                checkFootCollision(mCharacter->mFootCollide, mMain[i][j]->mBodyCollide);
            }
        }
    }

    // for (auto itr = mEnemy.begin(); itr != mEnemy.end();) {
    //     if (*itr && !(*itr)->isDie()) {
    //         for (int i = 0; i < mMain.size(); ++i) {
    //             for (int j = 0; j < mMain[i].size(); ++j) {
    //                 checkCollision((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
    //                 checkFootCollision((*itr)->mFootCollide, mMain[i][j]->mBodyCollide);
    //             }   
    //         }
    //         itr++;
    //     } else {
    //         itr = mEnemy.erase(itr);
    //     }
    // }

    for (auto itr = mEnemy.begin(); itr != mEnemy.end();) {
        if (*itr && !(*itr)->isDie()) {
            const float tileSize = 48.0f;
            Vector2 enemyPos = (*itr)->mPhysics.getPosition();
            int enemyCol = enemyPos.x / tileSize;
            int enemyRow = enemyPos.y / tileSize;
            int radius = 2;

            for (int i = enemyRow - radius; i <= enemyRow + radius; ++i) {
                for (int j = enemyCol - radius; j <= enemyCol + radius; ++j) {
                    if (i >= 0 && i < mMain.size() && j >= 0 && j < mMain[i].size()) {
                        checkCollision((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
                        checkFootCollision((*itr)->mFootCollide, mMain[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = mEnemy.erase(itr);
        }
    }

    for (auto itr = mProjectile.begin(); itr != mProjectile.end();) {
        if (*itr && !(*itr)->isDie()) {
            for (int i = 0; i < mMain.size(); ++i) {
                for (int j = 0; j < mMain[i].size(); ++j) {
                    checkCollision((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
                    checkFootCollision((*itr)->mFootCollide, mMain[i][j]->mBodyCollide);
                }   
            }
            itr++;
        } else {
            itr = mProjectile.erase(itr);
        }
    }


    if (mCharacter) {
        for (int i = 0; i < mEnemy.size(); ++i) {
            checkCollision(mCharacter->mBodyCollide, mEnemy[i]->mBodyCollide);
        }
    }

    for (int i = 0; i < mEnemy.size(); ++i) {
        for (int j = 0; j < mProjectile.size(); ++j) {
            checkCollision(mEnemy[i]->mBodyCollide, mProjectile[j]->mBodyCollide);
        }
    }

    if (mCharacter) {
        for (int i = 0; i < mMain.size(); ++i) {
            for (int j = 0; j < mMain[i].size(); ++j) {
                separate(mCharacter->mBodyCollide, mMain[i][j]->mBodyCollide);
            }
        }
    }

    // for (auto itr = mEnemy.begin(); itr != mEnemy.end();) {
    //     if (*itr && !(*itr)->isDie()) {
    //         for (int i = 0; i < mMain.size(); ++i) {
    //             for (int j = 0; j < mMain[i].size(); ++j) {
    //                 separate((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
    //             }   
    //         }
    //         itr++;
    //     } else {
    //         itr = mEnemy.erase(itr);
    //     }
    // }

    for (auto itr = mEnemy.begin(); itr != mEnemy.end();) {
        if (*itr && !(*itr)->isDie()) {
            const float tileSize = 48.0f;
            Vector2 enemyPos = (*itr)->mPhysics.getPosition();
            int enemyCol = enemyPos.x / tileSize;
            int enemyRow = enemyPos.y / tileSize;
            int radius = 2;

            for (int i = enemyRow - radius; i <= enemyRow + radius; ++i) {
                for (int j = enemyCol - radius; j <= enemyCol + radius; ++j) {
                    if (i >= 0 && i < mMain.size() && j >= 0 && j < mMain[i].size()) {
                        separate((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
                    }
                }
            }
            itr++;
        } else {
            itr = mEnemy.erase(itr);
        }
    }


    if (mCharacter) {
        for (int i = 0; i < mEnemy.size(); ++i) {
            separate(mCharacter->mBodyCollide, mEnemy[i]->mBodyCollide);
        }
    }

    for (auto itr = mProjectile.begin(); itr != mProjectile.end();) {
        if (*itr && !(*itr)->isDie()) {
            for (int i = 0; i < mMain.size(); ++i) {
                for (int j = 0; j < mMain[i].size(); ++j) {
                    separate((*itr)->mBodyCollide, mMain[i][j]->mBodyCollide);
                }   
            }
            itr++;
        } else {
            itr = mProjectile.erase(itr);
        }
    }

    for (int i = 0; i < mEnemy.size(); ++i) {
        for (int j = 0; j < mProjectile.size(); ++j) {
            separate(mEnemy[i]->mBodyCollide, mProjectile[j]->mBodyCollide);
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
    A.getOwner()->handleFootCollision();
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

// Side Collision::getCollisionSide(Rectangle hitBox, Rectangle intersection) {
//     float top = fabs(hitBox.y - intersection.y);
//     float bottom = fabs((hitBox.y + hitBox.height) - (intersection.y + intersection.height));
//     float left = fabs(hitBox.x - intersection.x);
//     float right = fabs((hitBox.x + hitBox.width) - (intersection.x + intersection.width));
//     float overlapX = (left < right) ? left : -right;
//     float overlapY = (top < bottom) ? top : -bottom;

//     if (fabs(overlapX) < fabs(overlapY) || (fabs(overlapX) == fabs(overlapY) && intersection.width < intersection.height)) {
//         return (overlapX > 0 || (overlapX == 0 && left == 0)) ? Side::LEFT : Side::RIGHT;
//     } else {
//         return (overlapY > 0 || (overlapY == 0 && top == 0)) ? Side::TOP : Side::BOTTOM;
//     }

// }

Side Collision::getCollisionSide(Rectangle hitBox, Rectangle intersection) {
    // Checking if the collision overlap is wider or taller.
    if (intersection.width < intersection.height) {
        float hitBoxCenterX = hitBox.x + hitBox.width / 2.0f;
        float intersectionCenterX = intersection.x + intersection.width / 2.0f;
        
        if (hitBoxCenterX < intersectionCenterX) {
            return Side::RIGHT;
        } else {
            return Side::LEFT;
        }
    } else {
        float hitBoxCenterY = hitBox.y + hitBox.height / 2.0f;
        float intersectionCenterY = intersection.y + intersection.height / 2.0f;
        
        if (hitBoxCenterY < intersectionCenterY) {
            return Side::BOTTOM;
        } else {
            return Side::TOP;
        }
    }
}