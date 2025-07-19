#include "Game.hpp"

Game::Game() {

    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(targetWidth, targetHeight, "Project CS202 - Group 7 - Super Mario Game");

    Resource::mTexture.load(TextureIdentifier::MENU_BACKGROUND, "resource\\Texture\\Background\\MenuBackground.jpg");
    Resource::mTexture.load(TextureIdentifier::LEVEL_BACKGROUND, "resource\\Texture\\Background\\LevelBackground.jpg");
    Resource::mTexture.load(TextureIdentifier::PLAY_BUTTON, "resource\\Texture\\Button\\PlayButton.png");
    Resource::mTexture.load(TextureIdentifier::SETTING_BUTTON, "resource\\Texture\\Button\\SettingButton.png");
    Resource::mTexture.load(TextureIdentifier::INSTRUCTION_BUTTON, "resource\\Texture\\Button\\InstructionButton.png");
    Resource::mTexture.load(TextureIdentifier::EXIT_BUTTON, "resource\\Texture\\Button\\ExitButton.png");
    Resource::mTexture.load(TextureIdentifier::LEVEL1, "resource\\Texture\\Button\\Level1.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_BLOCKS, "resource\\Texture\\Spritesheet\\Blocks\\tiles-2.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_ENEMIES, "resource\\Texture\\Spritesheet\\Blocks\\enemies-fixed.png");
    Resource::mTexture.load(TextureIdentifier::TILE_SET_ITEMS, "resource\\Texture\\Spritesheet\\Blocks\\items-objects.png");
    
    mStateStack.registerState<MenuState>(StateIdentifier::MENU);
    mStateStack.registerState<LevelState>(StateIdentifier::LEVEL);

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