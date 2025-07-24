#pragma once

#include <filesystem>
#include <fstream>
#include <raylib.h>
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Resource/ResourceHolder.hpp"

enum class MapEditorMode {
    SELECTION,
    VIEW,
    EDIT,
    PEN,
    ERASE,
    CONFIRM,
    RENAME
}

enum class Palette {
    NONE,
    BLOCKS,
    COINS,
    FOLIAGE1,
    FOLIAGE2,
    ITEMS
}

const int TILE_SIZE = 16;
const int SCALED_TILE_SIZE = 48;
const int workspaceWidth = 1440;
const int workspaceHeight = 750; 

class MapEditor : public State {
    public:
        MapEditor(StateStack& stack);
    private:
        virtual void draw();
        virtual bool handle();
        virtual bool update(float dt);
        
        void setupCamera();
        void cameraHandle();
        void paletteHandle();
        void stampingHandle();

        void drawUI();
        void drawMapPreview();
        void drawPalette();
        void drawGrid();
        void initMap(const string& name);
        int getTilesPerRow();

        std::vector<std::vector<int>> mMap;
        std::vector<std::vector<int>> mItems;

        MapEditorMode mMode;
        Palette mPalette;
        bool isShowPal;
        bool isDropDown;
        
        Label* currentMode;
        Label* subtext;
        Button* save;
        Button* pals;
        Button* display;
        Container mContainer;
        Container mContainer_selection;
        Container mContainer_view;
        Container mContainer_edit;
        Container mContainer_pen;
        Container mContainer_erase;
        Container mContainer_dropdown;
        Container mContainer_confirm;
        Container mContainer_rename;

        Camera2D mCamera;
        int tileX;
        int tileY;
        Rectangle palRect;
        Rectangle selectedTile;
        int palX;
        int palY;
        int selected;
        bool hasChanges;
        bool showPalette;
        bool showGrid;
};