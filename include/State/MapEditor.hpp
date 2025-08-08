#pragma once

#include <filesystem>
#include <fstream>
#include <raylib.h>
#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/TextBox.hpp"
#include "Resource/ResourceHolder.hpp"
#include "World/World.hpp"

enum class MapEditorMode {
    SELECTION,
    VIEW,
    EDIT,
    PEN,
    ERASE,
    CONFIRM,
    RENAME
};

enum class Palette {
    NONE,
    BLOCKS,
    COINS,
    FOLIAGE1,
    FOLIAGE2,
    ITEMS,
    GOOMBA
};

const int TILES_PER_ROW_BLOCKS = 29;
const int TILES_PER_ROW_ITEMS = 36; 
const int TILES_PER_ROW_ENEMIES = 18; 
const int DEFAULT_MAP_HEIGHT = 19;
const int DEFAULT_MAP_WIDTH = 30;
const int TILE_SIZE = 16;
const int SCALED_TILE_SIZE = 48;
const int workspaceWidth = 1440;
const int workspaceHeight = 762; 

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
        void drawGrid(int startX, int startY, int width, int height, int tileSize, Color lineColor = Fade(GRAY, 0.5f));
        void createMap();
        int getTilesPerRow();

        std::vector<std::vector<int>> mMap;
        std::vector<std::vector<int>> mItems;
        std::vector<std::vector<int>> mEnemies;
        void saveMap();
                
        std::string name;
        MapEditorMode mMode;
        Palette mPalette;
        bool showPalette;
        bool isDropDown;
        bool showGrid;

        bool hasChanges;
        bool confirm;
        bool cfReset;

        Label* currentMode;
        Label* subtext;
        Label* mapName;
        Button* save;
        Button* pals;
        Button* display;
        Button* muteButton;
        TextBox* txt;
        Rectangle dropdownRect;
        Rectangle palRect;
        Rectangle selectedTile;

        Container mContainer;
        Container mContainer_selection;
        Container mContainer_view;
        Container mContainer_edit;
        Container mContainer_pen;
        Container mContainer_erase;
        Container mContainer_dropdown;
        Container mContainer_confirm;
        Container mContainer_reset;
        Container mContainer_rename;

        Camera2D mCamera;
        int tileX;
        int tileY;
        int selected;
        
};