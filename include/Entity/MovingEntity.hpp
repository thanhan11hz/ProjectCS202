#pragma once

#include "Entity/Entity.hpp"
#include "Animation.hpp"
#include "Global.hpp"

class MovingEntity : public Entity {
    public:
        MovingEntity();

        Collide mFootCollide;

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual Vector2 getSize() = 0;

        virtual void handleFootCollision(Collide other);

        virtual std::string getTag() = 0;

        void setDie(bool flag);
        bool isDie();

        void setAfterBlock(bool flag);
        bool isAfterBlock();

        virtual void serialize(nlohmann::json& j) = 0;

        virtual ~MovingEntity() = default;
    
    protected:
        Animation mAnim;

    private:
        bool mIsDie = false;
        bool afterBlock = true;
        bool mCheckStandingMovingBlock = false;
};