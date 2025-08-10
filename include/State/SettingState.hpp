#pragma once
#include "Global.hpp"
#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Slider.hpp"
#include "Resource/ResourceHolder.hpp"
#include "World/World.hpp"
#include "Global.hpp"
#include <map>
class SettingState : public State {
    public:
        SettingState(StateStack& stack);
    private:
        int mCurrentPage;
        int mMaxPage;
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        bool isKeybindDuplicate(KeyboardKey key, Action reassign);
        void changeKeybind(Action action);
        std::string mapKeyToChar(KeyboardKey key);

        std::map<Action, KeyboardKey> mLocalKeybinds;
        std::map<Action, KeyboardKey> mLocalFuncKeybinds;
        std::map<Action, KeyboardKey> mLocalKeybinds2;

        Button* mReassigned;
        Button* muteButton;
        Action mReassigningKey;
        bool isReassigning;

        Container mContainer;
        Container mContainer_sound;
        Container mContainer_general;
        Container mContainer_movement;
        Container mContainer_movement2;

        bool changeMade;
        bool duplicate;

        Button* save;
        Button* fireKey;
        Button* pauseKey;
        Button* muteKey;
        Button* up;
        Button* down;
        Button* right;
        Button* left;
        
        Button* fireKey2;
        Button* up2;
        Button* down2;
        Button* right2;
        Button* left2;
        
        Slider* master;
        Slider* mus;
        Slider* sfx;
        Label* duplicateWarning;
};
