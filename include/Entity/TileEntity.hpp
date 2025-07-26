#pragma once
#include "Entity.hpp"
#include <raylib.h>
#include <vector>
#include <memory>

enum TileType {
    Empty=-1,        //Tile Underground,... = Overworld tile + 2*29*n;
    OwGround=0,    //cvs -> -1
    OwInitialTile=1,
    OwWall = 2,
    OwBlock = 3,
    OwAfterHitBlock = 26,
    OwCoinBlock1=23,
    OwCoinBlock2=24,
    OwCoinBlock3=25,
    OwPipeTop1=232,
    OwPipeTop2=233,
    OwPipeBottom1=261,
    OwPipeBottom2=262,
    OWBridge = 32,
    OwPole = 277,
    BrownCube = 29,
    GrassPlatform1 = 237,
    GrassPlatform2 = 238,
    GrassPlatform3 = 239,
    GreenDotPlatForm1 = 266,
    GreenDotPlatForm2 = 267,
    GreenDotPlatForm3 = 268,
    HoriPipe1 = 234,
    HoriPipe2 = 263,

    UnderTile = 60,
};


 extern std::vector<int> tileItemValues; 
enum TileItem {
    mushroom = 0, //Underground,... +=n*9
    flower = 72,
    star = 108,
    normalCoin = 180,
    specialCoin = 216,
    fragment = 4,
    underfragment = 13,
    invalidItem = -1,
};
class TileBlock;
class TileObject;

class IBlockBehavior{

public:
    Side side;
    Category other;
public:
    virtual void onHit(TileBlock& block, float dt) = 0;
    virtual void update(TileBlock& block, float dt) = 0;
    virtual ~IBlockBehavior() = default;
    virtual void setSide(Side side) { this->side = side; }
    virtual void setOther(Category other) { this->other = other; }
};
class TileBlock : public Entity{
public:
    TileBlock(int type, int row, int col);
    void draw() override;
    void handle() override;
    void handleCollision(Side side, Category other) override;
    Vector2 getSize() override;
    virtual void update(float dt) override;


    virtual void draw(Texture2D& background, Texture2D& object);
    void print();
    TileType getType(int type = -2);
    int calType();
    const Rectangle& getRect() const { return mRect; }
    const Rectangle& getSource() const { return aniRect; }

    void setVelocity(Vector2 velocity);
    void applyGravity(float dt);
    void addFragment();
    void setAnimation();
    void setState();
    bool isSolid();

    virtual ~TileBlock();


    static constexpr int TileCollum = 29;
    static constexpr int ObjectRow = 35;
    static constexpr float TILE_SCALE = 3.0f;
    static constexpr float TILE_SIZE = 16.0f;
    static constexpr float TILE_RENDER_SIZE = 48.0f;
    static constexpr float duration = 0.15f;
    static constexpr float Gravity = 950.f;
    friend class SimpleBlockBehavior;
    friend class CoinBlockBehavior;

private:
    void setRect(Rectangle rect);
    void setPostile(Vector2 pos);
    void setSource(Rectangle source);
    float calculateVec(float duration, float dis);
    virtual void createBehavior();
protected:
    int mType;
    Rectangle mRect;
    Rectangle mSource;
    Vector2 posTile;
    Vector2 mVelocity;
    Rectangle aniRect;
    bool printed;
    bool isDoneAnimation = true;
    bool bumped = false;
    bool isDestroyed = false;
    bool solid = false;
    float aniTime = 0.0f;
    IBlockBehavior* mBehavior = nullptr;
    std::vector<std::unique_ptr<TileObject>> frag;
    Color mColor = BLACK;
};



// Example behaviors



class SimpleBlockBehavior : public IBlockBehavior {
public:
    void onHit(TileBlock& block, float dt) override ;
    void update(TileBlock& block, float dt) override ;
    void bump(TileBlock& block, float dt) ;
    void destroy(TileBlock& bloc, float dt) ;
};


class CoinBlockBehavior : public SimpleBlockBehavior{
    public:
        void update(TileBlock& block, float dt) override ;
};

