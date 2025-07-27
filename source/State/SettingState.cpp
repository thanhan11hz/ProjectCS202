#include "State/SettingState.hpp"

SettingState::SettingState(StateStack& stack): State(stack), mCurrentPage(1), mMaxPage(3), changeMade(false), mReassigned(nullptr), isReassigning(false) {
    mLocalKeybinds = mKeyBinding;

    Label* title = new Label();
    title->changeShape({560, 92, 320, 40});
    title->changeSize(40);
    title->changeText("SETTINGS");
    title->changeColor(WHITE);
    mContainer.pack(title);
   
    muteButton = new Button();
    muteButton->changeToggle(true);
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
            else ResumeMusicStream(mPlayingMusic);
        }
    );

    Button* next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT_WHITE);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage = mCurrentPage % mMaxPage + 1;
            //setupPage(mCurrentPage);
        }
    );

    Button* previous = new Button();
    previous->changShape({21, 397, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS_WHITE);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage = (mCurrentPage - 2 + mMaxPage) % mMaxPage + 1;
            //setupPage(mCurrentPage);
        }
    );

    Button* cancel = new Button();
    cancel->changeToggle(true);
    cancel->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    cancel->changeText("CANCEL");
    cancel->changShape({442,777,245,65});
    mContainer.pack(cancel);
    cancel->changeCallback(
        [this]() {
            requestStackPop();
        }
    );

    save = new Button();
    save->changeTexture(TextureIdentifier::INACTIVE_BUTTON);
    save->changeText("SAVE");
    save->changShape({753,777,245,65});
    mContainer.pack(save);
    save->changeCallback(
        [this]() {
            changeMade = false;
            mKeyBinding = mLocalKeybinds;
            requestStackPop();
        }
    );

    //Sound config
    Label* masterVol = new Label();
    masterVol->changeShape({166, 261, 350, 25});
    masterVol->changeSize(25);
    masterVol->changeText("Master Volume:");
    masterVol->changeColor(WHITE);
    mContainer_sound.pack(masterVol);

    Label* sfxVol = new Label();
    sfxVol->changeShape({166, 349, 350, 25});
    sfxVol->changeSize(25);
    sfxVol->changeText("SFX:");
    sfxVol->changeColor(WHITE);
    mContainer_sound.pack(sfxVol);

    Label* musicVol = new Label();
    musicVol->changeShape({166, 437, 350, 25});
    musicVol->changeSize(25);
    musicVol->changeText("Music Volume: ");
    musicVol->changeColor(WHITE);
    mContainer_sound.pack(musicVol);

    Label* bgm = new Label();
    bgm->changeShape({166, 569, 309, 25});
    bgm->changeSize(25);
    bgm->changeText("Current BGM: ");
    bgm->changeColor(WHITE);
    mContainer_sound.pack(bgm);

    Label* currentSong = new Label();
    currentSong->changeShape({647, 569, 565, 25});
    currentSong->changeSize(25);
    currentSong->changeText("BGM_1");
    currentSong->changeColor(WHITE);
    mContainer_sound.pack(currentSong);

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

    fireKey = new Button();
    fireKey->changeText(mapKeyToChar(mKeyBinding[Action::FIRE]));
    fireKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    fireKey->changeTextColor(WHITE);
    fireKey->changShape({498, 253, 170, 45});
    mContainer_general.pack(fireKey);
    fireKey->changeCallback(
        [this]() {
            mReassigned = fireKey;
            changeKeybind(Action::FIRE);
        }
    );

    pauseKey = new Button();
    pauseKey->changeText(mapKeyToChar(mKeyBinding[Action::PAUSE]));
    pauseKey->changeTextColor(WHITE);
    pauseKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    pauseKey->changShape({498, 369, 170, 45});
    mContainer_general.pack(pauseKey);
    pauseKey->changeCallback(
        [this]() {
            mReassigned = pauseKey;
            changeKeybind(Action::PAUSE);
        }
    );
    muteKey = new Button();
    muteKey->changeText(mapKeyToChar(mKeyBinding[Action::MUTE]));
    muteKey->changeTextColor(WHITE);
    muteKey->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    muteKey->changShape({498, 485, 170, 45});
    mContainer_general.pack(muteKey);
    muteKey->changeCallback(
        [this]() {
            mReassigned = muteKey;
            changeKeybind(Action::MUTE);
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

    up = new Button();
    up->changeText(mapKeyToChar(mKeyBinding[Action::JUMP]));
    up->changeTextColor(WHITE);
    up->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    up->changShape({391, 265, 170, 45});
    mContainer_movement.pack(up);
    up->changeCallback(
        [this]() {
            mReassigned = up;
            changeKeybind(Action::JUMP);
        }
    );

    Label* downLabel = new Label();
    downLabel->changeShape({584, 624, 100, 25});
    downLabel->changeSize(25);
    downLabel->changeText("Move Down");
    downLabel->changeColor(WHITE);
    mContainer_movement.pack(downLabel);

    down = new Button();
    down->changeText(mapKeyToChar(mKeyBinding[Action::DOWN]));
    down->changeTextColor(WHITE);
    down->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    down->changShape({612, 569, 170, 45});
    mContainer_movement.pack(down);
    down->changeCallback(
        [this]() {
            mReassigned = down;
            changeKeybind(Action::DOWN);
        }
    );

    Label* leftLabel = new Label();
    leftLabel->changeShape({199, 535, 100, 25});
    leftLabel->changeSize(25);
    leftLabel->changeText("Move Left");
    leftLabel->changeColor(WHITE);
    mContainer_movement.pack(leftLabel);

    left = new Button();
    left->changeText(mapKeyToChar(mKeyBinding[Action::LEFT]));
    left->changeTextColor(WHITE);
    left->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    left->changShape({225, 572, 170, 45});
    mContainer_movement.pack(left);
    left->changeCallback(
        [this]() {
            mReassigned = left;
            changeKeybind(Action::LEFT);
        }
    );

    Label* rightLabel = new Label();
    rightLabel->changeShape({958, 540, 100, 25});
    rightLabel->changeSize(25);
    rightLabel->changeText("Move Right");
    rightLabel->changeColor(WHITE);
    mContainer_movement.pack(rightLabel);

    right = new Button();
    right->changeText(mapKeyToChar(mKeyBinding[Action::RIGHT]));
    right->changeTextColor(WHITE);
    right->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
    right->changShape({1000, 579, 170, 45});
    mContainer_movement.pack(right);
    right->changeCallback(
        [this]() {
            mReassigned = right;
            changeKeybind(Action::RIGHT);
        }
    );

}

void SettingState::draw() {
    DrawRectangle(0, 0, 1440, 912, {113,67,25,255});
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

    if (isReassigning && mReassigned) {
        mReassigned->changeText("");
        mReassigned->changeTexture(TextureIdentifier::HOVERED_BUTTON_SMALL);
    } else if (mReassigned) {
        mReassigned->changeTexture(TextureIdentifier::ACTIVE_BUTTON_SMALL);
        mReassigned = nullptr;
    }
}

bool SettingState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::MUTE]) && !isReassigning) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }

    mContainer.handle();
    
    if (mCurrentPage == 1) {
        mContainer_sound.handle();
    } else if (mCurrentPage == 2) {
        mContainer_general.handle();
    } else if (mCurrentPage == 3) {
        mContainer_movement.handle();
    }

    if (isReassigning && mReassigned) {
        KeyboardKey key = (KeyboardKey)GetKeyPressed();
        if (key != 0) {
            mLocalKeybinds[mReassigningKey] = key;
            mReassigned->changeText(mapKeyToChar(key));
            changeMade = true;
            isReassigning = false;
        }
    }
    return false;
}

