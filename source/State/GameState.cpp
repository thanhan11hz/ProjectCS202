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
    lvl->changeText("LEVEL 1 - 1");
    lvl->changeColor(WHITE);
    mContainer.pack(lvl);

    Label* time = new Label();
    time->changeShape({23,846,170, 17});
    time->changeSize(17);
    time->changeText("TIME: 00:00");
    time->changeColor(WHITE);
    mContainer.pack(time);

    Label* hp = new Label();
    hp->changeShape({229,794,187, 17});
    hp->changeSize(17);
    hp->changeText("LIVES:  x3");
    hp->changeColor(WHITE);
    mContainer.pack(hp);

    Label* coins = new Label();
    coins->changeShape({229,846,275, 17});
    coins->changeSize(17);
    coins->changeText("COINS 00000000");
    coins->changeColor(WHITE);
    mContainer.pack(coins);

    Label* items = new Label();
    items->changeShape({565,794,830, 17});
    items->changeSize(17);
    items->changeText("ACTIVE POWER-UPS:");
    items->changeColor(WHITE);
    mContainer.pack(items);
    //mMap.loadFromFile("resource\\Map\\01 - Field Area (1-1)");
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
    DrawTexture(bricksTexture, 0, 760, WHITE);
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