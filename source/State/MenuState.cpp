#include "State/MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context ctx): State(stack, ctx) {
    Button* playButton = new Button(ctx);
    playButton->changeTexture(TextureIdentifier::PLAY_BUTTON);
    playButton->changShape({520,450,400,100});
    playButton->changeCallback(
        [this]() {
            requestStackPop();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    mContainer.pack(playButton);
    
    Button* settingButton = new Button(ctx);
    settingButton->changeTexture(TextureIdentifier::SETTING_BUTTON);
    settingButton->changShape({520,550,400,100});
    mContainer.pack(settingButton);

    Button* instructionButton = new Button(ctx);
    instructionButton->changeTexture(TextureIdentifier::INSTRUCTION_BUTTON);
    instructionButton->changShape({520,650,400,100});
    mContainer.pack(instructionButton);

    Button* exitButton = new Button(ctx);
    exitButton->changeTexture(TextureIdentifier::EXIT_BUTTON);
    exitButton->changShape({520,750,400,100});
    mContainer.pack(exitButton);
}

void MenuState::draw() {
    Texture2D background = mContext.textures.get(TextureIdentifier::MENU_BACKGROUND);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    mContainer.draw();
}

bool MenuState::update(float dt) {
    return true;
}

bool MenuState::handle() {
    mContainer.handle();
    return true;
}