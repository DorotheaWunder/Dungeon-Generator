#include "LevelRoom.h"
#include "raylib.h"
#include <iostream>
#include <stdlib.h>

LevelRoom::LevelRoom()
    :x(0), y(0), size(10), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f) {}

LevelRoom::LevelRoom(int posX, int posY)
    :x(posX), y(posY), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f) {}
