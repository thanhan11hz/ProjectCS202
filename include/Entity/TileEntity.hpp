#pragma once

#include <raylib.h>


enum TileType {
    Empty=0,
    OwGround=1,
    UnderGround=59,
    OwInitialTile=24,
    OwCoinBlock1=24,
    OwPipeTop1=233,
    OwPipeTop2=234,
    OwPipeBottom1=262,
    OwPipeBottom2=263,
    UnderPipeTop1=291,
    UnderPipeTop2=292,
    UnderPipeBottom1=320,
    UnderPipeBottom2=321,
    UnderPipe2Top1=293,
    UnderPipe2Top2=294,
    UnderPipe2Top3=295,
    UnderPipe2Bottom1=322,
    UnderPipe2Bottom2=323,
    UnderPipe2Bottom3=324,
    OwSky=613,
    CLoudUpperLeftCorner=581,
    CloudUpperMiddel =582,
    CLoudUpperRightCorner=583,
    CLoudBottomLeftCorner=610,
    CLoudBottomMiddle=611,
    CLoudBottomRightCorner=612,
    MountainUpperLeft1 = 241,
    MountainUpperMiddle1 =242, 
    MountainUpperRight1 = 243,
    MountainBottomLeft1 = 270,
    MountainBottomMiddle1 =271, 
    MountainBottomRight1 = 272,
    BushLeft1 = 273,
    BushMiddle1=274,
    BushRight1=275,
    BlackBLock = 101,
    UnderInitialTile1= 72,
    Coin2=111,
    
};

class TileBlock  {
public:
    TileBlock(TileBlock&&) noexcept = default;
    TileBlock& operator=(TileBlock&&) noexcept = default;
    TileBlock(const TileBlock&) = delete;
    TileBlock& operator=(const TileBlock&) = delete;
    TileBlock(TileType type, int row, int col);
    void draw(Texture2D tileTexture);
    const Rectangle& getRect() const { return mRect; }
private:
    TileType mType;
    Rectangle mRect;
    Vector2 posTile;
    const int TileColumn = 29;
    float TILE_SCALE = 3.0f;
    float TILE_SIZE = 16.0f;
   float TILE_RENDER_SIZE = TILE_SIZE * TILE_SCALE;


};
