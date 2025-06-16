#include "State/GameState.hpp"

GameState::GameState(StateStack& stack, Context ctx) : State(stack, ctx), mWorld(ctx) {}

void GameState::draw() {
    mWorld.draw();
    mContainer.draw();
}

bool GameState::update(float dt) {
    mWorld.update(dt);
    return true;
}

bool GameState::handle() {
    mContainer.handle();
    return true;
}