#pragma once
#include "TileEntity.hpp"
#include <raylib.h>

class TileObject;

class IItemBehavior {
public:
    virtual void onCollect(TileObject& item) = 0;
    virtual void update(TileObject& item, float dt) = 0;
    virtual ~IItemBehavior() = default;
};


class FragmentBehavior : public IItemBehavior {
public: 
    void onCollect(TileObject& item) override ;
    void update(TileObject& item, float dt) override ;
    //void destroyFrag(TileObject& item, float dt);
};  

class FlowerBehavior : public IItemBehavior {
    public: 
        void onCollect(TileObject& item) override{} ;
        void update(TileObject& item, float dt) override  ;
        void moveUp(TileObject& item, float dt);
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
    friend class FlowerBehavior;
protected:
    IItemBehavior* mBehavior = nullptr;
    bool isOn = false;
    bool isUp = false;
    bool isMoving = false;
    bool isAbsorbed = false;
};

