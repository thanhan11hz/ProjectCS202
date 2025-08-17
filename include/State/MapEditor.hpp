#pragma once

#include <filesystem>
#include <fstream>
#include <map>
#include <raylib.h>
#include "State/State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/TextBox.hpp"
#include "Resource/ResourceHolder.hpp"
#include "World/World.hpp"
#include "State/MapEditorTypes.hpp"

class MapEditor : public State {
    public:
        MapEditor(StateStack& stack);

    private:
        virtual void draw();
        void drawUI();
        void drawMapPreview();
        void drawPalette(); 

        virtual bool handle();
        void cameraHandle();
        bool paletteHandle();
        void stampingHandle();

        virtual bool update(float dt);
        void setupCamera();
        
        //Map data
        Camera2D mCamera;
        int tileX;
        int tileY;
        int selected;
        std::vector<std::vector<int>> mMap;
        std::vector<std::vector<int>> mItems;
        std::vector<std::vector<int>> mEnemies;
        void drawGrid(int startX, int startY, int width, int height, int tileSize, Color lineColor = Fade(GRAY, 0.5f));
        void saveMap();
        int getTilesPerRow();

        //Metadata                
        std::string name;
        MapEditorMode mMode;
        EnemyType enemy;
        Palette mPalette;
        std::map<Palette, Rectangle> paletteRects;
        bool showPalette;
        bool isDropDown;
        bool showGrid;
        bool hasChanges;
        bool confirm;
        bool cfReset;

        //UI Elements
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
};

