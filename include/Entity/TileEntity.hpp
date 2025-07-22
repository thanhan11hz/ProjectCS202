#pragma once

#include <raylib.h>
#include <vector>

enum TileType {
    Empty=0,        //Tile Underground,... = Overworld tile + 2*29*n;
    OwGround=1,    
    OwInitialTile=3,
    OwAfterHitBlock = 4,
    OwCoinBlock1=24, 
    OwCoin1 = 53,
    OwPipeTop1=233,
    OwPipeTop2=234,
    OwPipeBottom1=262,
    OwPipeBottom2=263,
    OwSky=613,

    OwFragment = 4, //sửa lại sao cho không trùng với tileset
    OwLeftFrag = 40,
    OwRightFrag = 76,

    UnderGround=59,
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


    CLoudUpperLeftConer=581,
    CloudUpperMiddel =582,
    CLoudUpperRightCorner=583,
    CLoudBottomLeftCorner=610,
    CLoudBottomMiddle=611,
    CLoudBottomRightConer=612,

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
    TileBlock(int type, int row, int col, Texture2D& tile, Texture2D& object);
    void draw(Texture2D& tile, Texture2D& object);

    void print();
    TileType getType();
    const Rectangle& getRect() const { return mRect; }

    void update(float dt);
    void moveUp(float dt);
    void destroy(float dt);
    void destroyAnimation(float dt);

    void setVelocity(Vector2 velocity);
    void applyGravity(float dt);
    void usingBlockTexture();
    void addFragment();
    void setAnimation();

    void coin(float dt);
private:
    void setRect(Rectangle rect);
    void setPostile(Vector2 pos);
    void setSource(Rectangle source);
    float calculateVec(float duration, float dis);
private:
    int mType;
    Rectangle mRect;
    Rectangle mSource;
    Vector2 posTile;

    Texture2D tileTex;
    Texture2D objectTex;
    Vector2 mVelocity;
    Rectangle aniRect;

    std::vector<TileBlock> frag;
    bool printed ;
    bool isDoneAnimation = true;
    bool bumped = false;
    bool isUsingTile = true;
    bool isDestroyed = false;
    float aniTime= 0.0f;


    const int TileCollum = 29;
    const int ObjectRow = 35;
    const float TILE_SCALE = 3.0f;
    const float TILE_SIZE = 16.0f;
    const float TILE_RENDER_SIZE = 48.0f;
    const float duration = 0.15f;
    static constexpr float Gravity  = 950.f;



};

