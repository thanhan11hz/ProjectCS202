#pragma once

#include "Entity/MovingEntity.hpp"
#include "Global.hpp"
#include <memory>

class Enemy : public MovingEntity {
    public:
        Enemy();

        virtual void update(float dt);
        virtual void handle() = 0;
        virtual void draw() = 0;

        virtual void handleCollision(Side side, Collide other) = 0;
        virtual Vector2 getSize() = 0;

        virtual std::string getTag();

        void setActive(bool flag);
        bool isActive();
        virtual std::unique_ptr<Enemy> clone() const = 0;
        virtual ~Enemy() = default;
        template <typename Derived>
        std::unique_ptr<Enemy> cloneImpl() const {
            auto copy = std::make_unique<Derived>(static_cast<const Derived&>(*this));
            copy->mBodyCollide.setOwner(copy.get());
            copy->mFootCollide.setOwner(copy.get());
            return std::move(copy);
        }
    private:
        bool mIsActive = false;

};