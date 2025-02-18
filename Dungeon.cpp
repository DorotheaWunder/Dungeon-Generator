#include "LevelRoom.h"
#include "Dungeon.h"
#include "raylib.h"
#include <iostream>
#include <stdlib.h>

void Dungeon::InitLevelGrid()
{
    rooms = std::make_unique<std::unique_ptr<LevelRoom[]>[]>(LEVEL_WIDTH);

    for (int i = 0; i < LEVEL_WIDTH; i++)
    {
        rooms[i] = std::make_unique<LevelRoom[]>(LEVEL_HEIGHT);
        for (int j = 0; j < LEVEL_HEIGHT; j++)
        {
            rooms[i][j] = LevelRoom(i, j);
        }
    }
}

Dungeon::Dungeon()
{
    InitLevelGrid();
}

void Dungeon::DrawDungeon()
{

}