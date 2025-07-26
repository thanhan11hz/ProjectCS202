#include "GUI/TextBox.hpp"
#include <raylib.h>
#include <algorithm>

TextBox::TextBox() 
    : mText(""), 
      mTextColor(WHITE), 
      mBoxColor({96,96,96,255}),
      mFont(FontIdentifier::PressStart2P), 
      mFontSize(17), 
      mMaxLength(50), 
      mIsCursorVisible(true), 
      mCursorTimer(0.0f) {}

bool TextBox::isSelectable() {
    return true;
}

void TextBox::handle() {
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, mShape) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        select();
        activate();
    } else if (!CheckCollisionPointRec(mousePos, mShape) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        deactivate();
    }

    if (isActive()) {
        // Handle keyboard input
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126 && mText.length() < mMaxLength) {
                mText += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        // Handle backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !mText.empty()) {
            mText.pop_back();
        }

        if (IsKeyPressed(KEY_ENTER)) {
            deactivate();
        }

        // Update cursor blink
        mCursorTimer += GetFrameTime();
        if (mCursorTimer >= CURSOR_BLINK_TIME) {
            mIsCursorVisible = !mIsCursorVisible;
            mCursorTimer = 0.0f;
        }
    } else {
        mIsCursorVisible = true;
        mCursorTimer = 0.0f;
    }
}

void TextBox::draw() {
    // Draw background texture
    DrawRectangleRec(mShape, mBoxColor);
    Color color = WHITE;
    if (isSelected()) color = Fade(color, 0.9f);

    // Draw text
    if (!mText.empty() || isActive()) {
        Font font = Resource::mFont.get(mFont);
        Vector2 textSize = MeasureTextEx(font, mText.c_str(), mFontSize, 0);
        Vector2 textPos = {
            mShape.x + 20,
            mShape.y + (mShape.height - textSize.y) / 2.0f
        };
        DrawTextEx(font, mText.c_str(), textPos, mFontSize, 0, mTextColor);

        if (isActive() && mIsCursorVisible) {
            float cursorX = mShape.x+20;
            if (mText != "") cursorX = textPos.x + textSize.x + 2.0f; 
            float cursorY = mShape.y + (mShape.height - mFontSize) / 2.0f;
            DrawLineEx({cursorX, cursorY}, {cursorX, cursorY + mFontSize}, 3.0f, mTextColor);
        }
    }
}

void TextBox::changeShape(Rectangle shape) {
    mShape = shape;
}

void TextBox::changeText(const std::string& text) {
    mText = text.substr(0, mMaxLength);
}

void TextBox::changeBoxColor(Color color) {
    mBoxColor = color;
}
void TextBox::changeTextColor(Color color) {
    mTextColor = color;
}

void TextBox::changeFont(FontIdentifier id) {
    mFont = id;
}

void TextBox::changeFontSize(int size) {
    mFontSize = size;
}

void TextBox::changeMaxLength(int maxLength) {
    mMaxLength = std::max(1, maxLength);
    if (mText.length() > mMaxLength) {
        mText = mText.substr(0, mMaxLength);
    }
}


std::string TextBox::getText() const {
    return mText;
}