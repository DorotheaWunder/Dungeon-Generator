#include "LevelRoom.h"
#include "Dungeon.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>


//------------------------------------------------------ grid generation
void Dungeon::InitLevelGrid()
{
    rooms.resize(LEVEL_WIDTH, std::vector<LevelRoom>(LEVEL_HEIGHT));

    for (int i = 0; i < LEVEL_WIDTH; i++)
    {
        for (int j = 0; j < LEVEL_HEIGHT; j++)
        {
            rooms[i][j] = LevelRoom(i, j);
            rooms[i][j].roomType = RoomType::NONE;
        }
    }
}

Dungeon::Dungeon()
: isGenerating(true), roomCounter(0)
{
    InitLevelGrid();
}

void Dungeon::DrawDungeon()
{
    for (int i = 0; i < LEVEL_WIDTH; i++)
    {
        for (int j = 0; j < LEVEL_HEIGHT; j++)
        {
            LevelRoom& room = rooms[i][j];
            Color roomColor = room.SetRoomColor();
            float roomSize = room.size;
            Rectangle roomRectangle = { i * roomSize, j * roomSize, roomSize, roomSize };

            DrawRectangleRec(roomRectangle, roomColor);
            DrawRectangleLinesEx(roomRectangle, 2.0f, DARKGRAY);
        }
    }
}

//------------------------------------------------------ room/level generation

std::vector<std::pair<int, int>>
Dungeon::GetNeighborTile(int x, int y)
{
    std::vector<std::pair<int, int>> neighbors;

    if (x > 0) neighbors.push_back({x - 1, y});
    if (x < LEVEL_WIDTH - 1) neighbors.push_back({x + 1, y});
    if (y > 0) neighbors.push_back({x, y - 1});
    if (y < LEVEL_HEIGHT - 1) neighbors.push_back({x, y + 1});

    return neighbors;
}

void Dungeon::MarkAsVisited(int x, int y)
{
    rooms[x][y].roomType = RoomType::ROOM;
}

std::pair<int, int> Dungeon::GetRandomNeighbor(std::vector<std::pair<int, int>>& neighbors)
{
    if (neighbors.empty()) return {-1,-1};

    int randomIndex = rand() % neighbors.size();
    return neighbors[randomIndex];
}


void Dungeon::ResetAlgorithm()
{
    InitLevelGrid();
    frontier.clear();
    isGenerating = true;
    currentX = rand() % LEVEL_WIDTH;
    currentY = rand() % LEVEL_HEIGHT;
    MarkAsVisited(currentX, currentY);
    frontier.push_back({currentX, currentY});
}


void Dungeon::StepPrimAlgorithm()
{
    if (!isGenerating || frontier.empty()) return;

    int randIndex = rand() % frontier.size();
    std::pair<int, int> currentTile = frontier[randIndex];
    frontier.erase(frontier.begin() + randIndex);

    int x = currentTile.first;
    int y = currentTile.second;

    if (roomCounter == 0)
    {
        rooms[x][y].roomType = RoomType::ENTRY;
    }
    else
    {
        rooms[x][y].roomType = RoomType::ROOM;
    }

    //MarkAsVisited(x, y);
    roomCounter++;

    std::vector<std::pair<int, int>> neighbors = GetNeighborTile(x, y);

    for (auto& neighbor : neighbors)
    {
        int neighborX = neighbor.first;
        int neighborY = neighbor.second;

        if (rooms[neighborX][neighborY].roomType == RoomType::NONE)
        {
            rooms[neighborX][neighborY].roomType = RoomType::FRONTIER;
            frontier.push_back(neighbor);
        }

        if (frontier.empty())
        {
            isGenerating = false;
            rooms[x][y].roomType = RoomType::EXIT;
        }
    }
}







