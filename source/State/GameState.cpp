#include "State/GameState.hpp"

GameState::GameState(StateStack& stack) : State(stack) {
    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
            else ResumeMusicStream(mPlayingMusic);
        }
    );
    
    Button* pauseButton = new Button();
    pauseButton->changShape({1174,811,211,56});
    pauseButton->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pauseButton->changeText("PAUSE");
    mContainer.pack(pauseButton);
    pauseButton->changeCallback(
        [this]() {
            requestStackPush(StateIdentifier::PAUSE);
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
    hp->changeShape({562,806,187, 17});
    hp->changeSize(17);
    hp->changeText("LIVES   x3");
    hp->changeColor(WHITE);
    hp->changeCallback([this](Label* label) {
        size_t live = mWorld.getRestLive();
        label->changeText("LIVES   x" + std::to_string(live));
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

    Label* score = new Label();
    score->changeShape({229,806,238, 17});
    score->changeSize(17);
    score->changeText("SCORE 00000000");
    score->changeColor(WHITE);
    // score->changeCallback([this](Label* label) {
    //     size_t sc = mWorld.getScore();
    //     std::string text = std::to_string(sc);
    //     while (text.size() < 8) text = "0" + text;
    //     text = "SCORE " + text; 
    //     label->changeText(text);
    // });
    mContainer.pack(score);
}

void GameState::draw() {
    mWorld.draw();
    Texture2D bricksTexture = Resource::mTexture.get(TextureIdentifier::BRICKS_TEXTURE);
    DrawTexture(bricksTexture, 0, 772, WHITE);
    mContainer.draw();
    Texture2D hrt = Resource::mTexture.get(TextureIdentifier::HEART);
    DrawTexture(hrt, 665, 802, WHITE);
}

bool GameState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    mWorld.update(dt);
    if (((int)mWorld.getRestLive() <= 0 || (int)mWorld.getRestTime() <= 0) && mWorld.isEndEffect()) {
        requestStackClear();
        requestStackPush(StateIdentifier::GAMEOVER);
    }
    if (mWorld.isLevelComplete()) {
        requestStackClear();
        requestStackPush(StateIdentifier::COMPLETE);
    }
    return true;
}

bool GameState::handle() {
    if (IsKeyPressed(mKeyBinding[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) PauseMusicStream(mPlayingMusic);
        else ResumeMusicStream(mPlayingMusic);
    }
    if (IsKeyPressed(mKeyBinding[Action::PAUSE])) {
        requestStackPush(StateIdentifier::PAUSE);
    }
    mWorld.handle();
    mContainer.handle();
    return true;
}