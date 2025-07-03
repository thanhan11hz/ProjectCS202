#include "Entity/TileEntity.hpp"
#include <iostream>
#include <raylib.h>

TileBlock::TileBlock(TileType type, int col, int row)
    : mType(type), mRect({col * TILE_RENDER_SIZE, row * TILE_RENDER_SIZE, TILE_RENDER_SIZE, TILE_RENDER_SIZE}), posTile({0, 0}) {
    
    if (type != TileType::Empty) {
        int x = (static_cast<int>(type) - 1) % 29;
        int y = (static_cast<int>(type) - 1) / 29;
        posTile = { x * TILE_SIZE, y * TILE_SIZE };  
        std::cout << mRect.x << " " << mRect.y << " " << mRect.height  << std::endl;
    }
}


void TileBlock::draw(Texture2D tileTexture) {
    Rectangle dest = {100, 100, 48, 48}; // phóng to ra
    Rectangle source = {208, 48, 16, 16};  // vẽ ô đầu tiên
    DrawTexturePro(tileTexture, source, dest, {0, 0}, 0.0f, WHITE);
    if (mType != TileType::Empty) {      
        Rectangle source = {posTile.x, posTile.y, TILE_SIZE, TILE_SIZE }; 
        DrawTexturePro(tileTexture, source, mRect, {0, 0}, 0.0f, WHITE);
    }
}

