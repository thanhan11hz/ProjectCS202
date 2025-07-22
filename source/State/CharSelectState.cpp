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

    // Label* character = new Label();
    // character->changeShape({515, 648, 85, 17});
    // character->changeSize(17);
    // character->changeText("MARIO");
    // character->changeColor(WHITE);
    // mContainer.pack(character);

    Button* muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23, 22, 41, 41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );

    Button* back = new Button();
    back->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    back->changeText("BACK");
    back->changShape({84, 793, 211, 56});
    mContainer.pack(back);
    back->changeCallback(
        [this]() {
            requestStackPop();
        }
    );

    Button* confirm = new Button();
    confirm->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    confirm->changeText("CONFIRM");
    confirm->changShape({1145, 793, 211, 56});
    mContainer.pack(confirm);
    confirm->changeCallback(
        [this]() {
            requestStackClear();
            //mWorld.setCharater(selectedCharacter);
            requestStackPush(StateIdentifier::GAME1);
        }
    );
}

void CharSelectState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::CHAR_SELECT_BACKGROUND);
    DrawTexture(background, 0, 0, WHITE);
    Texture2D mario = Resource::mTexture.get(TextureIdentifier::CHARACTER_MARIO);
    DrawTexture(mario, 474, 308, WHITE);
    Texture2D luigi = Resource::mTexture.get(TextureIdentifier::CHARACTER_LUIGI);
    DrawTexture(luigi, 796, 276, WHITE);
    Texture2D pointer = Resource::mTexture.get(TextureIdentifier::CHARACTER_POINTER);
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
    return false;
}

bool CharSelectState::handle() {
    mContainer.handle();
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (selectedCharacter == 0) selectedCharacter = (selectedCharacter + 1) % 2;
    } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (selectedCharacter == 1) selectedCharacter = (selectedCharacter - 1) % 2;
    }
    return false;
}