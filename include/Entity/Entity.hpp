#pragma once

#include <nlohmann/json.hpp>

#include "Entity/Physics.hpp"
#include "Entity/Collide.hpp"
#include "Serialization.hpp"
#include "Animation.hpp"
#include "Global.hpp"

class Entity {
    public:
        Entity();

        Physics mPhysics;
        Collide mBodyCollide;
        Collide mFootCollide;

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual void handleFootCollision(Collide other);
        virtual Vector2 getSize() = 0;

        virtual std::string getTag() = 0;

        virtual void serialize(nlohmann::json& j) = 0;

        virtual ~Entity() = default;

        void setDie(bool flag);
        bool isDie();

        void setAfterBlock(bool flag);
        bool isAfterBlock();
        protected:
            Animation mAnim;
        
        private:
            bool mIsDie = false;
            bool afterBlock = true;
            bool mCheckStandingMovingBlock = false;
};