#include "GUI/Label.hpp"

Label::Label() {}

void Label::draw() {
    if (isBlink && !isDisplay) return;
    //Font font = mContext.fonts.get(mFont);
    Font font = GetFontDefault();
    Vector2 textSize = MeasureTextEx(font, mText.c_str(), mFontSize, 10);
    Vector2 textPos = {
        mShape.x + (mShape.width - textSize.x) / 2.0f,
        mShape.y + (mShape.height - textSize.y) / 2.0f
    };
    DrawTextEx(font, mText.c_str(), textPos, mFontSize, 10, BLACK);
}
        
void Label::handle() {
    if (isBlink) isDisplay = !isDisplay;
}
        
bool Label::isSelectable() {
    return false;
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