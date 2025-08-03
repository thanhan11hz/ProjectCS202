#include "State/GameOverState.hpp"

#include "State/GameState.hpp"

GameOverState::GameOverState(StateStack& stack) : State(stack) {
    Label* header = new Label();
    header->changeShape({359,325,722,50});
    header->changeAlignment(Alignment::CENTER);
    header->changeColor(WHITE);
    header->changeSize(50);
    if ((int)mWorld.getRestLive() <= 0) header->changeText("GAME OVER!");
    else header->changeText("TIME UP!");
    mContainer.pack(header);

    Button* retry = new Button();
    retry->changeText("RETRY");
    retry->changShape({615,433,211,56});
    mContainer.pack(retry);
    retry->changeCallback(
        [this]() {
            requestStackClear();
            requestStackPush(StateIdentifier::GAME1);
        }
    );

    Button* quit = new Button();
    quit->changeText("QUIT");
    quit->changShape({615,545,211,56});
    mContainer.pack(quit);
    quit->changeCallback(
        [this]() {
            requestStackClear();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    
    Label* lvl = new Label();
    lvl->changeShape({23,806,187, 17});
    lvl->changeSize(17);
    lvl->changeText("LEVEL " + std::to_string(mWorld.getCurrentMap() / 3 + 1) + " - " + std::to_string(mWorld.getCurrentMap() % 3 + 1));
    lvl->changeColor(WHITE);
    mContainer.pack(lvl);

    Label* time = new Label();
    time->changeShape({23,858,170, 17});
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
    hp->changeShape({229,806,187, 17});
    hp->changeSize(17);
    hp->changeText("LIVES:  x3");
    hp->changeColor(WHITE);
    hp->changeCallback([this](Label* label) {
        size_t live = mWorld.getRestLive();
        label->changeText("LIVES: x" + std::to_string(live));
    });
    mContainer.pack(hp);

    Label* coins = new Label();
    coins->changeShape({229,858,275, 17});
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
    items->changeShape({565,806,830, 17});
    items->changeSize(17);
    items->changeText("ACTIVE POWER-UPS:");
    items->changeColor(WHITE);
    mContainer.pack(items);
}

void GameOverState::draw() {
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),BLACK);
    Texture2D bricksTexture = Resource::mTexture.get(TextureIdentifier::BRICKS_TEXTURE);
    DrawTexture(bricksTexture, -10, 772, WHITE);
    mContainer.draw();
}

bool GameOverState::update(float dt) {
    return false;
}

bool GameOverState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }
    mWorld.handle();
    mContainer.handle();
    return true;
}