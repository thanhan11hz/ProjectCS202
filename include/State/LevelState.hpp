#pragma once

#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"
#include "World/World.hpp"

class LevelState : public State {
    public:
        LevelState(StateStack& stack);
    private:
        int mCurrentPage;
        int mMaxPage;
        void setupPage(int page);
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        Container mContainer;

        Label* tracker;
        Label* header_lv1;
        Button* level1;
        Label* header_lv2;
        Button* level2;
        Label* header_lv3;
        Button* level3;
        Label* header_lv4;
        Button* level4;
        Button* muteButton;
};
