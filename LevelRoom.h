#ifndef ROOM_H
#define ROOM_H
#include <stdlib.h>
#include "raylib.h"

enum class RoomType
{
    NORMAL,
    COMBAT,
    TREASURE,
    ENTRY,
    EXIT
};

class LevelRoom
{
public:
    int x,y;
    int size;
    RoomType roomType;
    Color roomColor;
    Color outlineColor;
    float outlineWidth;

    LevelRoom(int posX, int posY)
        : x(posX), y(posY), size(10), roomType(RoomType::NORMAL),
        roomColor(GRAY), outlineColor(DARKGRAY), outlineWidth(0.2f) {}
};

class MapRoom
{
public:
    int x,y;
    int size;
    RoomType roomType;
    Color roomColor;
    Color outlineColor;
    float outlineWidth;
    int hasPlayer;
    int wasVisited;

    MapRoom(int posX, int posY)
        : x(posX), y(posY),size(3), roomType(RoomType::NORMAL),
    roomColor(GRAY), outlineColor(BLACK), outlineWidth(0.1f),
    hasPlayer(0), wasVisited(0) {}
};


class Dungeon
{
public:
    static const int LEVEL_WIDTH = 20;
    static const int LEVEL_HEIGHT = 20;
    LevelRoom* rooms[LEVEL_WIDTH][LEVEL_HEIGHT];

    Dungeon()
    {
        for (int i = 0; i < LEVEL_WIDTH; i++)
        {
            for (int j = 0; j < LEVEL_HEIGHT; j++)
            {
                rooms[i][j] = new LevelRoom(i, j);
            }
        }
    }

    ~Dungeon()
    {
        for (int i = 0; i < LEVEL_WIDTH; i++)
        {
            for (int j = 0; j < LEVEL_HEIGHT; j++)
            {
                delete rooms[i][j];
            }
        }
    }
};



#endif //ROOM_H
