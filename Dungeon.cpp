#include "LevelTile.h"
#include "Dungeon.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>


//------------------------------------------------------ grid generation
void Dungeon::InitLevelGrid()
{
    rooms.resize(LEVEL_WIDTH, std::vector<LevelTile>(LEVEL_HEIGHT));

    for (int i = 0; i < LEVEL_WIDTH; i++)
    {
        for (int j = 0; j < LEVEL_HEIGHT; j++)
        {
            rooms[i][j] = LevelTile(i, j);
            rooms[i][j].roomType = TileType::NONE;
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
            LevelTile& room = rooms[i][j];
            Color roomColor = room.SetTileColor();
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
    int minDistance = 2;
    int maxDistance = 2;

    int stepX = minDistance + (rand() % (maxDistance - minDistance + 1));
    int stepY = minDistance + (rand() % (maxDistance - minDistance + 1));


    if (x > stepX)
    {
        if (rooms[x-stepX][y].roomType == TileType::NONE)
        {
            neighbors.push_back({x - stepX, y});
        }
    }

    if (x < LEVEL_WIDTH - stepX - 1)
    {
        if (rooms[x+stepX][y].roomType == TileType::NONE)
        {
            neighbors.push_back({x + stepX, y});
        }
    }

    if (y > stepY)
    {
        if (rooms[x][y-stepY].roomType == TileType::NONE)
        {
            neighbors.push_back({x, y - stepY});
        }
    }

    if (y < LEVEL_HEIGHT - stepY - 1)
    {
        if (rooms[x][y+stepY].roomType == TileType::NONE)
        {
            neighbors.push_back({x, y + stepY});
        }
    }
    return neighbors;
}

void Dungeon::MarkAsVisited(int x, int y)
{
    rooms[x][y].roomType = TileType::ROOM;
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

TileType Dungeon::DistributeRoomTypes()
{
    std::vector<TileProbability> roomProbabilities;

    if (roomProbabilities.empty())
    {
        switch (difficulty)
        {
        case 1:
            roomProbabilities =
                {
                    {TileType::COMBAT, 0.10f},
                    {TileType::TREASURE, 0.20f},
                    {TileType::TRAP, 0.10f},
                    {TileType::ROOM, 0.60f},
                    {TileType::BOSS, 0.00f},
                };
            break;
        case 2:
            roomProbabilities =
                {
                    {TileType::COMBAT, 0.30f},
                    {TileType::TREASURE, 0.20f},
                    {TileType::TRAP, 0.20f},
                    {TileType::ROOM, 0.60f},
                    {TileType::BOSS, 0.00f},
                };
            break;
        case 3:
            roomProbabilities =
                {
                    {TileType::COMBAT, 0.40f},
                    {TileType::TREASURE, 0.20f},
                    {TileType::TRAP, 0.300f},
                    {TileType::ROOM, 0.50f},
                    {TileType::BOSS, 0.10f},
                };
            break;
        case 4:
            roomProbabilities =
                {
                    {TileType::COMBAT, 0.50f},
                    {TileType::TREASURE, 0.20f},
                    {TileType::TRAP, 0.50f},
                    {TileType::ROOM, 0.40f},
                    {TileType::BOSS, 0.30f},
                };
            break;
        case 5:
            roomProbabilities =
                {
                    {TileType::COMBAT, 0.60f},
                    {TileType::TREASURE, 0.20f},
                    {TileType::TRAP, 0.60f},
                    {TileType::ROOM, 0.30f},
                    {TileType::BOSS, 1.00f},
                };
            break;
        default:
            roomProbabilities = {
            {TileType::ROOM, 1.0f}
            };
            break;
        }
    }

    float roll = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float cumulativeProbability = 0.0f;

    for (const auto& prob : roomProbabilities)
    {
        cumulativeProbability += prob.probability;
        if (roll <= cumulativeProbability)
        {
            return prob.type;
        }
    }

    return TileType::ROOM;
}

void Dungeon::SetRoomType(int x, int y) //add other room types -> switch statement?? with set exit method? combine??
{
    if (roomCounter == 0)
    {
        rooms[x][y].roomType = TileType::ENTRY;
    }
    else
    {
        //call distribute room types method
        rooms[x][y].roomType = TileType::ROOM;
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

        if (rooms[neighborX][neighborY].roomType == TileType::NONE)
        {
            rooms[neighborX][neighborY].roomType = TileType::FRONTIER;
            frontier.push_back(neighbor);

            int wallX = (x + neighborX) / 2;
            int wallY = (y + neighborY) / 2;
            rooms[wallX][wallY].roomType = TileType::ROOM;
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
                rooms[newX][newY].roomType == TileType::NONE)
            {
                rooms[newX][newY].roomType = TileType::WALL;
            }
        }
    }
}

void Dungeon::PlaceExit()
{
    std::vector<std::pair<int, int>> roomTiles;
    bool exitPlaced = false;

    for (int i = 0; i < LEVEL_WIDTH && !exitPlaced; i++)
    {
        for (int j = 0; j < LEVEL_HEIGHT && !exitPlaced; j++)
        {
            if (rooms[i][j].roomType == TileType::ROOM)
            {
                roomTiles.push_back({i, j});
                // rooms[i][j].roomType = RoomType::EXIT;
                // exitPlaced = true;
                // return;
            }
        }
    }

    if (!roomTiles.empty())
    {
        int randIndex = rand() % roomTiles.size();
        auto [exitX, exitY] = roomTiles[randIndex];

        rooms[exitX][exitY].roomType = TileType::EXIT;
    }
}

//------------------------------------------------------ corridor generation
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
    anchors.clear();
    InitLevelGrid();
    frontier.clear();
    isGenerating = true;
    roomCounter = 0;
    currentX = (rand() % (LEVEL_WIDTH/2)) * 2;
    currentY = (rand() % (LEVEL_HEIGHT/2)) * 2;
    MarkAsVisited(currentX, currentY);
    frontier.push_back({currentX, currentY});
}

//------------------------------------------------------ rooms
Anchor::Anchor(int x, int y) : x(x), y(y) {}

std::pair<int, int> SetAnchorNumber(int difficulty)
{
    switch (difficulty)
    {
        case 1: return {2, 5};
        case 2: return {5, 8};
        case 3: return {7, 10};
        case 4: return {10, 13};
        case 5: return {17, 20};
    }
}

int CalculateSquareDistance(const Anchor& a1, const Anchor& a2)
{
    return std::pow(a2.x - a1.x, 2) + std::pow(a2.y - a1.y, 2);
}

bool Dungeon::HasEnoughSpace(int x, int y, int minDistance, int maxDistance)
{
    for (const auto& anchor : anchors)
    {
        int distanceSqr = CalculateSquareDistance({x, y}, anchor);

        if (distanceSqr < minDistance * minDistance)
        {
            return false;
        }
        if (distanceSqr > maxDistance * maxDistance)
        {
            return false;
        }
    }
    return true;
}

void Dungeon::RandomAnchorPoint(int numAnchors, int minDistance, int maxDistance)
{
    int maxAttempts = 500;

    for (int i = 0; i < numAnchors; i++)
    {
        int anchorX, anchorY;
        bool validPlacement = false;
        int attempts = 0;

        while (!validPlacement && attempts < maxAttempts)
        {
            attempts++;
            anchorX = rand() % LEVEL_WIDTH;
            anchorY = rand() % LEVEL_HEIGHT;

            if (HasEnoughSpace(anchorX, anchorY, minDistance, maxDistance))
            {
                validPlacement = true;
            }
        }

        if (validPlacement)
        {
            rooms[anchorX][anchorY].roomType = TileType::ANCHOR;
            anchors.push_back(Anchor(anchorX,anchorY));
        }
        else
        {
            break;
        }
    }
}

void Dungeon::CreateOutlineTiles(int anchorX, int anchorY)
{
    int roomWidth = 2 + rand() % 3;
    int roomHeight = 2 + rand() % 3;

    int startX = std::max(0, anchorX - roomWidth/ 2);
    int endX = std::min(LEVEL_WIDTH - 1, startX + roomWidth);
    int startY = std::max(0, anchorY - roomWidth/ 2);
    int endY = std::min(LEVEL_HEIGHT - 1, startY + roomHeight);

    TileType roomType = DistributeRoomTypes();

    for (int x =  startX; x <= endX; x++)
    {
        for (int y = startY; y <= endY; y++)
        {
            if (rooms[x][y].roomType != TileType::ENTRY &&
                rooms[x][y].roomType != TileType::EXIT)
            {
                rooms[x][y].roomType = roomType;
            }
        }
    }
}

void Dungeon::CreateRooms()
{
    for (const auto& anchor : anchors)
    {
        CreateOutlineTiles(anchor.x, anchor.y);
    }
}

//------------------------------------------------------ Complete DUNGEON

void Dungeon::GenerateDungeon()
{
    ResetAlgorithm();

    while (isGenerating)
    {
        StepPrimAlgorithm();
    }

    auto anchorRange = SetAnchorNumber(difficulty);
    const int numAnchors = anchorRange.first + (rand() % (anchorRange.second - anchorRange.first + 1));

    const int minDistance = 5;
    const int maxDistance = 30;

    RandomAnchorPoint(numAnchors, minDistance, maxDistance);
    CreateRooms();

    difficulty = (difficulty % 5) + 1;
}