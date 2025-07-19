#include "Global.hpp"

int targetWidth = 1440, targetHeight = 900;

float timePerFrame = 1.0f/60;

TextureHolder& Resource::mTexture = *TextureHolder::getInstance(LoadTexture, UnloadTexture);

FontHolder& Resource::mFont = *FontHolder::getInstance(LoadFont, UnloadFont);

SoundHolder& Resource::mSound = *SoundHolder::getInstance(LoadSound, UnloadSound);

MusicHolder& Resource::mMusic = *MusicHolder::getInstance(LoadMusicStream, UnloadMusicStream);