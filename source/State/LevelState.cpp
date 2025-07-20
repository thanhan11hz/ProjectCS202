#include "State/LevelState.hpp"

LevelState::LevelState(StateStack& stack) : State(stack), mCurrentPage(1), mMaxPage(2) {
    Button* muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );

    Button* homeButton = new Button();
    muteButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    muteButton->changShape({1372,24,41,41});
    mContainer.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            mCurrentPage = 1;
            requestStackClear();
            requestStackPush(StateIdentifier::MENU);
        }
    );
    
    next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage++;
            setupPage(mCurrentPage);
        }
    );

    previous = new Button();
    previous->changShape({1314, 612, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage--;
            setupPage(mCurrentPage);
        }
    );

    Label* header = new Label();
    header->changeShape({420,72,600,40});
    header->changeSize(40);
    header->changeText("LEVEL SELECTION");
    header->changeColor(WHITE);
    mContainer.pack(header);

    tracker = new Label();
    tracker->changeShape({678, 136, 85, 17});
    tracker->changeSize(17);
    tracker->changeColor(WHITE);
    mContainer.pack(tracker);

    header_lv1 = new Label();
    header_lv1->changeShape({353,195,120,17});
    header_lv1->changeSize(17);
    mContainer.pack(header_lv1);

    level1 = new Button();
    level1->changShape({306, 436, 211, 56});
    level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level1->changeText("Enter");
    mContainer.pack(level1);

    header_lv2 = new Label();
    header_lv2->changeShape({981,195,120,17});
    header_lv2->changeSize(17);
    mContainer.pack(header_lv2);

    level2 = new Button();
    level2->changShape({934, 436, 211, 56});
    level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level2->changeText("Enter");
    mContainer.pack(level2);
    
    header_lv3 = new Label();
    header_lv3->changeShape({353,541,120,17});
    header_lv3->changeSize(17);
    mContainer.pack(header_lv3);

    level3 = new Button();
    level3->changShape({306, 780, 211, 56});
    level3->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level3->changeText("Enter");
    mContainer.pack(level3);

    header_lv4 = new Label();
    header_lv4->changeShape({981,541,120,17});
    header_lv4->changeSize(17);
    mContainer.pack(header_lv4);

    level4 = new Button();
    level4->changShape({934, 780, 211, 56});
    level4->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level4->changeText("Enter");
    mContainer.pack(level4);

    setupPage(mCurrentPage);
};

void LevelState::setupPage(int page) {
    mCurrentPage = page;
    tracker->changeText("(" + std::to_string(mCurrentPage) + "/" + std::to_string(mMaxPage) + ")");
    switch (mCurrentPage)
    {
        case 1: 
        {
            previous->changeToggle(false);
            next->changeToggle(true);
            header_lv1->changeText("LEVEL 1");
            level1->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::CHARSELECT);
                }
            );
            header_lv2->changeText("LEVEL 2");
            level2->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME2);
                }
            );  
            header_lv3->changeText("LEVEL 3");
            level3->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME3);
                }
            );
            header_lv4->changeText("LEVEL 4");
            level4->changeCallback([this]() {
                //requestStackPush(StateIdentifier::GAME4);
                }
            );
            break;
        }
        case 2: {
            previous->changeToggle(true);
            next->changeToggle(false);
            header_lv1->changeText("CUSTOM 1");
            level1->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME5);
                }
            );
            header_lv2->changeText("CUSTOM 2");
            level2->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME6);
                }
            );
            header_lv3->changeText("CUSTOM 3");
            level3->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME7);
                }
            );
            header_lv4->changeText("CUSTOM 4");
            level4->changeCallback([this]() {
                    //requestStackPush(StateIdentifier::GAME8);
                }
            );
            // Texture2D preview1 = Resource::mTexture.get(TextureIdentifier::PREVIEW5);
            // DrawTexture(preview1, 245, 229);
            // Texture2D preview2 = Resource::mTexture.get(TextureIdentifier::PREVIEW6);
            // DrawTexture(preview2, 873, 229);
            // Texture2D preview3 = Resource::mTexture.get(TextureIdentifier::PREVIEW7);
            // DrawTexture(preview3, 245, 575);
            // Texture2D preview4 = Resource::mTexture.get(TextureIdentifier::PREVIEW8);
            // DrawTexture(preview4, 873, 575);
            break;
        }
    }
}

void LevelState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::LEVEL_BACKGROUND);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    switch (mCurrentPage) {
        case 1: {
            Texture2D preview1 = Resource::mTexture.get(TextureIdentifier::PREVIEW);
            DrawTexture(preview1, 245, 229, WHITE);
            Texture2D preview2 = Resource::mTexture.get(TextureIdentifier::PREVIEW);
            DrawTexture(preview2, 873, 229, WHITE);
            Texture2D preview3 = Resource::mTexture.get(TextureIdentifier::PREVIEW);
            DrawTexture(preview3, 245, 575, WHITE);
            Texture2D preview4 = Resource::mTexture.get(TextureIdentifier::PREVIEW);
            DrawTexture(preview4, 873, 575, WHITE);
            break;
        }
        case 2: {
            // Texture2D preview1 = Resource::mTexture.get(TextureIdentifier::PREVIEW5);
            // DrawTexture(preview1, 245, 229);
            // Texture2D preview2 = Resource::mTexture.get(TextureIdentifier::PREVIEW6);
            // DrawTexture(preview2, 873, 229);
            // Texture2D preview3 = Resource::mTexture.get(TextureIdentifier::PREVIEW7);
            // DrawTexture(preview3, 245, 575);
            // Texture2D preview4 = Resource::mTexture.get(TextureIdentifier::PREVIEW8);
            // DrawTexture(preview4, 873, 575);
            break;
        }
    }
    mContainer.draw();
}

bool LevelState::handle() {
    mContainer.handle();
    return true;
}

bool LevelState::update(float dt) {
    return true;
}