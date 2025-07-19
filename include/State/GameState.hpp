#pragma once 

#include "State/State.hpp"
#include "World/World.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Container.hpp"
#include "World/TileMap.hpp"

class GameState: public State {
    public:
        GameState(StateStack& stack, Context ctx, TileMap* map);
    private:
        World mWorld;
        TileMap *mMap;
        virtual void draw();
        virtual bool update(float dt);
        virtual bool handle();
        Container mContainer;
};