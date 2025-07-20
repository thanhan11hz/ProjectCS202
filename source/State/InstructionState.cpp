#include "State/InstructionState.hpp"

InstructionState::InstructionState(StateStack& stack, Context ctx): State(stack, ctx), mCurrentPage(1), mMaxPage(10) {
    Label* title = new Label(ctx);
    title->changeShape({480, 103, 480, 40});
    title->changeSize(40);
    title->changeText("INSTRUCTIONS");
    title->changeColor(WHITE);
    mContainer.pack(title);

    tracker = new Label(ctx);
    tracker->changeShape({669, 860, 102, 17});
    tracker->changeSize(17);
    tracker->changeText("(" + std::to_string(mCurrentPage) + "/" + std::to_string(mMaxPage) + ")");
    tracker->changeColor(WHITE);
    mContainer.pack(tracker);   

    description = new Label(ctx);
    description->changeShape({191, 690, 1060, 100});
    description->changeSize(30);
    description->changeColor(WHITE);
    //description->changeFont(FontIdentifier::FONT_ARIAL);
    mContainer.pack(description);

    Button* muteButton = new Button(ctx);
    muteButton->changeToggle(true);
    muteButton->changeTexture(TextureIdentifier::MUTE_BUTTON);
    muteButton->changShape({23,22,41,41});
    mContainer.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );

    Button* homeButton = new Button(ctx);
    homeButton->changeToggle(true);
    muteButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    muteButton->changShape({1372,24,41,41});
    mContainer.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            mCurrentPage = 1;
            requestStackPop();
            requestStackPush(StateIdentifier::MENU);
        }
    );

    next = new Button(ctx);
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT_WHITE);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            mCurrentPage++;
            setupPage(mCurrentPage);
        }
    );

    previous = new Button(ctx);
    previous->changShape({1314, 612, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS_WHITE);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            mCurrentPage--;
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
            previous->changeToggle(false);
            next->changeToggle(true);
            description->changeText (
                "The game opens on a tranquil kingdom — until Bowser swoops in and\n 
                shatters the peace."
            );
            
            break;
        }
        case 2: {
            previous->changeToggle(true);
            next->changeToggle(true);
            description->changeText (
                "Bowser kidnaps Peach and unleashes his minions, plunging the kingdom\n
                into chaos."
            );
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION2);
            DrawTexture(illustration, 241, 202);
            break;
        }
        case 3: {
            description->changeText (
                "Mario springs into action, vowing to cross every world and bring Peach\n
                home."
            );
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION3);
            DrawTexture(illustration, 329, 202);
            break;
        }
        case 4: {
            description->changeText (
                "From sunny meadows to fiery volcanoes, each land introduces new\n
                enemies, secrets, and platforming twists."
            );
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION4);

            break;
        }
        case 5: {
            description->changeText (
                "Grab the Fire Flower to scorch foes with blazing fireballs and light dark\n
                paths ahead!"
            );
            break;
        }
        case 6: {
            description->changeText (
                "Grab the Super Mushroom to boost Mario’s size and strength — one hit\n
                no longer spells defeat!"
            );
            break;
        }
        case 7: {
            description->changeText (
                "Grab the 1-Up Mushroom to earn an extra life — cheat defeat and get\n
                another chance to press on!"
            );
            break;
        }
        case 8: {
            description->changeText (
                "Snag the Starman for brief invincibility and sprint through hazards\n
                unharmed!"
            );
            break;
        }
        case 9: {
            next->changeToggle(true);
            previous->changeToggle(true);
           description->changeText (
                "Outsmart Bowser’s generals — time your jumps, attacks, and power-\n
                ups to claim each key."
            );
            break; 
        }
        case 10: {
            next->changeToggle(false);
            previous->changeToggle(true);
            description->changeText (
                "With Bowser defeated, Peach is safe, the kingdom rejoices, and a new adventure \n
                glimmers on the horizon."
            );
            next->changeToggle(false);
            break;
        }
    }
}

void InstructionState::draw() {
    DrawRectangle(0, 0, 1440, 900, {113,67,25,255});
    switch (mCurrentPage) {
        case 1: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION1);
            DrawTexture(illustration, 241, 202);
            break;
        }
        case 2: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION2);
            DrawTexture(illustration, 241, 202);
            break;
        }
        case 3: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION3);
            DrawTexture(illustration, 329, 202);
            break;
        }
        case 4: {
            
            break;
        }
        case 5: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION5);
            DrawTexture(illustration, 306, 236);
            break;
        }
        case 6: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION6);
            DrawTexture(illustration, 362, 237);
            break;
        }
        case 7: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION10);
            DrawTexture(illustration, 412, 388);
            break;
        }
        case 8: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION7);
            DrawTexture(illustration, 370, 237);
            break;
        }
        case 9: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION8);
            DrawTexture(illustration, 270, 225);
            break;
        }
        case 10: {
            Texture2D illustration = mContext.textures.get(TextureIdentifier::INSTRUCTION9);
            DrawTexture(illustration, 242, 225);
            break;
        }
    }
    mContainer.draw();
}

bool InstructionState::handle() {
    mContainer.handle();
    return true;
}

bool InstructionState::update(float dt) {
    return true;
}