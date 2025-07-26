#pragma once

#include <string>
#include <functional>

#include "GUI/Component.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"
#include "Global.hpp"

enum class Alignment {
    LEFT,
    CENTER,
    RIGHT
};

class Label: public Component {
    public:
        Label();
        virtual void draw();
        virtual void handle();
        virtual bool isSelectable();
        void changeAlignment(Alignment alignment);
        void changeText(std::string text);
        void changeColor(Color color);
        void changeShape(Rectangle shape);
        void changeFont(FontIdentifier id);
        void changeSize(int fontSize);
        void changeBlink(bool flag);
        void changeCallback(std::function<void(Label *label)> callback);
    private:
        std::string mText = "";
        FontIdentifier mFont;
        Alignment mAlignment;
        Color mColor = BLACK;
        Rectangle mShape;
        std::function<void(Label *label)> mCallback = nullptr; 
        int mFontSize = 20;
        bool isBlink = false;
        bool isDisplay = true;
};