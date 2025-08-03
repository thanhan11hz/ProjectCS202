#pragma once

#include <raylib.h>
#include <iostream>
#include <map>

#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"

extern int targetWidth, targetHeight;

extern float timePerFrame;

typedef ResourceHolder<Texture2D, TextureIdentifier> TextureHolder;

typedef ResourceHolder<Font, FontIdentifier> FontHolder;
        
typedef ResourceHolder<Sound, SoundIdentifier> SoundHolder;

typedef ResourceHolder<Music, MusicIdentifier> MusicHolder;

namespace Resource {

    extern TextureHolder& mTexture;

    extern FontHolder& mFont;

    extern SoundHolder& mSound;

    extern MusicHolder& mMusic;
}

class World;

extern World& mWorld;

enum class Action {
    PAUSE,
    MUTE,
    FIRE,
    LEFT,
    RIGHT,
    JUMP,
    DOWN
};

extern std::map<Action, KeyboardKey> mKeyBinding;

extern Music mPlayingMusic;
extern float musicVolume;
extern float sfxVolume;

extern int createdCount;