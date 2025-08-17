#include "World/TileMap.hpp"
#include "Entity/TileEntity.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>

#include <sstream>
using namespace std;

TileMap::TileMap(const nlohmann::json& j) {
    for (const auto& je : j["enemy"]) {
        auto e = createEntityFromJson(je);
        Enemies.push_back(std::unique_ptr<Enemy>(static_cast<Enemy*>(e.release())));
    }

    for (const auto& ji: j["item"]) {
        Items.push_back(std::make_unique<TileObject>(ji));
    }
        
    for (const auto& jr: j["main"]) {
        std::vector<Btr> row;
        for (const auto& jc: jr) {
            row.push_back(std::make_unique<TileBlock>(jc));
        }
        mMain.push_back(std::move(row));
    }

    for (const auto& jr: j["background1"]) {
        std::vector<Btr> row;
        for (const auto& jc: jr) {
            row.push_back(std::make_unique<TileBlock>(jc));
        }
        mBackground.push_back(std::move(row));
    }

    for (const auto& jr: j["background2"]) {
        std::vector<Btr> row;
        for (const auto& jc: jr) {
            row.push_back(std::make_unique<TileBlock>(jc));
        }
        mBackground2.push_back(std::move(row));
    }
}

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
                        //dataItem.emplace_back(std::make_pair(tileId, Vector2{j*1.0f, i*1.0f}));
                        break;
                    default:
                        // Handle unknown item
                        break;
                    }
                //TileObject* block= nullptr;
                if(item){
                    //block = item.get();
                    Items.emplace_back(std::move(item));
                }
                //rows.emplace_back(block);
            }
            //mItem.emplace_back(std::move(rows));
            rows.clear();
        }
    
    }
    else if (choice == 5){
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
                        break;
                        
                    case 18:
                    case 19: 
                        Enemy = Goomba::spawnGoomba2({col * 48.0f, i * 48.0f});
                        break;
                    case 84:
                        Enemy = Piranha::spawnPiranha2({col * 48.0f, i * 48.0f});

                        break;
                    case 41:
                        Enemy = Koopa::spawnKoopa({col * 48.0f, i * 48.0f},Koopa::Type::K_RED);
                        break;
                    case 77:
                        Enemy = Koopa::spawnKoopa({col * 48.0f, i * 48.0f},Koopa::Type::K_BLUE);
                        
                        break;
                    case 116:
                        Enemy = Bowser::spawnBowser({col * 48.0f, i * 48.0f});
                        break;
                    case 55:
                        Enemy = Podoboo::spawnPodoboo({col * 48.0f, i * 48.0f});
                        break;
                    case 330:
                        firebar = std::move(FireBar::spawnFireBar({col * 48.0f, i * 48.0f}));
                        for (auto& f : firebar) {
                            Enemies.emplace_back(std::move(f));
                        }
                    default:
                        break;
                }
                if (Enemy) {
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
                Btr block = std::make_unique<TileBlock>(tileId, j,i);
                row.emplace_back(std::move(block));
            }
            mBackground2.emplace_back(std::move(row)); 
            row.clear();
        }
    }
    
     
}

vector<vector<int>> TileMap::loadMatrixFromCSV(const string& filepath) {
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

    Color color = mBackground[0][0]->getCorlor();
    ClearBackground(color);
      

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


void TileMap::drawItem(Rectangle& camera) {
    // Only draw the ones inside view.
    for (auto itr = Items.begin(); itr != Items.end(); ++itr) {
        // Get the item's bounding box
        Vector2 itemPos = (*itr)->mPhysics.getPosition();
        Vector2 itemSize = (*itr)->getSize();
        Rectangle itemRect = { itemPos.x, itemPos.y, itemSize.x, itemSize.y };

        // Check if the item's rectangle overlaps with the camera's view
        if (CheckCollisionRecs(camera, itemRect)) {
            (*itr)->draw(tileTexture, objectTexture); // Only draw the item if it's visible
        }
    }
}

void TileMap::drawEnemy1(Rectangle& camera) {
    // Only draw the ones inside view.
    for (auto itr = Enemies.begin(); itr != Enemies.end(); ++itr) {
        // Get the enemy's bounding box
        Vector2 enemyPos = (*itr)->mPhysics.getPosition();
        Vector2 enemySize = (*itr)->getSize();
        Rectangle enemyRect = { enemyPos.x, enemyPos.y, enemySize.x, enemySize.y };

        // Check if the enemy's rectangle overlaps with the camera's view
        if (CheckCollisionRecs(camera, enemyRect) && (*itr)->isAfterBlock()) {
            (*itr)->draw(); // Only draw the enemy if it's visible
        }
    }
}
void TileMap::drawEnemy2(Rectangle& camera) {
    // Only draw the ones inside view.
    for (auto itr = Enemies.begin(); itr != Enemies.end(); ++itr) {
        // Get the enemy's bounding box
        Vector2 enemyPos = (*itr)->mPhysics.getPosition();
        Vector2 enemySize = (*itr)->getSize();
        Rectangle enemyRect = { enemyPos.x, enemyPos.y, enemySize.x, enemySize.y };

        // Check if the enemy's rectangle overlaps with the camera's view
        if (CheckCollisionRecs(camera, enemyRect) && !(*itr)->isAfterBlock()) {
            (*itr)->draw(); // Only draw the enemy if it's visible
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
                //mMain[i][j]->print();
            }
        }
    }
}

