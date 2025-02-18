#include <memory>
#include <stdlib.h>
#include "maproom.h"
#include "levelroom.h"

MapRoom::MapRoom()
    :x(0), y(0), size(10.0f), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f),
hasPlayer(0), wasVisited(0) {}

MapRoom::MapRoom(int posX, int posY)
    :x(posX), y(posY), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f),
hasPlayer(0), wasVisited(0) {}
