#include "Global.hpp"
#include "World/World.hpp"

int targetWidth = 1440, targetHeight = 912;

float timePerFrame = 1.0f/60;

TextureHolder& Resource::mTexture = TextureHolder::getInstance(LoadTexture, UnloadTexture);

FontHolder& Resource::mFont = FontHolder::getInstance(LoadFont, UnloadFont);

SoundHolder& Resource::mSound = SoundHolder::getInstance(LoadSound, UnloadSound);

MusicHolder& Resource::mMusic = MusicHolder::getInstance(LoadMusicStream, UnloadMusicStream);

World& mWorld = World::getInstance();

std::map<Action, KeyboardKey> mFunctionKey = {
    {Action::PAUSE, KEY_P},
    {Action::MUTE, KEY_M},
};

std::map<Action, KeyboardKey> mKeyBinding = {
    {Action::FIRE, KEY_LEFT_SHIFT},
    {Action::JUMP, KEY_W},
    {Action::DOWN, KEY_S},
    {Action::LEFT, KEY_A},
    {Action::RIGHT, KEY_D}
};

std::map<Action, KeyboardKey> mKeyBinding2 = {
    {Action::FIRE, KEY_ENTER},
    {Action::JUMP, KEY_UP},
    {Action::DOWN, KEY_DOWN},
    {Action::LEFT, KEY_LEFT},
    {Action::RIGHT, KEY_RIGHT}
};

Music mPlayingMusic;
float musicVolume = 1.0f;
float sfxVolume = 1.0f;
bool isMute = false;

int createdCount = 0;