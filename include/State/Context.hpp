#pragma once

#include <raylib.h>

#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"

struct Context {
    TextureHolder* textures;
    FontHolder* fonts;
    SoundHolder* sounds;
    MusicHolder* musics;

    Context(TextureHolder* t, FontHolder* f, SoundHolder* s, MusicHolder* m) : textures(t), fonts(f), sounds(s), musics(m) {}
};