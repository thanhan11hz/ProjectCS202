#include "State/MapEditor.hpp"
MapEditor::MapEditor(StateStack& stack): State(stack), mMode(MapEditorMode::VIEW), mPalette(Palette::NONE), hasChanges(false), selected(-1), enemy(EnemyType::NONE), tileX(0), tileY(0), showPalette(false), showGrid(true), isDropDown(false), confirm(false) {
    
    mMap = std::vector<std::vector<int>>(DEFAULT_MAP_HEIGHT, std::vector<int>(DEFAULT_MAP_WIDTH, -1));
    mEnemies = std::vector<std::vector<int>>(DEFAULT_MAP_HEIGHT, std::vector<int>(DEFAULT_MAP_WIDTH, -1));
    mItems = std::vector<std::vector<int>>(DEFAULT_MAP_HEIGHT, std::vector<int>(DEFAULT_MAP_WIDTH, -1));

    name = "CustomMap";
    setupCamera();
    
    muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer_view.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            if (IsMusicStreamPlaying(mPlayingMusic)) if (!isMute) {
                PauseMusicStream(mPlayingMusic);
                isMute = true;
            }
            else {
                ResumeMusicStream(mPlayingMusic);
                isMute = false;
            }
            else ResumeMusicStream(mPlayingMusic);
        }
    );

    Button* homeButton = new Button();
    homeButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    homeButton->changShape({1372,24,41,41});
    mContainer_view.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            if (!hasChanges) {
                requestStackPop();
                requestStackPush(StateIdentifier::MENU);
            } else {
                confirm = true;
                mMode = MapEditorMode::CONFIRM;
            }
        }
    );

    Label* header = new Label();
    header->changeShape({440,72,560,40});
    header->changeSize(40);
    header->changeText("CREATE-A-LEVEL");
    header->changeColor(BLACK);
    mContainer.pack(header);
    
    mapName = new Label();
    mapName->changeShape({180,152,1080,30});
    mapName->changeSize(30);
    mapName->changeAlignment(Alignment::CENTER);
    mapName->changeText(name);
    mapName->changeColor(BLACK);
    mContainer.pack(mapName);

    Button* next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT);
    mContainer_view.pack(next);
    next->changeCallback(
        [this]() {
            mCamera.target.x+=20;
        }
    );

    Button* previous = new Button();
    previous->changShape({21, 397, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS);
    mContainer_view.pack(previous);
    previous->changeCallback(
        [this]() {
            mCamera.target.x-=20;
        }
    );

    currentMode = new Label();
    currentMode->changeShape({23,806,530,17});
    currentMode->changeSize(17);
    currentMode->changeAlignment(Alignment::LEFT);
    currentMode->changeText("VIEWING MODE");
    currentMode->changeColor(WHITE);
    mContainer.pack(currentMode);

    subtext = new Label();
    subtext->changeShape({23,854,530,17});
    subtext->changeSize(17);
    subtext->changeAlignment(Alignment::LEFT);
    subtext->changeText("Navigate using WASD");
    subtext->changeColor(WHITE);
    mContainer.pack(subtext);

    Button* edit = new Button();
    edit->changShape({463, 812, 211, 56});
    edit->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    edit->changeText("EDIT");
    edit->changeCallback([this]() {
            mMode = MapEditorMode::EDIT;
        }
    );
    mContainer_view.pack(edit);

    Button* rename = new Button();
    rename->changShape({696, 812, 211, 56});
    rename->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    rename->changeText("RENAME");
    rename->changeCallback([this]() {
            txt->changeText(name);
            mMode = MapEditorMode::RENAME;
        }
    );
    mContainer_view.pack(rename);

    Button* reset = new Button();
    reset->changShape({929, 812, 211, 56});
    reset->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    reset->changeText("RESET");
    reset->changeCallback([this]() {
            cfReset = true;
            mMode = MapEditorMode::CONFIRM;
        }
    );
    mContainer_view.pack(reset);

    save = new Button();
    save->changShape({1162, 812, 211, 56});
    save->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    save->changeText("SAVE");
    save->changeCallback([this]() {
            saveMap();
            hasChanges = false;
        }
    );
    mContainer_view.pack(save);

    //exit without saving
    Label* cfsHeader = new Label();
    cfsHeader->changeShape({476, 325, 490, 30});
    cfsHeader->changeSize(30);
    cfsHeader->changeText("UNSAVED CHANGES!");
    cfsHeader->changeColor(WHITE);
    mContainer_confirm.pack(cfsHeader);

    Button* confirmSave = new Button();
    confirmSave->changShape({478,440,211,56});
    confirmSave->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    confirmSave->changeText("SAVE");
    confirmSave->changeCallback([this]() {
            saveMap();
            hasChanges = false;
            requestStackPop();
            requestStackPush(StateIdentifier::MENU);
        }
    );
    mContainer_confirm.pack(confirmSave);

    Button* noSave = new Button();
    noSave->changShape({751,440,211,56});
    noSave->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    noSave->changeTextColor(RED);
    noSave->changeText("DON'T SAVE");
    noSave->changeCallback([this]() {
            confirm = false;
            hasChanges = false;
            requestStackPop();
            requestStackPush(StateIdentifier::MENU);
        }
    );
    mContainer_confirm.pack(noSave);
    
    Button* cancel = new Button();
    cancel->changShape({613,544,211,56});
    cancel->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    cancel->changeTextColor(BLACK);
    cancel->changeText("CANCEL");
    cancel->changeCallback([this]() {
            confirm = false;
            mMode = MapEditorMode::VIEW;
        }
    );
    mContainer_confirm.pack(cancel);
    
    //reset confirmation
    Label* cfrHeader = new Label();
    cfrHeader->changeShape({476, 351, 490, 30});
    cfrHeader->changeColor(WHITE);
    cfrHeader->changeSize(30);
    cfrHeader->changeText("ARE YOU SURE?");
    cfrHeader->changeAlignment(Alignment::CENTER);
    mContainer_reset.pack(cfrHeader);

    Button* confirmReset = new Button();
    confirmReset->changShape({478,440,211,56});
    confirmReset->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    confirmReset->changeTextColor(RED);
    confirmReset->changeText("RESET");
    confirmReset->changeCallback([this]() {
            cfReset = false;
            selected = -1;
            mMap.clear();
            mItems.clear();
            mMap = std::vector<std::vector<int>>(DEFAULT_MAP_HEIGHT, std::vector<int>(DEFAULT_MAP_WIDTH, -1));
            mItems = std::vector<std::vector<int>>(DEFAULT_MAP_HEIGHT, std::vector<int>(DEFAULT_MAP_WIDTH, -1));
            mMode = MapEditorMode::VIEW;
        }
    );
    mContainer_reset.pack(confirmReset);

    Button* cancelReset = new Button();
    cancelReset->changShape({751,440,211,56});
    cancelReset->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    cancelReset->changeText("CANCEL");
    cancelReset->changeCallback([this]() {
            cfReset = false;
            mMode = MapEditorMode::VIEW;
        }
    );
    mContainer_reset.pack(cancelReset);

    //edit mode
    Button* pen = new Button();
    pen->changShape({929, 812, 211, 56});
    pen->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pen->changeText("PEN");
    pen->changeCallback([this]() {
            showPalette = false;
            isDropDown = false;
            mMode = MapEditorMode::PEN;
            showGrid = true;
        }
    );
    mContainer_edit.pack(pen);

    Button* eraser = new Button();
    eraser->changShape({1162, 812, 211, 56});
    eraser->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    eraser->changeText("ERASER");
    eraser->changeCallback([this]() {
            mMode = MapEditorMode::ERASE;
            showGrid = true;
        }
    );
    mContainer_edit.pack(eraser);

    display = new Button();
    display->changShape({696, 812, 211, 56});
    display->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    display->changeText("DISPLAY");
    display->changeCallback([this]() {
            showPalette = !showPalette;
            isDropDown = false;
        }
    );
    mContainer_pen.pack(display);

    pals = new Button();
    pals->changShape({929, 812, 211, 56});
    pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pals->changeText("PALETTES");
    pals->changeCallback([this]() {
            isDropDown = !isDropDown;
            showPalette = false;
        }
    );
    mContainer_pen.pack(pals);

    Button* eraserPen = new Button();
    eraserPen->changShape({1162, 812, 211, 56});
    eraserPen->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    eraserPen->changeText("ERASER");
    eraserPen->changeCallback([this]() {
            showPalette = false;
            isDropDown = false;
            mMode = MapEditorMode::ERASE;
        }
    );
    mContainer_pen.pack(eraserPen);

    Button* pal_items = new Button(); 
    pal_items->changShape({920, 291, 211, 56});
    pal_items->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_items->changeText("ITEMS");
    pal_items->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette != Palette::ITEMS) selected = -1;
            mPalette = Palette::ITEMS;
        }
    );
    mContainer_dropdown.pack(pal_items);

    Button* pal_fol1 = new Button(); 
    pal_fol1->changShape({920, 372, 211, 56});
    pal_fol1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_fol1->changeText("FOLIAGE1");
    pal_fol1->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette == Palette::ITEMS || mPalette == Palette::ENEMIES) selected = -1;
            mPalette = Palette::FOLIAGE1;
        }
    );
    mContainer_dropdown.pack(pal_fol1);

    Button* pal_fol2 = new Button(); 
    pal_fol2->changShape({920, 453, 211, 56});
    pal_fol2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_fol2->changeText("FOLIAGE2");
    pal_fol2->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette == Palette::ITEMS || mPalette == Palette::ENEMIES) selected = -1;
            mPalette = Palette::FOLIAGE2;
        }
    );
    mContainer_dropdown.pack(pal_fol2);

    Button* pal_coins = new Button(); 
    pal_coins->changShape({920, 534, 211, 56});
    pal_coins->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_coins->changeText("COINS");
    pal_coins->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette == Palette::ITEMS || mPalette == Palette::ENEMIES) selected = -1;
            mPalette = Palette::COINS;
        }
    );
    mContainer_dropdown.pack(pal_coins);

    Button* pal_blocks = new Button(); 
    pal_blocks->changShape({920, 615, 211, 56});
    pal_blocks->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_blocks->changeText("BLOCKS");
    pal_blocks->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette == Palette::ITEMS || mPalette == Palette::ENEMIES) selected = -1;
            mPalette = Palette::BLOCKS;
        }
    );
    mContainer_dropdown.pack(pal_blocks);

    Button* pal_clr = new Button(); 
    pal_clr->changShape({920, 696, 211, 56});
    pal_clr->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_clr->changeText("CLEAR");
    pal_clr->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            selected = -1;
            mPalette = Palette::NONE;
        }
    );
    mContainer_dropdown.pack(pal_clr);

    Button* pal_enemy = new Button(); 
    pal_enemy->changShape({920, 210, 211, 56});
    pal_enemy->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_enemy->changeText("ENEMY");
    pal_enemy->changeCallback([this]() {
            selectedTile = {0,0,0,0};
            isDropDown = false;
            if (mPalette != Palette::ENEMIES) selected = -1;
            enemy = EnemyType::NONE;
            mPalette = Palette::ENEMIES;
    });
    mContainer_dropdown.pack(pal_enemy);

    Button* grid = new Button();
    grid->changShape({929, 812, 211, 56});
    grid->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    grid->changeText("GRID");
    grid->changeCallback([this]() {
            showGrid = !showGrid;
        }
    );
    mContainer_erase.pack(grid); 

    Button* penEraser = new Button();
    penEraser->changShape({1162, 812, 211, 56});
    penEraser->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    penEraser->changeText("PEN");
    penEraser->changeCallback([this]() {
            showGrid = true;
            mMode = MapEditorMode::PEN;
        }
    );
    mContainer_erase.pack(penEraser);

    //rename
    Label* renameHeader = new Label();
    renameHeader->changeShape({440, 351, 561, 30});
    renameHeader->changeSize(30);
    renameHeader->changeText("RENAME");
    renameHeader->changeAlignment(Alignment::CENTER);
    renameHeader->changeColor(WHITE);
    mContainer_rename.pack(renameHeader);
    
    txt = new TextBox();
    txt->changeShape({489,408,460,42});
    txt->changeMaxLength(35);
    txt->changeText(name);
    txt->changeFontSize(17);
    mContainer_rename.pack(txt);

    Button* renameConfirm = new Button();
    renameConfirm->changShape({613,544,211,56});
    renameConfirm->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    renameConfirm->changeTextColor(BLACK);
    renameConfirm->changeText("CONFIRM");
    renameConfirm->changeCallback([this]() {
            name = txt->getText();
            mapName->changeText(name);
            mMode = MapEditorMode::VIEW;
        }
    );
    mContainer_rename.pack(renameConfirm);

    dropdownRect = {884,167,284,629};
    paletteRects = {
        {Palette::BLOCKS,   {337, 388, 1104, 384}},
        {Palette::FOLIAGE1, {240, 196, 1200, 576}},
        {Palette::FOLIAGE2, {912, 388, 528, 384}},
        {Palette::COINS,    {1248, 388, 192, 384}},
        {Palette::ITEMS,    {1200, 340, 240, 432}},
        {Palette::ENEMIES,  {960, 676, 480, 96}}
    };
}

