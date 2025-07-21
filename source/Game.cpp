#include "Game.hpp"

Game::Game() {

    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(targetWidth, targetHeight, "Project CS202 - Group 7 - Super Mario Game");

    Resource::mTexture.load(TextureIdentifier::MENU_BACKGROUND, "resource\\Texture\\Background\\mainmenubg.png");
    Resource::mTexture.load(TextureIdentifier::LEVEL_BACKGROUND, "resource\\Texture\\Background\\cloudsbg.png");
    Resource::mTexture.load(TextureIdentifier::PLAY_BUTTON, "resource\\Texture\\Button\\PlayButton.png");
    Resource::mTexture.load(TextureIdentifier::SETTING_BUTTON, "resource\\Texture\\Button\\SettingButton.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION_BUTTON, "resource\\Texture\\Button\\InstructionButton.png");
    Resource::mTexture.load(TextureIdentifier::EXIT_BUTTON, "resource\\Texture\\Button\\ExitButton.png");
    Resource::mTexture.load(TextureIdentifier::LEVEL1, "resource\\Texture\\Button\\Level1.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_BLOCKS, "resource\\Texture\\Spritesheet\\Blocks\\tiles-2.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_ENEMIES, "resource\\Texture\\Spritesheet\\Blocks\\enemies-fixed.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_ITEMS, "resource\\Texture\\Spritesheet\\Blocks\\items-objects.png");
    Resource::mTexture.load(TextureIdentifier::LOGO, "resource\\Texture\\StateAsset\\supermariologo.png");
    Resource::mTexture.load(TextureIdentifier::ACTIVE_BUTTON, "resource\\Texture\\Button\\ActiveButton.png");
    Resource::mTexture.load(TextureIdentifier::ACTIVE_BUTTON_MEDIUM, "resource\\Texture\\Button\\ActiveMedium.png");
    Resource::mTexture.load(TextureIdentifier::ACTIVE_BUTTON_SMALL, "resource\\Texture\\Button\\ActiveSmall.png");
    Resource::mTexture.load(TextureIdentifier::HOVERED_BUTTON, "resource\\Texture\\Button\\HoveredButton.png");
    Resource::mTexture.load(TextureIdentifier::HOVERED_BUTTON_MEDIUM, "resource\\Texture\\Button\\HoveredMedium.png");
    Resource::mTexture.load(TextureIdentifier::HOVERED_BUTTON_SMALL, "resource\\Texture\\Button\\HoveredSmall.png");
    Resource::mTexture.load(TextureIdentifier::INACTIVE_BUTTON, "resource\\Texture\\Button\\InactiveButton.png");
    Resource::mTexture.load(TextureIdentifier::INACTIVE_BUTTON_MEDIUM, "resource\\Texture\\Button\\InactiveMedium.png");
    Resource::mTexture.load(TextureIdentifier::INACTIVE_BUTTON_SMALL, "resource\\Texture\\Button\\InactiveSmall.png");
    Resource::mTexture.load(TextureIdentifier::SOUND_ON, "resource\\Texture\\Button\\sound_on.png");
    Resource::mTexture.load(TextureIdentifier::SOUND_OFF, "resource\\Texture\\Button\\sound_off.png");
    Resource::mTexture.load(TextureIdentifier::HOME_BUTTON, "resource\\Texture\\Button\\home.png");
    Resource::mTexture.load(TextureIdentifier::NEXT, "resource\\Texture\\Button\\next.png");
    Resource::mTexture.load(TextureIdentifier::PREVIOUS, "resource\\Texture\\Button\\prev.png");
    Resource::mTexture.load(TextureIdentifier::NEXT_WHITE, "resource\\Texture\\Button\\nextWhite.png");
    Resource::mTexture.load(TextureIdentifier::PREVIOUS_WHITE, "resource\\Texture\\Button\\prevwhite.png");
    Resource::mTexture.load(TextureIdentifier::CHAR_SELECT_BACKGROUND, "resource\\Texture\\Background\\charselectbg.png");
    Resource::mTexture.load(TextureIdentifier::CHARACTER_MARIO, "resource\\Texture\\StateAsset\\marioart.png");
    Resource::mTexture.load(TextureIdentifier::CHARACTER_LUIGI, "resource\\Texture\\StateAsset\\luigiart.png");
    Resource::mTexture.load(TextureIdentifier::CHARACTER_POINTER, "resource\\Texture\\StateAsset\\uppointer.png");
    Resource::mTexture.load(TextureIdentifier::BRICKS_TEXTURE, "resource\\Texture\\StateAsset\\brickstexture.png");
    Resource::mTexture.load(TextureIdentifier::CONFIRM_BOX, "resource\\Texture\\StateAsset\\confirmbox.png");
    Resource::mTexture.load(TextureIdentifier::PREVIEW, "resource\\Texture\\StateAsset\\thumbnail.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION1, "resource\\Texture\\StateAsset\\Instructions\\ins1.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION2, "resource\\Texture\\StateAsset\\Instructions\\ins2.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION3, "resource\\Texture\\StateAsset\\Instructions\\ins3.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION4, "resource\\Texture\\StateAsset\\Instructions\\ins4.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION5, "resource\\Texture\\StateAsset\\Instructions\\ins5.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION6, "resource\\Texture\\StateAsset\\Instructions\\ins6.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION7, "resource\\Texture\\StateAsset\\Instructions\\ins7.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION8, "resource\\Texture\\StateAsset\\Instructions\\ins8.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION9, "resource\\Texture\\StateAsset\\Instructions\\ins9.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION10, "resource\\Texture\\StateAsset\\Instructions\\ins10.png");
    Resource::mTexture.load(TextureIdentifier::KEYBOARD, "resource\\Texture\\StateAsset\\keybinds.png");

    Resource::mFont.load(FontIdentifier::PressStart2P, "resource\\Fonts\\PressStart2P-Regular.ttf");
    Resource::mFont.load(FontIdentifier::PixelifySans, "resource\\Fonts\\PixelifySans-Regular.ttf");

    mStateStack.registerState<MenuState>(StateIdentifier::MENU);
    mStateStack.registerState<LevelState>(StateIdentifier::LEVEL);
    mStateStack.registerState<SettingState>(StateIdentifier::SETTINGS);
    mStateStack.registerState<InstructionState>(StateIdentifier::INSTRUCTIONS);
    mStateStack.registerState<PauseState>(StateIdentifier::PAUSE);
    mStateStack.registerState<CharSelectState>(StateIdentifier::CHARSELECT);
    mStateStack.registerState<GameState>(StateIdentifier::GAME1);
    
    mStateStack.pushState(StateIdentifier::MENU);

    
}

void Game::run() {

    float timeSinceLastUpdated = 0;
    RenderTexture2D target = LoadRenderTexture(targetWidth, targetHeight);
    float windowWidth = (float)GetScreenWidth();
    float windowHeight = (float)GetScreenHeight();
    float scale = fminf(windowWidth / targetWidth, windowHeight / targetHeight);
    float offsetX = (windowWidth - targetWidth * scale) / 2.0f;
    float offsetY = (windowHeight - targetHeight * scale) / 2.0f;
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(Resource::mFont.get(FontIdentifier::PressStart2P).texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(Resource::mFont.get(FontIdentifier::PixelifySans).texture, TEXTURE_FILTER_BILINEAR);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        timeSinceLastUpdated += GetFrameTime();
        while (timeSinceLastUpdated > timePerFrame) {
            timeSinceLastUpdated -= timePerFrame;
            inputProcess();
            update(timePerFrame);
        }
        
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        draw();
        EndTextureMode();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(target.texture, {0, 0, (float)targetWidth, -(float)targetHeight}, {offsetX, offsetY, targetWidth * scale, targetHeight * scale}, {0, 0}, 0.0f, WHITE);
        EndDrawing();

    }

    UnloadRenderTexture(target);
    CloseWindow();
}

void Game::inputProcess() {
    mStateStack.handle();
}

void Game::update(float dt) {
    mStateStack.update(dt);
}

void Game::draw() {
    mStateStack.draw();
}