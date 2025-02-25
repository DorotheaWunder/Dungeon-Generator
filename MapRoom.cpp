#include <memory>
#include <stdlib.h>
#include "maproom.h"
#include "LevelTile.h"

MapRoom::MapRoom()
    :x(0), y(0), size(10.0f), roomType(TileType::ROOM),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f),
hasPlayer(0), wasVisited(0) {}

MapRoom::MapRoom(int posX, int posY)
    :x(posX), y(posY), roomType(TileType::ROOM),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f),
hasPlayer(0), wasVisited(0) {}
