#pragma once

#include <raylib.h>
#include <string>
#include <functional>

#include "GUI/Component.hpp"
#include "Global.hpp"

class Button : public Component {
    public:
        
        explicit Button();
        virtual bool isSelectable();
        virtual void handle();
        virtual void draw();
        void changeTexture(TextureIdentifier id);
        void changShape(Rectangle shape);
        void changeCallback(std::function<void()> callback);
        void changeToggle(bool flag);
        
    private:
        std::function<void()> mCallback;
        Rectangle mShape;
        TextureIdentifier mID;
        bool mIsToggle = false;
};