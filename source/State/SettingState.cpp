#include "State/SettingState.hpp"

SettingState::SettingState(StateStack& stack): State(stack), mCurrentPage(1), mMaxPage(3), changeMade(false) {
    
    Label* title = new Label();
    title->changeShape({560, 92, 320, 40});
    title->changeSize(40);
    title->changeText("SETTINGS");
    title->changeColor(WHITE);
    mContainer.pack(title);

    Button* muteButton = new Button();
    muteButton->changeToggle(true);
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );

    next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT_WHITE);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage++;
            //setupPage(mCurrentPage);
        }
    );

    previous = new Button();
    previous->changShape({1314, 612, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS_WHITE);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage--;
            //setupPage(mCurrentPage);
        }
    );

    Button* cancel = new Button();
    cancel->changeToggle(true);
    cancel->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    cancel->changeText("CANCEL");
    cancel->changShape({442,765,245,65});
    mContainer.pack(cancel);
    cancel->changeCallback(
        [this]() {
            requestStackPop();
        }
    );

    Button* save = new Button();
    save->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    save->changeText("SAVE");
    save->changShape({753,765,245,65});
    mContainer.pack(save);
    cancel->changeCallback(
        [this]() {
            changeMade = false;
            //saveSettings();
            requestStackPop();
        }
    );

    //Sound config
    previous->changeToggle(false);
    next->changeToggle(true);
    Label* masterVol = new Label();
    masterVol->changeShape({166, 261, 350, 25});
    masterVol->changeSize(25);
    masterVol->changeText("Master Volume");
    masterVol->changeColor(WHITE);
    mContainer_sound.pack(masterVol);

    Label* sfxVol = new Label();
    sfxVol->changeShape({166, 349, 350, 25});
    sfxVol->changeSize(25);
    sfxVol->changeText("SFX Volume");
    sfxVol->changeColor(WHITE);
    mContainer_sound.pack(sfxVol);

    Label* musicVol = new Label();
    musicVol->changeShape({166, 437, 350, 25});
    musicVol->changeSize(25);
    musicVol->changeText("Music Volume: ");
    musicVol->changeColor(WHITE);
    mContainer_sound.pack(musicVol);

    Label* bgm = new Label();
    bgm->changeShape({166, 569, 1150, 25});
    bgm->changeSize(25);
    bgm->changeText("Current BGM: ♪");
    bgm->changeColor(WHITE);
    mContainer_sound.pack(bgm);

    Button* toggle = new Button();
    toggle->changeText("TOGGLE");
    toggle->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    toggle->changShape({166, 623, 170, 45});
    mContainer_sound.pack(toggle);
    toggle->changeCallback(
        [this]() {
            //toggleBGM();
        }
    );

    //General config
    Label* subtitleGen = new Label();
    subtitleGen->changeShape({560, 155, 320, 20});
    subtitleGen->changeSize(20);
    subtitleGen->changeText("General Keybinds");
    subtitleGen->changeColor(WHITE);
    mContainer_general.pack(subtitleGen);

    previous->changeToggle(true);
    Label* fire = new Label();
    fire->changeShape({170, 263, 350, 25});
    fire->changeSize(25);
    fire->changeText("Use ability: ");
    fire->changeColor(WHITE);
    mContainer_general.pack(fire);

    Label* pause = new Label();
    pause->changeShape({170, 379, 350, 25});
    pause->changeSize(25);
    pause->changeText("Pause game: ");
    pause->changeColor(WHITE);
    mContainer_general.pack(pause);
    
    Label* mute = new Label();
    mute->changeShape({170, 495, 350, 25});
    mute->changeSize(25);
    mute->changeText("Toggle mute: ");
    mute->changeColor(WHITE);
    mContainer_general.pack(mute);

    Button* fireKey = new Button();
    fireKey->changeText("LSHIFT");
    fireKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    fireKey->changShape({498, 253, 170, 45});
    mContainer_general.pack(fireKey);
    fireKey->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::FIRE);
        }
    );

    Button* pauseKey = new Button();
    pauseKey->changeText("P");
    pauseKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    pauseKey->changShape({498, 369, 170, 45});
    mContainer_general.pack(pauseKey);
    pauseKey->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::PAUSE);
        }
    );
    Button* muteKey = new Button();
    muteKey->changeText("M");
    muteKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    muteKey->changShape({498, 485, 170, 45});
    mContainer_general.pack(muteKey);
    muteKey->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::MUTE);
        }
    );

    //Movement config
    Label* subtitleMove = new Label();
    subtitleMove->changeShape({610, 151, 220, 20});
    subtitleMove->changeSize(20);
    subtitleMove->changeText("P1 Keybinds");
    subtitleMove->changeColor(WHITE);
    mContainer_movement.pack(subtitleMove);


    Label* upLabel = new Label();
    upLabel->changeShape({424, 229, 100, 25});
    upLabel->changeSize(25);
    upLabel->changeText("Jump");
    upLabel->changeColor(WHITE);
    mContainer_movement.pack(upLabel);

    Button* up = new Button();
    up->changeText("W");
    up->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    up->changShape({391, 265, 170, 45});
    mContainer_movement.pack(up);
    up->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::UP);
        }
    );

    Label* downLabel = new Label();
    downLabel->changeShape({584, 624, 100, 25});
    downLabel->changeSize(25);
    downLabel->changeText("Move Down");
    downLabel->changeColor(WHITE);
    mContainer_movement.pack(downLabel);

    Button* down = new Button();
    down->changeText("S");
    down->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    down->changShape({612, 569, 170, 45});
    mContainer_movement.pack(down);
    down->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::DOWN);
        }
    );

    Label* leftLabel = new Label();
    leftLabel->changeShape({199, 535, 100, 25});
    leftLabel->changeSize(25);
    leftLabel->changeText("Move Left");
    leftLabel->changeColor(WHITE);
    mContainer_movement.pack(leftLabel);

    Button* left = new Button();
    left->changeText("A");
    left->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    left->changShape({225, 572, 170, 45});
    mContainer_movement.pack(left);
    left->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::LEFT);
        }
    );

    Label* rightLabel = new Label();
    rightLabel->changeShape({958, 540, 100, 25});
    rightLabel->changeSize(25);
    rightLabel->changeText("Move Right");
    rightLabel->changeColor(WHITE);
    mContainer_movement.pack(rightLabel);

    Button* right = new Button();
    right->changeText("D");
    right->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    right->changShape({1000, 579, 170, 45});
    mContainer_movement.pack(right);
    right->changeCallback(
        [this]() {
            //changeKeybind(KeybindIdentifier::RIGHT);
        }
    );
}

void SettingState::draw() {
    DrawRectangle(0, 0, 1440, 900, {113,67,25,255});
    mContainer.draw();
    if (mCurrentPage == 1) {
        mContainer_sound.draw();
    } else if (mCurrentPage == 2) {
        mContainer_general.draw();
    } else if (mCurrentPage == 3) {
        Texture2D keys = Resource::mTexture.get(TextureIdentifier::KEYBOARD);
        DrawTexture(keys, 394, 288, WHITE);
        mContainer_movement.draw();
    }
}

bool SettingState::handle() {
    mContainer.handle();
    
    if (mCurrentPage == 1) {
        mContainer_sound.handle();
    } else if (mCurrentPage == 2) {
        mContainer_general.handle();
    } else if (mCurrentPage == 3) {
        mContainer_movement.handle();
    }
    return true;
}

bool SettingState::update(float dt) {
    if (mCurrentPage == 1) {
        previous->changeToggle(false);
        next->changeToggle(true);
    } else if (mCurrentPage == 2) {
        previous->changeToggle(true);
        next->changeToggle(true);
    } else if (mCurrentPage == 3) {
        previous->changeToggle(true);
        next->changeToggle(false);
    }
    return true;
}