void MapEditor::setupCamera() {
    mCamera = { 0 };
    mCamera.zoom = 2.0f;
    mCamera.target = {0,0};
    mCamera.offset = {workspaceWidth/8,workspaceHeight/2};
}

void MapEditor::cameraHandle() {
    if (IsKeyDown(KEY_A)) mCamera.target.x -= 5;
    if (IsKeyDown(KEY_D)) mCamera.target.x += 5;
    if (IsKeyDown(KEY_W)) mCamera.target.y -= 5;
    if (IsKeyDown(KEY_S)) mCamera.target.y += 5;
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        mCamera.zoom += wheel * 0.1f;
        if (mCamera.zoom < 1.0f) mCamera.zoom = 1.0f;
        if (mCamera.zoom > 10.0f) mCamera.zoom = 10.0f;
    }
    if (mCamera.target.x < -workspaceWidth/2) mCamera.target.x = -workspaceWidth/2;
    if (mCamera.target.x > workspaceWidth/2) mCamera.target.x = workspaceWidth/2;
    if (mCamera.target.y < 0) mCamera.target.y = 0;
    if (mCamera.target.y > workspaceHeight/2) mCamera.target.y = workspaceHeight/2;
}

bool MapEditor::paletteHandle() {
    Vector2 mouse = GetMousePosition();
    if (mMode == MapEditorMode::PEN && showPalette && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int tilesPerRow = getTilesPerRow();
        if (CheckCollisionPointRec(mouse, palRect)) {
            
            int localX = mouse.x - palRect.x;
            int localY = mouse.y - palRect.y;

            int tX = localX / SCALED_TILE_SIZE;
            int tY = localY / SCALED_TILE_SIZE;

            if (mPalette != Palette::ENEMIES) {
                selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y+tY*SCALED_TILE_SIZE, SCALED_TILE_SIZE, SCALED_TILE_SIZE};
                int index = tY * tilesPerRow + tX;
                if (mPalette == Palette::COINS) {
                    index += 23;
                    if (index >= 52 && index <=54) index += 128;
                    if (index >= 110 && index <= 112) index += 79;
                }
                else if (mPalette == Palette::FOLIAGE1) index += 8*tilesPerRow;
                else if (mPalette == Palette::FOLIAGE2) index += 20*tilesPerRow;
                selected = index;
            } else {
                switch (tX) {
                    case 0: 
                        enemy = EnemyType::GOOMBA;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y+SCALED_TILE_SIZE, SCALED_TILE_SIZE, SCALED_TILE_SIZE};
                        selected = 0;
                        break;
                    case 1: 
                        enemy = EnemyType::GOOMBA_BLUE;
                        selected = 18;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y+SCALED_TILE_SIZE, SCALED_TILE_SIZE, SCALED_TILE_SIZE};
                        break;
                    case 2: 
                        enemy = EnemyType::KOOPA_GREEN;
                        selected = 5;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE, SCALED_TILE_SIZE*2}; 
                        break;
                    case 3: 
                        enemy = EnemyType::KOOPA_RED;
                        selected = 41;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE, SCALED_TILE_SIZE*2}; 
                        break;
                    case 4: 
                        enemy = EnemyType::KOOPA_BLUE;
                        selected = 77;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE, SCALED_TILE_SIZE*2};  
                        break;
                    case 5: 
                        enemy = EnemyType::PIRANHA_GREEN;
                        selected = 48;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE, SCALED_TILE_SIZE*2};  
                        break;
                    case 6: 
                        enemy = EnemyType::PIRANHA_BLUE; 
                        selected = 84;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE, SCALED_TILE_SIZE*2}; 
                        break;
                    case 7: 
                    case 8: 
                        enemy = EnemyType::BOWSER;
                        selected = 116;
                        selectedTile = {palRect.x+7*SCALED_TILE_SIZE, palRect.y, SCALED_TILE_SIZE*2, SCALED_TILE_SIZE*2}; 
                        break;
                    case 9: 
                        enemy = EnemyType::FIRE;
                        selected = 330;
                        selectedTile = {palRect.x+tX*SCALED_TILE_SIZE, palRect.y+SCALED_TILE_SIZE, SCALED_TILE_SIZE, SCALED_TILE_SIZE};
                        break;
                }
                
            }
            return true;
        }
    }
    return false;
}

