#pragma once

#include <raylib.h>
#include <vector>

#include "GUI/Component.hpp"

#include <iostream>

class Container: public Component {
    public:
        Container();
        ~Container();
        void pack(Component* component);
        virtual bool isSelectable();
        virtual void handle();
        virtual void draw();
        
    private:
        bool hasSelection();
        void select(std::size_t index);
        void selectNext();
        void selectPrevious();
        int mSelectedChildren = -1;
        std::vector<Component*> mChildren; 
};