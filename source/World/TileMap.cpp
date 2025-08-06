#include "World/TileMap.hpp"
#include "Entity/TileEntity.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>


#include <sstream>
using namespace std;

void TileMap::loadFromFile(const std::string& directory) {
    std::string folderName = std::filesystem::path(directory).filename().string();
    std::string prefix =  folderName.substr(0, 2) + "_";
    for (const auto& file : std::filesystem::directory_iterator(directory)){
        std::string stem = file.path().stem().string();
        vector<vector<int>> matrix = loadMatrixFromCSV(file.path().string());
        if (stem == prefix + "Background") {
            createMap(1, matrix);
        } else if (stem == prefix + "Main") {
            createMap(2, matrix);
        } else if (stem == prefix + "Items") {
            createMap(3, matrix);
        }
        else if( stem == prefix + "Enemies") {
            createMap(5, matrix);
        }
        else if(stem == prefix + "Background1") {
            createMap(4, matrix);
        }
        
    }
}

void TileMap::createMap(int choice, vector<vector<int>>& matrix){
    std::vector<Btr> row;
    if(choice == 1){ //Background
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j;              
                row.emplace_back(std::move(Btr(new TileBlock(tileId, j, i))));
            }
            mBackground.emplace_back(std::move(row));
            row.clear();
        }
    }
    else if(choice == 2){ //main
        std::cout << "Load Main" << "\n";
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j;              
                Btr block = std::make_unique<TileBlock>(tileId, j, i);
                
                row.emplace_back(std::move(block));
            }
            mMain.emplace_back(std::move(row));
            row.clear();
        }
    }

    else if(choice == 3){
             //item
            std::vector<TileObject*> rows;
            for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j; 
                std::unique_ptr<TileObject> item = nullptr;
                switch (num){
                    case 0: 
                    case 1: 
                    case 10: 
                    case 72: 
                    case 108: 
                    case 180: 
                    case 216: 
                    case 13: 
                    case 189: 
                    case 44: 
                    case 252: 
                        item = std::make_unique<TileObject>(tileId, j, i);
                        
                        dataItem.emplace_back(std::make_pair(tileId, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    default:
                        // Handle unknown item
                        break;
                    }
                TileObject* block= nullptr;
                if(item){
                    block = item.get();
                    Items.emplace_back(std::move(item));
                }
                rows.emplace_back(block);
            }
            mItem.emplace_back(std::move(rows));
            rows.clear();
        }
    
    }
    else if (choice == 5){
        std::cout << "Load Enemies" << "\n";
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                if (num == -1) continue; 
                int tileId = num;
                int col =  j;
                std::vector<std::unique_ptr<FireBar>> firebar;
                Etr Enemy = nullptr;
                switch (num)
                {
                    case 0: // Goomba
                    case 1: 
                        Enemy = Goomba::spawnGoomba1({col * 48.0f, i * 48.0f});
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                        
                    case 18:
                    case 19: 
                        Enemy = Goomba::spawnGoomba2({col * 48.0f, i * 48.0f});
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 84:
                        Enemy = Piranha::spawnPiranha2({col * 48.0f, i * 48.0f});
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 41:
                        Enemy = Koopa::spawnKoopa({col * 48.0f, i * 48.0f},Koopa::Type::K_RED);
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 77:
                        Enemy = Koopa::spawnKoopa({col * 48.0f, i * 48.0f},Koopa::Type::K_BLUE);
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 116:
                        Enemy = Bowser::spawnBowser({col * 48.0f, i * 48.0f});
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 55:
                        Enemy = Podoboo::spawnPodoboo({col * 48.0f, i * 48.0f});
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                        break;
                    case 330:
                        firebar = std::move(FireBar::spawnFireBar({col * 48.0f, i * 48.0f}));
                        for (auto& f : firebar) {
                            Enemies.emplace_back(std::move(f));
                        }
                        mEnemy.emplace_back(std::make_pair(num, Vector2{col * 48.0f, i * 48.0f}));
                    default:
                        break;
                }
                if (Enemy) {
                    //Enemy->mPhysics.setPosition({col * 48.0f, i * 48.0f});
                    Enemies.emplace_back(std::move(Enemy));
                }
            }
        }
    }
    else {
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j;              
                Btr block = std::make_unique<TileBlock>(tileId, j, i);
                row.emplace_back(std::move(block));
            }
            mBackground2.emplace_back(std::move(row)); //có thể cân nhắc đưa vào mItem 
            row.clear();
        }
    }
    
     
}

vector<vector<int>> TileMap::loadMatrixFromCSV(const string& filepath) {
    std::cout << "Loading CSV file "  << '\n';
    vector<vector<int>> matrix;
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Không thể mở file: " << filepath << endl;
        return matrix;
    }

    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }

        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

// void TileMap::drawBackground() {
//     for (int i = 0; i < mBackground.size(); i++) {
//         for (int j = 0; j < mBackground[i].size(); j++) {
//             const Rectangle& rect = mBackground[i][j]->getRect(); 
//             // if (rect.x + rect.width >= 0 && rect.x <= screenW &&
//             //     rect.y + rect.height >= 0 && rect.y <= screenH) {
//             //     mBackground[i][j]->draw(tileTexture, objectTexture);
//             // }
//             mBackground[i][j]->draw(tileTexture, objectTexture);
//             if ( mBackground2.size() > 0) 
//                 mBackground2[i][j]->draw(tileTexture, objectTexture);
//         }
//     }
// }

