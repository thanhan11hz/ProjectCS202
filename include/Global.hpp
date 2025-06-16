#pragma once

#include <raylib.h>
#include <iostream>

#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"

extern int targetWidth, targetHeight;

extern float timePerFrame;

typedef ResourceHolder<Texture2D, TextureIdentifier> TextureHolder;

typedef ResourceHolder<Font, FontIdentifier> FontHolder;
        
typedef ResourceHolder<Sound, SoundIdentifier> SoundHolder;

typedef ResourceHolder<Music, MusicIdentifier> MusicHolder;