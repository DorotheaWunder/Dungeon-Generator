#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <stdlib.h>
#include <vector>
#include "raylib.h"

enum class TileType
{
    ROOM,
    WALL,
    BOSS,
    FRONTIER,
    ANCHOR,
    COMBAT,
    TREASURE,
    TRAP,
    ENTRY,
    EXIT,
    NONE
};

struct TileProbability
{
    TileType type;
    float probability;
};

class LevelTile
{
public:
    int x,y;
    float size;
    TileType roomType;
    Color roomColor;
    Color outlineColor;
    float outlineWidth;

    LevelTile();
    LevelTile(int posX, int posY);

    int GetX() const { return x; }
    int GetY() const { return y; }
    Color GetOutlineColor() const { return outlineColor; }
    float GetOutlineWidth() const { return outlineWidth; }
    TileType GetRoomType() const { return roomType; }
    Color SetTileColor() const;
    std::vector<TileProbability> roomProbabilities;
    void InitRoomProbabilities();
};

#endif //ROOM_H