bool SettingState::update(float dt) {
    if (changeMade) save->changeTexture(TextureIdentifier::ACTIVE_BUTTON);
    else save->changeTexture(TextureIdentifier::INACTIVE_BUTTON);
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    return false;
}

void SettingState::changeKeybind(Action action) {
    isReassigning = true;
    mReassigningKey = action;
}

std::string SettingState::mapKeyToChar(KeyboardKey key) {
    switch(key) {
        case KEY_APOSTROPHE: return "'"; break;
        case KEY_COMMA: return ","; break;
        case KEY_MINUS: return "-"; break;
        case KEY_PERIOD: return "."; break;
        case KEY_SLASH: return "/"; break;
        case KEY_ZERO: return "0"; break;
        case KEY_ONE: return "1"; break;
        case KEY_TWO: return "2"; break;
        case KEY_THREE: return "3"; break;
        case KEY_FOUR: return "4"; break;
        case KEY_FIVE: return "5"; break;
        case KEY_SIX: return "6"; break;
        case KEY_SEVEN: return "7"; break;
        case KEY_EIGHT: return "8"; break;
        case KEY_NINE: return "9"; break;
        case KEY_SEMICOLON: return ";"; break;
        case KEY_EQUAL: return "="; break;
        case KEY_A: return "A"; break;
        case KEY_B: return "B"; break;
        case KEY_C: return "C"; break;
        case KEY_D: return "D"; break;
        case KEY_E: return "E"; break;
        case KEY_F: return "F"; break;
        case KEY_G: return "G"; break;
        case KEY_H: return "H"; break;
        case KEY_I: return "I"; break;
        case KEY_J: return "J"; break;
        case KEY_K: return "K"; break;
        case KEY_L: return "L"; break;
        case KEY_M: return "M"; break;
        case KEY_N: return "N"; break;
        case KEY_O: return "O"; break;
        case KEY_P: return "P"; break;
        case KEY_Q: return "Q"; break;
        case KEY_R: return "R"; break;
        case KEY_S: return "S"; break;
        case KEY_T: return "T"; break;
        case KEY_U: return "U"; break;
        case KEY_V: return "V"; break;
        case KEY_W: return "W"; break;
        case KEY_X: return "X"; break;
        case KEY_Y: return "Y"; break;
        case KEY_Z: return "Z"; break;
        case KEY_LEFT_BRACKET: return "["; break;
        case KEY_BACKSLASH: return "\\"; break;
        case KEY_RIGHT_BRACKET: return "]"; break;
        case KEY_GRAVE: return "`"; break;
        case KEY_SPACE: return "SPACE"; break;
        case KEY_KP_0: return "0"; break;
        case KEY_KP_1: return "1"; break;
        case KEY_KP_2: return "2"; break;
        case KEY_KP_3: return "3"; break;
        case KEY_KP_4: return "4"; break;
        case KEY_KP_5: return "5"; break;
        case KEY_KP_6: return "6"; break;
        case KEY_KP_7: return "7"; break;
        case KEY_KP_8: return "8"; break;
        case KEY_KP_9: return "9"; break;
        case KEY_KP_DECIMAL: return "."; break;
        case KEY_KP_DIVIDE: return "/"; break;
        case KEY_KP_MULTIPLY: return "*"; break;
        case KEY_KP_SUBTRACT: return "-"; break;
        case KEY_KP_ADD: return "+"; break;
        case KEY_KP_EQUAL: return "="; break;
        case KEY_F1: return "F1"; break;
        case KEY_F2: return "F2"; break;
        case KEY_F3: return "F3"; break;
        case KEY_F4: return "F4"; break;
        case KEY_F5: return "F5"; break;
        case KEY_F6: return "F6"; break;
        case KEY_F7: return "F7"; break;
        case KEY_F8: return "F8"; break;
        case KEY_F9: return "F9"; break;
        case KEY_F10: return "F10"; break;
        case KEY_F11: return "F11"; break;
        case KEY_F12: return "F12"; break;
        case KEY_ESCAPE: return "ESC"; break;
        case KEY_ENTER: return "ENTER"; break;
        case KEY_TAB: return "TAB"; break;
        case KEY_BACKSPACE: return "BACKSPACE"; break;
        case KEY_INSERT: return "INSERT"; break;
        case KEY_DELETE: return "DELETE"; break;
        case KEY_RIGHT: return "ARROW_RIGHT"; break;
        case KEY_LEFT: return "ARROW_LEFT"; break;
        case KEY_DOWN: return "ARROW_DOWN"; break;
        case KEY_UP: return "ARROW_UP"; break;
        case KEY_PAGE_UP: return "PAGEUP"; break;
        case KEY_PAGE_DOWN: return "PAGEDOWN"; break;
        case KEY_HOME: return "HOME"; break;
        case KEY_END: return "END"; break;
        case KEY_CAPS_LOCK: return "CAPSLOCK"; break;
        case KEY_NUM_LOCK: return "NUMLOCK"; break;
        case KEY_PRINT_SCREEN: return "PRTSCRN"; break;
        case KEY_LEFT_SHIFT: return "LSHIFT"; break;
        case KEY_LEFT_CONTROL: return "LCTRL"; break;
        case KEY_LEFT_ALT: return "LALT"; break;
        case KEY_RIGHT_SHIFT: return "RSHIFT"; break;
        case KEY_RIGHT_CONTROL: return "RCTRL"; break;
        case KEY_RIGHT_ALT: return "RALT"; break;

        default: return ""; break; // Non-character keys (e.g., ESC, F1, arrows) return empty string
    }
}