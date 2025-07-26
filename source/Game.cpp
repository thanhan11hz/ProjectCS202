#include "Game.hpp"

Game::Game() {

    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(targetWidth, targetHeight, "Project CS202 - Group 7 - Super Mario Game");
    InitAudioDevice();

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
    Resource::mTexture.load(TextureIdentifier::Character_MARIO, "resource\\Texture\\StateAsset\\marioart.png");
    Resource::mTexture.load(TextureIdentifier::Character_LUIGI, "resource\\Texture\\StateAsset\\luigiart.png");
    Resource::mTexture.load(TextureIdentifier::Character_POINTER, "resource\\Texture\\StateAsset\\uppointer.png");
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

    Resource::mTexture.load(TextureIdentifier::PAL1, "resource\\Texture\\StateAsset\\Palettes\\ITEMS.png");
    Resource::mTexture.load(TextureIdentifier::PAL2, "resource\\Texture\\StateAsset\\Palettes\\FOLIAGE1.png");
    Resource::mTexture.load(TextureIdentifier::PAL3, "resource\\Texture\\StateAsset\\Palettes\\FOLIAGE2.png");
    Resource::mTexture.load(TextureIdentifier::PAL4, "resource\\Texture\\StateAsset\\Palettes\\COINS.png");
    Resource::mTexture.load(TextureIdentifier::PAL5, "resource\\Texture\\StateAsset\\Palettes\\BLOCKS.png");
  
    Resource::mTexture.load(TextureIdentifier::MARIO_N_IDLE, "resource\\Texture\\Spritesheet\\Mario_N_Idle.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_N_RUN, "resource\\Texture\\Spritesheet\\Mario_N_Run.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_N_JUMP, "resource\\Texture\\Spritesheet\\Mario_N_Jump.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_S_IDLE, "resource\\Texture\\Spritesheet\\Mario_S_Idle.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_S_RUN, "resource\\Texture\\Spritesheet\\Mario_S_Run.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_S_JUMP, "resource\\Texture\\Spritesheet\\Mario_S_Jump.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_S_CROUCH, "resource\\Texture\\Spritesheet\\Mario_S_Crouch.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_F_IDLE, "resource\\Texture\\Spritesheet\\Mario_F_Idle.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_F_RUN, "resource\\Texture\\Spritesheet\\Mario_F_Run.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_F_JUMP, "resource\\Texture\\Spritesheet\\Mario_F_Jump.png");
    Resource::mTexture.load(TextureIdentifier::MARIO_F_CROUCH, "resource\\Texture\\Spritesheet\\Mario_F_Crouch.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_N_IDLE, "resource\\Texture\\Spritesheet\\Luigi_N_Idle.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_N_RUN, "resource\\Texture\\Spritesheet\\Luigi_N_Run.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_N_JUMP, "resource\\Texture\\Spritesheet\\Luigi_N_Jump.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_S_IDLE, "resource\\Texture\\Spritesheet\\Luigi_S_Idle.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_S_RUN, "resource\\Texture\\Spritesheet\\Luigi_S_Run.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_S_JUMP, "resource\\Texture\\Spritesheet\\Luigi_S_Jump.png");
    Resource::mTexture.load(TextureIdentifier::LUIGI_S_CROUCH, "resource\\Texture\\Spritesheet\\Luigi_S_Crouch.png");
    Resource::mTexture.load(TextureIdentifier::GOOMBA_RUN, "resource\\Texture\\Spritesheet\\Goomba_Run.png");
    Resource::mTexture.load(TextureIdentifier::GOOMBA_DIE, "resource\\Texture\\Spritesheet\\Goomba_Die.png");
    Resource::mTexture.load(TextureIdentifier::GOOMBA2_RUN, "resource\\Texture\\Spritesheet\\Goomba2_Run.png");
    Resource::mTexture.load(TextureIdentifier::GOOMBA2_DIE, "resource\\Texture\\Spritesheet\\Goomba2_Die.png");
    Resource::mTexture.load(TextureIdentifier::PIRANHA_MOVE, "resource\\Texture\\Spritesheet\\Piranha_Move.png");
    Resource::mTexture.load(TextureIdentifier::PIRANHA_ATTACK, "resource\\Texture\\Spritesheet\\Piranha_Attack.png");
    Resource::mTexture.load(TextureIdentifier::PIRANHA2_MOVE, "resource\\Texture\\Spritesheet\\Piranha2_Move.png");
    Resource::mTexture.load(TextureIdentifier::PIRANHA2_ATTACK, "resource\\Texture\\Spritesheet\\Piranha_Attack.png");

    Resource::mFont.load(FontIdentifier::PressStart2P, "resource\\Fonts\\PressStart2P-Regular.ttf");
    Resource::mFont.load(FontIdentifier::PixelifySans, "resource\\Fonts\\PixelifySans-Regular.ttf");

    Resource::mMusic.load(MusicIdentifier::BACKGROUND_MUSIC, "resource\\Music\\backgroundMusic.ogg");
    SetMusicVolume(Resource::mMusic.get(MusicIdentifier::BACKGROUND_MUSIC), 1.0f);
    Resource::mMusic.get(MusicIdentifier::BACKGROUND_MUSIC).looping = true;

    mPlayingMusic = Resource::mMusic.get(MusicIdentifier::BACKGROUND_MUSIC);

    mStateStack.registerState<MenuState>(StateIdentifier::MENU);
    mStateStack.registerState<LevelState>(StateIdentifier::LEVEL);
    mStateStack.registerState<SettingState>(StateIdentifier::SETTINGS);
    mStateStack.registerState<InstructionState>(StateIdentifier::INSTRUCTIONS);
    mStateStack.registerState<PauseState>(StateIdentifier::PAUSE);
    mStateStack.registerState<CharSelectState>(StateIdentifier::CHARSELECT);
    mStateStack.registerState<GameState>(StateIdentifier::GAME1);
    mStateStack.registerState<MapEditor>(StateIdentifier::MAPEDITOR);

    mStateStack.pushState(StateIdentifier::MENU);

    mWorld.loadMap("resource\\Map\\01 - Field Area (1-1)");
    mWorld.loadMap("resource\\Map\\02 - Underground Area (1-2)");
    mWorld.loadMap("resource\\Map\\03 - Desert Area (2-3 & 4-1)");
    mWorld.loadMap("resource\\Map\\04 - Snowy Area (5-2)");
    mWorld.loadMap("resource\\Map\\05 - Castle (1-4)");
    mWorld.loadMap("resource\\Map\\06 - Sky Area (1-3)");
    mWorld.loadMap("resource\\Map\\07 - Mushroom Area (4-3)");
    mWorld.loadMap("resource\\Map\\08 - Sea Area (2-2)");

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
    PlayMusicStream(mPlayingMusic);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        timeSinceLastUpdated += GetFrameTime();
        while (timeSinceLastUpdated > timePerFrame) {
            timeSinceLastUpdated -= timePerFrame;
            inputProcess();
            update(timePerFrame);
        }
        
        UpdateMusicStream(mPlayingMusic);
        
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
    CloseAudioDevice();
    TextureHolder::destroyInstance();
    FontHolder::destroyInstance();
    SoundHolder::destroyInstance();
    MusicHolder::destroyInstance();
    World::destroyInstance();
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