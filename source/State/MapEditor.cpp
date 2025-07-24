#include "State/MapEditor.hpp"

MapEditor::MapEditor(StateStack& stack): State(stack), mMode(selection), mPalette(Palette::NONE) hasChanges(false), selected(-1), tileX(0), tileY(0), showPalette(false) {
    mMap = std::vector<std::vector<int>>(20, std::vector<int>(100, -1));
    mItems = std::vector<std::vector<int>>(20, std::vector<int>(100, -1));
    setupCamera();
    //beginEditing();
    Button* muteButton = new Button();
    muteButton->changeTexture(TextureIdentifier::SOUND_ON);
    muteButton->changShape({23,22,41,41});
    mContainer_view.pack(muteButton);
    mContainer_edit.pack(muteButton);
    muteButton->changeCallback(
        [this]() {
            //toggleMute();
        }
    );

    Button* homeButton = new Button();
    homeButton->changeTexture(TextureIdentifier::HOME_BUTTON);
    homeButton->changShape({1372,24,41,41});
    mContainer_view.pack(homeButton);
    homeButton->changeCallback(
        [this]() {
            endEditing();
            requestStackClear();
            requestStackPush(StateIdentifier::MENU);
        }
    );

    Label* header = new Label();
    header->changeShape({440,72,560,40});
    header->changeSize(40);
    header->changeText("CREATE-A-LEVEL");
    header->changeColor(BLACK);
    mContainer.pack(header);
    
    Label* mapName = new Label();
    mapName->changeShape({180,152,1080,30});
    mapName->changeSize(30);
    mapName->changeAlignment(Alignment::CENTER);
    mapName->changeText("MAP_NAME");
    mapName->changeColor(BLACK);
    mContainer.pack(header);

    Button* next = new Button();
    next->changShape({1314, 397, 105, 105});
    next->changeTexture(TextureIdentifier::NEXT);
    mContainer.pack(next);
    next->changeCallback(
        [this]() {
            camera.target.x+=5;
        }
    );

    Button* previous = new Button();
    previous->changShape({21, 397, 105, 105});
    previous->changeTexture(TextureIdentifier::PREVIOUS);
    mContainer.pack(previous);
    previous->changeCallback(
        [this]() {
            camera.target.x-=5;
        }
    );

    currentMode = new Label();
    currentMode->changeShape({23,794,530,17});
    currentMode->changeSize(17);
    currentMode->changeAlignment(Alignment::LEFT);
    currentMode->changeText("VIEWING MODE");
    currentMode->changeColor(WHITE);
    mContainer.pack(currentMode);

    subtext = new Label();
    subtext->changeShape({23,794,530,17});
    subtext->changeSize(17);
    subtext->changeAlignment(Alignment::LEFT);
    subtext->changeText("MAP NAME: ");
    subtext->changeColor(WHITE);
    mContainer.pack(subtext);

    Button* edit = new Button();
    edit->changShape({463, 800, 211, 56});
    edit->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    edit->changeText("EDIT");
    edit->changeCallback([this]() {
            mMode = MapEditorMode::EDIT;
        }
    );
    mContainer_view.pack(edit);

    Button* rename = new Button();
    rename->changShape({696, 800, 211, 56});
    rename->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    rename->changeText("RENAME");
    rename->changeCallback([this]() {
            mMode = MapEditorMode::RENAME;
        }
    );
    mContainer_view.pack(rename);

    Button* reset = new Button();
    reset->changShape({929, 800, 211, 56});
    reset->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    reset->changeText("RESET");
    reset->changeCallback([this]() {
            //gonna add a confirmation
        }
    );
    mContainer_view.pack(reset);

    save = new Button();
    save->changShape({1162, 800, 211, 56});
    save->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    save->changeText("SAVE");
    save->changeCallback([this]() {
            //gonna implement file saving later
            hasChanges = false;
        }
    );
    mContainer_view.pack(save);

    Button* pen = new Button();
    pen->changShape({929, 800, 211, 56});
    pen->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pen->changeText("PEN");
    pen->changeCallback([this]() {
            mMode = MapEditorMode::PEN;
            showGrid = true;
        }
    );
    mContainer_edit.pack(pen);

    Button* eraser = new Button();
    eraser->changShape({1162, 800, 211, 56});
    eraser->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    eraser->changeText("ERASER");
    eraser->changeCallback([this]() {
            mMode = MapEditorMode::ERASE;
            showGrid = true;
        }
    );
    mContainer_edit.pack(eraser);

    display = new Button();
    display->changShape({696, 800, 211, 56});
    display->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    display->changeText("DISPLAY");
    display->changeCallback([this]() {
            isShowPal = !isShowPal;
        }
    );
    mContainer_pen.pack(display);

    pals = new Button();
    pals->changShape({929, 800, 211, 56});
    pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pals->changeText("PALETTES");
    pals->changeCallback([this]() {
            isDropDown = true;
        }
    );
    mContainer_pen.pack(pals);

    Button* eraserPen = new Button();
    eraserPen->changShape({1162, 800, 211, 56});
    eraserPen->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    eraserPen->changeText("SAVE");
    eraserPen->changeCallback([this]() {
            mMode = MapEditorMode::ERASE;
        }
    );
    mContainer_pen.pack(eraserPen);

    Button* pal_items = new Button(); 
    pal_items->changShape({920, 279, 211, 56});
    pal_items->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_items->changeText("ITEMS");
    pal_items->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::ITEMS;
        }
    );
    mContainer_dropdown.pack(pal_items);

    Button* pal_fol1 = new Button(); 
    pal_fol1->changShape({920, 360, 211, 56});
    pal_fol1->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_fol1->changeText("FOLIAGE1");
    pal_fol1->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::FOLIAGE1;
        }
    );
    mContainer_dropdown.pack(pal_fol1);

    Button* pal_fol2 = new Button(); 
    pal_fol2->changShape({920, 441, 211, 56});
    pal_fol2->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_fol2->changeText("FOLIAGE2");
    pal_fol2->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::FOLIAGE2;
        }
    );
    mContainer_dropdown.pack(pal_fol2);

    Button* pal_coins = new Button(); 
    pal_coins->changShape({920, 522, 211, 56});
    pal_coins->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_coins->changeText("COINS");
    pal_coins->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::COINS;
        }
    );
    mContainer_dropdown.pack(pal_coins);

    Button* pal_blocks = new Button(); 
    pal_blocks->changShape({920, 603, 211, 56});
    pal_blocks->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_blocks->changeText("BLOCKS");
    pal_blocks->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::BLOCKS;
        }
    );
    mContainer_dropdown.pack(pal_blocks);

    Button* pal_clr = new Button(); 
    pal_clr->changShape({920, 441, 211, 56});
    pal_clr->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    pal_clr->changeText("CLEAR");
    pal_clr->changeCallback([this]() {
            isDropDown = false;
            mPalette = Palette::NONE;
        }
    );
    mContainer_dropdown.pack(pal_clr);

}

