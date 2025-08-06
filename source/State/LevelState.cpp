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
    header_lv4->changeShape({867,541,334,17});
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
            level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
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
            setupCustom();
            if (createdCount >= 1) {
                level1->changeCallback([this]() {
                    mWorld.setMap(8);
                    requestStackPush(StateIdentifier::CHARSELECT);
                });
                if (createdCount >= 2) {
                    level2->changeCallback([this]() {
                        mWorld.setMap(9);
                        requestStackPush(StateIdentifier::CHARSELECT);
                    });
                    if (createdCount >=3) {
                        level3->changeCallback([this]() {
                            mWorld.setMap(10);
                            requestStackPush(StateIdentifier::CHARSELECT);
                    });
                        if (createdCount >= 4) {
                            level4->changeCallback([this]() {
                                mWorld.setMap(7+createdCount);
                                requestStackPush(StateIdentifier::CHARSELECT);
                            });
                        }
                    }
                }   
            }
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

void LevelState::setupCustom() {
    level1->changeCallback([this]() {
                }
            );
            level2->changeCallback([this]() {
                }
            );  
            level3->changeCallback([this]() {
                }
            );
            level4->changeCallback([this]() {
                }
            );
            header_lv1->changeText("CUSTOM MAP");
            header_lv1->changeText("CUSTOM MAP");
            header_lv1->changeText("CUSTOM MAP");
            header_lv1->changeText("CUSTOM MAP");
    switch (createdCount) {
        case 0:
            level1->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            break;
        case 1:
            level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            break;
        case 2: 
            level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            break;
        case 3: 
            level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            break;
        default:
            level1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level3->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            level4->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            break;
    }
    std::filesystem::path exePath = std::filesystem::current_path().parent_path();
    std::filesystem::path customDir = exePath / "resource" / "Map" / "Custom";
    for (const auto& entry : std::filesystem::directory_iterator(customDir)) {
        // Check if the entry is a directory
        if (entry.is_directory()) {
            std::string folder_name = entry.path().filename().string();

            // Check if folder name matches the "0x_name" pattern
            if (folder_name.length() >= 3 && // Minimum length for "0x_"
                folder_name[0] == '0' && // Starts with '0'
                std::isdigit(folder_name[1]) && // Second character is a digit
                folder_name[2] == '_') { // Third character is '_'
                
                // Extract the name part after "0x_"
                std::string name_part = folder_name.substr(3);
                if (folder_name[1] == '1') header_lv1->changeText(name_part);
                if (folder_name[1] == '2') header_lv2->changeText(name_part);
                if (folder_name[1] == '3') header_lv3->changeText(name_part);
                if (folder_name[1] >= '4') header_lv4->changeText(name_part); 
            }
        }
    }
}