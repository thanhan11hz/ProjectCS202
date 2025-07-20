#include "GUI/Button.hpp"

Button::Button() : mCallback(), mIsToggle(false) {}

bool Button::isSelectable() {
    return true;
}
        
void Button::handle() {
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, mShape)) {
        select();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mCallback();
        }
    } else {
        deselect();
    }
}
        
void Button::changeTexture(TextureIdentifier id) {
    mID = id;
}
        
void Button::changShape(Rectangle shape) {
    mShape = shape;
}
        
void Button::changeCallback(std::function<void()> callback) {
    mCallback = callback;
}
        
void Button::changeToggle(bool flag) {
    mIsToggle = flag;
}

void Button::draw() {
    Color color = WHITE;
    if (mIsSelected) color = Fade(color,0.9);
    Texture2D& texture = Resource::mTexture.get(mID);
    DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, mShape, {0, 0}, 0.0f, color);
}