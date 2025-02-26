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
            return DARKGRAY;
        case TileType::WALL:
            return BLACK;
        case TileType::BOSS:
            return RED;
        case TileType::FRONTIER:
            return SKYBLUE;
        case TileType::ANCHOR:
            return GREEN;
        case TileType::COMBAT:
            return (Color){ 138, 53, 53, 255 };
        case TileType::TREASURE:
            return (Color){ 144, 122, 50, 255 };
        case TileType::TRAP:
            return (Color){ 121, 85, 54, 255 };
        case TileType::ENTRY:
            return GRAY;
        case TileType::EXIT:
            return WHITE;
        case TileType::NONE:
        default:
            return BLACK;
    }
}
