#pragma once

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
    FOLIAGE1, FOLIAGE2,
    ITEMS,
    ENEMIES
};

enum class EnemyType {
    GOOMBA,
    GOOMBA_BLUE,
    KOOPA_GREEN,
    KOOPA_RED,
    KOOPA_BLUE,
    PIRANHA_GREEN,
    PIRANHA_BLUE,
    BOWSER,
    FIRE,
    NONE
};

const int TILES_PER_ROW_BLOCKS = 29;
const int TILES_PER_ROW_ITEMS = 36; 
const int TILES_PER_ROW_ENEMIES = 18;

const int DEFAULT_MAP_HEIGHT = 19;
const int DEFAULT_MAP_WIDTH = 90;

const int TILE_SIZE = 16;
const int SCALED_TILE_SIZE = 48;

const int workspaceWidth = 1440;
const int workspaceHeight = 762; 