void TileMap::setEnemy(std::vector<std::unique_ptr<Enemy>>& enemy) {
    Enemies.clear();
    for (auto& e : enemy) {
        Enemies.push_back(std::move(e));
    }
    enemy.clear();
}

void TileMap::update(float dt){
    for (int i = 0; i < mMain.size(); i++) {
        for (int j = 0; j < mMain[i].size(); j++) {
            mMain[i][j]->update(dt);
        }
    }
}

TileMap::TileMap(const TileMap& other) {
    // Clone mMain
    
    mMain.resize(other.mMain.size());
    for (size_t i = 0; i < other.mMain.size(); ++i) {
        mMain[i].reserve(other.mMain[i].size());
        for (const auto& blockPtr : other.mMain[i]) {
            if (blockPtr) {
                mMain[i].push_back(blockPtr->clone()); 
            } else {
                mMain[i].push_back(nullptr);
            }
        }
    }
    // Clone mBackground
    mBackground.resize(1);
    mBackground[0].resize(1);
    mBackground[0][0] = other.mBackground[0][0]->clone();

    // Clone mBackground2
    mBackground2.resize(other.mBackground2.size());
    for (size_t i = 0; i < other.mBackground2.size(); ++i) {
        mBackground2[i].reserve(other.mBackground2[i].size());
        for (const auto& blockPtr : other.mBackground2[i]) {
            if (blockPtr) {
                mBackground2[i].push_back(blockPtr->clone()); 
            } else {
                mBackground2[i].push_back(nullptr);
            }
        }
    }

    // Clone Enemies
    Enemies.reserve(other.Enemies.size());
    for (const auto& enemyPtr : other.Enemies) {
        if (enemyPtr) {
            Enemies.push_back(enemyPtr->clone()); 
        }
    }

    // Clone Items
    Items.reserve(other.Items.size());
    for (const auto& itemPtr : other.Items) {
        if (itemPtr) {
            Items.push_back(itemPtr->clone()); 
        }
    }

   
    tileTexture = other.tileTexture;
    objectTexture = other.objectTexture;
}

void TileMap::updateEnemy(float dt) {
    for (auto itr = Enemies.begin(); itr != Enemies.end(); ) {
        // If an enemy falls too far down, mark it as dead.
        const float deathPlaneY = 2000.0f;
        if ((*itr)->mPhysics.getPosition().y > deathPlaneY) {
            (*itr)->setDie(true);
        }
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = Enemies.erase(itr);
        }
    }
}

void TileMap::updateItem(float dt) {
    for (auto itr = Items.begin(); itr != Items.end(); ) {
        if (*itr && !(*itr)->isDie()) {
            (*itr)->update(dt);
            ++itr;
        } else {
            itr = Items.erase(itr);
        }
    }
}

void TileMap::serialize(nlohmann::json& j) {
    j["enemy"] = nlohmann::json::array();
    for (const auto& e: Enemies) {
        nlohmann::json js;
        e->serialize(js);
        j["enemy"].push_back(js);
    }

    j["item"] = nlohmann::json::array();
    for (const auto& i: Items) {
        nlohmann::json js;
        i->serialize(js);
        j["item"].push_back(js);
    }

    j["main"] = nlohmann::json::array();
    for (int i = 0; i < mMain.size(); ++i) {
        j["main"].push_back(nlohmann::json::array());
        for (auto& m: mMain[i]) {
            nlohmann::json js;
            m->serialize(js);
            j["main"][i].push_back(js);
        }
    }

    j["background1"] = nlohmann::json::array();
    for (int i = 0; i < mBackground.size(); ++i) {
        j["background1"].push_back(nlohmann::json::array());
        for (auto& m: mBackground[i]) {
            nlohmann::json js;
            m->serialize(js);
            j["background1"][i].push_back(js);
        }
    }

    j["background2"] = nlohmann::json::array();
    for (int i = 0; i < mBackground2.size(); ++i) {
        j["background2"].push_back(nlohmann::json::array());
        for (auto& m: mBackground2[i]) {
            nlohmann::json js;
            m->serialize(js);
            j["background2"][i].push_back(js);
        }
    }
}