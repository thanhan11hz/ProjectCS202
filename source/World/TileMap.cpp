#include "World/TileMap.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

TileMap::TileMap(){}

void TileMap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string number;
    std::vector<TileBlock> row;
    char ch;

    while (file >> std::noskipws >> ch) {
        if (isdigit(ch) || ch == '-') {
            number += ch;
        } else if (ch == ',' || ch == '\n' || isspace(ch)) {
            if (!number.empty()) {
                int tileId = std::stoi(number);
                TileType type = static_cast<TileType>(tileId);
                int rowIndex =  static_cast<int>(row.size()); 
                int col =  static_cast<int>(mTiles.size());                
                row.emplace_back(type, rowIndex, col);
                number.clear();
            }

            if (row.size() == 300) {
                mTiles.push_back(std::move(row));
                row.clear();
            }
        }
        }


}

void TileMap::drawCurrent() {
    
}
void TileMap::draw(Texture2D tileTexture) {
    const int screenW = 1440;
    const int screenH = 900;
    for (int i = 0; i < mTiles.size(); i++) {
        for (int j = 0; j < mTiles[i].size(); j++) {
            const Rectangle& rect = mTiles[i][j].getRect(); 
            if (rect.x + rect.width >= 0 && rect.x <= screenW &&
                rect.y + rect.height >= 0 && rect.y <= screenH) {
                mTiles[i][j].draw(tileTexture);
            }
        }
    }
}
