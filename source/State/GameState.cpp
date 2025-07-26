#include "State/GameState.hpp"

GameState::GameState(StateStack& stack) : State(stack) {
    Button* muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );
    
    Button* pauseButton = new Button();
    pauseButton->changShape({1174,799,211,56});
    pauseButton->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pauseButton->changeText("PAUSE");
    mContainer.pack(pauseButton);
    pauseButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::PAUSE);
        }
    );

    Label* lvl = new Label();
    lvl->changeShape({23,794,187, 17});
    lvl->changeSize(17);
    lvl->changeText("LEVEL " + std::to_string(mWorld.getCurrentMap() / 3 + 1) + " - " + std::to_string(mWorld.getCurrentMap() % 3 + 1));
    lvl->changeColor(WHITE);
    mContainer.pack(lvl);

    Label* time = new Label();
    time->changeShape({23,846,170, 17});
    time->changeSize(17);
    time->changeText("TIME: 00:00");
    time->changeColor(WHITE);
    time->changeCallback([this](Label* label) {
        int time = (int)mWorld.getRestTime();
        int minute = time / 60;
        int second = time % 60;
        std::string text = "TIME: ";
        if (minute < 10) text += "0";
        text += std::to_string(minute) + ":";
        if (second < 10) text += "0";
        text += std::to_string(second);
        label->changeText(text);
    });
    mContainer.pack(time);

    Label* hp = new Label();
    hp->changeShape({229,794,187, 17});
    hp->changeSize(17);
    hp->changeText("LIVES:  x3");
    hp->changeColor(WHITE);
    hp->changeCallback([this](Label* label) {
        size_t live = mWorld.getRestLive();
        label->changeText("LIVES: x" + std::to_string(live));
    });
    mContainer.pack(hp);

    Label* coins = new Label();
    coins->changeShape({229,846,275, 17});
    coins->changeSize(17);
    coins->changeText("COINS 00000000");
    coins->changeColor(WHITE);
    coins->changeCallback([this](Label* label) {
        size_t coin = mWorld.getCoinCollected();
        std::string text = std::to_string(coin);
        while (text.size() < 8) text = "0" + text;
        text = "COINS " + text; 
        label->changeText(text);
    });
    mContainer.pack(coins);

    Label* items = new Label();
    items->changeShape({565,794,830, 17});
    items->changeSize(17);
    items->changeText("ACTIVE POWER-UPS:");
    items->changeColor(WHITE);
    mContainer.pack(items);
    mWorld.reset();
}

void GameState::draw() {
    mWorld.draw();
    // Texture2D tiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    // Texture2D object = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    // mMap.setTexture(tiles, object);
    // mMap.drawBackground();
    // mMap.drawItem();
    // mMap.drawMain();

    Texture2D bricksTexture = Resource::mTexture.get(TextureIdentifier::BRICKS_TEXTURE);
    DrawTexture(bricksTexture, -10, 772, WHITE);
    mContainer.draw();
}

bool GameState::update(float dt) {
    mWorld.update(dt);
    //mMap.update(dt);
    return true;
}

bool GameState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::PAUSE])) {
        requestStackPush(StateIdentifier::PAUSE);
    }
    mWorld.handle();
    mContainer.handle();
    return true;
}