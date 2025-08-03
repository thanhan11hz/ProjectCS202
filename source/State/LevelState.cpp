#include "State/LevelState.hpp"

LevelState::LevelState(StateStack& stack) : State(stack), mCurrentPage(1), mMaxPage(2) {
    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
            else ResumeMusicStream(mPlayingMusic);
        }
    );

    Button* homeButton = new Button();
    homeButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    homeButton->changShape({1372,24,41,41});
    mContainer.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            mCurrentPage = 1;
            requestStackClear();
            requestStackPush(StateIdentifier::MENU);
        }
    );
    
    Button* next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage = mCurrentPage % mMaxPage + 1;
            setupPage(mCurrentPage);
        }
    );

    Button* previous = new Button();
    previous->changShape({21, 397, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage = (mCurrentPage - 2 + mMaxPage) % mMaxPage + 1;
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
    header_lv1->changeShape({239,195,334,17});
    header_lv1->changeAlignment(Alignment::CENTER);
    header_lv1->changeSize(17);
    mContainer.pack(header_lv1);

    level1 = new Button();
    level1->changShape({301, 436, 211, 56});
    level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level1->changeText("Enter");
    mContainer.pack(level1);

    header_lv2 = new Label();
    header_lv2->changeShape({867,195,334,17});
    header_lv2->changeAlignment(Alignment::CENTER);
    header_lv2->changeSize(17);
    mContainer.pack(header_lv2);

    level2 = new Button();
    level2->changShape({929, 436, 211, 56});
    level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level2->changeText("Enter");
    mContainer.pack(level2);
    
    header_lv3 = new Label();
    header_lv3->changeShape({239,541,334,17});
    header_lv3->changeAlignment(Alignment::CENTER);
    header_lv3->changeSize(17);
    mContainer.pack(header_lv3);

    level3 = new Button();
    level3->changShape({301, 780, 211, 56});
    level3->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    level3->changeText("Enter");
    mContainer.pack(level3);

    header_lv4 = new Label();
    header_lv4->changeShape({867,541,120,17});
    header_lv4->changeAlignment(Alignment::CENTER);
    header_lv4->changeSize(17);
    mContainer.pack(header_lv4);

    level4 = new Button();
    level4->changShape({929, 780, 211, 56});
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
            header_lv1->changeText("LEVEL 1");
            level1->changeCallback([this]() {
                    mWorld.setMap(0);
                    requestStackPush(StateIdentifier::CHARSELECT);
                }
            );
            header_lv2->changeText("LEVEL 2");
            level2->changeCallback([this]() {
                    mWorld.setMap(1);
                    requestStackPush(StateIdentifier::CHARSELECT);
                }
            );  
            header_lv3->changeText("LEVEL 3");
            level3->changeCallback([this]() {
                    mWorld.setMap(5);
                    requestStackPush(StateIdentifier::CHARSELECT);
                }
            );
            header_lv4->changeText("LEVEL 4");
            level4->changeCallback([this]() {
                    mWorld.setMap(4);
                    requestStackPush(StateIdentifier::CHARSELECT);
                }
            );
            break;
        }
        case 2: {
            header_lv1->changeText("CUSTOM 1");
            level1->changeCallback([this]() {
                }
            );
            header_lv2->changeText("CUSTOM 2");
            level2->changeCallback([this]() {
                }
            );
            header_lv3->changeText("CUSTOM 3");
            level3->changeCallback([this]() {
                }
            );
            header_lv4->changeText("CUSTOM 4");
            level4->changeCallback([this]() {
                }
            );
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
            Texture2D preview2 = Resource::mTexture.get(TextureIdentifier::PREVIEW2);
            DrawTexture(preview2, 873, 229, WHITE);
            Texture2D preview3 = Resource::mTexture.get(TextureIdentifier::PREVIEW6);
            DrawTexture(preview3, 245, 575, WHITE);
            Texture2D preview4 = Resource::mTexture.get(TextureIdentifier::PREVIEW5);
            DrawTexture(preview4, 873, 575, WHITE);
            break;
        }
        case 2: {
            Texture2D preview1 = Resource::mTexture.get(TextureIdentifier::PREVIEW3);
            DrawTexture(preview1, 245, 229, WHITE);
            Texture2D preview2 = Resource::mTexture.get(TextureIdentifier::PREVIEW6);
            DrawTexture(preview2, 873, 229, WHITE);
            Texture2D preview3 = Resource::mTexture.get(TextureIdentifier::PREVIEW4);
            DrawTexture(preview3, 245, 575, WHITE);
            Texture2D preview4 = Resource::mTexture.get(TextureIdentifier::PREVIEW8);
            DrawTexture(preview4, 873, 575, WHITE);
            break;
        }
    }
    mContainer.draw();
}

bool LevelState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }
    mContainer.handle();
    return true;
}

bool LevelState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    //mMap.update(dt);
    return true;
}