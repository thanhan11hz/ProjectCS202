#include "State/MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context ctx): State(stack, ctx) {
    Button* muteButton = new Button(ctx);
    muteButton->changeTexture(TextureIdentifier::MUTE_BUTTON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    
    Label* subtext = new Label(ctx);
    title->changeShape({66,267,300,15});
    title->changeSize(15);
    title->changeText("Developed by Group 6");
    title->changeColor(WHITE);
    mContainer.pack(subtext);

    Button* playButton = new Button(ctx);
    playButton->changShape({93,319,245,65});
    playButton->changeText("New Game");
    playButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    mContainer.pack(playButton);

    Button* loadButton = new Button(ctx);
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

    Button* instructionButton = new Button(ctx);
    instructionButton->changShape({93,539,245,65});
    instructionButton->changeText("Instructions");
    mContainer.pack(instructionButton);
    instructionButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::INSTRUCTIONS);
        }
    );

    Button* settingButton = new Button(ctx);
    settingButton->changShape({93,649,245,65});
    settingButton->changeText("Settings");
    mContainer.pack(settingButton);
    settingButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    );    

    Button* exitButton = new Button(ctx);
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
    Texture2D background = mContext.textures.get(TextureIdentifier::MENU_BACKGROUND);
    Texture2D gameLogo = mContext.textures.get(TextureIdentifier::LOGO);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    DrawTexture(gameLogo, 51, 75);
    DrawRectangle(0, 0, 432, 900, {177, 146, 146, 185})
    mContainer.draw();
}

bool MenuState::update(float dt) {
    return true;
}

bool MenuState::handle() {
    mContainer.handle();
    return true;
}