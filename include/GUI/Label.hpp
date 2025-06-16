#pragma once

#include <string>

#include "GUI/Component.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "State/Context.hpp"

class Label: public Component {
    public:
        Label(Context& ctx);
        virtual void draw();
        virtual void handle();
        virtual bool isSelectable();
        void changeText(std::string text);
        void changeColor(Color color);
        void changeShape(Rectangle shape);
        void changeFont(FontIdentifier id);
        void changeSize(int fontSize);
        void changeBlink(bool flag);
    private:
        std::string mText = "";
        FontIdentifier mFont;
        Color mColor = BLACK;
        Rectangle mShape;
        Context mContext;
        int mFontSize = 20;
        bool isBlink = false;
        bool isDisplay = true;
};