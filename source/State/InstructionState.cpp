#include "State/InstructionState.hpp"

InstructionState::InstructionState(StateStack& stack): State(stack), mCurrentPage(1), mMaxPage(10) {
    Label* title = new Label();
    title->changeShape({480, 103, 480, 40});
    title->changeSize(40);
    title->changeText("INSTRUCTIONS");
    title->changeColor(WHITE);
    mContainer.pack(title);

    tracker = new Label();
    tracker->changeShape({669, 860, 102, 17});
    tracker->changeSize(17);
    tracker->changeText("(" + std::to_string(mCurrentPage) + "/" + std::to_string(mMaxPage) + ")");
    tracker->changeColor(WHITE);
    mContainer.pack(tracker);   

    description = new Label();
    description->changeShape({191, 690, 1060, 100});
    description->changeSize(30);
    description->changeColor(WHITE);
    description->changeAlignment(Alignment::CENTER);
    description->changeFont(FontIdentifier::PixelifySans);
    mContainer.pack(description);

    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) if (!isMute) {
                PauseMusicStream(mPlayingMusic);
                isMute = true;
            }
            else {
                ResumeMusicStream(mPlayingMusic);
                isMute = false;
            }
            else ResumeMusicStream(mPlayingMusic);
        }
    );

    Button* homeButton = new Button();
    homeButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    homeButton->changShape({1372,24,41,41});
    mContainer.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            mCurrentPage = 1;
            requestStackPop();
            requestStackPush(StateIdentifier::MENU);
        }
    );

    Button* next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT_WHITE);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage = mCurrentPage % mMaxPage + 1;
            setupPage(mCurrentPage);
        }
    );

    Button* previous = new Button();
    previous->changShape({21, 397, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS_WHITE);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage = (mCurrentPage - 2 + mMaxPage) % mMaxPage + 1;
            setupPage(mCurrentPage);
        }
    );

    setupPage(mCurrentPage);
}

void InstructionState::setupPage(int page) {
    mCurrentPage = page;
    tracker->changeText("(" + std::to_string(mCurrentPage) + "/" + std::to_string(mMaxPage) + ")");
    switch (mCurrentPage)
    {
        case 1: 
        {
            description->changeText (
                "The game opens on a tranquil kingdom — until Bowser swoops in and\nshatters the peace."
            );
            
            break;
        }
        case 2: {
            description->changeText (
                "Bowser kidnaps Peach and unleashes his minions, plunging the kingdom\ninto chaos."
            );
            break;
        }
        case 3: {
            description->changeText (
                "Mario springs into action, vowing to cross every world and bring Peach\nhome."
            );
            break;
        }
        case 4: {
            description->changeText (
                "From sunny meadows to fiery volcanoes, each land introduces new\nenemies, secrets, and platforming twists."
            );

            break;
        }
        case 5: {
            description->changeText (
                "Grab the Fire Flower to scorch foes with blazing fireballs and light dark\npaths ahead!"
            );
            break;
        }
        case 6: {
            description->changeText (
                "Grab the Super Mushroom to boost Mario’s size and strength — one hit\nno longer spells defeat!"
            );
            break;
        }
        case 7: {
            description->changeText (
                "Grab the 1-Up Mushroom to earn an extra life — cheat defeat and get\nanother chance to press on!"
            );
            break;
        }
        case 8: {
            description->changeText (
                "Snag the Starman for brief invincibility and sprint through hazards\nunharmed!"
            );
            break;
        }
        case 9: {
           description->changeText (
                "Outsmart Bowser’s generals — time your jumps, attacks, and power-\nups to claim each key."
            );
            break; 
        }
        case 10: {
            description->changeText (
                "With Bowser defeated, Peach is safe, the kingdom rejoices, and a new adventure\nglimmers on the horizon."
            );
            break;
        }
    }
}

void InstructionState::draw() {
    DrawRectangle(0, 0, 1440, 912, {113,67,25,255});
    switch (mCurrentPage) {
        case 1: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION1);
            DrawTexture(illustration, 241, 202, WHITE);
            break;
        }
        case 2: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION2);
            DrawTexture(illustration, 241, 202, WHITE);
            break;
        }
        case 3: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION3);
            DrawTexture(illustration, 329, 202, WHITE);
            break;
        }
        case 4: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION4);
            DrawTexture(illustration, 399, 201, WHITE);
            break;
        }
        case 5: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION5);
            DrawTexture(illustration, 306, 236, WHITE);
            break;
        }
        case 6: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION6);
            DrawTexture(illustration, 362, 237, WHITE);
            break;
        }
        case 7: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION7);
            DrawTexture(illustration, 412, 388, WHITE);
            break;
        }
        case 8: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION8);
            DrawTexture(illustration, 370, 237, WHITE);
            break;
        }
        case 9: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION9);
            DrawTexture(illustration, 270, 225, WHITE);
            break;
        }
        case 10: {
            Texture2D illustration = Resource::mTexture.get(TextureIdentifier::INSTRUCTION10);
            DrawTexture(illustration, 242, 225, WHITE);
            break;
        }
    }
    mContainer.draw();
}

bool InstructionState::handle() {
    if (IsKeyPressed(mFunctionKey[Action::MUTE])) {
        if (!isMute) {
            PauseMusicStream(mPlayingMusic);
            isMute = true;
        }
        else {
            ResumeMusicStream(mPlayingMusic);
            isMute = false;
        }
    }
    mContainer.handle();
    return true;
}

bool InstructionState::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    return true;
}