#include "GUI/Button.hpp"
#include <iostream>
Button::Button() : mCallback(), mIsToggle(false), mFontSize(17), mColor(BLACK) {
    changeTexture(TextureIdentifier::ACTIVE_BUTTON);
}

bool Button::isSelectable() {
    return true;
}
        
void Button::handle() {
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, mShape)) {
        select();
        // if (mID == TextureIdentifier::ACTIVE_BUTTON) changeTexture(TextureIdentifier::HOVERED_BUTTON);
        // else if (mID == TextureIdentifier::ACTIVE_BUTTON_MEDIUM) changeTexture(TextureIdentifier::HOVERED_BUTTON_MEDIUM);
        // else if (mID == TextureIdentifier::ACTIVE_BUTTON_SMALL) changeTexture(TextureIdentifier::HOVERED_BUTTON_SMALL);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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

void Button::changeText(const std::string& text) {
    mText = text;
}
void Button::changeTextSize(int size) {
    mFontSize = size;
}
void Button::changeTextColor(Color color) {
    mColor = color;
}
void Button::changeFont(FontIdentifier id) {
    mFont = id;
}

void Button::draw() {
    Color color = WHITE;
    if (mIsSelected) color = Fade(color,0.9);
    Texture2D& texture = Resource::mTexture.get(mID);
    DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, mShape, {0, 0}, 0.0f, color);

    if (!mText.empty()) {
        Vector2 textSize = MeasureTextEx(Resource::mFont.get(FontIdentifier::PressStart2P), mText.c_str(), mFontSize, 0);
        Vector2 textPos = {
             mShape.x + (mShape.width - textSize.x) / 2.0f,
             mShape.y + (mShape.height - mFontSize) / 2.0f
        };
        DrawTextEx(Resource::mFont.get(FontIdentifier::PressStart2P), mText.c_str(), textPos, mFontSize, 0, mColor);
        //DrawText(mText.c_str(), static_cast<int>(textPos.x), static_cast<int>(textPos.y), mFontSize, mColor);
    }

}