void TileMap::drawBackground(Camera2D& camera) {
    // Calculate the camera's view in world coordinates
    float startX = camera.target.x - camera.offset.x;
    float endX = startX + targetWidth;
    float startY = camera.target.y - camera.offset.y;
    float endY = startY + targetHeight;

    // Convert world coordinates to tile indices
    int startCol = startX / TileBlock::TILE_RENDER_SIZE;
    int endCol = endX / TileBlock::TILE_RENDER_SIZE;
    int startRow = startY / TileBlock::TILE_RENDER_SIZE;
    int endRow = endY / TileBlock::TILE_RENDER_SIZE;

    // Clamp values for the first layer
    int clampedStartRow1 = std::max(0, startRow);
    int clampedEndRow1 = std::min((int)mBackground.size() - 1, endRow);
    int clampedStartCol1 = std::max(0, startCol);
    int clampedEndCol1 = std::min((int)mBackground[0].size() - 1, endCol);

    for (int i = clampedStartRow1; i <= clampedEndRow1; i++) {
        for (int j = clampedStartCol1; j <= clampedEndCol1; j++) {
            if (mBackground[i][j]) {
                Color color = mBackground[i][j]->getCorlor();
                ClearBackground(color);
            }
        }
    }

    // Draw the second background layer
    if (!mBackground2.empty()) {
        // Clamp values for the second layer
        int clampedStartRow2 = std::max(0, startRow);
        int clampedEndRow2 = std::min((int)mBackground2.size() - 1, endRow);
        int clampedStartCol2 = std::max(0, startCol);
        int clampedEndCol2 = std::min((int)mBackground2[0].size() - 1, endCol);

        for (int i = clampedStartRow2; i <= clampedEndRow2; i++) {
            for (int j = clampedStartCol2; j <= clampedEndCol2; j++) {
                if (mBackground2[i][j]) {
                    mBackground2[i][j]->draw(tileTexture, objectTexture);
                }
            }
        }
    }
}

// void TileMap::drawItem() {
//     for (int i = 0; i < mItem.size(); i++) {
//         for (int j = 0; j < mItem[i].size(); j++) {
//             const Rectangle& rect = mItem[i][j]->getRect(); 

//             mItem[i][j]->draw(tileTexture, objectTexture);
//         }
//     }
// }

void TileMap::drawItem(Camera2D& camera) {
    // Calculate the camera's view in world coordinates
    float startX = camera.target.x - camera.offset.x;
    float endX = startX + targetWidth;
    float startY = camera.target.y - camera.offset.y;
    float endY = startY + targetHeight;

    // Convert world coordinates to tile indices
    int startCol = startX / TileBlock::TILE_RENDER_SIZE;
    int endCol = endX / TileBlock::TILE_RENDER_SIZE;
    int startRow = startY / TileBlock::TILE_RENDER_SIZE;
    int endRow = endY / TileBlock::TILE_RENDER_SIZE;

    // Clamp values to be within the map boundaries to prevent crashes
    startCol = std::max(0, startCol);
    endCol = std::min((int)mItem[0].size() - 1, endCol);
    startRow = std::max(0, startRow);
    endRow = std::min((int)mItem.size() - 1, endRow);

    // Loop only through the visible tiles
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            if (mItem[i][j] ) { // Check if the tile exists
                if(!mItem[i][j]->absorbed()) mItem[i][j]->draw(tileTexture, objectTexture);
            }
        }
    }
}

// void TileMap::drawMain() {
//     for (int i = 0; i < mMain.size(); i++) {
//         for (int j = 0; j < mMain[i].size(); j++) {
//             const Rectangle& rect = mMain[i][j]->getRect(); 
//             mMain[i][j]->draw(tileTexture, objectTexture);
//         }
//     }
// }

void TileMap::drawMain(Camera2D& camera) {
    // Calculate the camera's view in world coordinates
    float startX = camera.target.x - camera.offset.x;
    float endX = startX + targetWidth;
    float startY = camera.target.y - camera.offset.y;
    float endY = startY + targetHeight;

    // Convert world coordinates to tile indices
    int startCol = startX / TileBlock::TILE_RENDER_SIZE;
    int endCol = endX / TileBlock::TILE_RENDER_SIZE;
    int startRow = startY / TileBlock::TILE_RENDER_SIZE;
    int endRow = endY / TileBlock::TILE_RENDER_SIZE;

    // Clamp values to be within the map boundaries to prevent crashes
    startCol = std::max(0, startCol);
    endCol = std::min((int)mMain[0].size() - 1, endCol);
    startRow = std::max(0, startRow);
    endRow = std::min((int)mMain.size() - 1, endRow);

    // Loop only through the visible tiles
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            if (mMain[i][j]) { // Check if the tile exists
                mMain[i][j]->draw(tileTexture, objectTexture);
            }
        }
    }
}

void TileMap::update(float dt){
    for (int i = 0; i < mBackground.size(); i++) {
        for (int j = 0; j < mBackground[i].size(); j++) {
            const Rectangle& rect = mBackground[i][j]->getRect(); 
            // if (rect.x + rect.width >= 0 && rect.x <= screenW &&
            //     rect.y + rect.height >= 0 && rect.y <= screenH) {
            //     mBackground[i][j]->update(dt);
            //     mItem[i][j]->update(dt);
            //     mMain[i][j]->update(dt);
            // }
            if (mItem[i][j]) mItem[i][j]->update(dt);
            mMain[i][j]->update(dt);
        }
    }
}
