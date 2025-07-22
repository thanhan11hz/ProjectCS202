#include "World/TileMap.hpp"
#include "Entity/TileEntity.hpp"
#include <fstream>
#include <iostream>
#include <sstream>


void TileMap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string number;
    std::vector<Btr> row;
    char ch;
    while (file >> std::noskipws >> ch) {
        if (isdigit(ch) || ch == '-') {
            number += ch;
        } else if (ch == ',' || ch == '\n' || isspace(ch)) {
            if (!number.empty()) {
                int tileId = std::stoi(number);
                int col =  static_cast<int>(row.size()); 
                int rows =  static_cast<int>(mTiles.size());                        
                row.emplace_back(std::move(Btr(new TileBlock(tileId, col, rows, tileTexture, objectTexture))));
                number.clear();
            }

            if (row.size() == 300) {
                mTiles.emplace_back(std::move(row));
                row.clear();
            }
        }
        }


}

void TileMap::draw() {
    
}
void TileMap::draw() {
    const int screenW = 1440;
    const int screenH = 900;
    for (int i = 0; i < mTiles.size(); i++) {
        for (int j = 0; j < mTiles[i].size(); j++) {
            const Rectangle& rect = mTiles[i][j]->getRect(); 
            if (rect.x + rect.width >= 0 && rect.x <= screenW &&
                rect.y + rect.height >= 0 && rect.y <= screenH) {
                mTiles[i][j]->draw( tileTexture, objectTexture);

            }

        }
    }
}
void TileMap::update(float dt){
    const int screenW = 1440;
    const int screenH = 900;
    for (int i = 0; i < mTiles.size(); i++) {
        for (int j = 0; j < mTiles[i].size(); j++) {
            const Rectangle& rect = mTiles[i][j]->getRect(); 
            if (rect.x + rect.width >= 0 && rect.x <= screenW &&
                rect.y + rect.height >= 0 && rect.y <= screenH) {
                mTiles[i][j]->update(dt);
            }
        }
    }
}
