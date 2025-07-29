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

void EndingLevel::update(float dt) {
    if (!mChar->mPhysics.onGround()) mChar->mPhysics.accelerate({0, 50}); 
    else {
        if (mChar->mPhysics.getPosition().x < mDestination.x) {
            mChar->mPhysics.accelerate({100, 0});
        } else {
            setPlaying(false);
        }
    }
}

EndingLevel::~EndingLevel() {

}

// Go into Pipe

void GoIntoPipe::update(float dt) {
    if (mChar->mPhysics.getPosition().x < mPipePosition.x) mChar->mPhysics.accelerate({100, 0});
    else {
        mChar->mPhysics.setPosition(mDestination);
        setPlaying(false);
    }
}

GoIntoPipe::~GoIntoPipe() {
    
}