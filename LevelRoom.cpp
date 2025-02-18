#include "LevelRoom.h"
#include "raylib.h"
#include <iostream>
#include <stdlib.h>

LevelRoom::LevelRoom()
    :x(0), y(0), size(60.0f), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f) {}

LevelRoom::LevelRoom(int posX, int posY)
    :x(posX), y(posY), size(60.0f), roomType(RoomType::NORMAL),
roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f) {}

Color LevelRoom::SetRoomColor() const
{
    switch (roomType)
    {
        case RoomType::NORMAL:
            return GRAY;
        case RoomType::COMBAT:
            return RED;
        case RoomType::TREASURE:
            return GOLD;
        case RoomType::ENTRY:
            return PURPLE;
        case RoomType::EXIT:
            return PURPLE;
        case RoomType::NONE:
        default:
            return BLACK;
    }
}