void MapEditor::setupCamera() {
    mCamera = { 0 };
    mCamera.zoom = 1.0f;
    mCamera.target = (Vector2D){0,0};
    mCamera.offset = (Vector2D){workspaceWidth/2, workspaceHeight/2};
}

void MapEditor::cameraHandle() {
    if (IsKeyDown(KEY_A)) camera.target.x -= 5;
    if (IsKeyDown(KEY_D)) camera.target.x += 5;
    if (IsKeyDown(KEY_W)) camera.target.y -= 5;
    if (IsKeyDown(KEY_S)) camera.target.y += 5;
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        camera.zoom += wheel * 0.1f;
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;
    }
    if (camera.target.x < 0) camera.target.x = 0;
    if (camera.target.x > workspaceWidth) camera.target.x = workspaceWidth;
    if (camera.target.y < 0) camera.target.y = 0;
    if (camera.target.y > workspaceHeight) camera.target.y = workspaceHeight;
}

void MapEditor::paletteHandle() {
    Vector2 mouse = getMousePosition();
    if (mMode == MapEditorMode::PEN || isShowPal && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        
        int tilesPerRow = getTilesPerRow();
        if (CheckCollisionPointRec(mouse, palRect)) {
            // Convert mouse to palette-local coordinates
            int localX = mouse.x - palRect.x;
            int localY = mouse.y - palRect.y;

            // Figure out which tile index was clicked
            int tX = localX / SCALED_TILE_SIZE;
            int tY = localY / SCALED_TILE_SIZE;
            selectedTile = {palRect.x+localX, palRect.y+localY, SCALED_TILE_SIZE, SCALED_TILE_SIZE};
            int index = tY * tilesPerRow + tX;
            if (mPalette == Palette::COINS) index += 23;
            else if (mPalette == Palette::FOLIAGE1) index += 8*tilesPerRow;
            else if (mPalette == Palette::FOLIAGE2) index += 20*tilesPerRow;
            if (index >= 0 && index < tileCount) {
                selected = index;
            }
        }
    }
}

