#include "LevelTile.h"
#include "raylib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

LevelTile::LevelTile()
    :x(0), y(0), size(20.0f), roomType(TileType::ROOM),
roomColor(GRAY), outlineColor(BLACK), outlineWidth(0.1f) {}

LevelTile::LevelTile(int posX, int posY)
    :x(posX), y(posY), size(20.0f), roomType(TileType::ROOM),
roomColor(GRAY), outlineColor(BLACK), outlineWidth(0.1f) {}

Color LevelTile::SetTileColor() const
{
    switch (roomType)
    {
        case TileType::ROOM:
            return GRAY;
        case TileType::WALL:
            return BLACK;
        case TileType::CORRIDOR:
            return DARKGRAY;
        case TileType::FRONTIER:
            return SKYBLUE;
        case TileType::ANCHOR:
            return GREEN;
        case TileType::COMBAT:
            return RED;
        case TileType::TREASURE:
            return GOLD;
        case TileType::TRAP:
            return BROWN;
        case TileType::ENTRY:
            return PURPLE;
        case TileType::EXIT:
            return PURPLE;
        case TileType::NONE:
        default:
            return BLACK;
    }
}
