#ifndef ROOM_H
#define ROOM_H

typedef enum RoomType
{
    NORMAL,
    COMBAT,
    TREASURE,
    ENTRY,
    EXIT
} RoomType;




typedef struct LevelRoom
{
    int x,y;
    int size;
    RoomType roomType;
    Color roomColor;

} LevelRoom;

typedef struct MapRoom
{
    int x,y;
    int size;
    RoomType roomType;
    Color roomColor;

    int hasPlayer;
    int wasVisited;

} MapRoom;


#endif //ROOM_H
