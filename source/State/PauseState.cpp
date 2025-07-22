#include "State/PauseState.hpp"

PauseState::PauseState(StateStack& stack): State(stack), confirmMode(false) {
    Label* title = new Label();
    title->changeShape({570, 327, 300, 50});
    title->changeSize(50);
    title->changeText("PAUSED");
    title->changeColor(WHITE);
    mContainer.pack(title);
    
    Button* resume = new Button();
    resume->changeText("RESUME");
    resume->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    resume->changShape({484, 426, 211, 56});
    mContainer.pack(resume);
    resume->changeCallback(
        [this]() {
            requestStackPop();
        }
    );
    Button* restart = new Button();
    restart->changeText("RESTART");
    restart->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    restart->changShape({745, 426, 211, 56});
    mContainer.pack(restart);
    restart->changeCallback(
        [this]() {
            requestStackClear();
            requestStackPush(StateIdentifier::GAME1);
        }
    );
    Button* settings = new Button();
    settings->changeText("SETTINGS");
    settings->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    settings->changShape({484, 524, 211, 56});
    mContainer.pack(settings);
    settings->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::SETTINGS);
        }
    );
    Button* quit = new Button();
    quit->changeText("QUIT");
    quit->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    quit->changShape({745, 524, 211, 56});
    mContainer.pack(quit);
    quit->changeCallback(
        [this]() {
            confirmMode = true;
        }
    );

    Label* confirm = new Label();
    confirm->changeShape({496, 343, 458, 35});
    confirm->changeSize(35);
    confirm->changeText("ARE YOU SURE?");
    confirm->changeColor(WHITE);
    mConfirmContainer.pack(confirm);

    Button* ret = new Button();
    ret->changeText("RETURN");
    ret->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    ret->changShape({484, 426, 211, 56});
    mConfirmContainer.pack(ret);
    ret->changeCallback(
        [this]() {
            confirmMode = false;
        }
    );
    Button* yes = new Button();
    yes->changeText("YES");
    yes->changeTextColor(RED);
    yes->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    yes->changShape({745, 426, 211, 56});
    mConfirmContainer.pack(yes);
    yes->changeCallback(
        [this]() {
            confirmMode = false;
            requestStackClear();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
}

void PauseState::draw() {
    DrawRectangle(0, 0, 1440, 900, {83,83,83,100});
    Texture2D confirm = Resource::mTexture.get(TextureIdentifier::CONFIRM_BOX);
    DrawTexture(confirm, 426, 257, WHITE);
    
    if (confirmMode) {
        mConfirmContainer.draw();
    } else {
        mContainer.draw();
    }
}

bool PauseState::update(float dt) {
    return true;
}

bool PauseState::handle() {
    if (!confirmMode) mContainer.handle();
    else mConfirmContainer.handle();
    return true;
}