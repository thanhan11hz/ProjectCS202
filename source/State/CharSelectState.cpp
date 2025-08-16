#include "State/CharSelectState.hpp"

CharSelectState::CharSelectState(StateStack& stack): State(stack), selectedCharacter(0) {
    Label* lvl = new Label();
    lvl->changeShape({580, 72, 280, 40});
    lvl->changeSize(40);
    lvl->changeText("LEVEL 1");
    lvl->changeColor(WHITE);
    mContainer.pack(lvl);

    Label* header = new Label();
    header->changeShape({405, 168, 630, 30});
    header->changeSize(30);
    header->changeText("SELECT YOUR CHARACTER");
    header->changeColor(WHITE);
    mContainer.pack(header);

    // Label* Character = new Label();
    // Character->changeShape({515, 648, 85, 17});
    // Character->changeSize(17);
    // Character->changeText("MARIO");
    // Character->changeColor(WHITE);
    // mContainer.pack(Character);

    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23, 22, 41, 41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
            else ResumeMusicStream(mPlayingMusic);
        }
    );

    Button* back = new Button();
    back->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    back->changeText("BACK");
    back->changShape({84, 805, 211, 56});
    mContainer.pack(back);
    back->changeCallback(
        [this]() {
            requestStackPop();
        }
    );

    Button* confirm = new Button();
    confirm->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    confirm->changeText("CONFIRM");
    confirm->changShape({1145, 805, 211, 56});
    mContainer.pack(confirm);
    confirm->changeCallback(
        [this]() {
            requestStackClear();
            mWorld.setCharater(selectedCharacter);
            mWorld.reset();
            requestStackPush(StateIdentifier::GAME1);
        }
    );
}

void CharSelectState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::CHAR_SELECT_BACKGROUND);
    DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    Texture2D mario = Resource::mTexture.get(TextureIdentifier::Character_MARIO);
    DrawTexture(mario, 474, 308, WHITE);
    Texture2D luigi = Resource::mTexture.get(TextureIdentifier::Character_LUIGI);
    DrawTexture(luigi, 796, 276, WHITE);
    Texture2D pointer = Resource::mTexture.get(TextureIdentifier::Character_POINTER);
    if (selectedCharacter == 0) {
        DrawTexture(pointer, 533, 599, WHITE);
        DrawTextEx(Resource::mFont.get(FontIdentifier::PressStart2P), "MARIO", {515, 648}, 17, 0, WHITE);
    } else {
        DrawTexture(pointer, 856, 599, WHITE);
        DrawTextEx(Resource::mFont.get(FontIdentifier::PressStart2P), "LUIGI", {839, 648}, 17, 0, WHITE);
    }

    mContainer.draw();
}

bool CharSelectState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    return false;
}

bool CharSelectState::handle() {
    mContainer.handle();
    if (IsKeyPressed(mFunctionKey[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (selectedCharacter == 0) selectedCharacter = (selectedCharacter + 1) % 2;
    } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (selectedCharacter == 1) selectedCharacter = (selectedCharacter - 1 + 2) % 2;
    }
    return false;
}