void MapEditor::stampingHandle() {
    BeginScissorMode(0,0,workspaceWidth,workspaceHeight);
    BeginMode2D(mCamera);
    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), mCamera);
    if (mMode != MapEditorMode::RENAME) cameraHandle();
    tileX = mouse.x / TILE_SIZE;
    tileY = mouse.y / TILE_SIZE;

    bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY < mMap.size();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds && mMode == MapEditorMode::PEN && !isDropDown) {
        if (mPalette == Palette::ITEMS && selected != 292) mItems[tileY][tileX] = selected;
        else if (mPalette == Palette::COINS && ((selected >= 180 && selected <= 182) || (selected >= 189 && selected <= 190))) mItems[tileY][tileX] = selected;
        else if (mPalette == Palette::ENEMIES) {
            switch (enemy) {
                case EnemyType::GOOMBA:
                case EnemyType::GOOMBA_BLUE:
                case EnemyType::FIRE:
                    mEnemies[tileY][tileX] = selected;
                    break;
                case EnemyType::KOOPA_GREEN:
                case EnemyType::KOOPA_RED:
                case EnemyType::KOOPA_BLUE:
                case EnemyType::PIRANHA_GREEN:
                case EnemyType::PIRANHA_BLUE:
                    if (tileY+1 <= DEFAULT_MAP_HEIGHT) {
                        mEnemies[tileY][tileX] = selected;
                        mEnemies[tileY+1][tileX] = selected+TILES_PER_ROW_ENEMIES;
                    }
                    break;
                case EnemyType::BOWSER:
                    if (tileY+1 <= DEFAULT_MAP_HEIGHT && tileX+1 <= DEFAULT_MAP_WIDTH){
                        mEnemies[tileY][tileX] = selected;
                        mEnemies[tileY+1][tileX] = selected+TILES_PER_ROW_ENEMIES;
                        mEnemies[tileY][tileX+1] = selected+1;
                        mEnemies[tileY+1][tileX+1] = selected+TILES_PER_ROW_ENEMIES+1;
                    }
                    break;
            }
        }
        else mMap[tileY][tileX] = selected;
        hasChanges = true;
    } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds && mMode == MapEditorMode::ERASE) {
        mMap[tileY][tileX] = -1;
        mEnemies[tileY][tileX] = -1;
        mItems[tileY][tileX] = -1;
        hasChanges = true;
    }
    EndMode2D();
    EndScissorMode();
}

