#pragma once

#include <memory>
#include <vector>
#include <string>

class BaseComponent;

class Mediator {
    public:
        Mediator();
    private:
        std::vector<std::unique_ptr<BaseComponent*>> mComponent;
        void notify(std::string& event);
        void update();
        void draw();
};