void MapEditor::drawUI() {
    Texture2D bricksTexture = Resource::mTexture.get(TextureIdentifier::BRICKS_TEXTURE);
    DrawTexture(bricksTexture, 0, 760, WHITE);
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
            break;
        case MapEditorMode::ERASE:
            mContainer_erase.draw();
            break;
        case MapEditorMode::CONFIRM:
            mContainer_confirm.draw();
            break;
        case MapEditorMode::RENAME:
            mContainer_rename.draw();
            break;
    }
}

void MapEditor::drawMapPreview() {
    Texture2D brickTiles = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);
    Texture2D items = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);

    BeginScissorMode(0,0,workspaceWidth,workspaceHeight);
    BeginMode2D(mCamera);
    
    for (int y = 0; y < mMap.size(); ++y) {
        for (int x = 0; x < mMap[y].size(); ++x) {
            int tileID = mMap[y][x];
            if (tileID < 0) continue;

            int tx = tileID % 29;
            int ty = tileID / 29;
            Rectangle srcRect = { tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            Vector2 dest = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
            DrawTextureRec(brickTiles, srcRect, dest, WHITE);
        }
    }
    for (int y = 0; y < mItems.size(); ++y) {
        for (int x = 0; x < mItems[y].size(); ++x) {
            int tileID = mItems[y][x];
            if (tileID < 0) continue;

            int tx = tileID % 36;
            int ty = tileID / 36;
            Rectangle srcRect = { tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            Vector2 dest = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
            DrawTextureRec(items, srcRect, dest, WHITE);
        }
    }

    //ghost preview at cursor
    if (mMode == MapEditorMode::PEN && selected >= 0) {
        Texture2D tileset;
        if (mPalette != Palette::ITEMS) tileset = brickTiles;
        else tileset = items;
        int tx = selected % tilesPerRow;
        int ty = selected / tilesPerRow;
        Rectangle srcRect = { tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        Vector2 dest = { static_cast<float>(tileX * TILE_SIZE), static_cast<float>(tileY * TILE_SIZE) };
        DrawTextureRec(tileset, srcRect, dest, Fade(WHITE, 0.5f)); 
    }
    if (showGrid) drawGrid(workspaceWidth, workspaceHeight, TILE_SIZE);
    EndMode2D();
    EndScissorMode();
}
void MapEditor::drawPalette() {
    Texture2D pal = Resource::mTexture.get(TextureIdentifier::TILE_SET_ITEMS);;
    if (mPalette != Palette::ITEMS) pal = Resource::mTexture.get(TextureIdentifier::TILE_SET_BLOCKS);

    if (isShowPal) {
        Rectangle toDraw;
        Rectangle srcDraw;
        switch (mPalette) {
            case Palette::BLOCKS:
                toDraw = {337, 376, 1104, 384};
                srcDraw = {0, 0, 1104, 384};
                break;
            case Palette::FOLIAGE1:
                toDraw = {240, 184, 1200, 576};
                srcDraw = {0, 384, 1200, 576};
                break;
            case Palette::FOLIAGE2:
                toDraw = {912, 376, 528, 384};
                srcDraw = {0, 960, 528, 384};
                break;
            case Palette::COINS:
                toDraw = {1248, 376, 192, 384};
                srcDraw = {1104, 0, 192, 384};
                break;
            case Palette::ITEMS: {
                toDraw = {1200, 328, 240, 432};
                srcDraw = {0, 0, 240, 432};
                break;
            }
        }
        DrawRectangleRec(palRect, Fade({113, 67, 25}, 0.7f));
        DrawTexturePro(pal, srcDraw, toDraw, {0,0}, 0, WHITE);
        if (selected >= 0) DrawRectangleRec(selectedTile, Fade(YELLOW, 0.8f));
    }
}
void MapEditor::drawGrid(int width, int height, int tileSize, Color lineColor = Fade(GRAY, 0.5f)) {
    if (x % 10 == 0) lineColor = Fade(DARKGRAY, 0.8f);
    for (int y = 0; y <= height; y++) {
        DrawLine(0, y * tileSize, width * tileSize, y * tileSize, lineColor);
    }
    for (int x = 0; x <= width; x++) {
        DrawLine(x * tileSize, 0, x * tileSize, height * tileSize, lineColor);
    }
}
int MapEditor::getTilesPerRow() {
    if (mPalette != Palette::ITEMS) return 29;
    return 36;
}

void MapEditor::draw() {
    drawMapPreview();
    drawPalette();
    drawUI();    
}

bool MapEditor::update(float dt) {
    switch (mMode) {
        case MapEditorMode::VIEW:
            currentMode->changeText("VIEWING MODE");
            subtext->changeText("MAP NAME: ");
            break;
        case MapEditorMode::EDIT:
            currentMode->changeText("EDIT MODE");
            subtext->changeText("PRESS B TO EXIT EDIT MODE");
            break;
        case MapEditorMode::VIEW:
            currentMode->changeText("VIEWING MODE");
            subtext->changeText("MAP NAME: ");
            break;
        case MapEditorMode::PEN:
            if (mPalette == Palette::NONE) currentMode->changeText("EDIT MODE - PEN | PALETTE: NONE");
            else if (mPalette == Palette::BLOCKS) currentMode->changeText("EDIT MODE - PEN | PALETTE: BLOCKS");
            else if (mPalette == Palette::FOLIAGE1) currentMode->changeText("EDIT MODE - PEN | PALETTE: FOLIAGE1");
            else if (mPalette == Palette::FOLIAGE2) currentMode->changeText("EDIT MODE - PEN | PALETTE: FOLIAGE2");
            else if (mPalette == Palette::COINS) currentMode->changeText("EDIT MODE - PEN | PALETTE: COINS");
            else if (mPalette == Palette::ITEMS) currentMode->changeText("EDIT MODE - PEN | PALETTE: ITEMS");
            subtext->changeText("PRESS B TO EXIT PEN MODE");
            break;
    }

    if (!hasChanges) save->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
    else save->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
    
    switch (mPalette) {
        case Palette::BLOCKS:
            pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            display->changeText("");
            palRect = {337, 376, 1104, 384};
            break;
        case Palette::FOLIAGE1:
            pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            palRect = {240, 184, 1200, 576};
            break;
        case Palette::FOLIAGE2:
            pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            palRect = {912, 376, 528, 384};
            break;
        case Palette::COINS:
            pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            palRect = {1248, 376, 192, 384};
            break;
        case Palette::ITEMS:
            pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);
            palRect = {1200, 328, 240, 432};
            break;
        case Palette::NONE:
            display->changeTexture(TextureIdentifier::INACTIVE_BUTTON_MEDIUM);
            break;
    }
    if (isDropDown) pals->changeTexture(TextureIdentifier::HOVERED_BUTTON_MEDIUM);
    else pals->changeTexture(TextureIdentifier::ACTIVE_BUTTON_MEDIUM);

    if (isShowPal) display->changeText("HIDE");
    else display->changeText("DISPLAY");
    return false;
}


bool MapEditor::handle() {
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
            mContainer_confirm.handle();
            break;
        case MapEditorMode::RENAME:
            mContainer_rename.handle();
            break;
    }
    if (!isDropDown) {
        paletteHandle();
        stampingHandle();
    }

    if (mMode == MapEditorMode::PEN || mMode == MapEditorMode::ERASE && isKeyPressed(KEY_B)) mMode = MapEditorMode::EDIT;
    if (mMode == MapEditorMode::EDIT && isKeyPressed(KEY_B)) mMode = MapEditorMode::VIEW;
    return false;
}

void MapEditor::stampingHandle() {
    BeginScissorMode(0,0,workspaceWidth,workspaceHeight);
    BeginMode2D(mCamera);
    Vector2D mouse = GetScreenToWorld2D(GetMousePosition(), mCamera);
    cameraHandle();
    tileX = mouse.x / TILE_SIZE;
    tileY = mouse.y / TILE_SIZE;

    bool inBounds = tileX >= 0 && tileX < mMap[0].size() && tileY >= 0 && tileY < mMap.size();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds && mMode == MapEditorMode::PEN && !isDropDown) {
        if (mPalette != Palette::ITEMS || mPalette != Palette::COINS) mMap[tileY][tileX] = selectedTile;
        else mItems[tileY][tileX] = selectedTile;
        hasChanges = true;
    } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds && mMode == MapEditorMode::ERASE) {
        mMap[tileY][tileX] = -1;
        mItems[tileY][tileX] = -1;
        hasChanges = true;
    }
    EndMode2D();
    EndScissorMode();
}