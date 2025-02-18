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
    rooms = std::make_unique<std::unique_ptr<LevelRoom[]>[]>(LEVEL_WIDTH);

    for (int i = 0; i < LEVEL_WIDTH; i++)
    {
        rooms[i] = std::make_unique<LevelRoom[]>(LEVEL_HEIGHT);
        for (int j = 0; j < LEVEL_HEIGHT; j++)
        {
            rooms[i][j] = LevelRoom(i, j);
            rooms[i][j].roomType = RoomType::NONE;
        }
    }
}

Dungeon::Dungeon()
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
    rooms[x][y].roomType = RoomType::NORMAL;
}

std::pair<int, int> Dungeon::GetRandomNeighbor(std::vector<std::pair<int, int>>& neighbors)
{
    if (neighbors.empty()) return {-1,-1};

    int randomIndex = rand() % neighbors.size();
    return neighbors[randomIndex];
}

void Dungeon::PrimAlgorithm()
{
    int currentX = rand() % LEVEL_WIDTH;
    int currentY = rand() % LEVEL_HEIGHT;

    MarkAsVisited(currentX, currentY);

    std::vector<std::pair<int, int>> tilesToCheck;
    tilesToCheck.push_back({currentX, currentY});

    while (!tilesToCheck.empty())
    {
        int randIndex = rand() % tilesToCheck.size();
        std::pair<int, int> currentTile = tilesToCheck[randIndex];
        tilesToCheck.erase(tilesToCheck.begin() + randIndex);

        int x = currentTile.first;
        int y = currentTile.second;

        std::vector<std::pair<int, int>> neighbors = GetNeighborTile(x, y);

        for (auto& neighbor : neighbors)
        {
            int neighborX = neighbor.first;
            int neighborY = neighbor.second;

            if (rooms[neighborY][neighborY].roomType == RoomType::NONE)
            {
                MarkAsVisited(neighborX, neighborY);
                tilesToCheck.push_back(neighbor);
            }
        }

        std::pair<int, int> nextRoom = GetRandomNeighbor(tilesToCheck);
        if (nextRoom.first != -1 && nextRoom.second != -1)
        {
            currentX = nextRoom.first;
            currentY = nextRoom.second;
        }
    }
}




void Dungeon::GenerateLevelLayout()
{
    int roomsCreated = 0;
    int maxRooms = 10;

    while (roomsCreated < maxRooms)
    {
        PrimAlgorithm();
        roomsCreated++;
    }
}


//do method to check if tile has been visited; also method for random selection