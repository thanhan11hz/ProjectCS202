#pragma once

#include "Entity/Mario.hpp"

class Luigi : public Mario {
public:
    Luigi();
    void draw() override;
    void update(float dt) override;
    void startJump() override;
    void setAction(Action action) override;
};