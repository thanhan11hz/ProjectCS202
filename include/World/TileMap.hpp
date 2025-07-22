#pragma once
#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include <vector>
#include <string>

class TileMap {
public:
    using Btr = std::unique_ptr<TileBlock>;

    TileMap(){};
    void loadFromFile(const std::string& filename);
    void draw();
    void update(float dt);
    void setTexrure(Texture2D tileBlock, Texture2D tileObject) {tileTexture = tileBlock; objectTexture = tileObject;};
protected:
    void drawCurrent();

private:
    std::vector<std::vector<Btr>> mTiles;
    Texture2D tileTexture;
    Texture2D objectTexture;
};