void MapEditor::drawUI() {
    Texture2D bricksTexture = Resource::mTexture.get(TextureIdentifier::BRICKS_TEXTURE);
    DrawTexture(bricksTexture, 0, 772, WHITE);
    mContainer.draw();
    switch (mMode) {
        case MapEditorMode::VIEW:
            mContainer_view.draw();
            break;
        case MapEditorMode::EDIT:
            mContainer_edit.draw();
            break;
        case MapEditorMode::PEN:
            mContainer_pen.draw();
            if (isDropDown) {
                DrawRectangleRec(dropdownRect, {113,67,25,200});
                DrawRectangleLinesEx(dropdownRect, 5.0f, BLACK);
                mContainer_dropdown.draw();
            }
            break;
        case MapEditorMode::ERASE:
            mContainer_erase.draw();
            break;
        case MapEditorMode::CONFIRM:
        {    
            //std::cout << "cfmode" << std::endl;
            DrawRectangle(0,0,1440,900,Fade({83,83,83,255}, 0.7f));
            Texture2D cfbox = Resource::mTexture.get(TextureIdentifier::CONFIRM_BOX);
            DrawTexture(cfbox, 426, 257, WHITE);
            if (!cfReset) mContainer_confirm.draw();
            else mContainer_reset.draw();
            break;
        }
        case MapEditorMode::RENAME: {
            DrawRectangle(0,0,1440,900,Fade({83,83,83,255}, 0.7f));
            Texture2D cfbox = Resource::mTexture.get(TextureIdentifier::CONFIRM_BOX);
            DrawTexture(cfbox, 426, 257, WHITE);
            mContainer_rename.draw();
            break;
        }
    }
    
}

