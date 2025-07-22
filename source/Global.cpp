#include "Global.hpp"
#include "World/World.hpp"

int targetWidth = 1440, targetHeight = 900;

float timePerFrame = 1.0f/60;

TextureHolder& Resource::mTexture = TextureHolder::getInstance(LoadTexture, UnloadTexture);

FontHolder& Resource::mFont = FontHolder::getInstance(LoadFont, UnloadFont);

SoundHolder& Resource::mSound = SoundHolder::getInstance(LoadSound, UnloadSound);

MusicHolder& Resource::mMusic = MusicHolder::getInstance(LoadMusicStream, UnloadMusicStream);

World& mWorld;

std::vector<std::pair<KeyboardKey, Action>> mKeyBinding = {
    {KEY_P, Action::PAUSE},
    {KEY_M, Action::MUTE},
    {KEY_LEFT_SHIFT, Action::FIRE},
    {KEY_W, Action::JUMP},
    {KEY_S, Action::DOWN},
    {KEY_A, Action::LEFT},
    {KEY_D, Action::RIGHT}
};

Music mPlayingMusic;