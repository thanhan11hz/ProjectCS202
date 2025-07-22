#pragma once

#include "Observer/Observer.hpp"

class BaseComponent {
    public:
        BaseComponent(Observer* observer = nullptr);
        void setObserver(Observer* observer);
        virtual void draw() = 0;
        virtual void update(float dt);
        virtual ~BaseComponent() = default;
    protected:
        Observer* mObserver;
};