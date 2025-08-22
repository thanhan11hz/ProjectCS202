#include "State/MenuState.hpp"

MenuState::MenuState(StateStack& stack): State(stack), gamemode(false) {
    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    muteButton->changeCallback(
        [this]() {
            if (!isMute) {
                PauseMusicStream(mPlayingMusic);
                isMute = true;
            }
            else {
                ResumeMusicStream(mPlayingMusic);
                isMute = false;
            }
        }
    );
    mContainer.pack(muteButton);
    
    Label* subtext = new Label();
    subtext->changeShape({66,267,300,15});
    subtext->changeSize(15);
    subtext->changeText("Developed by Group 6");
    subtext->changeFont(FontIdentifier::PressStart2P);
    subtext->changeColor(WHITE);
    mContainer.pack(subtext);

    Button* playButton = new Button();
    playButton->changShape({93,319,245,65});
    playButton->changeText("NEW GAME");
    playButton->changeCallback(
        [this]() {
            gamemode = true;
        }
    );
    mContainer.pack(playButton);

    loadButton = new Button();
    loadButton->changShape({93,409,245,65});
    loadButton->changeText("LOAD GAME");
    loadButton->changeCallback(
        [this]() {
            mWorld.restore();
            requestStackPop();
            requestStackPush(StateIdentifier::GAME1);
        }
    );
    mContainer.pack(loadButton);

    Button* mapButton = new Button();
    mapButton->changShape({93,499,245,65});
    mapButton->changeFontSize(15);
    mapButton->changeText("CREATE-A-LEVEL");
    mapButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::MAPEDITOR);
        }
    );
    mContainer.pack(mapButton);

    Button* instructionButton = new Button();
    instructionButton->changShape({93,589,245,65});
    instructionButton->changeText("INSTRUCTIONS");
    instructionButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::INSTRUCTIONS);
        }
    );
    mContainer.pack(instructionButton);

    Button* settingButton = new Button();
    settingButton->changShape({93,679,245,65});
    settingButton->changeText("SETTINGS");
    settingButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    ); 
    mContainer.pack(settingButton);

    Button* exitButton = new Button();
    exitButton->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    exitButton->changShape({93,769,245,65});
    exitButton->changeText("EXIT");
    
    exitButton->changeCallback(
        [this]() {
            CloseAudioDevice();
            TextureHolder::destroyInstance();
            FontHolder::destroyInstance();
            SoundHolder::destroyInstance();
            MusicHolder::destroyInstance();
            World::destroyInstance();
            CloseWindow();
        }
    );
    mContainer.pack(exitButton);

    Label* modeselect = new Label();
    modeselect->changeShape({477,342,486,30});
    modeselect->changeSize(30);
    modeselect->changeText("SELECT GAME MODE");
    modeselect->changeFont(FontIdentifier::PressStart2P);
    modeselect->changeColor(WHITE);
    mContainer_gamemode.pack(modeselect);

    Button* p1 = new Button();
    p1->changShape({615,415,211,56});
    p1->changeText("1P GAME");
    p1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    p1->changeCallback(
        [this]() {
            mWorld.setMultiPlayers(false);
            gamemode = false;
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    ); 
    mContainer_gamemode.pack(p1);

    Button* p2 = new Button();
    p2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    p2->changShape({615,503,211,56});
    p2->changeText("2P GAME");
    p2->changeCallback(
        [this]() {
            mWorld.setMultiPlayers(true);
            gamemode = false;
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    mContainer_gamemode.pack(p2);

}

void MenuState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::MENU_BACKGROUND);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    DrawRectangle(0, 0, 432, 912, {177, 146, 146, 190});
    Texture2D gameLogo = Resource::mTexture.get(TextureIdentifier::LOGO);
    DrawTexture(gameLogo, 51, 75, WHITE);
    mContainer.draw();
    if (gamemode) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade({83,83,83,255}, 0.6f));
        Texture2D box = Resource::mTexture.get(TextureIdentifier::CONFIRM_BOX);
        DrawTexture(box, 426, 257, WHITE);
        mContainer_gamemode.draw();
    }
}

bool MenuState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    if (mWorld.haveSnapshot()) {
        loadButton->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
        loadButton->changeCallback(
        [this]() {
            mWorld.restore();
            requestStackPop();
            requestStackPush(StateIdentifier::GAME1);
        });
    } else {
        loadButton->changeTexture(TextureIdentifier::INACTIVE_BUTTON);
        loadButton->changeCallback([this]() {});
    }
    return true;
}

bool MenuState::handle() {
    if (IsKeyPressed(mFunctionKey[Action::MUTE])) {
        if (!isMute) {
            PauseMusicStream(mPlayingMusic);
            isMute = true;
        }
        else {
            ResumeMusicStream(mPlayingMusic);
            isMute = false;
        }
    }
    if (!gamemode) mContainer.handle();
    else mContainer_gamemode.handle();
    return true;
}