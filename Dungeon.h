#ifndef DUNGEON_H
#define DUNGEON_H

#include <memory>
#include "LevelRoom.h"

constexpr int LEVEL_WIDTH = 10;
constexpr int LEVEL_HEIGHT = 10;

class Dungeon
{
private:
    std::unique_ptr<std::unique_ptr<LevelRoom[]>[]> rooms;

public:
    Dungeon();
    void InitLevelGrid();
    void DrawDungeon();

    LevelRoom* GetRoom(int x, int y) { return &rooms[x][y]; }
    static int GetLevelWidth() { return LEVEL_WIDTH; }
    static int GetLevelHeight() { return LEVEL_HEIGHT; }
};

#endif //DUNGEON_H