void MapEditor::drawMapPreview() {
    Texture2D brickTiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D items = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);
    Texture2D enemies = Resource::mTexture.get(TextureIdentifier::TILE_SET_ENEMIES);

    BeginScissorMode(0,0,workspaceWidth,workspaceHeight);
    BeginMode2D(mCamera);
    for (int y = 0; y < mMap.size(); ++y) {
        for (int x = 0; x < mMap[y].size(); ++x) {
            int tiles = TILES_PER_ROW_BLOCKS;
            Texture2D tileset = brickTiles;
            int tileID = mMap[y][x];
            if (tileID < 0) continue;
            if (tileID == 292) {
                tiles = TILES_PER_ROW_ITEMS; 
                tileset = items;   
            }
            int tx = tileID % tiles;
            int ty = tileID / tiles;
            Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
            Vector2 dest = { float(x * TILE_SIZE), float(y * TILE_SIZE) };
            DrawTextureRec(tileset, srcRect, dest, WHITE);
        }
    }

    for (int y = 0; y < mItems.size(); ++y) {
        for (int x = 0; x < mItems[y].size(); ++x) {
            int tileID = mItems[y][x];
            if (tileID < 0) continue;
            ///std::cout << "Drawing item with tileID" << tileID << std::endl;
            int tx = tileID % TILES_PER_ROW_ITEMS;
            int ty = tileID / TILES_PER_ROW_ITEMS;
            Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
            Vector2 dest = { float(x * TILE_SIZE), float(y * TILE_SIZE) };
            DrawTextureRec(items, srcRect, dest, WHITE);
        }
    }

    for (int y = 0; y < mEnemies.size(); ++y) {
        for (int x = 0; x < mEnemies[y].size(); ++x) {
            int tiles = TILES_PER_ROW_ENEMIES;
            Texture2D tileset = enemies;
            int tileID = mEnemies[y][x];
            if (tileID < 0) continue;
            if (tileID == 330) {
                tiles = TILES_PER_ROW_ITEMS;
                tileset = items;
            }
            int tx = tileID % tiles;
            int ty = tileID / tiles;
            Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
            Vector2 dest = { float(x * TILE_SIZE), float(y * TILE_SIZE) };
            DrawTextureRec(tileset, srcRect, dest, WHITE);
        }
    }

    //ghost preview at cursor
    if (mMode == MapEditorMode::PEN && selected >= 0) {
        if (mPalette != Palette::ENEMIES) {
            Texture2D tileset = brickTiles;
            int tilesPerRow = TILES_PER_ROW_BLOCKS;
            if (mPalette == Palette::ITEMS) {
                tileset = items;
                tilesPerRow = TILES_PER_ROW_ITEMS;
            } else if (mPalette == Palette::COINS && ((selected >= 180 && selected <= 182) || (selected >= 189 && selected <= 190))) {
                tileset = items;
                tilesPerRow = TILES_PER_ROW_ITEMS;
            }
            int tx = selected % tilesPerRow;
            int ty = selected / tilesPerRow;
            Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
            Vector2 dest = { float(tileX * TILE_SIZE), float(tileY * TILE_SIZE) };
            DrawTextureRec(tileset, srcRect, dest, Fade(WHITE, 0.5f)); 

            bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY < mMap.size();
            if (!inBounds) DrawRectangleRec({float(tileX*TILE_SIZE), float(tileY*TILE_SIZE), TILE_SIZE, TILE_SIZE}, Fade(RED, 0.8f));
        } else {
            switch (enemy) {
                case EnemyType::GOOMBA:
                case EnemyType::GOOMBA_BLUE:
                {
                    int tx = selected % TILES_PER_ROW_ENEMIES;
                    int ty = selected / TILES_PER_ROW_ENEMIES;
                    Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
                    Vector2 dest = { float(tileX * TILE_SIZE), float(tileY * TILE_SIZE) };
                    DrawTextureRec(enemies, srcRect, dest, Fade(WHITE, 0.5f)); 

                    bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY < mMap.size();
                    if (!inBounds) DrawRectangleRec({float(tileX*TILE_SIZE), float(tileY*TILE_SIZE), TILE_SIZE, TILE_SIZE}, Fade(RED, 0.8f));
                    break;
                }
                case EnemyType::FIRE: 
                {
                    int tx = selected % TILES_PER_ROW_ITEMS;
                    int ty = selected / TILES_PER_ROW_ITEMS;
                    Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE };
                    Vector2 dest = { float(tileX * TILE_SIZE), float(tileY * TILE_SIZE) };
                    DrawTextureRec(items, srcRect, dest, Fade(WHITE, 0.5f)); 

                    bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY < mMap.size();
                    if (!inBounds) DrawRectangleRec({float(tileX*TILE_SIZE), float(tileY*TILE_SIZE), TILE_SIZE, TILE_SIZE}, Fade(RED, 0.8f));
                    break;
                }
                case EnemyType::KOOPA_GREEN:
                case EnemyType::KOOPA_RED:
                case EnemyType::KOOPA_BLUE:
                case EnemyType::PIRANHA_GREEN:
                case EnemyType::PIRANHA_BLUE:
                {
                    int tx = selected % TILES_PER_ROW_ENEMIES;
                    int ty = selected / TILES_PER_ROW_ENEMIES;
                    Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE, TILE_SIZE*2};
                    Vector2 dest = { float(tileX * TILE_SIZE), float(tileY * TILE_SIZE) };
                    DrawTextureRec(enemies, srcRect, dest, Fade(WHITE, 0.5f)); 

                    bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY+1 < mMap.size();
                    if (!inBounds) DrawRectangleRec({float(tileX*TILE_SIZE), float(tileY*TILE_SIZE), TILE_SIZE, TILE_SIZE*2}, Fade(RED, 0.8f));
                    break;
                }
                case EnemyType::BOWSER:
                {
                    int tx = selected % TILES_PER_ROW_ENEMIES;
                    int ty = selected / TILES_PER_ROW_ENEMIES;
                    Rectangle srcRect = { float(tx * TILE_SIZE), float(ty * TILE_SIZE), TILE_SIZE*2, TILE_SIZE*2};
                    Vector2 dest = { float(tileX * TILE_SIZE), float(tileY * TILE_SIZE) };
                    DrawTextureRec(enemies, srcRect, dest, Fade(WHITE, 0.5f)); 

                    bool inBounds = tileX >= 0 && tileX+1 < mMap[0].size() && tileY >= 0 && tileY+1 < mMap.size();
                    if (!inBounds) DrawRectangleRec({float(tileX*TILE_SIZE), float(tileY*TILE_SIZE), TILE_SIZE*2, TILE_SIZE*2}, Fade(RED, 0.8f));
                    break;
                }    
            }
        }
    } else if (mMode == MapEditorMode::ERASE) {
        DrawRectangle(tileX*TILE_SIZE, tileY*TILE_SIZE, TILE_SIZE, TILE_SIZE, Fade(BLACK, 0.2f));
    }

    if (showGrid) drawGrid(0, 0, mMap[0].size(), mMap.size(), TILE_SIZE);
    EndMode2D();
    EndScissorMode();
}

