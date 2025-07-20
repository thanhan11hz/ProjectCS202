#include "State/PauseState.hpp"

PauseState::PauseState(StateStack& stack): State(stack) {
    Label* title = new Label();
    title->changeShape({570, 327, 300, 50});
    title->changeSize(50);
    title->changeText("PAUSED");
    title->changeColor(WHITE);
    mContainer.pack(title);
    
    Button* resume = new Button();
    resume->changeText("Resume");
    resume->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    resume->changShape({484, 426, 211, 56});
    mContainer.pack(resume);
    resume->changeCallback(
        [this]() {
            requestStackPop();
        }
    );
    Button* restart = new Button();
    restart->changeText("Enter");
    restart->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    restart->changShape({745, 426, 211, 56});
    mContainer.pack(restart);
    restart->changeCallback(
        [this]() {
            //restartGame();
        }
    );
    Button* settings = new Button();
    settings->changeText("Settings");
    settings->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    settings->changShape({484, 524, 211, 56});
    mContainer.pack(settings);
    settings->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    );
    Button* quit = new Button();
    quit->changeText("Quit");
    quit->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    quit->changShape({484, 524, 211, 56});
    mContainer.pack(quit);
    quit->changeCallback(
        [this]() {
            requestStackClear();
            //requestStackPush(StateIdentifier::CONFIRM_EXIT);
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
}

void PauseState::draw() {
    DrawRectangle(0, 0, 1440, 900, {83,83,83,200});
    Texture2D confirm = Resource::mTexture.get(TextureIdentifier::CONFIRM_BOX);
    DrawTexture(confirm, 51, 75, WHITE);
    mContainer.draw();
}

bool PauseState::update(float dt) {
    return true;
}

bool PauseState::handle() {
    mContainer.handle();
    return true;
}