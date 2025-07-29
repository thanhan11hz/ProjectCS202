#pragma once

#include <vector>
#include <memory>
#include <raylib.h>

#include "Entity/Character.hpp"

class CutScene {
    public:
        bool isPlaying();
        virtual void update(float dt) = 0;
        void setPlaying(bool flag);
        virtual ~CutScene() = default;
    private:
        bool mIsPlaying = false;
};

class CutSceneManager {
    public:
        void update(float dt);
        void addCutScene(std::unique_ptr<CutScene> cutScene);
    private:
        std::vector<std::unique_ptr<CutScene>> mCutScene;
};

// Cần điều khiển Mario và lá cờ
class EndingLevel : public CutScene {
    public:
        EndingLevel();
        virtual void update(float dt);
        ~EndingLevel();
    private:
        Character* mChar;
        Vector2 mDestination;
};
// Cần điều khiển Mario
class GoIntoPipe : public CutScene {
    public:
        GoIntoPipe();
        virtual void update(float dt);
        ~GoIntoPipe();
    private:
        Character* mChar;
        Vector2 mDestination;
        Vector2 mPipePosition;
};