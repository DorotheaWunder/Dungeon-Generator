#ifndef MAPROOM_H
#define MAPROOM_H

#include <memory.h>
#include "levelroom.h"

class MapRoom
{
public:
    int x,y;
    float size;
    RoomType roomType;
    Color roomColor;
    Color outlineColor;
    float outlineWidth;
    int hasPlayer;
    int wasVisited;

    MapRoom();
    MapRoom(int posX, int posY);

    int GetX() const { return x; }
    int GetY() const { return y; }
    RoomType GetRoomType() const { return roomType; }
    Color GetRoomColor() const { return roomColor; }
    Color GetOutlineColor() const { return outlineColor; }
    float GetOutlineWidth() const { return outlineWidth; }
    int HasPlayer() const { return hasPlayer; }
    int WasVisited() const { return wasVisited; }
};

#endif //MAPROOM_H
