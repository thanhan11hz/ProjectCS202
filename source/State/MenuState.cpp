#include "State/MenuState.hpp"

MenuState::MenuState(StateStack& stack): State(stack) {
    Button* muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    
    Label* subtext = new Label();
    subtext->changeShape({66,267,300,15});
    subtext->changeSize(15);
    subtext->changeText("Developed by Group 6");
    subtext->changeColor(WHITE);
    mContainer.pack(subtext);

    Button* playButton = new Button();
    playButton->changShape({93,319,245,65});
    playButton->changeText("New Game");
    playButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    mContainer.pack(playButton);

    Button* loadButton = new Button();
    loadButton->changShape({93,429,245,65});
    loadButton->changeText("Load Game");
    loadButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    loadButton->changeToggle(false);
    mContainer.pack(loadButton);

    Button* instructionButton = new Button();
    instructionButton->changShape({93,539,245,65});
    instructionButton->changeText("Instructions");
    mContainer.pack(instructionButton);
    instructionButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::INSTRUCTIONS);
        }
    );

    Button* settingButton = new Button();
    settingButton->changShape({93,649,245,65});
    settingButton->changeText("Settings");
    mContainer.pack(settingButton);
    settingButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    );    

    Button* exitButton = new Button();
    exitButton->changShape({93,759,245,65});
    exitButton->changeText("Exit");
    mContainer.pack(exitButton);
    exitButton->changeCallback(
        [this]() {
            CloseWindow();
        }
    );   
}

void MenuState::draw() {
    
    Texture2D background = Resource::mTexture.get(TextureIdentifier::MENU_BACKGROUND);
    
    Texture2D gameLogo = Resource::mTexture.get(TextureIdentifier::LOGO);
    
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, BLACK);
    DrawTexture(gameLogo, 51, 75, WHITE);
    DrawRectangle(0, 0, 432, 900, {177, 146, 146, 185});
    mContainer.draw();
}

bool MenuState::update(float dt) {
    return true;
}

bool MenuState::handle() {
    mContainer.handle();
    return true;
}