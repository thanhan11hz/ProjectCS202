#pragma once

#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include "Entity/TileItem.hpp"
#include <memory>
#include <vector>
#include <string>

class TileMap {
public:
    using Btr = std::unique_ptr<TileBlock>;

    TileMap(){};
    void loadFromFile(const std::string& directory);
    std::vector<std::vector<int>> loadMatrixFromCSV(const std::string& filepath);
    void createMap(int choice, std::vector<std::vector<int>>& matrix);
    void drawBackground();
    void drawItem();
    void drawMain();
    void update(float dt);
    void setTexture(Texture2D tileBlock, Texture2D tileObject) {tileTexture = tileBlock; objectTexture = tileObject;};

private:
    std::vector<std::vector<Btr>> mMain;
    std::vector<std::vector<Btr>> mBackground;
    std::vector<std::vector<Btr>> mItem;
    std::vector<Btr> magItem;
    Texture2D tileTexture;
    Texture2D objectTexture;
};
