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
            DrawRectangleLinesEx(roomRectangle, 0.5f, BLACK);
        }
    }
}

//------------------------------------------------------ helper functions

std::vector<std::pair<int, int>>
Dungeon::GetNeighborTile(int x, int y)
{
    std::vector<std::pair<int, int>> neighbors;

    if (x > 1)
    {
        if (rooms[x-2][y].roomType == RoomType::NONE)
        {
            neighbors.push_back({x - 2, y});
        }
    }

    if (x < LEVEL_WIDTH - 2)
    {
        if (rooms[x+2][y].roomType == RoomType::NONE)
        {
            neighbors.push_back({x + 2, y});
        }
    }

    if (y > 1)
    {
        if (rooms[x][y-2].roomType == RoomType::NONE)
        {
            neighbors.push_back({x, y - 2});
        }
    }

    if (y < LEVEL_HEIGHT - 2)
    {
        if (rooms[x][y+2].roomType == RoomType::NONE)
        {
            neighbors.push_back({x, y + 2});
        }
    }
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

bool Dungeon::IsValidCell(int x, int y) const
{
    return x >= 0 && x < LEVEL_WIDTH && y >= 0 && y < LEVEL_HEIGHT;
}

void Dungeon::SetRoomType(int x, int y) //add other room types
{
    if (roomCounter == 0)
    {
        rooms[x][y].roomType = RoomType::ENTRY;
    }
    else
    {
        rooms[x][y].roomType = RoomType::ROOM;
    }
    roomCounter++;
}

void Dungeon::ProcessNeighbors(int x, int y)
{
    auto neighbors = GetNeighborTile(x, y);

    for (auto& neighbor : neighbors)
    {
        int neighborX = neighbor.first;
        int neighborY = neighbor.second;

        if (rooms[neighborX][neighborY].roomType == RoomType::NONE)
        {
            rooms[neighborX][neighborY].roomType = RoomType::FRONTIER;
            frontier.push_back(neighbor);

            int wallX = (x + neighborX) / 2;
            int wallY = (y + neighborY) / 2;
            rooms[wallX][wallY].roomType = RoomType::ROOM;
        }
    }
}

void Dungeon::FillWalls(int x, int y)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int newX = x + dx;
            int newY = y + dy;

            if (IsValidCell(newX, newY) &&
                rooms[newX][newY].roomType == RoomType::NONE)
            {
                rooms[newX][newY].roomType = RoomType::WALL;
            }
        }
    }
}

void Dungeon::PlaceExit()
{
    bool exitPlaced = false;
    std::cout << "Placing exit...\n";

    for (int i = LEVEL_WIDTH-1; i >= 0 && !exitPlaced; i--)
    {
        for (int j = LEVEL_HEIGHT-1; j >= 0 && !exitPlaced; j--)
        {
            if (rooms[i][j].roomType == RoomType::ROOM)
            {
                std::cout << "Exit placed at: " << i << ", " << j << std::endl;
                rooms[i][j].roomType = RoomType::EXIT;
                exitPlaced = true;
                return;
            }
        }
    }
}

//------------------------------------------------------ room/level generation
void Dungeon::StepPrimAlgorithm()
{
    if (!isGenerating || frontier.empty())
    {
        if (frontier.empty() && isGenerating)
        {
            isGenerating = false;
            PlaceExit();
        }
        return;
    }

    int randIndex = rand() % frontier.size();
    std::pair<int, int> currentTile = frontier[randIndex];
    frontier.erase(frontier.begin() + randIndex);

    int x = currentTile.first;
    int y = currentTile.second;

    SetRoomType(x, y);

    ProcessNeighbors(x, y);

    FillWalls(x, y);
}

void Dungeon::ResetAlgorithm()
{
    InitLevelGrid();
    frontier.clear();
    isGenerating = true;
    roomCounter = 0;
    currentX = (rand() % (LEVEL_WIDTH/2)) * 2;
    currentY = (rand() % (LEVEL_HEIGHT/2)) * 2;
    MarkAsVisited(currentX, currentY);
    frontier.push_back({currentX, currentY});
}