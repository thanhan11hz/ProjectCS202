#include "State/CompleteState.hpp"

CompleteState::CompleteState(StateStack& stack) : State(stack) {
    
    Label* header = new Label();
    header->changeShape({343,245,754,50});
    header->changeAlignment(Alignment::CENTER);
    header->changeColor(WHITE);
    header->changeSize(50);
    header->changeText("LEVEL COMPLETE!");
    mContainer_level.pack(header);

    Button* cont = new Button();
    cont->changeText("CONTINUE");
    cont->changShape({490,603,211,56});
    cont->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    mContainer_level.pack(cont);
    cont->changeCallback(
        [this]() {
            mWorld.setMap(mWorld.getCurrentMap() + 1);
            requestStackClear();
            requestStackPush(StateIdentifier::CHARSELECT);
        }
    );

    Button* ret = new Button();
    ret->changeText("RETURN");
    ret->changShape({739,603,211,56});
    mContainer_level.pack(ret);
    ret->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    ret->changeCallback(
        [this]() {
            requestStackClear();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );
    
    Label* lvl = new Label();
    lvl->changeShape({578,354,284, 20});
    lvl->changeSize(20);
    lvl->changeAlignment(Alignment::CENTER);
    lvl->changeText("LEVEL " + std::to_string(mWorld.getCurrentMap() / 3 + 1));
    lvl->changeColor(WHITE);
    mContainer_level.pack(lvl);

    Label* sep = new Label();
    sep->changeShape({578,385,284, 20});
    sep->changeSize(20);
    sep->changeAlignment(Alignment::CENTER);
    sep->changeText("--------------");
    sep->changeColor(WHITE);
    mContainer_level.pack(sep);

    Label* score = new Label();
    score->changeShape({578,425,284, 20});
    score->changeSize(20);
    score->changeText("SCORE 00000000");
    score->changeColor(WHITE);
    score->changeCallback([this](Label* label) {
        size_t sc = mWorld.getCurrentPoint();
        std::string text = std::to_string(sc);
        while (text.size() < 8) text = "0" + text;
        text = "SCORE " + text; 
        label->changeText(text);
    });
    mContainer_level.pack(score);

    Label* coins = new Label();
    coins->changeShape({578,474,284, 20});
    coins->changeSize(20);
    coins->changeText("COINS 00000000");
    coins->changeColor(WHITE);
    coins->changeCallback([this](Label* label) {
        size_t coin = mWorld.getCoinCollected();
        std::string text = std::to_string(coin);
        while (text.size() < 8) text = "0" + text;
        text = "COINS " + text; 
        label->changeText(text);
    });
    mContainer_level.pack(coins);

    Label* time = new Label();
    time->changeShape({598,521,200, 20});
    time->changeSize(20);
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
    mContainer_level.pack(time);

    Label* gameHeader = new Label();
    gameHeader->changeShape({343,245,754,50});
    gameHeader->changeAlignment(Alignment::CENTER);
    gameHeader->changeColor(WHITE);
    gameHeader->changeSize(50);
    gameHeader->changeText("GAME COMPLETE!");
    mContainer_game.pack(gameHeader);
    
    Label* game1 = new Label();
    game1->changeShape({505,354,431,25});
    game1->changeAlignment(Alignment::CENTER);
    game1->changeColor(WHITE);
    game1->changeSize(25);
    game1->changeText("THANK YOU MARIO!");
    mContainer_game.pack(game1);

    Label* game2 = new Label();
    game2->changeShape({182,413,1077,25});
    game2->changeAlignment(Alignment::CENTER);
    game2->changeColor(WHITE);
    game2->changeSize(25);
    game2->changeText("PRINCESS PEACH HAS BEEN RESCUED TO SAFETY.");
    mContainer_game.pack(game2);

    Label* game3 = new Label();
    game3->changeShape({379,482,683,25});
    game3->changeAlignment(Alignment::CENTER);
    game3->changeColor(WHITE);
    game3->changeSize(25);
    game3->changeText("YOUR QUEST IS OVER...");
    mContainer_game.pack(game3);

    Button* fin = new Button();
    fin->changeText("FINISH");
    fin->changShape({615,574,211,56});
    mContainer_game.pack(fin);
    fin->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    fin->changeCallback(
        [this]() {
            requestStackClear();
            requestStackPush(StateIdentifier::LEVEL);
        }
    );

    PauseMusicStream(mPlayingMusic);
    if (mWorld.getCurrentMap() == FINAL_LEVEL) {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::GAME_COMPLETE), sfxVolume);
        PlaySound(Resource::mSound.get(SoundIdentifier::GAME_COMPLETE));
        
    } else {
        SetSoundVolume(Resource::mSound.get(SoundIdentifier::LEVEL_COMPLETE), sfxVolume);
        PlaySound(Resource::mSound.get(SoundIdentifier::LEVEL_COMPLETE));
        
    }
}

void CompleteState::draw() {
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),BLACK);
    if (mWorld.getCurrentMap() != FINAL_LEVEL) mContainer_level.draw();
    else mContainer_game.draw();
}

bool CompleteState::update(float dt) {
    if (!IsSoundPlaying(Resource::mSound.get(SoundIdentifier::GAME_COMPLETE)) && !IsSoundPlaying(Resource::mSound.get(SoundIdentifier::LEVEL_COMPLETE))) {
        ResumeMusicStream(mPlayingMusic);
    } else {
        PauseMusicStream(mPlayingMusic);
    }
    return false;
}

bool CompleteState::handle() {
    if (IsKeyPressed(mFunctionKey[Action::MUTE])) {
        if (IsMusicStreamPlaying(mPlayingMusic)) {
            isMute = true;
            PauseMusicStream(mPlayingMusic);
            PauseSound(Resource::mSound.get(SoundIdentifier::GAME_COMPLETE));
            PauseSound(Resource::mSound.get(SoundIdentifier::LEVEL_COMPLETE));
        }
        else {
            isMute = false;
            ResumeMusicStream(mPlayingMusic);
            ResumeSound(Resource::mSound.get(SoundIdentifier::GAME_COMPLETE));
            ResumeSound(Resource::mSound.get(SoundIdentifier::LEVEL_COMPLETE));
        }
    }
    if (mWorld.getCurrentMap() != FINAL_LEVEL) mContainer_level.handle();
    else mContainer_game.handle();
    return true;
}