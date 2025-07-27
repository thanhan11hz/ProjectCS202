#pragma once
#include "Global.hpp"
#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"
#include <map>
class SettingState : public State {
    public:
        SettingState(StateStack& stack);
    private:
        int mCurrentPage;
        int mMaxPage;
        //void setupPage(int page);
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        void changeKeybind(Action action);
        std::string mapKeyToChar(KeyboardKey key);

        std::map<Action, KeyboardKey> mLocalKeybinds;
        Button* mReassigned;
        Button* muteButton;
        Action mReassigningKey;
        bool isReassigning;

        Container mContainer;
        Container mContainer_sound;
        Container mContainer_general;
        Container mContainer_movement;

        bool changeMade;

        Button* save;
        Button* fireKey;
        Button* pauseKey;
        Button* muteKey;
        Button* up;
        Button* down;
        Button* right;
        Button* left;
};
