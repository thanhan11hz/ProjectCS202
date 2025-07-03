#pragma once
#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include "SceneNode.hpp"
#include <vector>
#include <string>

class TileMap : public SceneNode {
public:
    TileMap();
    void loadFromFile(const std::string& filename);
    void draw(Texture2D tileTexture);
protected:
    void drawCurrent() override;

private:
    std::vector<std::vector<TileBlock>> mTiles;

};
