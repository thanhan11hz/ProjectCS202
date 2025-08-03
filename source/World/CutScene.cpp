#include "World/CutScene.hpp"

// CutScene

bool CutScene::isPlaying() {
    return mIsPlaying;
}

void CutScene::setPlaying(bool flag) {
    mIsPlaying = flag;
}

// CutSceneManager

void CutSceneManager::update(float dt) {
    for (int i = 0; i < mCutScene.size(); ++i) {
        mCutScene[i]->update(dt);
    }
}
        
void CutSceneManager::addCutScene(std::unique_ptr<CutScene> cutScene) {
    mCutScene.push_back(std::move(cutScene));
}

// Ending Level

EndingLevel::EndingLevel() {
    mChar->setLockUpdate(true);
}

void EndingLevel::update(float dt) {
    mTimer += dt;
    if (!step1) {
        mChar->setAfterBlock(false);
        step1 = true;
    } else if (!step2) {
        if (!mChar->mPhysics.onGround()) {
            mChar->mPhysics.accelerate({0, 50});
            mChar->setMove(Character::Move::FLAGSLIP);
        } else {
            mChar->mPhysics.setRight(false);
            mChar->mPhysics.setPosition(mChar->mPhysics.getPosition() + Vector2{16, 0});
            if (mTimer > 2.0f) step2 = true;
        }
    } else if (!step3) {
        mChar->mPhysics.startJump(1);
        mChar->setMove(Character::Move::JUMP);
        step3 = true;
    } else if (!step4) {
        if (!mChar->mPhysics.onGround()) {
            mChar->mPhysics.accelerate({100, 0});
        } else {
            mChar->setMove(Character::Move::RUN);
            step4 = true;
        }
    } else {
        if (mChar->mPhysics.getPosition().x < mDestination.x) {
            mChar->mPhysics.accelerate({mChar->mLength, 0});
            mChar->setMove(Character::Move::RUN);
        } else {
            mChar->setAfterBlock(true);
            setPlaying(false);
        }
    }
}

EndingLevel::~EndingLevel() {
    mChar->setLockUpdate(false);
}

// Go into Pipe

GoIntoPipe::GoIntoPipe() {
    mChar->setLockUpdate(true);
}

void GoIntoPipe::update(float dt) {
    if (!step1) {
        mChar->setMove(Character::Move::RUN);
        mChar->mBodyCollide.setFilter(Category::BLOCK);
        step1 = true;
    } else if (!step2) {
        if (mChar->mPhysics.getPosition().x < mPipePosition.x) mChar->mPhysics.accelerate({mChar->mLength, 0});
        else step2 = true;
    } else if (!step3) {
        mChar->setMove(Character::Move::JUMP);
        mChar->mPhysics.setPosition(mDestination);
        mWorld.getCamera().target = mDestination;
        step3 = true;
    } else {
        if (mChar->mPhysics.onGround()) {
            mChar->mBodyCollide.setFilter(Category::NONE);
            setPlaying(false);
        }
    }
}

GoIntoPipe::~GoIntoPipe() {
    mChar->setLockUpdate(false);
}