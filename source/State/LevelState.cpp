#include "State/LevelState.hpp"

LevelState::LevelState(StateStack& stack, Context ctx) : State(stack,ctx) {
    Label* title = new Label(ctx);
    title->changeShape({0,0,1440,300});
    title->changeSize(80);
    title->changeText("Level");
    mContainer.pack(title);

    Button* level1 = new Button(ctx);
    level1->changShape({300, 200, 200, 50});
    level1->changeTexture(TextureIdentifier::LEVEL1);
    mContainer.pack(level1);
};

void LevelState::draw() {
    Texture2D background = mContext.textures.get(TextureIdentifier::TILE_SET_BLOCKS);
    mMap.loadFromFile("resource\\Map\\map1.txt");
    mMap.draw(background);
    //DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    mContainer.draw();
}

bool LevelState::handle() {
    mContainer.handle();
    return true;
}

bool LevelState::update(float dt) {
    return true;
}