void MapEditor::drawPalette() {
    Texture2D pal = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);;
    if (mPalette != Palette::ITEMS) pal = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);

    if (showPalette) {
        DrawRectangleRec(palRect, Fade({113, 67, 25}, 0.7f));
        
        Texture2D toDraw;
        switch (mPalette) {
            case Palette::ITEMS:
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL1);
                DrawTexture(toDraw, 1200, 340, WHITE);
                break;
            case Palette::FOLIAGE1:
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL2);
                DrawTexture(toDraw, 240, 196, WHITE);
                break;
            case Palette::FOLIAGE2:
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL3);
                DrawTexture(toDraw, 912, 388, WHITE);
                break;
            case Palette::COINS:
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL4);
                DrawTexture(toDraw, 1248, 388, WHITE);
                break;
            case Palette::BLOCKS: {
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL5);
                DrawTexture(toDraw, 337, 388, WHITE);
                break;
            }
            case Palette::ENEMIES: {
                toDraw = Resource::mTexture.get(TextureIdentifier::PAL6);
                DrawTexture(toDraw, 960, 676, WHITE);
                break;
            }
        }
        
        if (selected >= 0) {
            DrawRectangleRec(selectedTile, Fade(YELLOW, 0.4f));
            DrawRectangleLinesEx(selectedTile, 2.0f, BLACK);
        }

    }
}

