#pragma once

#include <string>

#include "GUI/Component.hpp"
#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"

class TextBox : public Component {
public:
    explicit TextBox();
    virtual bool isSelectable() override;
    virtual void handle() override;
    virtual void draw() override;

    void changeShape(Rectangle shape);
    void changeText(const std::string& text);
    void changeBoxColor(Color color);
    void changeTextColor(Color color);
    void changeFont(FontIdentifier id);
    void changeFontSize(int size);
    void changeMaxLength(int maxLength);

    std::string getText() const;

private:
    std::string mText;
    Rectangle mShape;
    Color mTextColor;
    Color mBoxColor;
    FontIdentifier mFont;
    int mFontSize;
    int mMaxLength;
    bool mIsCursorVisible;
    float mCursorTimer;
    static constexpr float CURSOR_BLINK_TIME = 0.5f; // Time in seconds for cursor blink
};