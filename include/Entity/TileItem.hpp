#pragma once
#include "TileEntity.hpp"
#include <raylib.h>

class TileObject;

class IItemBehavior {
protected:
    Side side;
    Category other;
public:
    virtual void onCollect(TileObject& item) = 0;
    virtual void update(TileObject& item, float dt) = 0;
    virtual ~IItemBehavior() = default;
    void handleCollision(TileObject& item, Side side, Category other) {
        this->side = side;
        this->other = other;
    }
};


class FragmentBehavior : public IItemBehavior {
public: 
    void onCollect(TileObject& item) override ;
    void update(TileObject& item, float dt) override ;
    //void destroyFrag(TileObject& item, float dt);
};  

class SimpleBehavior : public IItemBehavior {
    public: 
        void onCollect(TileObject& item) override{} ;
        virtual void update(TileObject& item, float dt) override  ;
        void moveUp(TileObject& item, float dt);
};

class NormalCoinBehavior : public IItemBehavior {
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override ;
};

class SpecialCoinBehavior : public IItemBehavior {
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override;
        void moveUp(TileObject& item, float dt) ;
};
class MushroomBehavior : public SimpleBehavior{
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override ;
        
};
class StarBehavior : public SimpleBehavior{
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override;
};
class TileObject : public TileBlock {
public:
    TileObject(int type, int row, int col);
    ~TileObject(){};
    TileItem getType();
    void createBehavior() override;
    void draw(Texture2D& background, Texture2D& object) override;
    void update(float dt) override;
    void setOn(bool on) { isOn = on; };
    friend class FragmentBehavior;
    friend class SimpleBehavior;
    friend class NormalCoinBehavior;
    friend class SpecialCoinBehavior;
    friend class MushroomBehavior;
    friend class StarBehavior;
protected:
    IItemBehavior* mBehavior = nullptr;
    
    bool isUp = false;
    bool isMoving = false;
    bool isAbsorbed = false;
};

