#pragma once

#include "Entity/Entity.hpp"
#include "Animation.hpp"

class MovingEntity : public Entity {
    public:
        MovingEntity();

        Collide mFootCollide;

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual Vector2 getSize() = 0;

        virtual void handleFootCollision();

        virtual std::string getTag() = 0;

        void setDie(bool flag);
        bool isDie();

        virtual ~MovingEntity() = default;
    
    protected:
        Animation mAnim;

    private:
        bool mIsDie = false;

};