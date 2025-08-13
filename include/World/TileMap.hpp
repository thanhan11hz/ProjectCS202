#pragma once

#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Entity/TileEntity.hpp"
#include "Entity/FireBar.hpp"
#include "Entity/Bowser.hpp"
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
                                            
    TileMap(){};
    void loadFromFile(const std::string& directory);
    std::vector<std::vector<int>> loadMatrixFromCSV(const std::string& filepath);
    void createMap(int choice, std::vector<std::vector<int>>& matrix);

    void drawBackground(Camera2D& camera);
    void drawEnemy1(Rectangle& camera);
    void drawEnemy2(Rectangle& camera);

    void drawItem(Rectangle& camera);
    void drawMain(Camera2D& camera);

    void update(float dt);

    float getBound() const { 
        if(!mMain.empty() && !mMain[0].empty()) {
            return mMain[0].size() * 48.0f;
        }
        return 0.0f; 
    }

    void setTexture(Texture2D tileBlock, Texture2D tileObject) {tileTexture = tileBlock; objectTexture = tileObject;};

    std::vector<std::vector<Btr>>& getMain() {return mMain;}
    std::vector<Etr>& getEnemy() {return Enemies;}
    std::vector<std::unique_ptr<Enemy>> takeEnemies() {return std::move(Enemies); }
    std::vector<std::unique_ptr<TileObject>>& getItems() {return Items;}
    std::vector<std::unique_ptr<TileObject>> takeItems() {return std::move(Items); }
    void setEnemy(std::vector<std::unique_ptr<Enemy>>& enemy);
    void resetItem() { Items.clear(); }

    TileMap(const TileMap&);
    std::unique_ptr<TileMap> clone() const {
        return std::make_unique<TileMap>(*this);
    }
    
    void updateEnemy(float dt);
    void updateItem(float dt);
    
private:
    std::vector<std::vector<Btr>> mMain;
    std::vector<std::vector<Btr>> mBackground;
    std::vector<std::vector<Btr>> mBackground2;
    std::vector<Etr> Enemies;
    std::vector<std::unique_ptr<TileObject>> Items;
    Texture2D tileTexture;
    Texture2D objectTexture;
};
