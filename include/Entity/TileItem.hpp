#pragma once
#include "TileEntity.hpp"
#include <raylib.h>

class TileObject;

class IItemBehavior {
protected:
    Side side;
    Category other;
    std::string oTag;
public:
    virtual void onCollect(TileObject& item) = 0;
    virtual void update(TileObject& item, float dt) = 0;
    virtual ~IItemBehavior() = default;
    virtual void handleCollision(TileObject& item) = 0;
    virtual void setSide(Side side) { this->side = side; }
    virtual void setOther(Category other) { this->other = other; }
    virtual void setTag(std::string tag) { this->oTag = tag; }
    virtual std::string getTag(){return "";};
   
};


class FragmentBehavior : public IItemBehavior {
public: 
    void onCollect(TileObject& item) override ;
    void update(TileObject& item, float dt) override ;
    //void destroyFrag(TileObject& item, float dt);
    void handleCollision(TileObject& item) override{};
};  

class SimpleBehavior : public IItemBehavior {
    public: 
        void onCollect(TileObject& item) override{} ;
        virtual void update(TileObject& item, float dt) override;
        virtual void handleCollision(TileObject& item) override;
        void moveUp(TileObject& item, float dt);
        std::string getTag() override { return "Flower"; }
};

class NormalCoinBehavior : public IItemBehavior {
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override ;
        void handleCollision(TileObject& item) override;
        std::string getTag() override { return "Coin"; }
};

class SpecialCoinBehavior : public IItemBehavior {
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override;
        void moveUp(TileObject& item, float dt);
        void handleCollision(TileObject& item) override;
        std::string getTag() override { return "Coin"; }
};
class MushroomBehavior : public SimpleBehavior{
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override; 
        void handleCollision(TileObject& item) override;    
        std::string getTag() override {  return "Mushroom";}
};
class GreenMushroomBehavior : public MushroomBehavior{
    public:  
        std::string getTag() override {  return "GreenMushroom";}
};
class StarBehavior : public SimpleBehavior{
    public:
        void onCollect(TileObject& item) override ;
        void update(TileObject& item, float dt) override;
        void handleCollision(TileObject& item) override;
        std::string getTag() override { return "Star"; }
};
class TileObject : public TileBlock {
public:
    TileObject(int type, int col, int row);
    TileObject(const nlohmann::json& j);
    ~TileObject(){};
    TileItem getType();
    std::string getTag();
    void createBehavior() override;
    bool absorbed() const { return isAbsorbed; }
    void draw(Texture2D& background, Texture2D& object) override;
    void update(float dt) override;
    void handleCollision(Side side, Collide other) override;
    void setOn(bool on) { isOn = on; };
    bool on(){return isOn;}
    bool up() {return isUp;}
    void handleFootCollision() {
       mPhysics.setOnGround(true);
    }
    void serialize(nlohmann::json& j) override;
    std::unique_ptr<TileObject> clone() const {
        return std::make_unique<TileObject>(mType, mCol, mRow);
    }
    friend class FragmentBehavior;
    friend class SimpleBehavior;
    friend class NormalCoinBehavior;
    friend class SpecialCoinBehavior;
    friend class MushroomBehavior;
    friend class StarBehavior;
protected:
    IItemBehavior* mBehavior = nullptr;
    
    bool isUp = true;
    bool isMoving = false;
    bool isAbsorbed = false;
};

