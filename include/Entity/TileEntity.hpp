#pragma once
#include "Entity/Entity.hpp"
#include <raylib.h>
#include <vector>
#include <string>
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
    Finial =248,//Hitbox khác thường
    BrownCube = 29,
    GrassPlatform1 = 237,
    GrassPlatform2 = 238,
    GrassPlatform3 = 239,
    GreenDotPlatForm1 = 266,
    GreenDotPlatForm2 = 267,
    GreenDotPlatForm3 = 268,

    OrangeDotPlatForm1 = 382,
    OrangeDotPlatForm2 = 383,
    OrangeDotPlatForm3 = 384,
    HoriPipe1 = 234,
    HoriPipe2 = 263,
    HiddenBox = 556,
    CastleTile = 147,
    CastleBrigde = 700,
    HoriMovingBlock = 301,
    VertMovingBlock = 292,

    EndingPoint = 567,
    UnderTile = 60,
};


 extern std::vector<int> tileItemValues; 
enum TileItem {
    mushroom = 0,
    greenMushroom = 1,
    underMushroom = 10,
    flower = 72,
    star = 108,
    normalCoin = 180,
    specialCoin = 216,
    fragment = 4,
    underfragment = 13,
    underCoin = 189,
    flag = 44,
    hammer = 252,
    invalidItem = -1,
};
class TileBlock;
class TileObject;

class IBlockBehavior{

public:
    Side side;
    Category other;
    std::string oTag;
public:
    virtual void onHit(TileBlock& block, float dt) = 0;
    virtual void update(TileBlock& block, float dt) = 0;
    virtual ~IBlockBehavior() ;
    virtual void setSide(Side side) { this->side = side; }
    virtual void setOther(Category other) { this->other = other; }
    virtual void setTag(std::string tag) { this->oTag = tag; }
    virtual void handleCollision(TileBlock& block) = 0;
    virtual std::string getTag(){return "";};
    
};


class TileBlock : public Entity{
    public:
    TileBlock(int type, int col, int row);
    int type() const { return mType; }
    void draw() override;
    void handle() override;
    void handleCollision(Side side, Collide other) override;
    Vector2 getSize() override;
    virtual void update(float dt) override;
    float calculateVec(float duration, float dis);
    void serialize(nlohmann::json& j) override {}
    

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
    bool isSolid();
    virtual std::string getTag();

    virtual ~TileBlock();
    Color getCorlor() const { 
        if(mType == 42) {
            return BLACK;}
        return {99, 173, 255, 255};
     }
    std::unique_ptr<TileBlock> clone() const {
        return std::make_unique<TileBlock>(mType, mCol, mRow);
    }

    static constexpr int TileCollum = 29;
    static constexpr int ObjectRow = 35;
    static constexpr float TILE_SCALE = 3.0f;
    static constexpr float TILE_SIZE = 16.0f;
    static constexpr float TILE_RENDER_SIZE = 48.0f;
    static constexpr float duration = 0.15f;
    static constexpr float Gravity = 950.f;
    friend class SimpleBlockBehavior;
    friend class CoinBlockBehavior;
    friend class MovingBlockBehavior;

private:
    void setRect(Rectangle rect);
    void setPostile(Vector2 pos);
    void setSource(Rectangle source);
    virtual void createBehavior();
protected:
    int mType;
    Rectangle mRect;
    Rectangle mSource;
    Vector2 posTile;
    Vector2 mVelocity;
    Rectangle aniRect;
    bool printed;
    bool isOn = false;
    bool isDoneAnimation = true;
    bool bumped = false;
    bool isDestroyed = false;
    bool solid = false;
    float aniTime = 0.0f;
    IBlockBehavior* mBehavior = nullptr;
    int mRow;
    int mCol;
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
    void handleCollision(TileBlock& block) override;
    std::string getTag() override { return "SimpleBlock"; }
};


class CoinBlockBehavior : public SimpleBlockBehavior{
    public:
        void update(TileBlock& block, float dt) override ;
        void handleCollision(TileBlock& block) override;
        std::string getTag() override { return "CoinBlock"; }

};

class MovingBlockBehavior : public IBlockBehavior {
    int mType;
public:
    MovingBlockBehavior(int type = 0) : mType(type) {}
    void onHit(TileBlock& block, float dt) override{} ;
    void update(TileBlock& block, float dt) override ;
    void handleCollision(TileBlock& block) override{};
    std::string getTag() override { 
        if (mType == 292) return "VertMovingBlock";
        return "HoriMovingBlock";
    }
};