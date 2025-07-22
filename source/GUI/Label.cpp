#include "GUI/Label.hpp"

Label::Label(): mFont(FontIdentifier::PressStart2P), mAlignment(Alignment::LEFT) {}

void Label::draw() {
    if (isBlink && !isDisplay) return;
    Font font = Resource::mFont.get(mFont);
    Vector2 textSize = MeasureTextEx(font, mText.c_str(), mFontSize, 0);
    Vector2 textPos = {
        mShape.x + (mShape.width - textSize.x) / 2.0f,
        mShape.y + (mShape.height - textSize.y) / 2.0f
    };
    if (mAlignment == Alignment::LEFT) {
        textPos.x = mShape.x + 10;
    } else if (mAlignment == Alignment::RIGHT) {
        textPos.x = mShape.x + mShape.width - textSize.x - 10; 
    }
    DrawTextEx(font, mText.c_str(), textPos, mFontSize, 0, mColor);
}
        
void Label::handle() {
    if (isBlink) isDisplay = !isDisplay;
}
        
bool Label::isSelectable() {
    return false;
}
void Label::changeAlignment(Alignment alignment) {
    mAlignment = alignment;
}
void Label::changeText(std::string text) {
    mText = text;
}
        
void Label::changeColor(Color color) {
    mColor = color;
}
        
void Label::changeShape(Rectangle shape) {
    mShape = shape;
}
        
void Label::changeSize(int fontSize) {
    mFontSize = fontSize;
}

void Label::changeFont(FontIdentifier id) {
    mFont = id;
}

void Label::changeBlink(bool flag) {
    isBlink = flag;
}