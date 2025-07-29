#include "World/Collision.hpp"

static bool check = false;

Collision::Collision() : mCharacter(nullptr) {

}

void Collision::addItem() {
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
        
void Collision::addCharacter(Character* character) {
    mCharacter = character;
}

void Collision::addEnemy(Entity* enemy) {
    mEnemies.push_back(enemy);
}

void Collision::clearCollidables() {
    mCharacter = nullptr; 
    mMain.clear();        
    mEnemies.clear();     
}

void Collision::handleCollision() {
    if (mCharacter) {
        for (int i = 0; i < mMain.size(); ++i) {
            for (int j = 0; j < mMain[i].size(); ++j) {
                checkCollision(mCharacter->mCollide, mMain[i][j]->mCollide);
            }
        }
    }

    // Character vs. Enemies Collision
    if (mCharacter) {
        for (const auto& enemy : mEnemies) {
            if (enemy && !enemy->isDie()) {
                checkCollision(mCharacter->mCollide, enemy->mCollide);
            }
        }
    }

    // Enemies vs. Blocks Collision
    for (const auto& enemy : mEnemies) {
        if (enemy && !enemy->isDie()) {
            for (int i = 0; i < mMain.size(); ++i) {
                for (int j = 0; j < mMain[i].size(); ++j) {
                     if (mMain[i][j]) { // Check if block pointer is valid
                        checkCollision(enemy->mCollide, mMain[i][j]->mCollide);
                    }
                }
            }
        }
    }

    // Enemies vs. Enemies Collision (e.g., spinning shell hitting another enemy)
    for (size_t i = 0; i < mEnemies.size(); ++i) {
        if (!mEnemies[i] || mEnemies[i]->isDie()) continue; 

        for (size_t j = i + 1; j < mEnemies.size(); ++j) {
            if (!mEnemies[j] || mEnemies[j]->isDie()) continue; 

            if (mEnemies[i]->mCollide.getLabel() == Category::ENEMY_SHELL || 
                mEnemies[j]->mCollide.getLabel() == Category::ENEMY_SHELL) 
            {
                checkCollision(mEnemies[i]->mCollide, mEnemies[j]->mCollide);
            }
        }
    }
}
        
void Collision::checkCollision(Collide A, Collide B) {
    if (!checkBroadPhase(A, B)) return;
    std::pair<Side,Side> side = checkNarrowPhase(A, B);
    if (!A.canOverlap(B)) separate(A, B, side.first, side.second);
    A.getOwner()->handleCollision(side.first, B.getLabel());
    B.getOwner()->handleCollision(side.second, A.getLabel());
}

bool Collision::checkBroadPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    return CheckCollisionRecs(hitBoxA, hitBoxB);
}
        
std::pair<Side,Side> Collision::checkNarrowPhase(Collide A, Collide B) {
    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    if (hitBoxB.x == 816 && hitBoxB.y == 528) {
        std::cout << hitBoxA.x << " " << hitBoxA.y;
        //exit(0);
    }
    Rectangle intersection = {
        fmax(hitBoxA.x, hitBoxB.x),
        fmax(hitBoxA.y, hitBoxB.y),
        fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x),
        fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y),
    };
    // std::cout << "Collision" << hitBoxA.x << " " << hitBoxA.y << " " << hitBoxA.width << " " << hitBoxA.height << " " << hitBoxB.x << " " << hitBoxB.y << " " << hitBoxB.width << " " << hitBoxB.height << " "
    // << intersection.x << " " << intersection.y << " " << intersection.width << " " << intersection.height << "\n";
    return {getCollisionSide(hitBoxA, intersection), getCollisionSide(hitBoxB, intersection)};
}
        
void Collision::separate(Collide A, Collide B, Side sideA, Side sideB) {

    if (A.isStatic() && !B.isStatic()) std::swap(A, B); 
    else if (A.isStatic() && B.isStatic()) return; 

    Rectangle hitBoxA = A.getHitBox();
    Rectangle hitBoxB = B.getHitBox();
    Vector2 position = A.getOwner()->mPhysics.getPosition();

    float overlap_width = fmin(hitBoxA.x + hitBoxA.width, hitBoxB.x + hitBoxB.width) - fmax(hitBoxA.x, hitBoxB.x);
    float overlap_height = fmin(hitBoxA.y + hitBoxA.height, hitBoxB.y + hitBoxB.height) - fmax(hitBoxA.y, hitBoxB.y);

    switch (sideA) {
        case Side::TOP:
            position.y += overlap_height; 
            A.getOwner()->mPhysics.setPosition(position);
            A.getOwner()->mPhysics.setVelocity(A.getOwner()->mPhysics.getVelocity().x, 0.0f); 
            A.getOwner()->mPhysics.setOnGround(true); 
            break;
        case Side::BOTTOM:
            position.y -= overlap_height; 
            A.getOwner()->mPhysics.setPosition(position);
            A.getOwner()->mPhysics.setVelocity(A.getOwner()->mPhysics.getVelocity().x, 0.0f); 
            break;
        case Side::LEFT:
            position.x += overlap_width; 
            A.getOwner()->mPhysics.setPosition(position);
            A.getOwner()->mPhysics.setVelocity(0.0f, A.getOwner()->mPhysics.getVelocity().y); 
            break;
        case Side::RIGHT:
            position.x -= overlap_width; 
            A.getOwner()->mPhysics.setPosition(position);
            A.getOwner()->mPhysics.setVelocity(0.0f, A.getOwner()->mPhysics.getVelocity().y); 
            break;
        case Side::NONE: 
            break;
    }
    
    Vector2 updatedPosition = A.getOwner()->mPhysics.getPosition();
    Vector2 size = A.getOwner()->getSize(); 
    A.getOwner()->mCollide.setHitBox({
        updatedPosition.x,
        updatedPosition.y,
        size.x,
        size.y
    });
}

Side Collision::getCollisionSide(Rectangle hitBox, Rectangle intersection) {
    float topOverlap = fabs(hitBox.y - intersection.y);
    float bottomOverlap = fabs((hitBox.y + hitBox.height) - (intersection.y + intersection.height));
    float leftOverlap = fabs(hitBox.x - intersection.x);
    float rightOverlap = fabs((hitBox.x + hitBox.width) - (intersection.x + intersection.width));
    
    bool horizontalCollision = false;
    if (intersection.width < intersection.height) { 
        horizontalCollision = true;
    } else if (intersection.height < intersection.width) { 
        horizontalCollision = false;
    } else { 
        if (fmin(leftOverlap, rightOverlap) < fmin(topOverlap, bottomOverlap)) {
            horizontalCollision = true;
        } else {
            horizontalCollision = false;
        }
    }

    if (horizontalCollision) {
        return (leftOverlap < rightOverlap) ? Side::LEFT : Side::RIGHT;
    } else {
        return (topOverlap < bottomOverlap) ? Side::TOP : Side::BOTTOM;
    }
}