#pragma once

#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include <vector>
#include <string>

class TileMap {
public:
    TileMap();
    void loadFromFile(const std::string& filename);
    void draw();
    void drawTile(Texture2D tileTexture);
private:
    std::vector<std::vector<TileBlock>> mTiles;
};
