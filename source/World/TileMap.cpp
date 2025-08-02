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

    else if(choice == 3){ //item
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j;              
                Btr block = std::make_unique<TileObject>(tileId, j, i);
                row.emplace_back(std::move(block));
            }
            mItem.emplace_back(std::move(row));
            row.clear();
        }
    }
    else if (choice == 5){
        std::cout << "Load Enemies" << "\n";
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                int num = matrix[i][j];
                int tileId = num;
                int col =  j;
                Etr Enemy = nullptr;
                switch (num)
                {
                    case 0: // Goomba
                        Enemy = std::make_unique<Goomba>();
                        std::cout << "Spawn Goomba at: " << col << ", " << i << "\n";
                        break;
                    default:
                        break;
                }
                if (Enemy) {
                    Enemy->mPhysics.setPosition({col * 48.0f, i * 48.0f});
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

void TileMap::drawBackground() {
    for (int i = 0; i < mBackground.size(); i++) {
        for (int j = 0; j < mBackground[i].size(); j++) {
            const Rectangle& rect = mBackground[i][j]->getRect(); 
            // if (rect.x + rect.width >= 0 && rect.x <= screenW &&
            //     rect.y + rect.height >= 0 && rect.y <= screenH) {
            //     mBackground[i][j]->draw(tileTexture, objectTexture);
            // }
            mBackground[i][j]->draw(tileTexture, objectTexture);
            if ( mBackground2.size() > 0) 
                mBackground2[i][j]->draw(tileTexture, objectTexture);
        }
    }
}

void TileMap::drawItem() {
    for (int i = 0; i < mItem.size(); i++) {
        for (int j = 0; j < mItem[i].size(); j++) {
            const Rectangle& rect = mItem[i][j]->getRect(); 

            mItem[i][j]->draw(tileTexture, objectTexture);
        }
    }
}

void TileMap::drawMain() {
    for (int i = 0; i < mMain.size(); i++) {
        for (int j = 0; j < mMain[i].size(); j++) {
            const Rectangle& rect = mMain[i][j]->getRect(); 
            mMain[i][j]->draw(tileTexture, objectTexture);
        }
    }
}

void TileMap::drawEnemy() {
    for (auto& enemy : Enemies) {
        if (enemy->isActive()) {
            
            enemy->draw();
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
            mBackground[i][j]->update(dt);
            mItem[i][j]->update(dt);
            mMain[i][j]->update(dt);
            if(i < Enemies.size()) {
                if ((Enemies[i]->mPhysics.getPosition().y < 1000000.0f) && (Enemies[i]->isActive())) {
                    std::cout << "Drawing Enemy: " << i << " at position: " << Enemies[i]->mPhysics.getPosition().x << ", " << Enemies[i]->mPhysics.getPosition().y << "\n";
                }
                Enemies[i]->update(dt);
            }
        }


    }
}