void MapEditor::drawGrid(int startX, int startY, int width, int height, int tileSize, Color lineColor) {
    for (int y = startY; y <= height; y++) {
        //if (y % 10 == 0) lineColor = Fade(DARKGRAY, 0.8f);
        DrawLine(startX, y * tileSize, width * tileSize, y * tileSize, lineColor);
    }
    for (int x = startX; x <= width; x++) {
        //if (x % 10 == 0) lineColor = Fade(DARKGRAY, 0.8f);
        DrawLine(x * tileSize, startY, x * tileSize, height * tileSize, lineColor);
    }
}

int MapEditor::getTilesPerRow() {
    if (mPalette == Palette::ITEMS) return TILES_PER_ROW_ITEMS;
    else if (mPalette == Palette::ENEMIES) return TILES_PER_ROW_ENEMIES;
    return TILES_PER_ROW_BLOCKS;
}
 
void MapEditor::saveMap() {
    int order = (createdCount >= 4 ? 3 : createdCount);
    std::filesystem::path exePath = std::filesystem::current_path();
    std::filesystem::path customDir = exePath / "resource" / "Map" / "Custom";

    std::string prefix = "0" + std::to_string(order+1);
    std::string dirName = prefix + "_"+ name;

    //always overwrite 4th map if overflow
    if (createdCount < 4) std::filesystem::create_directory(customDir / dirName);
    else {
        for (const auto& entry : std::filesystem::directory_iterator(customDir)) {
            std::string folderName = entry.path().filename().string();
        if (entry.is_directory() && folderName != "EmptyMapTemplate" && folderName[1] == '4') {
            std::filesystem::path original_path = entry.path();
            std::filesystem::path new_path = customDir / dirName;
            std::filesystem::rename(original_path, new_path);
        }
    }
    }

    std::filesystem::path directory = customDir / dirName;
    std::string extension = ".csv";
    std::filesystem::path filePath1 = directory / (prefix + "_Main" + extension);
    std::filesystem::path filePath2 = directory / (prefix + "_Items" + extension);
    std::filesystem::path filePath3 = directory / (prefix + "_Background" + extension);
    std::filesystem::path filePath4 = directory / (prefix + "_Enemies" + extension);

    std::ofstream outFile(filePath1);
    if (!outFile.is_open()) {
        std::cerr << "Cannot access output file at " << filePath1 << std::endl;
        return;
    }

    // Save mMap data
    for (const auto& row : mMap) {
        for (int i = 0; i < row.size()-1; i++) {
            outFile << row[i] << ",";
        }
        outFile << row[row.size()-1] << "\n";
    }
    outFile.close();

    outFile.open(filePath2);
    if (!outFile.is_open()) {
        std::cerr << "Cannot access output file at" << filePath2 << std::endl;
        return;
    }

    // Save mItem data
    for (const auto& row : mItems) {
        for (int i = 0; i < row.size()-1; i++) {
            outFile << row[i] << ",";
        }
        outFile << row[row.size()-1] << "\n";
    }
    outFile.close();

    outFile.open(filePath3);
    if (!outFile.is_open()) {
        std::cerr << "Cannot access output file at" << filePath3 << std::endl;
        return;
    }

    // Generate backgrond data
    for (const auto& row : mItems) {
        for (int i = 0; i < row.size()-1; i++) {
            outFile << 612 << ",";
        }
        outFile << 612 << "\n";
    }
    outFile.close();


    outFile.open(filePath4);
    if (!outFile.is_open()) {
        std::cerr << "Cannot access output file at" << filePath4 << std::endl;
        return;
    }

    for (const auto& row : mEnemies) {
        for (int i = 0; i < row.size()-1; i++) {
            outFile << row[i] << ",";
        }
        outFile << row[row.size()-1] << "\n";
    }
    outFile.close();

    std::string loadmap = directory.string();
    ///std::cout << "Loading map from " << loadmap << std::endl;
    mWorld.loadMap(loadmap);

    createdCount++;
}

