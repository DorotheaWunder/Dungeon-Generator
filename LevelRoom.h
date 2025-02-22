#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <stdlib.h>
#include <vector>
#include "raylib.h"

enum class RoomType
{
    ROOM,
    WALL,
    VISITED,
    FRONTIER,
    COMBAT,
    TREASURE,
    TRAP,
    ENTRY,
    EXIT,
    NONE
};

struct RoomProbability
{
    RoomType type;
    float probability;
};

class LevelRoom
{
public:
    int x,y;
    float size;
    RoomType roomType;
    Color roomColor;
    Color outlineColor;
    float outlineWidth;

    LevelRoom();
    LevelRoom(int posX, int posY);

    int GetX() const { return x; }
    int GetY() const { return y; }
    Color GetOutlineColor() const { return outlineColor; }
    float GetOutlineWidth() const { return outlineWidth; }
    RoomType GetRoomType() const { return roomType; }
    Color SetRoomColor() const;
    std::vector<RoomProbability> roomProbabilities;
    void InitRoomProbabilities();
};

#endif //ROOM_H
