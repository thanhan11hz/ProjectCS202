#include "State/MenuState.hpp"

MenuState::MenuState(StateStack& stack): State(stack) {
    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
            else ResumeMusicStream(mPlayingMusic);
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
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    mContainer.pack(playButton);

    Button* mapButton = new Button();
    mapButton->changShape({93,429,245,65});
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
    instructionButton->changShape({93,539,245,65});
    instructionButton->changeText("INSTRUCTIONS");
    instructionButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::INSTRUCTIONS);
        }
    );
    mContainer.pack(instructionButton);

    Button* settingButton = new Button();
    settingButton->changShape({93,649,245,65});
    settingButton->changeText("SETTINGS");
    settingButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    ); 
    mContainer.pack(settingButton);

    Button* exitButton = new Button();
    exitButton->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    exitButton->changShape({93,759,245,65});
    exitButton->changeText("EXIT");
    
    exitButton->changeCallback(
        [this]() {
            CloseWindow();
        }
    );
    mContainer.pack(exitButton);
}

void MenuState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::MENU_BACKGROUND);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    DrawRectangle(0, 0, 432, 912, {177, 146, 146, 190});
    Texture2D gameLogo = Resource::mTexture.get(TextureIdentifier::LOGO);
    DrawTexture(gameLogo, 51, 75, WHITE);
    mContainer.draw();
}

bool MenuState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    return true;
}

bool MenuState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }
    mContainer.handle();
    return true;
}