#include "State/LevelState.hpp"

LevelState::LevelState(StateStack& stack) : State(stack) {
    Label* title = new Label();
    title->changeShape({0,0,1440,300});
    title->changeSize(80);
    title->changeText("Level");
    mContainer.pack(title);

    Button* level1 = new Button();
    level1->changShape({300, 200, 200, 50});
    level1->changeTexture(TextureIdentifier::LEVEL1);
    mContainer.pack(level1);
    Texture2D background = mContext.textures.get(TextureIdentifier::TILE_SET);
    Texture2D object = mContext.textures.get(TextureIdentifier::OBJECT);
    mMap.loadFromFile("resource\\Texture\\Map\\map1.txt");
    mMap.setTexrure(background, object);
};

void LevelState::draw() {
    Texture2D background = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    mMap.loadFromFile("resource\\Map\\map1.txt");
    mMap.drawTile(background);
    //DrawTexturePro(background, {0, 0, (float)background.width, (float)background.height}, {0, 0, (float)targetWidth, (float)targetHeight}, {0, 0}, 0.0f, WHITE);
    mContainer.draw();
}

bool LevelState::handle() {
    mContainer.handle();
    return true;
}

bool LevelState::update(float dt) {
    mMap.update(dt);
    return true;
}