bool MapEditor::handle() {
    if (IsKeyPressed(mFunctionKey[Action::MUTE]) && mMode != MapEditorMode::RENAME) {
        if (!isMute) {
            PauseMusicStream(mPlayingMusic);
            isMute = true;
        }
        else {
            ResumeMusicStream(mPlayingMusic);
            isMute = false;
        }
    }
    switch (mMode) {
        case MapEditorMode::VIEW:
            mContainer.handle();
            mContainer_view.handle();
            break;
        case MapEditorMode::EDIT:
            mContainer.handle();
            mContainer_edit.handle();
            break;
        case MapEditorMode::PEN:
            mContainer_pen.handle();
            if (isDropDown) mContainer_dropdown.handle();
            break;
        case MapEditorMode::ERASE:
            mContainer_erase.handle();
            break;
        case MapEditorMode::CONFIRM:
            if (!cfReset) mContainer_confirm.handle();
            else mContainer_reset.handle();
            break;
        case MapEditorMode::RENAME:
            mContainer_rename.handle();
            break;
    }
    Vector2 mouse = GetMousePosition();
    if (!isDropDown) {
        if (showPalette) {
            bool handleCheck = paletteHandle();
            if (!handleCheck && !CheckCollisionPointRec(mouse, palRect)) stampingHandle();
        } else if (!isDropDown)  {
            stampingHandle();
        }  
    }
    if ((mMode == MapEditorMode::PEN || mMode == MapEditorMode::ERASE) && IsKeyPressed(KEY_B)) {
        mMode = MapEditorMode::EDIT;
        showPalette = false;
        isDropDown = false;
    }
    if (mMode == MapEditorMode::EDIT && IsKeyPressed(KEY_B)) mMode = MapEditorMode::VIEW;
    return false;
}

bool MapEditor::update(float dt) {
    if (IsMusicStreamPlaying(mPlayingMusic)) muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    else muteButton->changeTexture(TextureIdentifier::SOUND_OFF);
    switch (mMode) {
        case MapEditorMode::VIEW:
            currentMode->changeText("VIEWING MODE");
            subtext->changeText("Navigate using WASD");
            break;
        case MapEditorMode::EDIT:
            currentMode->changeText("EDIT MODE");
            subtext->changeText("PRESS B TO EXIT EDIT MODE");
            break;
        case MapEditorMode::ERASE:
            if (showGrid) currentMode->changeText("EDIT MODE - ERASER | GRID: ON");
            else currentMode->changeText("EDIT MODE - ERASER | GRID: OFF");
            subtext->changeText("PRESS B TO EXIT ERASER MODE");
            break;
        case MapEditorMode::PEN:
            if (mPalette == Palette::NONE) currentMode->changeText("EDIT MODE - PEN | PALETTE: NONE");
            else if (mPalette == Palette::BLOCKS) currentMode->changeText("EDIT MODE - PEN | PALETTE: BLOCKS");
            else if (mPalette == Palette::FOLIAGE1) currentMode->changeText("EDIT MODE - PEN | PALETTE: FOLIAGE1");
            else if (mPalette == Palette::FOLIAGE2) currentMode->changeText("EDIT MODE - PEN | PALETTE: FOLIAGE2");
            else if (mPalette == Palette::COINS) currentMode->changeText("EDIT MODE - PEN | PALETTE: COINS");
            else if (mPalette == Palette::ITEMS) currentMode->changeText("EDIT MODE - PEN | PALETTE: ITEMS");
            else if (mPalette == Palette::ENEMIES) currentMode->changeText("EDIT MODE - PEN | PALETTE: ENEMY");
            subtext->changeText("PRESS B TO EXIT PEN MODE");
            break;
    }

    if (!hasChanges) save->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
    else save->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    display->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    if (paletteRects.count(mPalette)) {
        palRect = paletteRects[mPalette];
    }
    if (mPalette == Palette::NONE) {
        display->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
    }
    if (isDropDown) {
        pals->changeTexture(TextureIdentifier::HOVERED_BUTTON_MEDIUM); 
    }

    if (showPalette) display->changeText("HIDE");
    else display->changeText("DISPLAY");
    return false;
}

void MapEditor::draw() {
    drawMapPreview();
    drawPalette();
    drawUI();    
}
