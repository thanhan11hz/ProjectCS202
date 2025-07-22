#pragma once

#include "Observer/Observer.hpp"

class BaseComponent {
    public:
        BaseComponent(Mediator* mediator = nullptr);
        void setMediator(Mediator* mediator);
        virtual void draw() = 0;
        virtual void update(float dt);
        virtual ~BaseComponent() = default;
    protected:
        Mediator* mMediator;
};