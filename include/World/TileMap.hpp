#pragma once

#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include "Entity/Goomba.hpp"
#include "Entity/Koopa.hpp"
#include "Entity/Podoboo.hpp"
#include "Entity/Piranha.hpp"
#include "Entity/TileItem.hpp"
#include "Entity/Enemy.hpp"
#include <memory>
#include <vector>
#include <string>

class TileMap {
public:
    using Btr = std::unique_ptr<TileBlock>;
    using Etr = std::unique_ptr<Enemy>;
                                            //hàm getBounds
                                            //fix bug sọc trắng
                                            //load enemy
                                            //block màn 6
                                            //sửa hiệu ứng vỡ gạch
                                            //warp, movingblock, rìu, hiệu ứng rút cầu
    TileMap(){};
    void loadFromFile(const std::string& directory);
    std::vector<std::vector<int>> loadMatrixFromCSV(const std::string& filepath);
    void createMap(int choice, std::vector<std::vector<int>>& matrix);
    // void drawBackground();
    void drawBackground(Camera2D& camera);
    void drawEnemy();
    // void drawItem();
    void drawItem(Camera2D& camera);
    // void drawMain();
    void drawMain(Camera2D& camera);
    void update(float dt);
    void setTexture(Texture2D tileBlock, Texture2D tileObject) {tileTexture = tileBlock; objectTexture = tileObject;};
    std::vector<std::vector<Btr>>& getMain() {return mMain;}

private:
    std::vector<std::vector<Btr>> mMain;
    std::vector<std::vector<Btr>> mBackground;
    std::vector<std::vector<Btr>> mItem;
    std::vector<std::vector<Btr>> mBackground2;
    std::vector<Etr> mEnemy;
    std::vector<Etr> Enemies;
    std::vector<TileObject*> Items;
    Texture2D tileTexture;
    Texture2D objectTexture;
};
